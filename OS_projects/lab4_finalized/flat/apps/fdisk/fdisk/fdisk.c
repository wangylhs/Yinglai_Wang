#include "usertraps.h"
#include "misc.h"

#include "fdisk.h"

dfs_superblock sb;
dfs_inode inodes[FDISK_NUM_INODES];
uint32 fbv[DFS_FBV_MAX_NUM_WORDS];

int diskblocksize = 0; // These are global in order to speed things up
int disksize = 0;      // (i.e. fewer traps to OS to get the same number)

int FdiskWriteBlock(uint32 blocknum, dfs_block *b); //You can use your own function. This function 
//calls disk_write_block() to write physical blocks to disk

void main (int argc, char *argv[])
{	
	int i;
	dfs_block dfs_b;
	
	// STUDENT: put your code here. Follow the guidelines below. They are just the main steps. 
	// You need to think of the finer details. You can use bzero() to zero out bytes in memory

  //Initializations and argc check
  if(argc>1){
  	Printf("There should not be any args!\n");
  	Exit();
  }
  bzero(dfs_b.data, DFS_BLOCKSIZE);
  diskblocksize = disk_blocksize();
	disksize = disk_size();
  Printf("(%d) Sizeof dfs_inode is %d\n", getpid(),sizeof(dfs_inode));
	Printf("(%d) diskblocksize = %d, disksize = %d\n", getpid(),diskblocksize, disksize);
	Printf("(%d) init superblock\n", getpid());
  // Need to invalidate filesystem before writing to it to make sure that the OS
  // doesn't wipe out what we do here with the old version in memory
  // You can use dfs_invalidate(); but it will be implemented in Problem 2. You can just do 
  dfs_invalidate();
  sb.valid = 0;
  sb.fb_size = DFS_BLOCKSIZE;
  sb.num_fb = disksize/sb.fb_size;
	sb.inode_start = FDISK_INODE_BLOCK_START;
	sb.num_inode = FDISK_NUM_INODES;
	sb.fbv_start = FDISK_FBV_BLOCK_START;
	sb.fbv_num_words = DFS_FBV_MAX_NUM_WORDS;
	sb.fbv_num_blocks = DFS_FBV_MAX_NUM_WORDS*sizeof(uint32)/DFS_BLOCKSIZE;
	sb.data_start = sb.fbv_start + sb.fbv_num_blocks;
  //disksize = 
  //diskblocksize = 
  //num_filesystem_blocks = 

  // Make sure the disk exists before doing anything else
  if(disk_create()== DISK_FAIL){
  	Printf("disk_create() FAIL!\n");
  	Exit();
  }
 
  // Write all inodes as not in use and empty (all zeros)
  Printf("(%d) write inode blocks\n", getpid());
	for(i=sb.inode_start;i<sb.fbv_start;i++){
		FdiskWriteBlock(i,&dfs_b);
	}
  Printf("(%d) done with writing inode blocks\n", getpid());
  // Next, setup free block vector (fbv) and write free block vector to the disk
  Printf("(%d) write fbv blocks\n", getpid());
  for(i=0;i<DFS_FBV_MAX_NUM_WORDS;i++){
  	fbv[i]=0;
  }
  for(i=sb.data_start;i<sb.num_fb;i++){
  	fbv[i/32] = (fbv[i/32] & ((1<<(i%32))^0xFFFFFFFF)) | (1<<(i%32));
  }
  for(i=0;i<sb.fbv_num_blocks;i++){
  	bcopy(&(((char*)fbv)[i*sb.fb_size]),dfs_b.data,sb.fb_size);
  	FdiskWriteBlock(sb.fbv_start+i, &dfs_b);
  }
  Printf("(%d) done with writing fbv blocks\n");
  // Finally, setup superblock as valid filesystem and write superblock and boot record to disk: 
  sb.valid=1;
  Printf("(%d) write first and second physical blocks\n", getpid());
  // boot record is all zeros in the first physical block, and superblock structure goes into the second physical block
  bzero(dfs_b.data, sb.fb_size);
  bcopy((char*)&sb, &(dfs_b.data[diskblocksize]), sizeof(sb));
  FdiskWriteBlock(0,&dfs_b);
  
  Printf("fdisk (%d): Formatted DFS disk for %d bytes.\n", getpid(), disksize);
  
  
}

int FdiskWriteBlock(uint32 blocknum, dfs_block *b) {
  // STUDENT: put your code here
  disk_block disk_b;
  int i;
  for(i=0;i<sb.fb_size/diskblocksize;i++){
  	bcopy(&(b->data[i*diskblocksize]),disk_b.data,diskblocksize);
  	//Printf("start write to physic block %d\n", blocknum*(sb.fb_size/diskblocksize)+i);
  	if(disk_write_block(blocknum*(sb.fb_size/diskblocksize)+i, disk_b.data)==DISK_FAIL){
  		Printf("write to physic block %d FAIL!\n",blocknum*(sb.fb_size/diskblocksize)+i);
  		return DISK_FAIL;
  	}
  }
  return DISK_SUCCESS;
}