#include "types.h"
#include "user.h"

int main(int argc,char *argv[])
{
	if(argc==3)
	{
		int pid,priority,k;	
		priority=atoi(argv[1]);
		pid=atoi(argv[2]);
		k=set_priority(priority,pid);
		printf(1,"%d is the old priority of the process with pid=%d\n",k,pid);
	}
	else
	{
		printf(1,"Error running setPriority command\n");
	}
	exit();
}