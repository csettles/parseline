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
                fprintf(stderr, "command too long\n");
		exit(EXIT_FAILURE);
        } 

	/* checks for any errors, will exit if any found */ 
	len = split_line(line, stages);
	clean_line(line, stages, len-1); 

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
   
    /* Need strcpy to not ruin input string */  
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

void clean_line(char *line, char **stages, int len) {
	int i; 
	char line_copy[LINE_MAX]; 
	char *temp;

	/* Checks there are no empty stages */
	
	strcpy(line_copy, line);  
	temp = strtok(line_copy, "|");
	
	/* TODO: If multiple spaces between things?? */ 
	while(temp != NULL) {
		if (strlen(temp) == 1) {
			fprintf(stderr, "invalid null command\n"); 
			exit(EXIT_FAILURE);
		}
		/* Handle excess white spae? */ 
		temp = strtok(NULL, "|");
	}

	 /* TODO: Handle missing names and get command failed on */
	/* Checks there aren't more than one '<' or '>' in any stages*/
	for (i = 0; i < len; i++) {
		
		/* Find first <, move past it, check if another exist */ 
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
	}

	for (i = 0; i < len; i++) {	
		/* Find first >, move past, check if another exists */
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
			/* Stages after 1 MUST have a pipe in, if also <, exit */
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
