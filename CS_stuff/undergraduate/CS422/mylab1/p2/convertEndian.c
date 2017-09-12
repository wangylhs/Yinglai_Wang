#include "p2.h"

// Checks Endianness, if Little Endian, converts to big Endian & returns
uint64_t convertEndian(uint64_t chksum)
{
	unsigned int i = 1;
	char *c = (char*)&i;
    
	if (*c){
		//Little endian
		chksum =
	   	((chksum &  (uint64_t)(0x00000000000000FF)) << 56) |
	   	((chksum &  (uint64_t)(0x000000000000FF00)) << 40) |
	   	((chksum &  (uint64_t)(0x0000000000FF0000)) << 24) |
	   	((chksum &  (uint64_t)(0x00000000FF000000)) << 8)  |
	   	((chksum &  (uint64_t)(0x000000FF00000000)) >> 8)  |
	   	((chksum &  (uint64_t)(0x0000FF0000000000)) >> 24) |
	   	((chksum &  (uint64_t)(0x00FF000000000000)) >> 40) |
	   	((chksum &  (uint64_t)(0xFF00000000000000)) >> 56);
	}else{
		//Big endian (Do Nothing)
	}
	return chksum;
}
