#include "lab2-api.h"
#include "usertraps.h"
#include "misc.h"

#include "spawn.h"

void main (int argc, char *argv[])
{
  uint32 h_mem;                   // Used to hold handle to shared memory page
  sem_t s_procs_completed;        // Semaphore used to wait until all spawned processes have completed
  char h_mem_str[10];             // Used as command-line argument to pass mem_handle to new processes
  char s_procs_completed_str[10]; // Used as command-line argument to pass page_mapped handle to new processes
	//int numprocs = 4;
	int numprocs;
	int n_proc;
	int o_proc;
	
	data *dat;
	int i;
	
 	
  if (argc != 4) {
    Printf("Usage: "); Printf(argv[0]); Printf(" <number of N atoms> <number of O atoms> <temperature>\n");
    Exit();
  }


  // Allocate space for a shared memory page, which is exactly 64KB
  // Note that it doesn't matter how much memory we actually need: we 
  // always get 64KB
  if ((h_mem = shmget()) == 0) {
    Printf("ERROR: could not allocate shared memory page in "); Printf(argv[0]); Printf(", exiting...\n");
    Exit();
  }
	// Map shared memory page into this process's memory space
  if ((dat = (data *) shmat(h_mem)) == NULL) {
    Printf("Could not map the shared page to virtual address in "); Printf(argv[0]); Printf(", exiting..\n");
    Exit();
  }
	
	// Convert string from ascii command line argument to integer number
  //dat->n = dstrtol(argv[1], NULL, 10); // the "10" means base 10
  //dat->o = dstrtol(argv[2], NULL, 10);
  dat->temp = dstrtol(argv[3], NULL, 10);
  n_proc = dstrtol(argv[1], NULL, 10);
  o_proc = dstrtol(argv[2], NULL, 10);
  numprocs = n_proc + o_proc;
  
  dat->curr_n=0;
  dat->curr_o=0;
  dat->curr_n2=0;
  dat->curr_o2=0;
  Printf(" %d Nitrogen atoms, %d Oxygen atoms, Temperature: %d\n", n_proc, o_proc, dat->temp);

  // Create semaphore to not exit this process until all other processes 
  // have signalled that they are complete.  To do this, we will initialize
  // the semaphore to (-1) * (number of signals), where "number of signals"
  // should be equal to the number of processes we're spawning - 1.  Once 
  // each of the processes has signaled, the semaphore should be back to
  // zero and the final sem_wait below will return.
  if ((s_procs_completed = sem_create(-(numprocs-1))) == SYNC_FAIL) {
    Printf("Bad sem_create in "); Printf(argv[0]); Printf("\n");
    Exit();
  }
  
	// init locks and condition variables
	dat->lock = lock_create();
  dat->c_n2 = cond_create(dat->lock);
  dat->c_o2 = cond_create(dat->lock);
  dat->c_no2 = cond_create(dat->lock);
  dat->c_o3 = cond_create(dat->lock);
  
  // Setup the command-line arguments for the new process.  We're going to
  // pass the handles to the shared memory page and the semaphore as strings
  // on the command line, so we must first convert them from ints to strings.
  ditoa(h_mem, h_mem_str);
  ditoa(s_procs_completed, s_procs_completed_str);


  // Now we can create the processes.  Note that you MUST end your call to
  // process_create with a NULL argument so that the operating system
  // knows how many arguments you are sending.


	//create N O processes
	for(i=0;i<n_proc;i++){
  	process_create(INJECT_N, h_mem_str, s_procs_completed_str, NULL);
  }
  for(i=0;i<o_proc;i++){
  	process_create(INJECT_O, h_mem_str, s_procs_completed_str, NULL);
  }
  
  //Printf("Process %d created\n", i);

  // And finally, wait until all spawned processes have finished.
  if (sem_wait(s_procs_completed) != SYNC_SUCCESS) {
    Printf("Bad semaphore s_procs_completed (%d) in ", s_procs_completed); Printf(argv[0]); Printf("\n");
    Exit();
  }
  Printf("All other processes completed, exiting main process.\n");
}
