/*

        MEMory

  Set of memory related utilities

*/

#ifndef UTILS_H_MEM_H
#define UTILS_H_MEM_H

#if defined(UTILS_H_ALL) || defined(UTILS_H_MEM) //Avoid defining if module was turned off
//Define types/macros here
#ifndef mem_typeof
  #define mem_typeof(V) __typeof__(V)
#endif

#define mem_base_type(PT) mem_typeof(* ( (PT) 0 ))
#define mem_ptr_type(T) mem_typeof(T)*

#ifndef mem_malloc
  #include <stdlib.h>
  #define mem_malloc(S) malloc(S)
#endif

#define mem_one(T) ((mem_ptr_type(T))mem_malloc(sizeof(T)))

#define mem_one_cpy(V) ({ \
  mem_ptr_type(mem_typeof(V)) MEM_TMP_VAL = mem_one(mem_typeof(V)); \
  *MEM_TMP_VAL = V; \
  MEM_TMP_VAL; \
})

//end of types/macros
#if defined(UTILS_H_IMPLEMENTATION) || defined(UTILS_H_MEM_IMPLEMENTATION) //Implementation part only gets compiled once
//Declare variables here

//end of variables
#endif //UTILS_H_MEM_IMPLEMENTATION

#endif //UTILS_H_ALL || UTILS_H_MEM

#endif //UTILS_H_MEM_H
