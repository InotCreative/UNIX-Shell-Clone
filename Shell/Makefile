MAIN = src/main.c
LIB_ONE = src/tokenizer.c
LIB_TWO = src/execute.c
OUTPUT = builds/bash
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

all: $(OUTPUT)

$(OUTPUT): $(MAIN)
	$(CC) $(CFLAGS) $(MAIN) -o $(OUTPUT)

clean:
	rm -rf $(OUTPUT)
