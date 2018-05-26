#include "ostraps.h"
#include "dlxos.h"
#include "process.h"
#include "dfs.h"
#include "files.h"
#include "synch.h"

// You have already been told about the most likely places where you should use locks. You may use 
// additional locks if it is really necessary.

// STUDENT: put your file-level functions here

static file_descriptor f_d[FILE_MAX_OPEN_FILES];
static lock_t f_lock;


void FileInit(){
	int i;
	f_lock = LockCreate();
	for(i=0;i<FILE_MAX_OPEN_FILES;i++){
		f_d[i].inuse=0;
		bzero(f_d[i].filename,FILE_MAX_FILENAME_LENGTH);
		f_d[i].inode=0;
		f_d[i].mode=0;
	}
}


int FileOpen(char *filename, char *mode){
	int i;
	int m;
	int inode_handle;
	int file_handle;
	if(mode[0]=='r' && mode[1]=='w'){
		m = F_MODE_RW;
	}
	if(mode[0]=='r' && mode[1]!='w'){
		m = F_MODE_READ;
	}
	if(mode[0]=='w'){
		m = F_MODE_WRITE;
	}
	inode_handle = DfsInodeFilenameExists(filename);
	
	if(inode_handle==DFS_FAIL && m==F_MODE_READ){
		printf("FileOpen() try to read a file that does not exists!\n");
		return FILE_FAIL;
	}
	
	
	LockHandleAcquire(f_lock);
	//check if this file is already opened
	for(i=0;i<FILE_MAX_OPEN_FILES;i++){
		if(f_d[i].inuse==1){
			if(f_d[i].inode==inode_handle){
				printf("FileOpen() file(inode %d) is already opened!\n", inode_handle);
				LockHandleRelease(f_lock);
				return FILE_FAIL;
			}
		}
	}
	//find an available f_d
	for(i=0;i<FILE_MAX_OPEN_FILES;i++){
		if(f_d[i].inuse==0){
			file_handle=i;
			break;
		}
	}
	//update the available file descriptor
	dstrncpy(f_d[file_handle].filename, filename, FILE_MAX_FILENAME_LENGTH);
	if(inode_handle!=DFS_FAIL){
		f_d[file_handle].inode = inode_handle;
	}else{
		//file does not exist, create one
		f_d[file_handle].inode = DfsInodeOpen(filename);
	}
	f_d[file_handle].curr_byte=0;
	f_d[file_handle].mode=m;
	f_d[file_handle].inuse=1;
	LockHandleRelease(f_lock);
	
	//printf("FileOpen() inode=%d\n",f_d[file_handle].inode);
	
	return file_handle;

}
int FileClose(int handle){
	if(f_d[handle].inuse==0){
		printf("file_descriptor[%d] is not inuse!\n",handle);
		return FILE_FAIL;
	}
	//update file descriptor
	LockHandleAcquire(f_lock);
	f_d[handle].inuse=0;
	bzero(f_d[handle].filename,FILE_MAX_FILENAME_LENGTH);
	LockHandleRelease(f_lock);
	return FILE_SUCCESS;

}
int FileRead(int handle, void *mem, int num_bytes){
	int byte_read=0;
	int file_size;
	if(f_d[handle].inuse==0){
		printf("FileRead() file_descriptor[%d] is not inuse!\n",handle);
		return FILE_FAIL;
	}
	if((f_d[handle].mode&F_MODE_READ)!=1){
		printf("FileRead() file_descriptor[%d].mode is not READ!\n",handle);
		return FILE_FAIL;
	}
	//printf("f_d[%d].curr_byte=%d\n",handle,f_d[handle].curr_byte);
	
	file_size = DfsInodeFilesize(f_d[handle].inode);
	//only read bytes in scope if curr_byte+num_bytes beyond file size
	if(f_d[handle].curr_byte+num_bytes >= file_size){
		num_bytes = file_size - f_d[handle].curr_byte;
	}
	byte_read = DfsInodeReadBytes(f_d[handle].inode, mem, f_d[handle].curr_byte, num_bytes);
	
	f_d[handle].curr_byte =f_d[handle].curr_byte + byte_read;
	//printf("f_d[%d].curr_byte=%d\n",handle,f_d[handle].curr_byte);
	
	//printf("file_size is %d\n",file_size);
	if(f_d[handle].curr_byte >= file_size){
		f_d[handle].mode = f_d[handle].mode | F_MODE_EOF;
		//printf("in EOF file_size is %d\n",file_size);
		//printf("readed data: %s\n",mem);
		//return FILE_EOF;
	}
	
	//printf("f_d[%d].curr_byte=%d\n",handle,f_d[handle].curr_byte);
	
	return byte_read;

}
int FileWrite(int handle, void *mem, int num_bytes){
	int byte_write;
	if(f_d[handle].inuse==0){
		printf("FileWrite() file_descriptor[%d] is not inuse!\n",handle);
		return FILE_FAIL;
	}
	if((f_d[handle].mode&F_MODE_WRITE)!=2){
		printf("FileWrite() file_descriptor[%d].mode is not WRITE!\n",handle);
		return FILE_FAIL;
	}
	
	//printf("f_d[%d].curr_byte=%d\n",handle,f_d[handle].curr_byte);
	byte_write = DfsInodeWriteBytes(f_d[handle].inode,mem,f_d[handle].curr_byte,num_bytes);
	f_d[handle].curr_byte += byte_write;
	//printf("f_d[%d].curr_byte=%d\n",handle,f_d[handle].curr_byte);
	return byte_write;

}
int FileSeek(int handle, int num_bytes, int from_where){
	uint32 mask = 0xFFFF;
	
	if(f_d[handle].inuse==0){
		printf("FileSeek() file_descriptor[%d] is not inuse!\n",handle);
		return FILE_FAIL;
	}
	switch(from_where){
		case FILE_SEEK_SET:
			f_d[handle].curr_byte=num_bytes;
			break;
		case FILE_SEEK_END:
			f_d[handle].curr_byte=num_bytes + DfsInodeFilesize(f_d[handle].inode);
			break;
		case FILE_SEEK_CUR:
			f_d[handle].curr_byte=num_bytes + f_d[handle].curr_byte;
			break;
		default:
			printf("FileSeek() got into default\n");
			break;
	}
	//clear EOF bit
	f_d[handle].mode = f_d[handle].mode & (F_MODE_EOF^mask);
	return FILE_SUCCESS;
	
}
int FileDelete(char *filename){
	int inode_handle;
	//get inode
	inode_handle = DfsInodeFilenameExists(filename);
	//printf("inode is %d\n",inode_handle);
	if(inode_handle==DFS_FAIL) return FILE_FAIL;
	DfsInodeDelete(inode_handle);
	return FILE_SUCCESS;
}
