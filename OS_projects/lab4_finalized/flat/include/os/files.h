#ifndef __FILES_H__
#define __FILES_H__

#include "dfs.h"
#include "files_shared.h"

#define	F_MODE_READ	0x1
#define	F_MODE_WRITE	0x2
#define	F_MODE_RW	(F_MODE_READ | F_MODE_WRITE)
#define	F_MODE_EOF	0x4

#define FILE_MAX_OPEN_FILES 15
void FileInit();
int FileOpen(char *filename, char *mode);
int FileClose(int handle);
int FileRead(int handle, void *mem, int num_bytes);
int FileWrite(int handle, void *mem, int num_bytes);
int FileSeek(int handle, int num_bytes, int from_where);
int FileDelete(char *filename);
/*
uint32 check_R(uint32 mode);
uint32 check_W(uint32 mode);
uint32 check_RW(uint32 mode);
uint32 check_EOF(uint32 mode);
*/
#endif