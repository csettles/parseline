/**
  main.c
  asgn5

  Created by Caitlin Settles on 3/3/18.
  Copyright © 2018 Caitlin Settles. All rights reserved.
**/

#include "parseline.h"

int main(int argc, const char * argv[]) {
	char *stages[STAGE_MAX], line[LINE_MAX + 1];
	int i, len = 0;
	
	printf("line: ");
	fgets(line, LINE_MAX + 1, stdin);

	len = split_line(line, stages);
	
	for (i = 0; i < len; i++) {
		/* process stage */;
	}
	
	return 0;
}

int split_line(char *line, char **stages) {
	char *token;
	int len = 1; /* any input is automatically a stage */
	
	token = strtok(line, "|");
	
	while (token != NULL && len < STAGE_MAX) {
		*stages = token;
		token = strtok(NULL, "|");
		stages++, len++;
	}
	*stages = NULL;
	
	if (token != NULL) {
		/* token would be NULL if */
		fprintf(stderr, "pipeline too deep\n");
		exit(EXIT_FAILURE);
	}
	return len;
}
