#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <malloc.h>
#include <assert.h>

#include "get_functions.h"

char* ReturnLink_ToFirstLetter(char* string) {
    assert(string != NULL);

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

char* ReturnLink_ToLastLetter(char* string) {
    assert(string != NULL);

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

int GetStringLength(char* string) {
    assert(string != NULL);

    int index = 0;
    while (string[index] != '\0' && string[index] != '\n') {
        index++;
    }
    return index;
}

int GetNumberOfStrings(const char* array) {
    assert(array != NULL);

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

long GetFileSize(const char* source) {
    assert(source != NULL);

    const char *filename = source;
    struct stat file_info;
    stat(filename, &file_info);
    return file_info.st_size;
}

char* GetText(const char* source, int file_size) {\
    assert(source != NULL);

    FILE* source_file = fopen(source, "rb" ); // file == NULL
    char* text = (char*) malloc(sizeof(char) * (file_size + 1)); // text == NULL?
    //errno
    //perror strerror
    fread(text, 1, file_size, source_file); 
    //ferror/feof
    fclose (source_file);
    text[file_size] = '\0';
    return text;
}