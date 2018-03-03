/**
  parseline.h
  asgn5

  Created by Caitlin Settles on 3/3/18.
  Copyright © 2018 Caitlin Settles. All rights reserved.
**/

#ifndef parseline_h
#define parseline_h

#include <stdio.h>
#include <string.h>

#define PATH_SIZE 512

char **split_line(char *line, char **stages);

#endif /* parseline_h */
