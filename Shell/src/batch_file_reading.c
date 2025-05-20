#ifdef batch_file_reading_c
#define batch_file_reading_c

#include "command_execute.c"
#include "string_handler.c"

void readAndExecuteBatchScript(const char *filePath) {
    FILE *inputFile = fopen(filePath, "r");

    if (inputFile == NULL) {
        perror("FILE OPENING");
        exit(EXIT_FAILURE);
    }

    StringArray fileLines;
    init(&fileLines);

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, inputFile)) != -1) {
        if (read > 0 && line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        uint8_t *lineCopy = (uint8_t *)malloc(strlen(line) + 1);
        MEMORY_TEST(lineCopy);
        strcpy((char *)lineCopy, line);

        fileLines.push(&fileLines, lineCopy, 1);
    }

    free(line);
    fclose(inputFile);

    for (int i = 0; i < fileLines.size; i++) {
        printf("X");
    }

    fileLines.printArray(&fileLines, 0);

    fileLines.freeArray(&fileLines);
}

#endif