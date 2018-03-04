#include "checker.h"

/* Will take in the array of arguments and do stuff with it */

/** Will take in an input string **/
int handle_line(char *input, int stageno) {
	char *rest;
	rest = strtok(input, " ");
	/* input is now the command */
	
        handle_input(rest, stageno);
        handle_output(rest, stageno);
        handle_args(rest, stageno);
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
int handle_args(char **arguments, char *input, int stageno) {
        return 0;
}

