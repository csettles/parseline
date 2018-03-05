#ifndef CHECKER_H
#define CHECKER_H

#define STAGE_MAX 10
#define LINE_MAX 512
#define ARG_MAX 10
#define CMD_MAX 20

typedef struct stage stage;
struct stage {
	int num, argc;
	char input[20], output[20];
	char command[CMD_MAX];
	char *args[ARG_MAX]; /* list of null terminated arguments */
	stage *next;
};

int handle_stage(stage *s, char *input, int stage_max);

int handle_input(stage *s, char *input, int stage_max);
int handle_output(stage *s, char *input, int stage_max);
int handle_count(stage *s, char *input, int stage_max);
int handle_args(stage *s, char *input, int stage_max);

stage *new_stage(int number);
stage build_stages(char **stages, int len);
void print_stage(stage s);
void print_stages(stage head);

#endif
