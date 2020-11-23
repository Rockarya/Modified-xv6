#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"
#include "pstat.h"

#define vll volatile long long int
#define MAX 5000000

int main(int argc, char **argv)
{
	for(int i=0; i < 10; i++)
    {
        printf(1, "Process %d\n", i);
        int pid = fork();
        if (pid < 0)
        {
            printf(2, "Failed to fork\n");
            exit();
        }

        if(pid == 0)
        {
            #ifdef PBS
                int my_pid = getpid();
                set_priority(my_pid, (i*10+17)%100);
                //set_priority(my_pid, 10);
            #endif

            int f = 0;
            for(int j=0; j < 5; j++)
            {
                if(f==0)
                {
                    sleep(i*10 + j +100);
                    f=1;
                }
                
                else
                {
                    f = 0;
                    for(int k=0; k < j+ 5 ;k++)
                    {
                        vll x = 0, y;
                        for (y = 0; y < MAX; y++)
                            x = 1 ^ x; //cpu time
                    }
                    
                }

            }
            // printf("noice");
            exit();

        } 
    }

    for (int i = 0; i < 10; i++)
        wait();

    struct proc_stat p; 
    int pid = getpid();
    getpinfo(&p, pid);
    printf(1, "Process with PID=%d has\nRunTime=%d\nNum_Run=%d\n",p.pid, p.runtime, p.num_run);

    #ifdef MLFQ
        printf(1, "Queue no=%d\nThe ticks received in each queue are:\n",p.current_queue);
        for(int i=0; i<5; i++)
            printf(1, "%d: %d\n", i, p.ticks[i]);
    #endif

    exit();
}