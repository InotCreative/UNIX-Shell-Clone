// In batch_file_reading.h

#ifndef BATCH_FILE_READING_H
#define BATCH_FILE_READING_H

#include <stdio.h>    // For FILE*
#include <stdlib.h>   // For exit(), malloc()
#include <stdint.h>   // For uint8_t
#include <string.h>   // For strlen(), strcpy()

void readAndExecuteBatchScript(const char *filePath);

#endif // BATCH_FILE_READING_H