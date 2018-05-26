#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "spawn.h"

void main (int argc, char *argv[])
{

  uint32 h_mem;            // Handle to the shared memory page
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done

	data *dat;
	//int i;								 
	
  if (argc != 3) { 
    Printf("Usage: "); Printf(argv[0]); Printf(" <handle_to_shared_memory_page> <handle_to_page_mapped_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  h_mem = dstrtol(argv[1], NULL, 10); // The "10" means base 10
  s_procs_completed = dstrtol(argv[2], NULL, 10);

  // Map shared memory page into this process's memory space
  if ((dat = (data *)shmat(h_mem)) == NULL) {
    Printf("Could not map the virtual address to the memory in "); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
	//inject N and make N2 NO2
	lock_acquire(dat->lock);
  dat->curr_n++;
  Printf("An atom of Nitrogen was created.\n");
  if(dat->curr_n>1) cond_signal(dat->c_n2);
  while(dat->curr_n<2){
  	cond_wait(dat->c_n2);
  }
  dat->curr_n2++;
  dat->curr_n-=2;
  Printf("2 atoms of Nitrogen combined to produce 1 molecule of N2.\n");
  lock_release(dat->lock);
   
  while(dat->temp<=100){
  	lock_acquire(dat->lock);
  	cond_wait(dat->c_no2);
  	dat->curr_n2-=1;
  	dat->curr_o2-=2;
  	Printf("1 molecule of N2 and 2 molecules of O2 combined to produce 2 molecules of NO2.\n");
  	lock_release(dat->lock);
  }
  
  
  // Signal the semaphore to tell the original process that we're done
  Printf("N producer: PID %d is complete.\n", Getpid());
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
}
