#ifndef __USERPROG__
#define __USERPROG__

typedef struct buffer{
	char buffer[BUFFERSIZE];
	int head;
	int tail;
}c_buffer;

#define FILENAME_PRODUCER "producer.dlx.obj"
#define FILENAME_CONSUMER "consumer.dlx.obj"

#endif