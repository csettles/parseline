#include "checker.h"
#include "parseline.h"

/* Will take in the array of arguments and do stuff with it */

stage new_stage(int number) {
	stage s;
	s.next = NULL;
	s.num = number;
	
	return s;
}

/** Will take in an input string **/
int handle_stage(char *input, int stageno, int stage_max) {
	int last_index;
	
	last_index = (int)strlen(input) - 1;
        if (input[last_index] == '\n') {
                input[last_index] = '\0';
                last_index--;
        }
	
	printf("\n--------\n");
        printf("Stage %d: \"%s\"\n", stageno, input);
        printf("--------\n");	

	/* input is now the command */
	
        handle_input(input, stageno, stage_max);
        handle_output(input, stageno, stage_max);
        handle_count(input, stageno, stage_max);
	handle_args(input, stageno, stage_max);
        return 0;
}

/** Will determine where the input is coming from **/
int handle_input(char *input, int stageno, int stage_max) {
        char *redir_pos, *input_dest;
	char position_temp[LINE_MAX]; 

	strcpy(position_temp, input);
	
	if (stageno == 0) {
		/* Find the redirection */
                redir_pos = strchr(position_temp, '<');
	        /* Couldn't find redirection */
                if (redir_pos == NULL) {
                        printf("%*s", 12, "input: ");
                        printf("original stdin\n");
                } else {
			/* Moves to space, then moves to word */
                        input_dest = strtok(redir_pos, " ");
			input_dest = strtok(NULL, " ");
			/* if extra white space, moves past */
                        while(*input_dest == ' ') {
                                input_dest = strtok(NULL, " ");
                        }
			printf("%*s", 12, "input: ");
                        printf("%s\n", input_dest);
                }
        /* Interior of pipeline now only have to consider next pipe */
        } else {
                printf("%*s", 12, "input: ");
                printf("pipe from stage %d\n", stageno-1);
	}
	return 0;
}

/** Will determine where the output should be **/
int handle_output(char *input, int stageno, int stage_max) {
	char *redir_pos, *output; 
	char position_temp[LINE_MAX];
	
	strcpy(position_temp, input);
	
	/* if last stage or if only one stage */
	if (stageno == stage_max) {
		/* Find the redirection */
		redir_pos = strchr(position_temp, '>');
		/* Couldn't find redirection */ 
		if (redir_pos == NULL) {
			printf("%*s", 12, "output: ");
			printf("original stdout\n"); 
		/* Redirection found */ 
		} else {
			/* Moves to space, then moves to word */ 
			output = strtok(redir_pos, " ");
			output = strtok(NULL, " ");  
			/* if extra white space, moves past */
			while(*output == ' ') {
				output = strtok(NULL, " ");
			}
			printf("%*s", 12, "output: ");
			printf("%s\n", output);
		}
	/* Interior of pipeline now only have to consider next pipe */ 
	} else {
		printf("%*s", 12, "output: ");
                printf("pipe to stage %d\n", stageno+1);
	}
	return 0;
}

int handle_count( char *input, int stageno, int stage_max) {
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
	printf("%*s", 12, "argc: ");
        printf("%d\n", arg_counter);
	return 0;
}
	
/** Will get the arg list and size**/
int handle_args(char *input, int stageno, int stage_max) {
	char input_copy[LINE_MAX];
	char *token, *args[ARG_MAX + 1];
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
	args[len] = NULL;
	
	if (len == ARG_MAX && token != NULL) {
		fprintf(stderr, "too many arguments\n");
		exit(EXIT_FAILURE);
	}
	
	printf("%12s", "argv: ");
	for (i = 0; i < len - 1; i++) {
		printf("\"%s\",", args[i]);
	}
	printf("\"%s\"\n", args[i]);
	
	return 0;
}


