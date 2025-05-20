#include "command_execute.h"

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
