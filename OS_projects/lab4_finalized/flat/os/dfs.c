#include "ostraps.h"
#include "dlxos.h"
#include "traps.h"
#include "queue.h"
#include "disk.h"
#include "dfs.h"
#include "synch.h"

static dfs_inode inodes[DFS_NUM_INODES]; // all inodes
static dfs_superblock sb; // superblock
static uint32 fbv[DFS_FBV_MAX_NUM_WORDS]; // Free block vector
static lock_t lock_fbv;
static lock_t lock_inode;

static uint32 negativeone = 0xFFFFFFFF;
static inline uint32 invert(uint32 n) { return n ^ negativeone; }

// You have already been told about the most likely places where you should use locks. You may use 
// additional locks if it is really necessary.

// STUDENT: put your file system level functions below.
// Some skeletons are provided. You can implement additional functions.

uint32 FindFreeBlock(){
	int i;
	uint32 ret;
	uint32 bit;
	for(i=0;i<sb.fbv_num_words;i++){
		if(fbv[i]!=0) break;
	}
	ret = fbv[i];
	bit=0;
	while((ret&(1<<bit))==0){
		bit++;
	}
	fbv[i] = fbv[i]&(invert(1<<bit));
	ret = i*32 + bit;
	return ret;
}


///////////////////////////////////////////////////////////////////
// Non-inode functions first
///////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------
// DfsModuleInit is called at boot time to initialize things and
// open the file system for use.
//-----------------------------------------------------------------

void DfsModuleInit() {
// You essentially set the file system as invalid and then open 
// using DfsOpenFileSystem().
	sb.valid=0;
	DfsOpenFileSystem();

}

//-----------------------------------------------------------------
// DfsInavlidate marks the current version of the filesystem in
// memory as invalid.  This is really only useful when formatting
// the disk, to prevent the current memory version from overwriting
// what you already have on the disk when the OS exits.
//-----------------------------------------------------------------

void DfsInvalidate() {
// This is just a one-line function which sets the valid bit of the 
// superblock to 0.
	sb.valid=0;

}

//-------------------------------------------------------------------
// DfsOpenFileSystem loads the file system metadata from the disk
// into memory.  Returns DFS_SUCCESS on success, and DFS_FAIL on 
// failure.
//-------------------------------------------------------------------

int DfsOpenFileSystem() {
	disk_block disk_b;
	dfs_block dfs_b;
	int i;
	char* b_data;
	bzero(disk_b.data, DISK_BLOCKSIZE);
	bzero(dfs_b.data, DFS_BLOCKSIZE);
	
	lock_fbv = LockCreate();
	lock_inode = LockCreate();
	
//Basic steps:
// Check that filesystem is not already open
	if(sb.valid==1){
		printf("DfsOpenFileSystem() filesystem is already opened!\n");
		return DFS_FAIL;
	}

// Read superblock from disk.  Note this is using the disk read rather 
// than the DFS read function because the DFS read requires a valid 
// filesystem in memory already, and the filesystem cannot be valid 
// until we read the superblock. Also, we don't know the block size 
// until we read the superblock, either.
	DiskReadBlock(1,&disk_b);

// Copy the data from the block we just read into the superblock in memory
	bcopy(disk_b.data,(char*)&sb,sizeof(sb));
	
// All other blocks are sized by virtual block size:
// Read inodes
	b_data = (char*)inodes;
	for(i=sb.inode_start;i<sb.fbv_start;i++){
		DfsReadBlock(i,&dfs_b);
		bcopy(dfs_b.data, &(b_data[(i-sb.inode_start)*sb.fb_size]),sb.fb_size);
	}
	bzero(dfs_b.data, DFS_BLOCKSIZE);
// Read free block vector
	b_data = (char*)fbv;
	for(i=0;i<sb.fbv_num_blocks;i++){
		DfsReadBlock(i+sb.fbv_start,&dfs_b);
		bcopy(dfs_b.data, &(b_data[i*sb.fb_size]),sb.fb_size);
	}
// Change superblock to be invalid, write back to disk, then change 
// it back to be valid in memory
	bzero(disk_b.data, DISK_BLOCKSIZE);
	bzero(dfs_b.data, DFS_BLOCKSIZE);
	sb.valid=0;
	bcopy((char*)&sb,disk_b.data,sizeof(sb));
	DiskWriteBlock(1,&disk_b);
	sb.valid=1;
	
	return DFS_SUCCESS;
}


