CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
BUILD_DIR = builds
OUTPUT = $(BUILD_DIR)/bash

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

all: $(OUTPUT)

# Rule to link object files into executable
$(OUTPUT): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile .c files into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(OUTPUT)
