#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <malloc.h>


int GetNumberOfStrings(char* array);
int CreateArrayOfPointers(char* text, char ** pointers_array);

int main()
{
    FILE* ptrFile = fopen("small.txt" , "rb" );

    fseek(ptrFile , 0 , SEEK_END);                     
    long lSize = ftell(ptrFile);                           
    rewind (ptrFile);                                       


    char* text = (char*) malloc(sizeof(char) * (lSize + 1));
    fread(text, 1, lSize, ptrFile);
    fclose (ptrFile);
    char** pointers_array = (char**) calloc(GetNumberOfStrings(text), sizeof(char*));


    text[lSize] = '\0';
    CreateArrayOfPointers(text, pointers_array);

    printf("%s\n", text);
    printf("Number of strings: %d\n", GetNumberOfStrings(text));
    printf("Number of symbols: %ld\n", lSize);
}




/*int BubleSort(char* array) {
    array + 1;
    return 0;
}*/


int GetNumberOfStrings(char* array) {
    int index = 0;
    int count = 0;
    while (array[index] != '\0') {
        index++;
        if (array[index] == '\n') {
            count++;
        }
    }
    return (count + 1);
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