//-------------------------------------------------------------------
// DfsCloseFileSystem writes the current memory version of the
// filesystem metadata to the disk, and invalidates the memory's 
// version.
//-------------------------------------------------------------------

int DfsCloseFileSystem() {
	disk_block disk_b;
	dfs_block dfs_b;
	int i;
	char* b_data;
	bzero(disk_b.data, DISK_BLOCKSIZE);
	bzero(dfs_b.data, DFS_BLOCKSIZE);
	if(sb.valid==0){
		printf("DfsCloseFileSystem() filesystem is not opened!\n");
		return DFS_FAIL;
	}
	//write inodes
	b_data = (char*)inodes;
	for(i=sb.inode_start;i<sb.fbv_start;i++){
		bcopy(&(b_data[(i-sb.inode_start)*sb.fb_size]),dfs_b.data,sb.fb_size);
		DfsWriteBlock(i,&dfs_b);
	}
	bzero(dfs_b.data, DFS_BLOCKSIZE);
	//write fbv
	b_data = (char*)fbv;
	for(i=0;i<sb.fbv_num_blocks;i++){
		bcopy(&(b_data[i*sb.fb_size]),dfs_b.data,sb.fb_size);
		DfsWriteBlock(i+sb.fbv_start,&dfs_b);
	}
	//write sb
	bzero(disk_b.data, DISK_BLOCKSIZE);
	bzero(dfs_b.data, DFS_BLOCKSIZE);
	bcopy((char*)&sb,disk_b.data,sizeof(sb));
	DiskWriteBlock(1,&disk_b);
	sb.valid=0;
	return DFS_SUCCESS;
}


//-----------------------------------------------------------------
// DfsAllocateBlock allocates a DFS block for use. Remember to use 
// locks where necessary.
//-----------------------------------------------------------------

uint32 DfsAllocateBlock() {

	uint32 ret;
// Check that file system has been validly loaded into memory
	if(sb.valid==0){
		printf("DfsAllocateBlock() file system not loaded!\n");
		return DFS_FAIL;
	}
// Find the first free block using the free block vector (FBV), mark it in use
	LockHandleAcquire(lock_fbv);
  ret = FindFreeBlock();
  printf("DfsAllocateBlock() allocated block %d\n",ret);
  LockHandleRelease(lock_fbv);
  
// Return handle to block
	return ret;
}


//-----------------------------------------------------------------
// DfsFreeBlock deallocates a DFS block.
//-----------------------------------------------------------------

int DfsFreeBlock(uint32 blocknum) {
	uint32 i = blocknum/32;
	uint32 bit = blocknum%32;
	if(sb.valid==0){
		printf("DfsFreeBlock() file system not loaded!\n");
		return DFS_FAIL;
	}
	LockHandleAcquire(lock_fbv);
	fbv[i] = (fbv[i]&invert(1<<bit)) | (1<<bit);
	printf("DfsFreeBlock() free block %d\n", blocknum);
	LockHandleRelease(lock_fbv);
	return DFS_SUCCESS;
}


//-----------------------------------------------------------------
// DfsReadBlock reads an allocated DFS block from the disk
// (which could span multiple physical disk blocks).  The block
// must be allocated in order to read from it.  Returns DFS_FAIL
// on failure, and the number of bytes read on success.  
//-----------------------------------------------------------------

