#include "commands.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

static int parse_long(const char *s, long *v)
{
    char *end;

    errno = 0;
    *v = strtol(s, &end, 10);
    return errno == 0 && end != s && *end == '\0';
}

static void show(const struct board *b, FILE *out)
{
    if (b->nplayers == 0)
        fputs("OK empty\n", out);
    for (int i = 0; i < b->nplayers; i++)
        fprintf(out, "OK %d %s %ld\n", i, b->names[i], b->scores[i]);
}

void run_command(struct board *b, const char *line, FILE *out)
{
    char verb[16], a[64], c[64];
    long slot, points;
    int n, w;

    a[0] = c[0] = '\0';
    n = sscanf(line, "%15s %63s %63s", verb, a, c);
    if (n < 1)
        return;
    if (strcmp(verb, "JOIN") == 0 && n == 2) {
        int s = board_join(b, a);
        if (s < 0)
            fputs("ERR board full or bad name\n", out);
        else
            fprintf(out, "OK %d\n", s);
    } else if (strcmp(verb, "SCORE") == 0 && n == 3) {
        if (!parse_long(a, &slot) || !parse_long(c, &points)
            || slot < -2147483647L || slot > 2147483647L)
            fputs("ERR usage: SCORE <slot> <points>\n", out);
        else if (board_add(b, (int)slot, points) != 0)
            fputs("ERR no such player\n", out);
        else
            fprintf(out, "OK %s %ld\n", b->names[slot], b->scores[slot]);
    } else if (strcmp(verb, "RENAME") == 0 && n == 3) {
        if (!parse_long(a, &slot) || slot < 0 || slot > MAX_PLAYERS
            || board_rename(b, (int)slot, c) != 0)
            fputs("ERR usage: RENAME <slot> <name>\n", out);
        else
            fputs("OK\n", out);
    } else if (strcmp(verb, "RESET") == 0) {
        board_reset(b);
        fputs("OK\n", out);
    } else if (strcmp(verb, "SHOW") == 0) {
        show(b, out);
    } else if (strcmp(verb, "WINNER") == 0) {
        w = board_winner(b);
        if (w < 0)
            fputs("ERR no players\n", out);
        else
            fprintf(out, "OK %s %ld\n", b->names[w], b->scores[w]);
    } else
        fputs("ERR unknown command\n", out);
}
