#include "commands.h"

char cwd[STR_MAX_SZ];

void set_cwd(char *s)
{
	// must be called on first call to the module
	// maybe we can call chdir() without paramters and receive the cwd
	// and then we don't need to pass *s
	strcpy_s(cwd, STR_MAX_SZ, s);
}

int process_cmd(char* s)
{
	// process the command
	// returns 0 if the command is 'exit', otherewise, return 1
	command cmd_type = get_cmd_type(s);
	int bg = is_background(s);
	if(cmd_type == CMD_EXTERNAL)
		run_external(s, bg);
	else
		run_internal(s);
	return cmd_type == CMD_EXIT ? 0 : 1;
}

int is_background(char* s)
{
	if (strlen(s) < 2)
		return 0;
	return s[strlen(s) - 2] == '&';
}

command get_cmd_type(char* s)
{
	// return 1 if s is an internal command

	if (strcmp(s, "exit\n") == 0)
		return CMD_EXIT;

	if (strcmp(s, "jobs\n") == 0)
		return CMD_JOBS;

	if (strncmp(s, "cd ", 3) == 0)
		return CMD_CD;

	return CMD_EXTERNAL;
}

void run_external(char*s, int bg)
{
	// run the exec()
	printf("Received external command %s in %s\n", s, bg ? "BACKGROUND" : "FOREGROUND");
	if (bg)
	{
		// "(non-blocking)"
		background(s);
	}
	else
	{
		// this is foreground, so just call exec ("blocking")
		// exec(s);
		printf("Executing %s in the foreground\n", s);
	}
}

void run_internal(char* s)
{
	// must return 0 if the command is exit, otherwise 1
	printf("Received internal command %s\n", s);

	// was the command cd?
	command cmd_type = get_cmd_type(s);
	switch (cmd_type)
	{
		case CMD_CD:
			cmd_cd(s);
			break;
		case CMD_JOBS:
			cmd_jobs();
			break;
		case CMD_EXIT:
			break;
		default:
			printf("Command not implemented yet; is this an exeternal command?");
			break;
	}
}

void cmd_cd(char* s)
{
	/* 
		parse the cd string, e.g. cd c:\doc\itay, the command is cd and the argument is c:\doc\itay
		* we then call chdir with the argument
	*/
	printf("Received CD command\n");
	if (strlen(s) < 4)
	{
		// no arguments
		return;
	}
	else
	{
		char arg[STR_MAX_SZ];
		strcpy_s(arg, STR_MAX_SZ - 3, s + 3);		// itay to check maybe this is 3?
		if (strcmp(arg, "..\n") == 0)
		{
			// go to upper directory
			cd_up();
		}
		else
		{
			cd_chdir(arg);
		}
		// call chdir(arg); in comment because this is windows
	}
}

void cd_up()
{
	// implement cd ..
	// here we change the variable cwd
	printf("Received CD_UP command\n");
}

void cd_chdir(char *args)
{
	// call chdir
	// here we also change the variable cwd accordingly
	// also handle wrong chdir, or chdir failure
	printf("Received CHDIR command with arguments %s", args);
}

void cmd_jobs()
{
	// print all the jobs per the requirement
	print_jobs();
}