int DfsReadBlock(uint32 blocknum, dfs_block *b) {
	disk_block disk_b;
	int i;
	int bit;
	int byte_read=0;
	uint32 tmp;
	int disk_b_size;
	if(sb.valid==0){
		printf("DfsReadBlock() file system not loaded!\n");
		return DFS_FAIL;
	}
	i=blocknum/32;
	bit = blocknum%32;
	tmp = fbv[i]&invert(1<<bit);
	if(fbv[i]!=tmp){
		printf("DfsReadBlock() block %d is not allocated!\n",blocknum);
		//return DFS_FAIL;
	}
	
	//printf("DfsReadBlock() reading block %d\n",blocknum);
	disk_b_size = DiskBytesPerBlock();
	for(i=0;i<sb.fb_size/disk_b_size;i++){
		if(DiskReadBlock(blocknum*(sb.fb_size/disk_b_size)+i,&disk_b)==DISK_FAIL){
			break;
		}
		bcopy(disk_b.data, &(b->data[i*disk_b_size]),disk_b_size);
		//printf("b->data: %s\n",b->data);
		byte_read += disk_b_size;
	}
	
	return byte_read;
	
}


//-----------------------------------------------------------------
// DfsWriteBlock writes to an allocated DFS block on the disk
// (which could span multiple physical disk blocks).  The block
// must be allocated in order to write to it.  Returns DFS_FAIL
// on failure, and the number of bytes written on success.  
//-----------------------------------------------------------------

int DfsWriteBlock(uint32 blocknum, dfs_block *b){
	disk_block disk_b;
	int i;
	int bit;
	int byte_write=0;
	uint32 tmp;
	int disk_b_size;
	if(sb.valid==0){
		printf("DfsWriteBlock() file system not loaded!\n");
		return DFS_FAIL;
	}
	i=blocknum/32;
	bit = blocknum%32;
	tmp = fbv[i]&invert(1<<bit);
	if(fbv[i]!=tmp){
		printf("DfsWriteBlock() block %d is not allocated!\n",blocknum);
		//return DFS_FAIL;
	}
	disk_b_size = DiskBytesPerBlock();
	for(i=0;i<sb.fb_size/disk_b_size;i++){
		bcopy(&(b->data[i*disk_b_size]),disk_b.data,disk_b_size);
		DiskWriteBlock(blocknum*(sb.fb_size/disk_b_size)+i, &disk_b);
		byte_write += disk_b_size;
	}
	return byte_write;
}


////////////////////////////////////////////////////////////////////////////////
// Inode-based functions
////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------
// DfsInodeFilenameExists looks through all the inuse inodes for 
// the given filename. If the filename is found, return the handle 
// of the inode. If it is not found, return DFS_FAIL.
//-----------------------------------------------------------------

uint32 DfsInodeFilenameExists(char *filename) {
	uint32 i;
	if(sb.valid==0){
		printf("DfsInodeFilenameExists() file system not loaded!\n");
		return DFS_FAIL;
	}
	for(i=0;i<sb.num_inode;i++){
		if(inodes[i].inuse==1){
			if(dstrncmp(filename, inodes[i].filename, DFS_FILENAME_LENGTH)==0){
				return i;
			}
		}
	}
	return DFS_FAIL;
}


//-----------------------------------------------------------------
// DfsInodeOpen: search the list of all inuse inodes for the 
// specified filename. If the filename exists, return the handle 
// of the inode. If it does not, allocate a new inode for this 
// filename and return its handle. Return DFS_FAIL on failure. 
// Remember to use locks whenever you allocate a new inode.
//-----------------------------------------------------------------

uint32 DfsInodeOpen(char *filename) {
	uint32 i;
	i = DfsInodeFilenameExists(filename);
	if(i!=DFS_FAIL){
		return i;
	}
	
	LockHandleAcquire(lock_inode);
  for(i=0;i<sb.num_inode;i++){
  	if(inodes[i].inuse!=1){
  		inodes[i].inuse=1;
  		inodes[i].file_size=0;
  		inodes[i].indir = 0;
  		dstrncpy(inodes[i].filename,filename,DFS_FILENAME_LENGTH);
  		break;
  	}
  }

  LockHandleRelease(lock_inode);
  return i;
}


