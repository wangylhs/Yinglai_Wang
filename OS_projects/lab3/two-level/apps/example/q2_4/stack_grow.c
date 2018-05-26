#include "usertraps.h"
#include "misc.h"

int foo(int);

void main (int argc, char *argv[])
{
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
  int n = 20000;
	int ret;
  if (argc != 2) { 
    Printf("Usage: %s <handle_to_procs_completed_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  s_procs_completed = dstrtol(argv[1], NULL, 10);

  // Now print a message to show that everything worked
  Printf("stack_grow (%d): This program will cause stack to grow larger than 1 page!\n", getpid());
	
	ret=foo(n);
	
  // Signal the semaphore to tell the original process that we're done
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("stack_grow (%d): Bad semaphore s_procs_completed (%d)!\n", getpid(), s_procs_completed);
    Exit();
  }
  
  Printf("stack_grow (%d): Done!\n", getpid());
}

int foo(int n){
	if(n==1) return 1;
	return foo(n-1);
}
