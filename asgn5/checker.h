#ifndef CHECKER_H
#define CHECKER_H

typedef struct stage stage;
struct stage {
	int num, argc;
	char *input;
	char *output;
	char *command;
	char **args; /* list of null terminated arguments */
	stage *next;
};

int handle_stage(char *input, int stagno, int stage_max);
int handle_input(char *input, int stageno, int stage_max);
int handle_output(char *input, int stageno, int stage_max);
int handle_count(char *input, int stageno, int stage_max);
int handle_args(char *input, int stageno, int stage_max);

stage new_stage(int number);

#endif
