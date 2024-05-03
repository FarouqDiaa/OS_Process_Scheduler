#include "Clock/headers.h"

int prev;
int curr;

void SIGCONThandler (int signum);

int main(int agrc, char * argv[])
{
    initClk();
    signal(SIGCONT, SIGCONThandler);
    int runningtime = atoi(argv[1]);
    int arrivaltime = atoi(argv[2]);

    //TODO it needs to get the remaining time from somewhere
    //remainingtime = ??;
    remainingtime = runningtime;
   printf("Starting process with ID = %d - Remaining time = %d\n", getpid(), remainingtime);

    prev = getClk();
//  printf("Start run ID: %d at time: %d and rem time = %d\n", getpid(), getClk(), remainingtime);
  while (remainingtime > 0 )
      {      
        curr = getClk();
        if (curr != prev)
        {
          prev = getClk();   
          remainingtime --;   
         printf("Process ID = %d - Remaining time = %d - Current time = %d\n", getpid(), remainingtime, getClk());
        }
      }
   printf("Process with pid = %d - Finish time = %d\n",getpid(), prev);
    // kill(getppid(), SIGUSR1);
    kill(getppid(), SIGUSR2);
    destroyClk(false);
    raise(SIGTERM);
    
    return 0;
}

void SIGCONThandler(int signum)
{
  printf("Process ID = %d Started running at time = %d\n", getpid(), getClk());
  prev = curr = getClk();
  signal(SIGCONT, SIGCONThandler); 
}