//-----------------------------------------------------------------
// DfsInodeDelete de-allocates any data blocks used by this inode, 
// including the indirect addressing block if necessary, then mark 
// the inode as no longer in use. Use locks when modifying the 
// "inuse" flag in an inode.Return DFS_FAIL on failure, and 
// DFS_SUCCESS on success.
//-----------------------------------------------------------------

int DfsInodeDelete(uint32 handle) {
	int i;
	dfs_block dfs_b;
	int* block_array = (int*)dfs_b.data;
	if(sb.valid==0){
		printf("DfsInodeDelete() file system not loaded!\n");
		return DFS_FAIL;
	}
	
	if(inodes[handle].inuse==0){
		printf("DfsInodeDelete() inode %d is not inuse!\n",handle);
		return DFS_FAIL;
	}
	
	//printf("got in here.......deleting inode %d\n",handle);
	
	LockHandleAcquire(lock_inode);
	//check if there is a indirect block
	if(inodes[handle].indir>0){
	//printf("got in here.......clear indirect table %d\n",inodes[handle].indir);
		DfsReadBlock(inodes[handle].indir,&dfs_b);
		for(i=0;i<(sb.fb_size/sizeof(int));i++){
			if(block_array[i]>0){
				DfsFreeBlock(block_array[i]);
			}
		}
		//clear indirect block
		bzero(dfs_b.data,sb.fb_size);
		DfsWriteBlock(inodes[handle].indir,&dfs_b);
		DfsFreeBlock(inodes[handle].indir);
		inodes[handle].indir = 0;
	
	}
	
	//clear direct table
	for(i=0;i<10;i++){
	//printf("got in here.......clear direct table\n");
		if(inodes[handle].direct_table[i]>0){
			DfsFreeBlock(inodes[handle].direct_table[i]);
			inodes[handle].direct_table[i]=0;
		}
	}
	
	inodes[handle].inuse=0;
	
	LockHandleRelease(lock_inode);
	return DFS_SUCCESS;
}


//-----------------------------------------------------------------
// DfsInodeReadBytes reads num_bytes from the file represented by 
// the inode handle, starting at virtual byte start_byte, copying 
// the data to the address pointed to by mem. Return DFS_FAIL on 
// failure, and the number of bytes read on success.
//-----------------------------------------------------------------

int DfsInodeReadBytes(uint32 handle, void *mem, int start_byte, int num_bytes) {
	char* byte_mem = (char*)mem;
	int byte_ct=0;
	dfs_block dfs_b;
	int block_num;
	int copy_size;
	if(sb.valid==0){
		printf("DfsInodeReadBytes() file system not loaded!\n");
		return DFS_FAIL;
	}
	
	if(inodes[handle].inuse==0){
		printf("DfsInodeReadBytes() inode %d is not inuse!\n",handle);
		return DFS_FAIL;
	}
	
	while(byte_ct<num_bytes){
		block_num = DfsInodeTranslateVirtualToFilesys(handle, (start_byte+byte_ct)/sb.fb_size);
		
		if(DfsReadBlock(block_num,&dfs_b)==DFS_FAIL){
			break;
		}
		//printf("DfsInodeReadBytes()\n");
		
		copy_size = sb.fb_size-((start_byte+byte_ct)%sb.fb_size);
		if((byte_ct+copy_size) > num_bytes){
			copy_size -= (byte_ct+copy_size-num_bytes);
		}
		bcopy(&dfs_b.data[(start_byte+byte_ct)%sb.fb_size],&byte_mem[byte_ct],copy_size);
		byte_ct += copy_size;
	}
	//printf("DfsInodeReadBytes(): %s\n",mem);
	return byte_ct;
}


//-----------------------------------------------------------------
// DfsInodeWriteBytes writes num_bytes from the memory pointed to 
// by mem to the file represented by the inode handle, starting at 
// virtual byte start_byte. Note that if you are only writing part 
// of a given file system block, you'll need to read that block 
// from the disk first. Return DFS_FAIL on failure and the number 
// of bytes written on success.
//-----------------------------------------------------------------

