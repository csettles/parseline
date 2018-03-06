/**
 main.c
 asgn5
 
 Created by Caitlin Settles on 3/3/18.
 Copyright © 2018 Caitlin Settles. All rights reserved.
 **/

#include "checker.h"
#include "parseline.h"

int main(int argc, const char * argv[]) {
	char line[LINE_MAX + 2];
	int str_len;
	stage s;
	
	printf("line: ");
	fgets(line, LINE_MAX + 2, stdin);
	
	str_len = (int)strlen(line);
	if (str_len > LINE_MAX) {
		fprintf(stderr, "command too long\n");
		exit(EXIT_FAILURE);
	}
	
	s = build_stages(line);
	
	/* checks for any errors, will exit if any found */
	
	print_stages(s);
	
	return 0;
}

/**
 Splits a line of input into "stages" based on piping. Each chunk of input
 between a pipe is called a stage.

 @param line the line of input
 @param stages an array of char *, which will hold each stage as a string
 @return the number of stages found in the line
 */
int split_line(char *line, char stages[STAGE_MAX][LINE_MAX]) {
	char *token, line_copy[LINE_MAX];
	int len = 0;
	
	strcpy(line_copy, line);
	token = strtok(line_copy, "|");
	
	while (token != NULL && len < STAGE_MAX) {
		strncpy(stages[len], token, LINE_MAX);
		token = strtok(NULL, "|");
		len++;
	}
	
	if (token != NULL) {
		/* token would be NULL if */
		fprintf(stderr, "pipeline too deep\n");
		exit(EXIT_FAILURE);
	}
	
	return len;
}

/**
 Error checks to make sure that the input does not violate certain parameters,
 such as exceeding the maximum number of pipes or giving ambiguous inputs
 or outputs.

 @param line the line of input
 @param stages a list of char* pointing to each stage in the input
 @param len the number of stages in the line
 */
void clean_line(char *line, char stages[STAGE_MAX][LINE_MAX], int len) {
	int i;
	char line_copy[LINE_MAX];
	char *temp;
	
	/* Checks there are no empty stages */
	memcpy(line_copy, line, strlen(line) + 1);
	temp = strtok(line_copy, "|");
	
	while(temp != NULL) {
		if (all_space(temp)) {
			fprintf(stderr, "invalid null command\n");
			exit(EXIT_FAILURE);
		}
		/* Handle excess white spae? */
		temp = strtok(NULL, "|");
	}
	
	/* TODO: Handle missing names and get command failed on */
	/* Checks there aren't more than one '<' or '>' in any stages*/
	for (i = 0; i < len; i++) {
		
		/* check input */
		temp = strchr(stages[i], '<');
		if (temp != NULL) {
			temp++;
			temp = strchr(temp, '<');
			if (temp != NULL) {
				/* Need to get command it failed on */
				fprintf(stderr, "bad input redirection\n");
				exit(EXIT_FAILURE);
			}
		}
		
		/* check output */
		temp = strchr(stages[i], '>');
		if (temp != NULL) {
			temp++;
			temp = strchr(temp, '>');
			if (temp != NULL) {
				/* Need to get command failed on */
				fprintf(stderr, "bad output redirection\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	
	/* Handle check for both a redirect and pipe */
	/* Handle input, check everything after first */
	if (len > 1) {
		for (i = 1; i < len; i++) {
			/* Stages after 1 have a pipe in, if also <, exit */
			if ((temp = strchr(stages[i], '<')) != NULL) {
				fprintf(stderr, "ambigious input\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	/* Handle output, check everything but last */
	for (i = 0; i < len-1; i++) {
		/* Stages that pipe out cannot have a file redirection out */
		if ((temp = strchr(stages[i], '>')) != NULL) {
			fprintf(stderr, "ambigious output\n");
			exit(EXIT_FAILURE);
		}
	}
}    

/**
 Checks if a string is "empty" -- a.k.a., it contains spaces or is null.

 @param line the string in question
 @return whether it is "empty"
 */
int all_space(char *line) {
	char temp[LINE_MAX];
	int i;
	
	i = 0;
	strcpy(temp, line);
	while(temp[i] != '\0') {
		if (!(isspace((unsigned char)temp[i]))) {
			return 0;
		}
		i++;
	}
	return 1;
}
