#include <stdio.h>

#include "batch_file_reading.c"
#include "string_handler.c"
#include "command_execute.c"

#define MAX_COMMAND_SIZE 128

int main(int argc, char const *argv[]) {
    (void)argc;
    (void)argv;

    const char filePath[] = "/workspaces/UNIX-Shell-Clone/Shell/src/test.txt";
    readAndExecuteBatchScript(filePath);
    exit(EXIT_SUCCESS);
}
