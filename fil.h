/***********************
  FIL - FILe utils
 ***********************/

//TODO: Make this more abstract, so it can use other functions than the ones provided by stdio/stdlib/string
 
#ifndef UTILS_NO_FIL
#define UTILS_NO_FIL

#include <stdio.h>
#include <string.h>

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

#endif