int DfsInodeWriteBytes(uint32 handle, void *mem, int start_byte, int num_bytes) {
	char* byte_mem = (char*)mem;
	int byte_ct=0;
	dfs_block dfs_b;
	int block_num;
	int copy_size;
	
	if(sb.valid==0){
		printf("DfsInodeWriteBytes() file system not loaded!\n");
		return DFS_FAIL;
	}
	
	if(inodes[handle].inuse==0){
		printf("DfsInodeWriteBytes() inode %d is not inuse!\n",handle);
		return DFS_FAIL;
	}
	
	while(byte_ct<num_bytes){
		block_num = DfsInodeAllocateVirtualBlock(handle, (start_byte+byte_ct)/sb.fb_size);
		copy_size = sb.fb_size-((start_byte+byte_ct)%sb.fb_size);
		//check the start_byte and end_byte are block alligned
		if(copy_size == sb.fb_size){
			//start_byte is block alligned, check for end_byte
			if((byte_ct+copy_size) > num_bytes){
				copy_size = copy_size - (byte_ct+copy_size-num_bytes);
				if(DfsReadBlock(block_num,&dfs_b)==DFS_FAIL){
					break;
				}
			}
		
		}else{
			//start is not block alligned, check if end is block alligned
			if((byte_ct+copy_size) > num_bytes){
				copy_size -= (byte_ct+copy_size-num_bytes);
			}
			if(DfsReadBlock(block_num,&dfs_b)==DFS_FAIL){
				break;
			}
		
		}
		
		bcopy(&byte_mem[byte_ct],&dfs_b.data[(start_byte+byte_ct)%sb.fb_size],copy_size);
		DfsWriteBlock(block_num,&dfs_b);
		byte_ct += copy_size;
	}
	if(inodes[handle].file_size < (start_byte+byte_ct)){
		inodes[handle].file_size = start_byte+byte_ct;
	}
	return byte_ct;
}


//-----------------------------------------------------------------
// DfsInodeFilesize simply returns the size of an inode's file. 
// This is defined as the maximum virtual byte number that has 
// been written to the inode thus far. Return DFS_FAIL on failure.
//-----------------------------------------------------------------

uint32 DfsInodeFilesize(uint32 handle) {
	if(sb.valid==0){
		printf("DfsInodeFileSize() file system not loaded!\n");
		return DFS_FAIL;
	}
	
	if(inodes[handle].inuse==0){
		printf("DfsInodeFileSize() inode %d is not inuse!\n",handle);
		return DFS_FAIL;
	}
	
	return inodes[handle].file_size;
}


//-----------------------------------------------------------------
// DfsInodeAllocateVirtualBlock allocates a new filesystem block 
// for the given inode, storing its blocknumber at index 
// virtual_blocknumber in the translation table. If the 
// virtual_blocknumber resides in the indirect address space, and 
// there is not an allocated indirect addressing table, allocate it. 
// Return DFS_FAIL on failure, and the newly allocated file system 
// block number on success.
//-----------------------------------------------------------------

