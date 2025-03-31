/*

        FIL.h

  Description for FIL.h

*/

#ifndef UTILS_H_FIL_H
#define UTILS_H_FIL_H

#if defined(UTILS_H_ALL) || defined(UTILS_H_FIL) //Avoid defining if module was turned off
//Define types/macros here
#include <stdio.h>
#include <string.h>

size_t read_file_to_string(const char *filename, char **out_string);

//end of types/macros
#if defined(UTILS_H_IMPLEMENTATION) || defined(UTILS_H_FIL_IMPLEMENTATION) //Implementation part only gets compiled once
//Declare variables here
size_t read_file_to_string(const char *filename, char **out_string) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    *out_string = (char *)malloc(size + 1);
    if (!*out_string) {
        perror("Memory allocation failed");
        fclose(file);
        return 0;
    }

    size_t read_size = fread(*out_string, 1, size, file);
    (*out_string)[read_size] = '\0';

    fclose(file);
    return read_size;
}
//end of variables
#endif //UTILS_H_FIL_IMPLEMENTATION

#endif //UTILS_H_ALL || UTILS_H_FIL

#endif //UTILS_H_FIL_H
