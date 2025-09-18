#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <malloc.h>


int GetNumberOfStrings(const char* array);
int CreateArrayOfPointers(char* text, char ** pointers_array);
void PutToFile(char** pointers_array, int numbers_of_strings);

int main()
{
    FILE* ptrFile = fopen("small.txt" , "rb" );

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

    printf("%s\n", text);
    printf("Number of strings: %d\n", GetNumberOfStrings(text));
    printf("Number of symbols: %ld\n", lSize);
    pointers_array[2] = pointers_array[0];
    PutToFile(pointers_array, number_of_strings);
}




/* int BubleSort(char* array) {
    array + 1;
    printf("14\n");
    printf("Number of strings: %d\n", GetNumberOfStrings("12\n45\n78\n98\n8988988"));
    return 0;
} */


/* int GetNumberOfStrings(char* array) {
    int index = 0;
    int count = 0;
    while (array[index] != '\0') {
        index++;
        if (array[index] == '\n') {
            count++;
        }
    }
    return (count + 1);
} */

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
    int count = 1;
    const char* link = array;
    while (true) {
        link = strchr(link, '\n');
        if (link == NULL) {  
            return count;
        }
        link = link + 1;
        count++;
    }
}


void PutToFile(char** pointers_array, int numbers_of_strings) {
    FILE *file;
    file = fopen("result.txt", "w");
    int index_in_string = 0;
    int index_in_pointers = 0;
    char symbol = *(pointers_array[0]);
    while (index_in_pointers <= (numbers_of_strings - 1)) {
        index_in_string = 0;
        symbol = *(pointers_array[index_in_string]);
        while (symbol != '\n' && symbol != '\0') {
            fputc(symbol, file);
            index_in_string++;
            symbol = *(pointers_array[index_in_pointers] + index_in_string);
        }
        index_in_pointers++;
}
    fclose(file);
}