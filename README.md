# scoreboard

A tiny score keeper for tabletop and pub-quiz games. One process holds one
board of up to 16 players; commands arrive one per line on standard input
(or over a socket, through `socat`), so a phone or a buzzer box can drive it.

```
$ ./scoreboard
JOIN alice
OK 0
JOIN bob
OK 1
SCORE 1 5
OK bob 5
SHOW
OK 0 alice 0
OK 1 bob 5
```

## Commands

| Command | Effect |
|---|---|
| `JOIN <name>` | adds a player (names up to 23 characters) and prints its slot |
| `SCORE <slot> <points>` | adds points (possibly negative) to a player |
| `RENAME <slot> <name>` | renames a player |
| `RESET` | sets every score to zero |
| `SHOW` | prints every player, one per line |
| `WINNER` | prints the leading player |

## Building

`make` builds `./scoreboard`; `make test` runs the tests. `make fuzz CC=clang`
builds a libFuzzer harness for the command parser (`fuzz/`).
