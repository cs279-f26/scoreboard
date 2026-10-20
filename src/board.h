#ifndef SCOREBOARD_BOARD_H
#define SCOREBOARD_BOARD_H

#define MAX_PLAYERS 16
#define NAME_LEN 24

struct board {
    int nplayers;
    char names[MAX_PLAYERS][NAME_LEN];
    long scores[MAX_PLAYERS];
};

struct board *board_new(void);
void board_free(struct board *b);
int board_join(struct board *b, const char *name);       /* slot, or -1 */
int board_rename(struct board *b, int slot, const char *name);
int board_add(struct board *b, int slot, long points);   /* 0 on success */
void board_reset(struct board *b);
int board_winner(const struct board *b);                 /* slot, or -1 */

#endif
