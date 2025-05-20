#include "string_handler.h"

void growArray(StringArray *array) {
    if (array->array == NULL) {
        array->capacity = INITAL_CAPACITY;
        array->array = (uint8_t **)malloc(array->capacity * sizeof(uint8_t *));
        MEMORY_TEST(array->array);

    } else if (array->size + 1 > array->capacity) {
        array->capacity = array->capacity * 2;
        array->array = (uint8_t **)realloc(array->array, array->capacity * sizeof(uint8_t *));
        MEMORY_TEST(array->array);
        
    }
}

void push(StringArray *array, uint8_t *string, uint8_t flag) {
    if (flag == 0) {
        array->array[array->size] = string;
        array->size += 1;
        
        return;
    } else {
        growArray(array);
        array->array[array->size] = string;
        array->size += 1;

        return;
    }
}

void tokenizeString(StringArray *arguements, uint8_t *rawString) {
    int32_t lengthOfRawString = strlen((const char *)rawString);
    int32_t numberOfArguements = 0;
    bool isDelimeter = false;

    uint8_t *copy = (uint8_t *)malloc((lengthOfRawString + 2) * sizeof(uint8_t));
    MEMORY_TEST(copy);

    strcpy((char *)copy, (const char *)rawString);
    copy[lengthOfRawString] = ' ';
    copy[lengthOfRawString + 1] = '\0';

    for (int32_t i = 0; i < lengthOfRawString + 2; i++) {
        if (strchr(WHITE_SPACE, copy[i])) {
            if (isDelimeter == false) {
                isDelimeter = true;
                numberOfArguements++;
            }
        } else {
            isDelimeter = false;
        }
    }

    isDelimeter = false;
    arguements->size = 0;
    arguements->array = (uint8_t **)malloc((numberOfArguements + 1) * sizeof(uint8_t *));
    MEMORY_TEST(arguements->array);

    uint8_t *startPtr = &copy[0];
    uint8_t *endPtr = NULL;

    for (int32_t i = 0; i < lengthOfRawString + 2; i++) {
        if (strchr(WHITE_SPACE, copy[i])) {
            if (isDelimeter == false) {
                isDelimeter = true;
                endPtr = &copy[i];

                uint32_t lengthOfSubstring = (uint32_t)(endPtr - startPtr);
                if (lengthOfSubstring == 0) continue;

                uint8_t *subString = (uint8_t *)malloc((lengthOfSubstring + 1) * sizeof(char));
                MEMORY_TEST(subString);

                strncpy((char *)subString, (const char *)startPtr, lengthOfSubstring);
                subString[lengthOfSubstring] = '\0';

                arguements->push(arguements, subString, 0);
            }
        } else {
            if (isDelimeter == true) {
                startPtr = &copy[i];
            }
            isDelimeter = false;
        }
    }

    arguements->push(arguements, NULL, 0);
    free(copy);
}

void freeArray(StringArray *array) {
    for (uint32_t i = 0; i < array->size; i++) {
        free(array->array[i]);
    }

    free(array->array);

    init(array);
}

void printArray(StringArray *array, uint8_t flag) {
    for (uint32_t i = 0; i < array->size; i++) {
        switch (flag) {
            case 0:
                printf("INDEX: %d | STRING: %s\n", i, array->array[i]);
                break;
            case 1:
                printf("[%d] %s", i+1, array->array[i]);
        }
    }
}

void init(StringArray *array) {
    array->size       = 0;
    array->capacity   = INITAL_CAPACITY;
    array->array      = NULL;
    array->freeArray  = freeArray;
    array->printArray = printArray; 
    array->push       = push;
}
