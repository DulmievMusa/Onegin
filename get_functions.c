#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <malloc.h>
#include <assert.h>

#include "get_functions.h"

char* ReturnLink_ToFirstLetter(char* string) { // TODO: weird naming?
    assert(string != NULL);

    int index = 0;
    char symbol = string[index];
    while (!isalpha(symbol) && symbol != '\n' && symbol != '\0') { // TODO: why stop at '\n', this behaviour isn't obvious
        index++;
        symbol = string[index];
    }
    if (isalpha(symbol)) {
        return string + index;
    }
    return string;

}

char* ReturnLink_ToLastLetter(char* string) { // TODO: you can take in direction flag which shows direction (i.e. direction = -1, +1)
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

int GetStringLength(char* string) { // TODO: get _line_ length
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
    while (true) { // NOTE: improve control-flow
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

char* GetText(const char* source, int file_size) {
    assert(source != NULL);

    FILE* source_file = fopen(source, "rb" ); // file == NULL // TODO: why rb? explain // TODO: also, yeah, check for errors everywhere
    char* text = (char*) malloc(sizeof(char) * (file_size + 1)); // TODO: text == NULL? + calloc
    //errno
    //perror strerror
    fread(text, 1, file_size, source_file); 
    //ferror/feof
    fclose (source_file);
    text[file_size] = '\0';
    return text;
}