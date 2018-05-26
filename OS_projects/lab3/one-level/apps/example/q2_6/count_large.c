#include "usertraps.h"
#include "misc.h"


void main (int argc, char *argv[])
{
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
  int n = 100000;
	int i;
  if (argc != 2) { 
    Printf("Usage: %s <handle_to_procs_completed_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  s_procs_completed = dstrtol(argv[1], NULL, 10);

  // Now print a message to show that everything worked
  Printf("count_large (%d): Start counting!\n", getpid());
	
	for(i=0;i<n;i++){}
	
	Printf("count_large (%d): Done!\n", getpid());
}

