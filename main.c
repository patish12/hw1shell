#include "main.h"

int main(int argc, void* argv[])
{
	// variables
	char cmdline[STR_MAX_SZ];

	// itay to figure out how to determine what is the current working directory
	// and call it to set_cwd()
	// set_cwd(s);

	// main loop
	while (1)
	{
		fprintf(stdout, "hw1shell$ ");
		fgets(cmdline, STR_MAX_SZ, stdin);
		if (process_cmd(cmdline) == 0)
			break;
	}

	// cleanup all the processes
	cleanup();

	return 0;
}