uint32 DfsInodeAllocateVirtualBlock(uint32 handle, uint32 virtual_blocknum) {
	int block_num;
	dfs_block dfs_b;
	int* block_array;

	
	if(sb.valid==0){
		printf("DfsInodeAllocateVirtualBlock() file system not loaded!\n");
		return DFS_FAIL;
	}
	
	if(inodes[handle].inuse==0){
		printf("DfsInodeAllocateVirtualBlock() inode %d is not inuse!\n",handle);
		return DFS_FAIL;
	}
	if(virtual_blocknum>=10){
		block_array = (int*)dfs_b.data;
		if(inodes[handle].indir==0){
			block_num = DfsAllocateBlock();
			bzero(dfs_b.data,sb.fb_size);
			DfsWriteBlock(block_num,&dfs_b);
			inodes[handle].indir = block_num;
		}
		DfsReadBlock(inodes[handle].indir,&dfs_b);
		virtual_blocknum -= 10;
		if(block_array[virtual_blocknum]!=0){
			return block_array[virtual_blocknum];
		}else{
			block_num = DfsAllocateBlock();
			block_array[virtual_blocknum] = block_num;
			DfsWriteBlock(inodes[handle].indir,&dfs_b);
		}
		return block_num;
	}else{
		block_array = inodes[handle].direct_table;
		if(block_array[virtual_blocknum]!=0){
			return block_array[virtual_blocknum];
		}else{
			block_num = DfsAllocateBlock();
			block_array[virtual_blocknum] = block_num;
			return block_num;
		}
	}
	
	
	
	/*block_num = DfsAllocateBlock();
	// store block_num into direct_table if virtual_blocknum<10
	// update block_array if virtual_blocknum>=10
	if(virtual_blocknum < 10){
		inodes[handle].direct_table[virtual_blocknum]=block_num;
		return block_num;
	}else{
		// get block_array from indir_block
		if(inodes[handle].indir!=-1){
			// indir_block exists
			DfsReadBlock(inodes[handle].indir, &dfs_b);
			bcopy((char*)&dfs_b,(char*)block_array,sb.fb_size);
		}else{
			// indir_block does not exists, allocate it and init it
			inodes[handle].indir = DfsAllocateBlock();
			for(i=0;i<sb.fb_size/sizeof(int);i++){
				block_array[i]=-1;
			}
		}
		// update block_array that stored in indir_block
		// check if virtual_blocknum can be in one indir_block
		if(virtual_blocknum-10 < sb.fb_size/sizeof(int)){
			block_array[virtual_blocknum-10]=block_num;
			bzero(dfs_b.data, sb.fb_size);
			bcopy((char*)block_array, (char*)dfs_b.data, sb.fb_size);
			DfsWriteBlock(block_num, &dfs_b);
			return block_num;
		}
		
	}*/
	return DFS_FAIL;

}



//-----------------------------------------------------------------
// DfsInodeTranslateVirtualToFilesys translates the 
// virtual_blocknum to the corresponding file system block using 
// the inode identified by handle. Return DFS_FAIL on failure.
//-----------------------------------------------------------------

uint32 DfsInodeTranslateVirtualToFilesys(uint32 handle, uint32 virtual_blocknum) {

	dfs_block dfs_b;
	int* block_array;

	if(sb.valid==0){
		printf("DfsInodeTranslateVirtualToFilesys() file system not loaded!\n");
		return DFS_FAIL;
	}
	
	if(inodes[handle].inuse==0){
		printf("DfsInodeTranslateVirtualToFilesys() inode %d is not inuse!\n",handle);
		return DFS_FAIL;
	}
	
	if(virtual_blocknum>=10){
		block_array = (int*)dfs_b.data;
		if(inodes[handle].indir<=0){
			printf("DfsInodeTranslateVirtualToFilesys() invalid indirect block!\n");
			return DFS_FAIL;
		}
		DfsReadBlock(inodes[handle].indir,&dfs_b);
		virtual_blocknum -= 10;
		if(block_array[virtual_blocknum]<=0){
			printf("DfsInodeTranslateVirtualToFilesys() invalid block entry in indirect block!\n");
			return DFS_FAIL;
		}else{
			return block_array[virtual_blocknum];
		}
		
	}else{
		block_array = inodes[handle].direct_table;
		if(block_array[virtual_blocknum]<=0){
			printf("DfsInodeTranslateVirtualToFilesys() invalid direct block!\n");
			return DFS_FAIL;
		}else{
			return block_array[virtual_blocknum];
		}
		
	}
	
	/*
	if(virtual_blocknum<10){
		return inodes[handle].direct_table[virtual_blocknum];
	}else{
		DfsReadBlock(inodes[handle].indir, &dfs_b);
		bcopy((char*)&dfs_b,(char*)block_array,sb.fb_size);
		return block_array[virtual_blocknum-10];
	}*/
	
	return DFS_FAIL;
}
