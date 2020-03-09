#include "types.h"
#include "user.h"
#include "stat.h"

#define PING 0
#define PONG 1


int
main(int argc, char **argv)
{
	int n=atoi(argv[1]);
	int pid;
	int i;
	
	sem_init(PING, 1);
	sem_init(PONG, 0);
	pid=fork();	
	for(i=0;i<n;i++)
	{
		if (pid<0)
			printf(1, "pingpong: fork failed\n");
		if (pid==0)
		{
			sem_down(PING);
			printf(1,"PING \n");
			sem_up(PONG);
		}
		if (pid>0)
		{
			sem_down(PONG);
			printf(1,"\tPONG \n");
			sem_up(PING);
		}
	}
	sem_release(PING);
	sem_release(PONG);
	if (pid>0)
		wait();
	exit();
}
