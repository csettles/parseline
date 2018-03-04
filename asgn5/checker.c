#include "checker.h"
#include "parseline.h"

/* Will take in the array of arguments and do stuff with it */

/** Will take in an input string **/
int handle_line(char *input, int stageno) {
	unsigned char last_index;

	/* removes leading white space */ 
	while(isspace((unsigned char) *input)) {
		input++; 
	}

	/* removes trailing white space from fgets */
	last_index = strlen(input) - 1;
	if (*input && (input[last_index] == '\n')) {
		input[last_index] = '\0'; 
	}
	/* input is now the command */
	
	printf("%s\n", input); 
        handle_input(input, stageno);
        handle_output(input, stageno);
        handle_args(input, stageno);
        return 0;
}

/** Will determine where the input is coming from **/
int handle_input(char *input, int stageno) {
	/* find first < */
	/* if there is no redirection, input is stdin for stage #0
	 and the previous stage for stages 1+ */
        return 0;
}

/** Will determine where the output should be **/
int handle_output(char *input, int stageno) {
        return 0;
}

/** Will get the arg list and size**/
int handle_args(char *input, int stageno) {
        return 0;
}

