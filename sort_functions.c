#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>

#include "get_functions.h"
#include "sort_functions.h"

int Strcmp(char* first_string, char* second_string) {
    assert(first_string != NULL);
    assert(second_string != NULL);

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

int CompareStrFromEnd(const void* first_element,
                const void* second_element) {
        assert(first_element != NULL);
        assert(second_element != NULL);
        
         
        char* first_element_of_first_string = * (char**) first_element;
        char* first_element_of_second_string = * (char**) second_element;


        int index = 0, different = 0;
        char* last_element_of_first_string = ReturnLink_ToLastLetter(first_element_of_first_string);
        char* last_element_of_second_string = ReturnLink_ToLastLetter(first_element_of_second_string);
        while ((((size_t) (first_element_of_first_string)) - ((size_t) (last_element_of_first_string - index)) != 0) && (((size_t) (first_element_of_second_string)) - ((size_t) (last_element_of_second_string - index)) != 0)) {
            different = toupper(*(last_element_of_first_string - index)) - toupper(*(last_element_of_second_string - index));
            if (different != 0) {
                return different;
            }
            index++;
        }
        return toupper(*(last_element_of_first_string - index)) - toupper(*(last_element_of_second_string - index));

    }

int BubleSort(char** pointers_array, int number_of_strings) {
    assert(pointers_array != NULL);

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

int BubleSort_PointersArray(char** pointers_array, int number_of_strings) {
    assert(pointers_array != NULL);

    bool was_replaced = true;
    int number_of_cycles_passed = 0;
    int index_of_pointer = 0;
    int different = 0;
    char* buffer = 0;
    while (was_replaced == true) {
        was_replaced = false;
        index_of_pointer = 0;
        while (index_of_pointer <= number_of_strings - 2 - number_of_cycles_passed) {
            different = ((size_t) ((pointers_array[index_of_pointer]))) - ((size_t) ((pointers_array[index_of_pointer + 1])));
            buffer = pointers_array[index_of_pointer];
            if (different > 0) {
                pointers_array[index_of_pointer] = pointers_array[index_of_pointer + 1];
                pointers_array[index_of_pointer + 1] = buffer;
                was_replaced = true;
            }
            index_of_pointer++;
        }
        
        number_of_cycles_passed++;
    }
    return 0;
}