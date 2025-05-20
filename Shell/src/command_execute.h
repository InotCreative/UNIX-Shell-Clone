#ifndef command_execute_c
#define command_execute_c

#include "string_handler.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

#define FORK_ERROR perror("FORK"), exit(EXIT_FAILURE)
#define EXEC_ERROR perror("EXEC"), exit(EXIT_FAILURE)

void executeCommands(StringArray *arguementArray);

#endif