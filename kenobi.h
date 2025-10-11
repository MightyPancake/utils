/*

        general KENOBI

  General quality of life macros :)

*/

#ifndef UTILS_H_KENOBI_H
#define UTILS_H_KENOBI_H

#if defined(UTILS_H_ALL) || defined(UTILS_H_KENOBI) //Avoid defining if module was turned off
//Define types/macros here
#define kenobi_new_struct(NAME, ...) typedef struct NAME{ \
        __VA_ARGS__  \
}NAME

#define kenobi_new_struct_free(NAME, ...) kenobi_new_struct(NAME, __VA_ARGS__); \
void NAME##_free()

#define kenobi_new_enum(NAME, ...) typedef enum NAME{ \
        __VA_ARGS__  \
}NAME

//end of types
#if defined(UTILS_H_IMPLEMENTATION) || defined(UTILS_H_KENOBI_IMPLEMENTATION) //Implementation part only gets compiled once
//Declare variables here

//end of variables
#endif //UTILS_H_KENOBI_IMPLEMENTATION

#endif //UTILS_H_ALL || UTILS_H_KENOBI

#endif //UTILS_H_KENOBI_H
