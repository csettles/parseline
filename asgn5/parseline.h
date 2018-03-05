/**
  parseline.h
  asgn5

  Created by Caitlin Settles on 3/3/18.
  Copyright © 2018 Caitlin Settles. All rights reserved.
**/

#ifndef parseline_h
#define parseline_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int split_line(char *line, char **stages);
void clean_line(char *line, char **stages, int len);
int all_space(char *line); 
#endif /* parseline_h */
