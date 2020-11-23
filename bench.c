#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"
#include "pstat.h"

#define vll volatile long long int
#define MAX 100000000

int main(int argc, char *argv[])
{
	for (int i = 0; i < 10; i++)
	{
		int pid = fork();

		if (pid < 0)
		{
			printf(2, "Failed to fork\n");
			exit();
		}

		else if (pid == 0)
		{
			//#ifdef PBS
				set_priority(107 - 9 * i,getpid());
			//#endif
			
			for(int j=0; j < 10; j++)
			{
				if(j <= i)
					sleep(200);

				else
				{
					for (vll k = 0; k < MAX; k++)
						k = 1 ^ k; //cpu
				}
				
			}

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