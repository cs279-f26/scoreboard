/* libFuzzer harness: the input is a sequence of command lines. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    struct board *b = board_new();
    FILE *sink = fopen("/dev/null", "w");
    char *text = malloc(size + 1), *line, *save = NULL;

    memcpy(text, data, size);
    text[size] = '\0';
    for (line = strtok_r(text, "\n", &save); line != NULL; line = strtok_r(NULL, "\n", &save))
        run_command(b, line, sink);
    free(text);
    fclose(sink);
    board_free(b);
    return 0;
}
