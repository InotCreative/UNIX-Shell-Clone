#include <stdio.h>
#include "string_handler.h"
#include "command_execute.h"
#include "batch_file_reading.h"

#define MAX_COMMAND_SIZE 1024

int main(int argc, char const *argv[]) {
    if (argc == 2) {
        readAndExecuteBatchScript(argv[1]);
        exit(EXIT_SUCCESS);
    }

    uint8_t buffer[1024] = {0};
    StringArray arguements;
    StringArray history;

    init(&arguements);
    init(&history);

    while (true) {
        printf(">>> ");

        if (fgets((char *)buffer, MAX_COMMAND_SIZE, stdin) == NULL) exit(EXIT_FAILURE);
        if (buffer[0] == '\n') continue;

        tokenizeString(&arguements, buffer);

        if ((arguements.size > 0) && ((strcmp((const char *)arguements.array[0], "quit") == 0) || (strcmp((const char *)arguements.array[0], "exit") == 0))) {
            exit(EXIT_SUCCESS);
        }

        if ((arguements.size > 0) && ((strcmp((const char *)arguements.array[0], "history") == 0))) {
            history.push(&history, (uint8_t *)strdup((const char *)buffer), 1);
            history.printArray(&history, 1);

        } else if ((arguements.size > 0) && ((strcmp((const char *)arguements.array[0], "cd") == 0))) {
            if (chdir((const char *)arguements.array[1]) != 0) perror("cd");

        } else if ((arguements.size > 0) && (arguements.array[0][0] == '!')) {
            uint32_t index = atoi((const char *)buffer+1) - 1;

            if (strcmp((const char *)history.array[index], "history") == 0) {
                history.printArray(&history, 1);
            } else {
                tokenizeString(&arguements, history.array[index]);
                executeCommands(&arguements);
            }

        } else {
            executeCommands(&arguements);

        }

        history.push(&history, (uint8_t *)strdup((const char *)buffer), 1);

        init(&arguements);
    }

    arguements.freeArray(&arguements);
    history.freeArray(&history);

    exit(EXIT_SUCCESS);
}
