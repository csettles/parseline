//
//  main.c
//  asgn5
//
//  Created by Caitlin Settles on 3/3/18.
//  Copyright © 2018 Caitlin Settles. All rights reserved.
//

#include "parseline.h"

int main(int argc, const char * argv[]) {
	char *stages[10], line[512];
	
	sscanf(stdin, "%512s", line);
	
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
