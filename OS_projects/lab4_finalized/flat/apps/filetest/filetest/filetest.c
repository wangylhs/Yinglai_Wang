#include "usertraps.h"
#include "misc.h"
#include "files_shared.h"


void main (int argc, char *argv[])
{
	int file_handle;
	int i,ct,str_len;
	int i_buffer;
	char content[] = "hello world";
	char buffer[FILE_MAX_READWRITE_BYTES];
	str_len = dstrlen(content);
	
	
	Printf("============ file write test start ================\n\n");
	Printf("creating file test1.txt if test1.txt not exist, otherwise open file\n\n");
	file_handle = file_open("test1.txt","w");
	if(file_handle==FILE_FAIL){
		Printf("error on file_open() test1.txt\n");
		return;
	}
	Printf("writing to test1.txt\n\n");
	ct = file_write(file_handle,content,str_len);
	if(ct==str_len){
		Printf("Succeed to wrote %d bytes to file\n",ct);
	}else{
		Printf("Fail to write %d bytes to file\n",ct);
	}
	Printf("closing file test1.txt\n\n");
	file_close(file_handle);
	
	Printf("creating file test2.txt if test2.txt not exist, otherwise open file\n\n");
	file_handle = file_open("test2.txt","w");
	if(file_handle==FILE_FAIL){
		Printf("error on file_open() test2.txt\n");
		return;
	}
	Printf("========test writing beyond direct table(beyond 5120 bytes)======\n\n");
	Printf("writing 5600 bytes to file test2.txt\n");
	for(i=0;i<1400;i++){
		ct = file_write(file_handle,&i,sizeof(i));
	}
	Printf("closing file test2.txt\n\n");
	file_close(file_handle);
	Printf("========= file write test done =================\n\n");
	
	Printf("========= file read test start =================\n\n");
	Printf("opening file test1.txt\n\n");
	file_handle = file_open("test1.txt","r");
	if(file_handle==FILE_FAIL){
		Printf("error on file_open() test1.txt\n");
		return;
	}
	Printf("reading from test1.txt\n\n");
  ct = file_read(file_handle,buffer,FILE_MAX_READWRITE_BYTES);
  if(ct==str_len){
  	Printf("Succeed to reach end of file\n");
  }else{
  	Printf("Fail to reach end of file\n");
  }
  if(file_seek(file_handle,0,FILE_SEEK_SET)==FILE_SUCCESS){
  	Printf("FileSeek Succeed!\n");
  }else{
  	Printf("FileSeek FAIL!\n");
  }
  file_read(file_handle,buffer,FILE_MAX_READWRITE_BYTES);
  //Printf("buffer: %s\n",buffer);
  if(dstrncmp(buffer,content,FILE_MAX_READWRITE_BYTES)==0){
  	Printf("Succeed to read content: %s\n",buffer);
  }else{
  	Printf("Fail to read buffer: %s\n",buffer);
  }
  
  Printf("closing file test1.txt\n\n");
	file_close(file_handle);
	
	Printf("opening file test2.txt\n\n");
	file_handle = file_open("test2.txt","r");
	if(file_handle==FILE_FAIL){
		Printf("error on file_open() test2.txt\n");
		return;
	}
	Printf("reading from test2.txt\n\n");
  for(i=0;i<1400;i++){
  	ct = file_read(file_handle,&i_buffer,sizeof(i));
  	//Printf("reading %d\n",i_buffer);
  	if(i_buffer!=i){
  		Printf("Reading error, should be %d, reading %d\n",i,i_buffer);
  		break;
  	}
  }
  file_read(file_handle,&i_buffer,sizeof(i));
  if(i==1400) Printf("Succeed to read 5600 bytes from test2.txt\n\n");
  Printf("closing file test2.txt\n\n");
	file_close(file_handle);
	Printf("========= file read test done =================\n\n");
	
	file_delete("test1.txt");
  file_delete("test2.txt");
	Printf("deleted file test1.txt and test2.txt\n\n");
	
	
}
