#pragma once
#include <string.h>
#include <stdio.h>
#include "defines.h"
#include "process.h"

/* commands */
typedef enum _command
{
	CMD_EXIT,
	CMD_CD,
	CMD_JOBS,
	CMD_EXTERNAL
} command;

/* function prototypes */
int process_cmd(char*);
command get_cmd_type(char*);
void run_external(char*, int);
void run_internal(char*);
void cmd_cd(char*);
void cd_up();
void cd_chdir(char*);
void cmd_jobs();
int is_background(char*);



