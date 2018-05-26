#ifndef __DFS_SHARED__
#define __DFS_SHARED__

typedef struct dfs_superblock {
  // STUDENT: put superblock internals here
  int valid;
  int fb_size;
  int num_fb;
  int inode_start;
  int num_inode;
  int fbv_start;
  unsigned int fbv_num_words;
  unsigned int fbv_num_blocks;
  unsigned int data_start;
} dfs_superblock;

#define DFS_BLOCKSIZE 512  // Must be an integer multiple of the disk blocksize

typedef struct dfs_block {
  char data[DFS_BLOCKSIZE];
} dfs_block;

typedef struct dfs_inode {
  // STUDENT: put inode structure internals here
  // IMPORTANT: sizeof(dfs_inode) MUST return 96 in order to fit in enough
  // inodes in the filesystem (and to make your life easier).  To do this, 
  // adjust the maximumm length of the filename until the size of the overall inode 
  // is 96 bytes.
  int inuse;	// 4 bytes
  int file_size; 	// 4 bytes
  uint32 direct_table[10];	// 40 bytes
  uint32 indir;
  char filename[44]; 		// 96-4-4-4-40=44
} dfs_inode;

#define DFS_MAX_FILESYSTEM_SIZE 0x1000000  // 16MB
#define DFS_FBV_MAX_NUM_WORDS ((DFS_MAX_FILESYSTEM_SIZE/DFS_BLOCKSIZE)/32)
#define DFS_NUM_INODES 192
#define DFS_FILENAME_LENGTH 44

#define DFS_FAIL -1
#define DFS_SUCCESS 1



#endif
