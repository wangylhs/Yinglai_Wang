#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "spawn.h"

void main (int argc, char *argv[])
{
  //missile_code *mc;        // Used to access missile codes in shared memory page
  uint32 h_mem;            // Handle to the shared memory page
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
  c_buffer *cir_buffer;		 // Used to access circular buffer in shared memory page
  lock_t buffer_lock;			 // lock used to access circular buffer(shared)
  int curr = 0;

  if (argc != 4) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  h_mem = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[2], NULL, 10);
  buffer_lock = dstrtol(argv[3], NULL, 10);

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
  	//buffer is not empty, remove character from buffer and increment head 
  	if(cir_buffer->tail != cir_buffer->head){
  		Printf("Consumer %d removed: %c\n", Getpid(), cir_buffer->buffer[cir_buffer->head]);
  		cir_buffer->head = (cir_buffer->head+1)%BUFFERSIZE;
  		curr++;
  	}
  	// release lock
  	if(lock_release(buffer_lock) != SYNC_SUCCESS){
  		Printf("Bad lock_release in "); Printf(argv[0]); Printf("\n");
  		Exit();
  	}
 	
 	}
 	
  // Now print a message to show that everything worked
  //Printf("spawn_me: This is one of the %d instances you created.  ", mc->numprocs);
  //Printf("spawn_me: Missile code is: %c\n", mc->really_important_char);
  //Printf("spawn_me: My PID is %d\n", Getpid());

  // Signal the semaphore to tell the original process that we're done
  Printf("consumer: PID %d is complete.\n", Getpid());
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}