#ifndef string_handler_c
#define string_handler_c

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define WHITE_SPACE " \t\n"
#define INITAL_CAPACITY 8

#define MEMORY_TEST(arrayPtr) {if (arrayPtr == NULL) {perror("MALLOC"); return;}}

typedef struct StringArray {
    uint32_t size;
    uint32_t capacity;
    uint8_t **array;

    void (* printArray)(struct StringArray *, uint8_t);
    void (* freeArray)(struct StringArray *);
    void (* push)(struct StringArray *, uint8_t *, uint8_t);
} StringArray;

void growArray(StringArray *array);
void push(StringArray *array, uint8_t *string, uint8_t flag);
void tokenizeString(StringArray *arguements, uint8_t *rawString);
void freeArray(StringArray *array);
void printArray(StringArray *array, uint8_t flag);
void init(StringArray *array);

#endif