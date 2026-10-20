#include <stdio.h>
#include <string.h>

#include "commands.h"

int main(void)
{
    struct board *b = board_new();
    char line[256];

    if (b == NULL)
        return 1;
    setvbuf(stdout, NULL, _IOLBF, 0);
    while (fgets(line, sizeof line, stdin) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';
        run_command(b, line, stdout);
    }
    board_free(b);
    return 0;
}
