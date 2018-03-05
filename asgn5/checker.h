#ifndef CHECKER_H
#define CHECKER_H

#define STAGE_MAX 10
#define LINE_MAX 512
#define ARG_MAX 10
#define CMD_MAX 20
#define ARG_LEN 20

typedef struct stage stage;
struct stage {
	int num, argc;
	char input[CMD_MAX], output[CMD_MAX];
	char command[CMD_MAX];
	char line[LINE_MAX];
	char args[ARG_MAX][ARG_LEN]; /* list of null terminated arguments */
	stage *next;
};

int handle_stage(stage *s, char *input, int stage_max);

int handle_input(stage *s, char *input, int stage_max);
int handle_output(stage *s, char *input, int stage_max);
int handle_count(stage *s, char *input, int stage_max);
int handle_args(stage *s, char *input, int stage_max);

stage *new_stage(int number);
stage new_stage_s(int number);
stage build_stages(char *line);
void print_stage(stage s);
void print_stages(stage head);

#endif
