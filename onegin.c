#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <malloc.h>
#include <ctype.h>

#define DIRECTION "result.txt"
#define SOURCE "onegin.txt"


int GetNumberOfStrings(const char* array);
int CreateArrayOfPointers(char* text, char ** pointers_array);
void PutToFile_PointersArray(char** pointers_array, int numbers_of_strings);
int BubleSort(char** pointers_array, int number_of_strings);
char* ReturnLink_ToFirstLetter(char* string);
int CompareStrFromEnd(const void* first_string,
                const void* second_string);
void ClearResultFile(const char* direction);
int Strcmp(char* first_string, char* second_string);
char* ReturnLink_ToLastLetter(char* string);
int GetStringLength(char* string);
int BubleSort_PointersArray(char** pointers_array, int number_of_strings);

int main()
{
    ClearResultFile(DIRECTION);
    FILE* ptrFile = fopen(SOURCE, "rb" );

    fseek(ptrFile , 0 , SEEK_END);                     
    long lSize = ftell(ptrFile);                           
    rewind (ptrFile);                                       


    char* text = (char*) malloc(sizeof(char) * (lSize + 1));
    fread(text, 1, lSize, ptrFile);
    fclose (ptrFile);
    

    int number_of_strings = GetNumberOfStrings(text);

    char** pointers_array = (char**) calloc(number_of_strings, sizeof(char*));


    text[lSize] = '\0';
    CreateArrayOfPointers(text, pointers_array);

    BubleSort(pointers_array, number_of_strings);
    PutToFile_PointersArray(pointers_array, number_of_strings);

    qsort(pointers_array, number_of_strings, sizeof(char*), &CompareStrFromEnd);
    PutToFile_PointersArray(pointers_array, number_of_strings);

    BubleSort_PointersArray(pointers_array, number_of_strings);
    PutToFile_PointersArray(pointers_array, number_of_strings);
}

void ClearResultFile(const char* direction) {
    FILE *file;
    file = fopen(direction, "w");
    fclose(file);
}


char* ReturnLink_ToFirstLetter(char* string) {
    int index = 0;
    char symbol = string[index];
    while (!isalpha(symbol) && symbol != '\n' && symbol != '\0') {
        index++;
        symbol = string[index];
    }
    if (isalpha(symbol)) {
        return string + index;
    }
    return string;

}


int Strcmp(char* first_string, char* second_string) {
    int index = 0, different = 0;
    first_string = ReturnLink_ToFirstLetter(first_string);
    second_string = ReturnLink_ToFirstLetter(second_string);
    while (first_string[index] != '\n' && second_string[index] != '\n') {
        different = toupper(first_string[index]) - toupper(second_string[index]);
        if (different != 0) {
            return different;
        }
        index++;
    }
    return toupper(first_string[index]) - toupper(second_string[index]);
}

int BubleSort(char** pointers_array, int number_of_strings) {
    bool was_replaced = true;
    int number_of_cycles_passed = 0;
    int index = 0;
    int different = 0;
    char* buffer = 0;
    while (was_replaced == true) {
        was_replaced = false;
        index = 0;
        while (index <= number_of_strings - 2 - number_of_cycles_passed) {
            different = Strcmp(pointers_array[index], pointers_array[index + 1]);
            buffer = pointers_array[index];
            if (different > 0) {
                pointers_array[index] = pointers_array[index + 1];
                pointers_array[index + 1] = buffer;
                was_replaced = true;
            }
            index++;
        }
        
        number_of_cycles_passed++;
    }
    return 0;
}

int CreateArrayOfPointers(char* text, char ** pointers_array) {
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



int GetNumberOfStrings(const char* array) {
    int number_of_strings = 1;
    const char* link = array;
    while (true) {
        link = strchr(link, '\n');
        if (link == NULL) {  
            return number_of_strings;
        }
        link = link + 1;
        number_of_strings++;
    }
}

void PutToFile_PointersArray(char** pointers_array, int numbers_of_strings) {
    FILE *file;
    file = fopen("result.txt", "a");
    int index_in_string = 0;
    int index_in_pointers = 0;
    char symbol = *(pointers_array[0]);
    while (index_in_pointers <= (numbers_of_strings - 1)) {
        index_in_string = 0;
        symbol = *(pointers_array[index_in_pointers]);
        while (symbol != '\n' && symbol != '\0') {
            fputc(symbol, file);
            index_in_string++;
            symbol = *(pointers_array[index_in_pointers] + index_in_string);
        }
        index_in_pointers++;
}
    fclose(file);
}

int GetStringLength(char* string) {
    int index = 0;
    while (string[index] != '\0' && string[index] != '\n') {
        index++;
    }
    return index;
}

char* ReturnLink_ToLastLetter(char* string) {
    int index = 0;
    int length = GetStringLength(string);
    char symbol = string[length - 1 - index];
    while (!isalpha(symbol) && (length - 1 - index) != 0) {
        index++;
        symbol = string[length - 1 - index];
    }
    if (isalpha(symbol)) {
        return string + length - 1 - index;
    }
    return string + length - 1;
}


int CompareStrFromEnd(const void* first_element,
                const void* second_element) 
    {
        char* first_element_of_first_string = * (char**) first_element;
        char* first_element_of_second_string = * (char**) second_element;


        int index = 0, different = 0;
        char* first_string = ReturnLink_ToLastLetter(first_element_of_first_string);
        char* second_string = ReturnLink_ToLastLetter(first_element_of_second_string);
        while ((((size_t) (first_element_of_first_string)) - ((size_t) (first_string - index)) != 0) && (((size_t) (first_element_of_second_string)) - ((size_t) (second_string - index)) != 0)) {
            different = toupper(*(first_string - index)) - toupper(*(second_string - index));
            if (different != 0) {
                return different;
            }
            index++;
        }
        return toupper(*(first_string - index)) - toupper(*(second_string - index));

    }


int BubleSort_PointersArray(char** pointers_array, int number_of_strings) {
    bool was_replaced = true;
    int number_of_cycles_passed = 0;
    int index = 0;
    int different = 0;
    char* buffer = 0;
    while (was_replaced == true) {
        was_replaced = false;
        index = 0;
        while (index <= number_of_strings - 2 - number_of_cycles_passed) {
            different = ((size_t) ((pointers_array[index]))) - ((size_t) ((pointers_array[index + 1])));
            buffer = pointers_array[index];
            if (different > 0) {
                pointers_array[index] = pointers_array[index + 1];
                pointers_array[index + 1] = buffer;
                was_replaced = true;
            }
            index++;
        }
        
        number_of_cycles_passed++;
    }
    return 0;
}