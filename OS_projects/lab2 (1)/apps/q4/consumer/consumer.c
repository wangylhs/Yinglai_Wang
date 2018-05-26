#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "spawn.h"

void main (int argc, char *argv[])
{

  uint32 h_mem;            // Handle to the shared memory page
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
  c_buffer *cir_buffer;		 // Used to access circular buffer in shared memory page
  lock_t buffer_lock;			 // lock used to access circular buffer(shared)
  int curr = 0;
  //=======================added for q4========================================
	cond_t c_full;
	cond_t c_empty;
	//===========================================================================

  if (argc != 6) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore> <lock> <c_full> <c_empty>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  h_mem = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[2], NULL, 10);
  buffer_lock = dstrtol(argv[3], NULL, 10);
  //=======================added for q4========================================
	c_full = dstrtol(argv[4], NULL, 10);
	c_empty = dstrtol(argv[5], NULL, 10);
	//===========================================================================

  // Map shared memory page into this process's memory space
  if ((cir_buffer = (c_buffer *)shmat(h_mem)) == NULL) {
    Printf("Could not map the virtual address to the memory in "); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
 
 	//remove characters
 	while(curr < BUFFERSIZE){
  	
 		// acquire lock for buffer_lock
  	if(lock_acquire(buffer_lock) != SYNC_SUCCESS){
  		Printf("Bad lock_acquire in "); Printf(argv[0]); Printf("\n");
    	Exit();
  	}
  	
  	//wait for available slots
 		while(cir_buffer->tail == cir_buffer->head){
 			if(cond_wait(c_full) != SYNC_SUCCESS){
 				Printf("Bad cond_wait(c_fullslots) "); Printf(argv[0]); Printf("\n");
  			Exit();
 			}
 		} 
  	
  	// remove character, increment head
  	Printf("Consumer %d removed: %c\n", Getpid(), cir_buffer->buffer[cir_buffer->head]);
  	cir_buffer->head = (cir_buffer->head+1)%BUFFERSIZE;
  	curr++;
  	
  	// signal the condition variable character removed
 		if(cond_signal(c_empty) != SYNC_SUCCESS){
 			Printf("Bad cond_signal(c_emptyslots) "); Printf(argv[0]); Printf("\n");
 			Exit();
 		}
  	// release lock
  	if(lock_release(buffer_lock) != SYNC_SUCCESS){
  		Printf("Bad lock_release in "); Printf(argv[0]); Printf("\n");
  		Exit();
  	}
  	
 	}

  // Signal the semaphore to tell the original process that we're done
  Printf("consumer: PID %d is complete.\n", Getpid());
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}
