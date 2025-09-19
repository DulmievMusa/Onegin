#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdarg.h>

#include "sort_functions.h"
#include "get_functions.h"


const char* SOURCE = "onegin.txt";
const char* DIRECTION = "result.txt";


int CreateArrayOfPointers(char* text, char ** pointers_array);
void PutStringArrayToFile(char** pointers_array, int numbers_of_strings, bool skip_spaces, FILE* file);
void ClearResultFile(const char* direction);
void AllPut_ToFile(char** pointers_array, int number_of_strings, bool skip_spaces);


int main(int number_of_arguments, char* values_of_arguments[]) {
    bool to_skip_spaces = false;
    if (number_of_arguments == 2) {
        if (!strcmp(values_of_arguments[1], "skip")) {
            to_skip_spaces = true;
        }
    }
    ClearResultFile(DIRECTION);
    long file_size = GetFileSize(SOURCE);
    char* text = GetText(SOURCE, file_size);
    int number_of_strings = GetNumberOfStrings(text);
    char** pointers_array = (char**) calloc(number_of_strings, sizeof(char*));
    CreateArrayOfPointers(text, pointers_array);
    AllPut_ToFile(pointers_array, number_of_strings, to_skip_spaces);
    return 0;
}


void AllPut_ToFile(char** pointers_array, int number_of_strings, bool skip_spaces) {
    assert(pointers_array != NULL);

    FILE *file;
    file = fopen(DIRECTION, "a");

    BubleSort(pointers_array, number_of_strings);
    PutStringArrayToFile(pointers_array, number_of_strings, skip_spaces, file);

    qsort(pointers_array, number_of_strings, sizeof(char*), &CompareStrFromEnd);
    PutStringArrayToFile(pointers_array, number_of_strings, skip_spaces, file);

    BubleSort_PointersArray(pointers_array, number_of_strings);
    PutStringArrayToFile(pointers_array, number_of_strings, false, file);

    fclose(file);
}

void ClearResultFile(const char* direction) {
    assert(direction != NULL);

    FILE *file;
    file = fopen(direction, "w");
    fclose(file);
}


int CreateArrayOfPointers(char* text, char ** pointers_array) { // rename
    assert(text != NULL);
    assert(pointers_array != NULL);

    *pointers_array = text;
    int index_text = 0;
    int index_array = 1;
    while (text[index_text] != '\0') {
        if (text[index_text] == '\n') {
            pointers_array[index_array] = text + (index_text + 1);
            index_array++;
        }
        index_text++;
    }
    return 0;
}

// PutStringArrayToFile
void PutStringArrayToFile(char** pointers_array, int numbers_of_strings, bool skip_spaces, FILE* file) {
    assert(pointers_array != NULL);
    int index_in_string = 0;
    int index_in_pointers = 0;
    char symbol = *(pointers_array[0]);
    while (index_in_pointers <= (numbers_of_strings - 1)) {
        index_in_string = 0;
        symbol = *(pointers_array[index_in_pointers]);
        if (symbol == '\r' && skip_spaces) {
            index_in_pointers++;
            continue;
            }
        while (symbol != '\n' && symbol != '\0') {
            fputc(symbol, file);
            index_in_string++;
            symbol = *(pointers_array[index_in_pointers] + index_in_string);
        }
        index_in_pointers++;
    }   
    for (int index = 0; index < 100 && skip_spaces; index++) {
        fputc('\n', file);
    }
    fputc('\n', file);
    
}