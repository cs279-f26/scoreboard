#include "board.h"

#include <stdlib.h>
#include <string.h>

struct board *board_new(void)
{
    return calloc(1, sizeof(struct board));
}

void board_free(struct board *b)
{
    free(b);
}

static int valid_name(const char *name)
{
    size_t len = strlen(name);
    return len > 0 && len < NAME_LEN;
}

int board_join(struct board *b, const char *name)
{
    if (b->nplayers == MAX_PLAYERS || !valid_name(name))
        return -1;
    strcpy(b->names[b->nplayers], name);
    b->scores[b->nplayers] = 0;
    return b->nplayers++;
}

int board_rename(struct board *b, int slot, const char *name)
{
    if (slot < 0 || slot >= b->nplayers || !valid_name(name))
        return -1;
    strcpy(b->names[slot], name);
    return 0;
}

int board_add(struct board *b, int slot, long points)
{
    if (slot >= b->nplayers)
        return -1;
    b->scores[slot] += points;
    return 0;
}

void board_reset(struct board *b)
{
    for (int i = 0; i < b->nplayers; i++)
        b->scores[i] = 0;
}

int board_winner(const struct board *b)
{
    int best = -1;

    for (int i = 0; i < b->nplayers; i++)
        if (best < 0 || b->scores[i] > b->scores[best])
            best = i;
    return best;
}
