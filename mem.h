/***********************
  MEM - MEMory utils
 ***********************/

#ifndef UTILS_NO_MEM
#define UTILS_NO_MEM
#define mem_base_type(PT) __typeof__(* ( (PT) 0 ))
#define mem_ptr_type(T) __typeof__(T)*

#ifndef mem_malloc
  #include <stdlib.h>
  #define mem_malloc(S) malloc(S)
#endif

#define mem_one(T) ((mem_ptr_type(T))mem_malloc(sizeof(mem_ptr_type(T))))

#endif
