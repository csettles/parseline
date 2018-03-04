#ifndef CHECKER_H
#define CHECKER_H

int handle_stage(char *input, int stagno, int stage_max);
int handle_input(char *input, int stageno, int stage_max);
int handle_output(char *input, int stageno, int stage_max);
int handle_count(char *input, int stageno, int stage_max);
int handle_args(char *input, int stageno, int stage_max, int arg_counts);

#endif
