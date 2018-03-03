/**
  main.c
  asgn5

  Created by Caitlin Settles on 3/3/18.
  Copyright © 2018 Caitlin Settles. All rights reserved.
**/

#include "parseline.h"

int main(int argc, const char * argv[]) {
	int i, str_length; 
	char *stages[10], line[PATH_SIZE + 1];
	
	for (i = 0; i < PATH_SIZE + 1; i++) {
                line[i] = '\0';
        }

        printf("line: ");
        fgets(line, PATH_SIZE + 1, stdin);
        str_length = strlen(line);

        if (str_length >= PATH_SIZE) {
                fprintf(stderr, "parseline: command line length too long\n");
        } else {
                printf("%d\n", str_length);
        }
		
	split_line(line, stages);

	return 0;
}

char **split_line(char *line, char **stages) {
	char *token;
	
	token = strtok(line, "|");
	
	while (token != NULL) {
		*stages = token;
		token = strtok(NULL, "|");
		stages++;
	}
	stages = NULL;
	
	return stages;
}
