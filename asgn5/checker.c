#include "checker.h"
#include "parseline.h"

/* Will take in the array of arguments and do stuff with it */

/** Will take in an input string **/
int handle_stage(char *input, int stageno, int stage_max) {
	unsigned char last_index;
	
	last_index = strlen(input) - 1;
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
	/* Check start of pipeline */
	if (stageno == 0) {
		/* Find the redirection */
                redir_pos = strchr(position_temp, '<');
	        /* Couldn't find redirection */
                if (redir_pos == NULL) {
                        printf("%*s", 12, "input: ");
                        printf("original stdin\n");
                /* Redirection found */
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
	/* Checking end of pipeline */
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
	char *temp;

	strcpy(input_copy, input);
	temp = strtok(input_copy, " ");
	printf("%s\n", temp);
	return 0;
}
	
/** Will get the arg list and size**/
int handle_args(char *input, int stageno, int stage_max) {
       	 
	return 0;
}


