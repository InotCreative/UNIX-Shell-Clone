#ifndef command_execute_c
#define command_execute_c

#include "string_handler.c"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

#define FORK_ERROR perror("FORK"), exit(EXIT_FAILURE)
#define EXEC_ERROR perror("EXEC"), exit(EXIT_FAILURE)

void executeCommands(StringArray *arguementArray) {
    int32_t childProcess = fork();

    if (childProcess < 0) {
        FORK_ERROR;
    } else if (childProcess == 0) {
        if (execvp((const char *)arguementArray->array[0], (char *const *)arguementArray->array) == -1) EXEC_ERROR;
    } else {
        waitpid(childProcess, NULL, 0);
    }
}

#endif