#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

#define ll volatile long long int

//argc is storing the number of words written on command line 
int main(int argc, char **argv)
{
	int wtime, rtime, status = 0;
	int pid = fork();
	if (pid < 0)
	{
		printf(2, "Failed to fork\n");
		exit();
	}
	else if (pid == 0)
	{
		if (argc == 1)
		{
			printf(1,"Timing default program\n");
			for (int itr = 0; itr < 10000000; itr++)
			{

			}
			exit();
		}
		else
		{
			printf(1,"Timing %s\n", argv[1]);
			if (exec(argv[1], argv + 1) < 0)
			{
				printf(2, "exec %s failed\n", argv[1]);
				exit();
			}
		}
	}
	else if (pid > 0)
	{
		status = waitx(&wtime, &rtime);
		if (argc == 1)
		{
			printf(1, "Time taken by default process\nWait time: %d\nRun time: %d with Status %d\n\n", wtime, rtime, status);
		}
		else
		{
			printf(1, "Time taken by %s\nWait time: %d\nRun time: %d with Status %d\n\n", argv[1], wtime, rtime, status);
		}
		exit();
	}
}