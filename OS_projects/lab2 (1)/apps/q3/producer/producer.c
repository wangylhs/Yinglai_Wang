#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "spawn.h"

void main (int argc, char *argv[])
{
  c_buffer *cir_buffer;        // Used to access circular buffer in shared memory page
  uint32 h_mem;            // Handle to the shared memory page
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
	lock_t buffer_lock;			 		 // lock used to access circular buffer(shared)
	char item[] = "Hello World"; // item will be inserted into buffer
	int head = 0;								 
	//=======================added for q3========================================
	sem_t s_fullslots;
	sem_t s_emptyslots;
	//===========================================================================
	
  if (argc != 6) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  h_mem = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[2], NULL, 10);
  buffer_lock = dstrtol(argv[3], NULL, 10);
  //=======================added for q3========================================
	s_fullslots = dstrtol(argv[4], NULL, 10);
	s_emptyslots = dstrtol(argv[5], NULL, 10);
	//===========================================================================

  // Map shared memory page into this process's memory space
  if ((cir_buffer = (c_buffer *)shmat(h_mem)) == NULL) {
    Printf("Could not map the virtual address to the memory in "); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
 	//insert characters when there's empty slots
  while(head < BUFFERSIZE){
  	
  	// wait for empty slots
  	if(sem_wait(s_emptyslots) != SYNC_SUCCESS){
  		Printf("Bad sem_wait(s_emptyslots) "); Printf(argv[0]); Printf("\n");
  		Exit();
  	}
  	// acquire lock for buffer_lock
  	if(lock_acquire(buffer_lock) != SYNC_SUCCESS){
  		Printf("Bad lock_acquire in "); Printf(argv[0]); Printf("\n");
    	Exit();
  	}
  	//write to buffer and increment tail 
  	cir_buffer->buffer[cir_buffer->tail] = item[head];
  	cir_buffer->tail = (cir_buffer->tail+1)%BUFFERSIZE;
  	Printf("Producer %d inserted: %c\n", Getpid(), item[head]);
  	head++;
  	// release lock
  	if(lock_release(buffer_lock) != SYNC_SUCCESS){
  		Printf("Bad lock_release in "); Printf(argv[0]); Printf("\n");
  		Exit();
  	}
  	// signal the semaphore character inserted
 		if(sem_signal(s_fullslots) != SYNC_SUCCESS){
 			Printf("Bad sem_signal(s_fullslots) "); Printf(argv[0]); Printf("\n");
 			Exit();
 		}
  
  }

  // Signal the semaphore to tell the original process that we're done
  Printf("producer: PID %d is complete.\n", Getpid());
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}
