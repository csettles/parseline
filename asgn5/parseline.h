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

#define STAGE_MAX 10
#define LINE_MAX 512
#define ARG_MAX 10

int split_line(char *line, char **stages);

#endif /* parseline_h */
