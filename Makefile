CC      ?= cc
CFLAGS  ?= -O2 -g -Wall -Wextra
LDFLAGS ?=

SRC = src/board.c src/commands.c

all: scoreboard

scoreboard: src/main.c $(SRC) src/board.h src/commands.h
	$(CC) $(CFLAGS) -o $@ src/main.c $(SRC) $(LDFLAGS)

# libFuzzer harness: make fuzz CC=clang
fuzz: fuzz/fuzz_commands.c $(SRC)
	$(CC) -g -O1 -fsanitize=fuzzer,address -Isrc -o fuzz_commands fuzz/fuzz_commands.c $(SRC)

test: scoreboard
	sh tests/run.sh ./scoreboard

clean:
	rm -f scoreboard fuzz_commands

.PHONY: all fuzz test clean
