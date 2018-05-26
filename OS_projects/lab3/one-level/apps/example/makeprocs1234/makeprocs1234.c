#include "usertraps.h"
#include "misc.h"

#define HELLO_WORLD "hello_world.dlx.obj"
#define BEYOND_MAX "beyond_max.dlx.obj"
#define OUT_PAGE "out_page.dlx.obj"
#define STACK_GROW "stack_grow.dlx.obj"
#define COUNT_LARGE "count_large.dlx.obj"

void main (int argc, char *argv[])
{
  int num_hello_world = 0;             // Used to store number of processes to create
  int i;                               // Loop index variable
  sem_t s_procs_completed;             // Semaphore used to wait until all spawned processes have completed
  char s_procs_completed_str[10];      // Used as command-line argument to pass page_mapped handle to new processes
	
	sem_t sem2;													// semaphore used for "access memory beyond max virtual address"
	char sem2_str[10];
	sem_t sem3;													// semaphore used for "access memory outside of allocated pages"
	char sem3_str[10];
	sem_t sem4;													// semaphore used for "stack to grow larger than 1 page"
	char sem4_str[10];

								
  if (argc != 2) {
    Printf("Usage: %s <number of hello world processes to create>\n", argv[0]);
    Exit();
  }

  // Convert string from ascii command line argument to integer number
  num_hello_world = dstrtol(argv[1], NULL, 10); // the "10" means base 10

  // Create semaphore to not exit this process until all other processes 
  // have signalled that they are complete.
  if ((s_procs_completed = sem_create(0)) == SYNC_FAIL) {
    Printf("makeprocs (%d): Bad sem_create\n", getpid());
    Exit();
  }

  // Setup the command-line arguments for the new processes.  We're going to
  // pass the handles to the semaphore as strings
  // on the command line, so we must first convert them from ints to strings.
  ditoa(s_procs_completed, s_procs_completed_str);

  // Create testing processes
  Printf("-------------------------------------------------------------------------------------\n");
  Printf("makeprocs (%d): Creating test program to test 1\n", getpid());
  for(i=0; i<num_hello_world; i++) {
    Printf("makeprocs (%d): Creating hello world #%d\n", getpid(), i);
    process_create(HELLO_WORLD, s_procs_completed_str, NULL);
    if (sem_wait(s_procs_completed) != SYNC_SUCCESS) {
      Printf("Bad semaphore s_procs_completed (%d) in %s\n", s_procs_completed, argv[0]);
      Exit();
    }
  }
  
  Printf("makeprocs (%d): Creating test program to test 3\n", getpid());
  //create semaphore and process to access memory outside of currently allocated pages
	if ((sem3 = sem_create(0)) == SYNC_FAIL) {
    Printf("makeprocs (%d): Bad sem_create\n", getpid());
    Exit();
  }
  ditoa(sem3, sem3_str);
	process_create(OUT_PAGE, sem3_str, NULL);
	if (sem_wait(sem3) != SYNC_SUCCESS) {
      Printf("Bad semaphore s_procs_completed (%d) in %s\n", sem3, argv[0]);
      Exit();
  }
  
  Printf("makeprocs (%d): Creating test program to test 4\n", getpid());
  //create semaphore and process to cause user function call stack to grow larger than 1 page
	if ((sem4 = sem_create(0)) == SYNC_FAIL) {
    Printf("makeprocs (%d): Bad sem_create\n", getpid());
    Exit();
  }
  ditoa(sem4, sem4_str);
	process_create(STACK_GROW, sem4_str, NULL);
	if (sem_wait(sem4) != SYNC_SUCCESS) {
      Printf("Bad semaphore s_procs_completed (%d) in %s\n", sem4, argv[0]);
      Exit();
  }
  
  Printf("makeprocs (%d): Creating test program to test 2\n", getpid());
  //create semaphore and process to access memory beyond maximum virtual address
	if ((sem2 = sem_create(0)) == SYNC_FAIL) {
    Printf("makeprocs (%d): Bad sem_create\n", getpid());
    Exit();
  }
  ditoa(sem2, sem2_str);
	process_create(BEYOND_MAX, sem2_str, NULL);
	if (sem_wait(sem2) != SYNC_SUCCESS) {
      Printf("Bad semaphore s_procs_completed (%d) in %s\n", sem2, argv[0]);
      Exit();
  }

}
