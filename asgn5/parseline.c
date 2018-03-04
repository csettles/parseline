/**
  main.c
  asgn5

  Created by Caitlin Settles on 3/3/18.
  Copyright © 2018 Caitlin Settles. All rights reserved.
**/

#include "checker.h"
#include "parseline.h"

int main(int argc, const char * argv[]) {
	char *stages[STAGE_MAX], line[LINE_MAX + 2];
	int i, len = 0, str_len;
    
	printf("line: ");
	fgets(line, LINE_MAX + 2, stdin);

        str_len = (int)strlen(line);
        if (str_len > LINE_MAX) {
                fprintf(stderr, "parseline: command line length too long\n");
		exit(EXIT_FAILURE);
        } 

	len = split_line(line, stages);
	
	/* 1 indexed, so need to do len -1 */ 	
	for (i = 0; i < len-1; ++i) {
		/* process stage */;
		handle_stage(stages[i], i, len-2); 	
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
