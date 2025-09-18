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
 
  fseek(ptrFile , 0 , SEEK_END);                          // устанавливаем позицию в конец файла
  long lSize = ftell(ptrFile);                            // получаем размер в байтах
  rewind (ptrFile);                                       // устанавливаем указатель в конец файла
  
 
  char* text = (char*) malloc(sizeof(char) * (lSize + 1)); // выделить память для хранения содержимого файла
  char** pointers_array = (char**) calloc(GetNumberOfStrings(text), sizeof(char*));
  text[lSize] = '\0';
  fread(text, 1, lSize, ptrFile);       // считываем файл в буфер
  CreateArrayOfPointers(text, pointers_array);
 
  //содержимое файла теперь находится в буфере
  puts(text);
 
  fclose (ptrFile);
  printf("%d\n", GetNumberOfStrings(text));
  // printf("%p", pointers_array);
  return 0;
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
        printf("%d\n", index_text);
        if (text[index_text] == '\n') {
            pointers_array[index_array] = text + (index_text + 1);
            index_array++;
        }
        index_text++;
    }
    return 0;
}