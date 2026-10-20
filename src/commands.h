#ifndef SCOREBOARD_COMMANDS_H
#define SCOREBOARD_COMMANDS_H

#include <stdio.h>

#include "board.h"

/* Executes one command line, writing the reply to out. */
void run_command(struct board *b, const char *line, FILE *out);

#endif
