#include "ostraps.h"
#include "dlxos.h"
#include "traps.h"
#include "disk.h"
#include "dfs.h"
#include "misc.h"

void RunOSTests() {
  // STUDENT: run any os-level tests here
  int handle;
	char test1[] = "test1";
	char test2[] = "test2";
	char ece[] = "ece";
	int i;
	char buffer[512];
	
	if(DfsInodeFilenameExists("test") == DFS_FAIL) {
		printf("==================This is the first run of ostest=================\n\n");
  	printf("file 'test' did not exist\n");
  	printf("creating test file\n");
		printf("use DfsInodeOpen() to create test file\n");
		handle = DfsInodeOpen("test");
		
		printf("write to different blocks\n");
		printf("writing test1 to test file at location 40, 552, 1240 byte\n");
		DfsInodeWriteBytes(handle, test1, 40, dstrlen(test1) + 1);
		DfsInodeReadBytes(handle, buffer, 40, dstrlen(test1) + 1);
		printf("Read from test(40) found: %s\n",buffer);
		DfsInodeWriteBytes(handle, test1, 552, dstrlen(test1) + 1);
		DfsInodeReadBytes(handle, buffer, 552, dstrlen(test1) + 1);
		printf("Read from test(552) found: %s\n",buffer);
		DfsInodeWriteBytes(handle, test1, 1240, dstrlen(test1) + 1);
		DfsInodeReadBytes(handle, buffer, 1240, dstrlen(test1) + 1);
		printf("Read from test(1240) found: %s\n",buffer);
		printf("DfsInodeFileSize() returned %d (should be 1246)\n\n", DfsInodeFilesize(handle));

		printf("write beyond direct table(write to 5160 byte)\n");
		printf("DFS block size is 512, 5160 should be in indirect block\n");
		printf("writing test2 on test file at location 5160\n");
		for(i=4;i<11;i++){
		 DfsInodeWriteBytes(handle, test2, (i*512)+40, dstrlen(test2) + 1);
		}
		//DfsInodeWriteBytes(handle, test2, 5160, dstrlen(test2) + 1);
		DfsInodeReadBytes(handle, buffer, 5160, dstrlen(test2) + 1);
		printf("Read from test(5160) found: %s\n",buffer);
		printf("DfsInodeFileSize() returned %d (should be 5166)\n\n", DfsInodeFilesize(handle));
		printf("===============First run of ostest finished=======================\n\n");
		
	}else{
		printf("==================This is the second run of ostest=================\n\n");
		printf("file 'test' exist\n");
		printf("opening test file\n");
		printf("use DfsInodeOpen() to open test file\n");
		handle = DfsInodeOpen("test");
		printf("check location 1240 of test, should be test1\n");
		DfsInodeReadBytes(handle, buffer, 1240, dstrlen(test1) + 1);
		printf("Read from test(1240) found: %s\n",buffer);
		printf("check location 5160 of test, should be test2\n");
		DfsInodeReadBytes(handle, buffer, 5160, dstrlen(test2) + 1);
		printf("Read from test(5160) found: %s\n\n",buffer);
		
		printf("write 'ece' to 1240 of test (this should overwrite the test1)\n");
		DfsInodeWriteBytes(handle, ece, 1240, dstrlen(ece) + 1);
		printf("check location 1240 of test, should be ece\n");
		DfsInodeReadBytes(handle, buffer, 1240, dstrlen(ece) + 1);
		printf("Read from test(1240) found: %s\n\n",buffer);
		
		printf("write 'test2' to 5200 of test to see file_size growth\n\n");
		DfsInodeWriteBytes(handle, test2, 5200, dstrlen(test2) + 1);
		printf("DfsInodeFileSize() returned %d (should be 5206)\n\n", DfsInodeFilesize(handle));
		
		printf("deleting test file\n");
		DfsInodeDelete(handle);
		printf("test file deleted\n");
		printf("================Second run of ostest finished===================\n\n");
	}
  
}

