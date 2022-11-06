#include "process.h"

int num_running = 0;
int pid[MAX_NUM_PROC] = { 0, 0, 0, 0 };

void cleanup()
{
	/*
		Before exiting, we must make sure to wait
		and reap all the child processes possibly running in the 
		background (as well as do cleanups such as free dynamically 
		allocated memory if any).
	*/

}

void background(char *s)
{
	// run a process in the background
	if(num_running == MAX_NUM_PROC)
	{
		printf("too many background commands running");
		return;
	}
	pid[num_running++] = 10 * num_running + 1;
	printf("Running process %s in the background, num processes = %d\n", s, num_running);
}

void print_jobs()
{
	int i = 0;
	printf("current running jobs\n");
	for (i = 0; i < MAX_NUM_PROC; i++)
	{
		if (pid[i] != 0)
		{
			printf("%d\t%d\n", i, pid[i]);
		}
	}
}