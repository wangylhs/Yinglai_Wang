#include "usertraps.h"
#include "misc.h"

void main (int argc, char *argv[])
{
  int childpid;
  int was = 300;
  // Now print a message to show that everything worked
  Printf("\n\ntest for fork starts (%d)=======================\n", getpid());
  Printf("test for fork (%d): Before fork  was=%d\n", getpid(), was);  
  Printf("PID=%d: forking child process\n", getpid());
  childpid = fork();
  if(childpid != 0) {
    // parent process
    Printf("test for fork (%d): This is parent process\n", getpid());
    Printf("test for fork (%d): After fork, was=%d child_pid=%d\n", getpid(), was, childpid);
    Printf("Parent process try to change the value of was\n");
    was = 600;
    Printf("test for fork (%d): This is parent process, was=%d\n", getpid(), was);
  }
  else {
    Printf("test for fork (%d): This is child process\n", getpid());
    Printf("test for fork (%d): After fork, was=%d cpid=%d\n", getpid(), was, childpid);
    Printf("Child process try to change the value of was\n");
    was = 900;
    Printf("test for fork (%d): This is child process, was=%d\n", getpid(), was);;
  }

  Printf("test for fork (%d):  Done!\n", getpid());
}