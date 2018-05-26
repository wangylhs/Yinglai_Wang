#include "usertraps.h"
#include "misc.h"

void main (int argc, char *argv[])
{
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
	char * addr;
  if (argc != 2) { 
    Printf("Usage: %s <handle_to_procs_completed_semaphore>\n");
    Exit();
  }
	
	
  // Convert the command-line strings into integers for use as handles
  s_procs_completed = dstrtol(argv[1], NULL, 10);
  // Now print a message to show that everything worked
  Printf("beyond_max (%d): This program will access memory beyond max virtual address!\n", getpid());
	
  // Signal the semaphore to tell the original process that we're done
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("beyond_max (%d): Bad semaphore s_procs_completed (%d)!\n", getpid(), s_procs_completed);
    Exit();
  }
  addr = 0x2FFFFF;
	*addr = 2;
  Printf("beyond_max (%d): Done!\n", getpid());
}
