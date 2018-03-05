#include "checker.h"
#include "parseline.h"

/* Will take in the array of arguments and do stuff with it */

stage *new_stage(int number) {
	stage *s;
	s = malloc(sizeof(struct stage))
	s->next = NULL;
	s->num = number;
	s->argc = 0;

	return s;
}

/** Will take in an input string **/
int handle_stage(stage *s, char *input, int stage_max) {
	int last_index;
	
	last_index = (int)strlen(input) - 1;
	if (input[last_index] == '\n') {
		input[last_index] = '\0';
		last_index--;
	}
	
	if (last_index + 1 == 0 || all_space(input)) {
		fprintf(stderr, "invalid null command\n");
		exit(EXIT_FAILURE);
	}
	
	/* input is now the command */
	
	handle_input(s, input, stage_max);
	handle_output(s, input, stage_max);
	handle_count(s, input, stage_max);
	handle_args(s, input, stage_max);
	return 0;
}

/** Will determine where the input is coming from **/
int handle_input(stage *s, char *input, int stage_max) {
	char *redir_pos, *input_dest;
	char position_temp[LINE_MAX];
	
	strcpy(position_temp, input);
	
	if (s->num == 0) {
		/* Find the redirection */
		redir_pos = strchr(position_temp, '<');
		/* Couldn't find redirection */
		if (redir_pos == NULL) {
			strcpy(s->input, "original stdin"); /* no redirection */
		} else {
			/* Moves to space, then moves to word */
			input_dest = strtok(redir_pos, " ");
			input_dest = strtok(NULL, " ");
			/* if extra white space, moves past */
			while(*input_dest == ' ') {
				input_dest = strtok(NULL, " ");
			}
			strcpy(s->input, input_dest); /* found redirection */
		}
		/* Interior of pipeline now only have to consider next pipe */
	} else {
		sprintf(s->input, "pipe from stage %d", s->num - 1);
	}
	return 0;
}

/** Will determine where the output should be **/
int handle_output(stage *s, char *input, int stage_max) {
	char *redir_pos, *output;
	char position_temp[LINE_MAX];
	
	strcpy(position_temp, input);
	
	/* if last stage or if only one stage */
	if (s->num == stage_max) {
		/* Find the redirection */
		redir_pos = strchr(position_temp, '>');
		/* Couldn't find redirection */
		if (redir_pos == NULL) {
			strcpy(s->input, "original stdout");
		} else {
			/* Moves to space, then moves to word */
			output = strtok(redir_pos, " ");
			output = strtok(NULL, " ");
			/* if extra white space, moves past */
			while(*output == ' ') {
				output = strtok(NULL, " ");
			}
			strcpy(s->input, output); /* found redirection */
		}
		/* Interior of pipeline now only have to consider next pipe */
	} else {
		sprintf(s->input, "pipe to stage %d", s->num + 1);
	}
	return 0;
}

int handle_count(stage *s, char *input, int stage_max) {
	char input_copy[LINE_MAX];
	char *token;
	int arg_counter;
	
	strcpy(input_copy, input);
	
	token = strtok(input_copy, " ");
	
	arg_counter = 0;
	while(token != NULL) {
		if ((strcmp(token,"<") != 0) && (strcmp(token, ">") != 0)) {
			arg_counter++;
		} else {
			arg_counter--;
		}
		token = strtok(NULL, " ");
	}
	s->argc = arg_counter;
	return 0;
}

/** Will get the arg list and size**/
int handle_args(stage *s, char *input, int stage_max) {
	char input_copy[LINE_MAX];
	char *token, *args[ARG_MAX];
	int len = 0, i;
	
	strcpy(input_copy, input);
	
	token = strtok(input_copy, " ");
	while (token != NULL && len < ARG_MAX) {
		if ((strcmp(token,"<") == 0) || (strcmp(token, ">") == 0)) {
			token = strtok(NULL, " "); /* skip file name */
			token = strtok(NULL, " "); /* go to next arg */
			continue;
		}
		args[len] = token;
		len++;
		token = strtok(NULL, " ");
	}
	
	if (len == ARG_MAX && token != NULL) {
		fprintf(stderr, "too many arguments\n");
		exit(EXIT_FAILURE);
	}
	
	for (i = 0; i < len; i++) {
		s->args[i] = args[i];
	}
	
	return 0;
}

stage build_stages(char **stages, int len) {
	int i;
	stage *s, *temp;
	
	temp = s = new_stage(0);
	for (i = 0; i < len; i++) {
		handle_stage(temp, stages[i], len);
		temp->next = new_stage(i + 1);
		temp = temp->next;
	}
	
	return *s;
}

void print_stage(stage s) {
	int i;
	
	printf("\n--------\n");
	printf("Stage %d: \"%s\"\n", s.num, s.command);
	printf("--------\n");
	
	printf("%12s", "input: ");
	printf("%s\n", s.input);
	
	printf("%12s", "output: ");
	printf("%s\n", s.output);
	
	printf("%12s", "argc: ");
	printf("%d\n", s.argc);
	
	printf("%12s", "argv: ");
	for (i = 0; i < s.argc - 1; i++) {
		printf("\"%s\",", s.args[i]);
	}
	printf("\"%s\"\n", s.args[i]);
}

void print_stages(stage head) {
	print_stage(head);
	
	while (head.next != NULL) {
		print_stage(*head.next);
		head = *head.next;
	}
}


