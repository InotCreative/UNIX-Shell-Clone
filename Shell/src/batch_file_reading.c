#include "batch_file_reading.h"
#include "command_execute.h"
#include "string_handler.h"

#define FILE_CHECK(filePtr) {if (filePtr == NULL) {perror("FILE"); exit(EXIT_FAILURE);}}

void readAndExecuteBatchScript(const char *filePath) {
    FILE *inputFile = fopen(filePath, "r");
    FILE_CHECK(inputFile);

    StringArray fileLines;
    StringArray arguements;
    
    init(&fileLines);
    init(&arguements);

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


    for (uint32_t i = 0; i < fileLines.size; i++) {
        tokenizeString(&arguements, fileLines.array[i]);
        executeCommands(&arguements);
    }

    fileLines.freeArray(&fileLines);
    arguements.freeArray(&arguements);
    
    free(line);
    fclose(inputFile);
}