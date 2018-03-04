#include "checker.h"
#include "parseline.h"

/* Will take in the array of arguments and do stuff with it */

/** Will take in an input string **/
int handle_stage(char *input, int stageno, int stage_max) {
	unsigned char last_index;

	last_index = strlen(input) - 1;
        if (*input && (input[last_index] == '\n')) {
                input[last_index] = '\0';
                last_index--;
        }	

	printf("\n--------\n");
        printf("Stage %d: \"%s\"\n", stageno, input);
        printf("--------\n");	

	/* removes leading white space */ 
	while(isspace((unsigned char) *input)) {
		input++; 
	}
	
	while(isspace((unsigned char) input[last_index])) {
		input[last_index] = '\0';
		last_index--; 
	}
	/* input is now the command */
	
        handle_input(input, stageno, stage_max);
        handle_output(input, stageno, stage_max);
        handle_args(input, stageno, stage_max);
        return 0;
}

/** Will determine where the input is coming from **/
int handle_input(char *input, int stageno, int stage_max) {
	/* find first < */
	/* if there is no redirection, input is stdin for stage #0
	 and the previous stage for stages 1+ */
        return 0;
}

/** Will determine where the output should be **/
int handle_output(char *input, int stageno, int stage_max) {
	char *redir_pos, *output; 

	/* Checking end of pipeline */
	if (stageno == stage_max) {
		/* Find the redirection */
		redir_pos = strchr(input, '>');
		/* Couldn't find redirection */ 
		if (redir_pos == NULL) {
			printf("output: original stdout\n"); 
		/* Redirection found */ 
		} else {
			/* Moves to space, then moves to word */ 
			output = strtok(redir_pos, " ");
			output = strtok(NULL, " ");  
			/* if extra white space, moves past */
			while(*output == ' ') {
				output = strtok(NULL, " ");
			}
			printf("output: %s\n", output);
		}
	/* TODO: I don't think we need to worry about redirections here */ 
	/* Interior of pipeline now have to consider next pipe */ 
	} else {
		/* Find the redirection, if not, pipe */
                redir_pos = strchr(input, '>');
                /* Couldn't find redirection */
                if (redir_pos == NULL) {
                        printf("output: pipe to stage %d\n", stageno+1);
                /* Redirection found */
                } else {
			/* moves to space, then to word */
			output = strtok(redir_pos, " ");
			output = strtok(NULL, " "); 
			/* if extra white space, moves past */ 
			while(*output == ' ') {
				output = strtok(NULL, " "); 
                        }
			printf("output: %s\n", output);
                }	
	}
	return 0;
}

/** Will get the arg list and size**/
int handle_args(char *input, int stageno, int stage_max) {
        return 0;
}


