#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <sys/stat.h>

#include "sort_functions.h"
#include "get_functions.h"


const char* SOURCE = "onegin.txt";
const char* DIRECTION = "result.txt";


int CreateArrayOfPointers(char* text, char ** pointers_array);
void PutToFile_PointersArray(char** pointers_array, int numbers_of_strings, bool skip_spaces);
void ClearResultFile(const char* direction);
void AllPut_ToFile(char** pointers_array, int number_of_strings, bool skip_spaces);


int main()
{
    ClearResultFile(DIRECTION);
    long file_size = GetFileSize(SOURCE);
    char* text = GetText(SOURCE, file_size);
    int number_of_strings = GetNumberOfStrings(text);
    char** pointers_array = (char**) calloc(number_of_strings, sizeof(char*));
    CreateArrayOfPointers(text, pointers_array);
    AllPut_ToFile(pointers_array, number_of_strings, true);
    return 0;
}


void AllPut_ToFile(char** pointers_array, int number_of_strings, bool skip_spaces) {
    assert(pointers_array != NULL);

    BubleSort(pointers_array, number_of_strings);
    PutToFile_PointersArray(pointers_array, number_of_strings, skip_spaces);

    qsort(pointers_array, number_of_strings, sizeof(char*), &CompareStrFromEnd);
    PutToFile_PointersArray(pointers_array, number_of_strings, skip_spaces);

    BubleSort_PointersArray(pointers_array, number_of_strings);
    PutToFile_PointersArray(pointers_array, number_of_strings, false);
}

void ClearResultFile(const char* direction) {
    assert(direction != NULL);

    FILE *file;
    file = fopen(direction, "w");
    fclose(file);
}


int CreateArrayOfPointers(char* text, char ** pointers_array) {
    assert(text != NULL);
    assert(pointers_array != NULL);

    *pointers_array = text;
    int index_text = 0;
    int index_array = 1;
    while (text[index_text] != '\0') {
        if (text[index_text] == '\n') {
            pointers_array[index_array] = text + (index_text + 1);
            index_array++;
            text[index_text] = '\n';
        }
        index_text++;
    }
    return 0;
}


void PutToFile_PointersArray(char** pointers_array, int numbers_of_strings, bool skip_spaces) {
    assert(pointers_array != NULL);

    FILE *file;
    file = fopen(DIRECTION, "a");
    int index_in_string = 0;
    int index_in_pointers = 0;
    char symbol = *(pointers_array[0]);
    while (index_in_pointers <= (numbers_of_strings - 1)) {
        index_in_string = 0;
        symbol = *(pointers_array[index_in_pointers]);
        if ((int) symbol == 13 && skip_spaces) {
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
    fclose(file);
}