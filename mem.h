/***********************
  MEM - MEMory utils
 ***********************/

#ifndef UTILS_NO_MEM
#define UTILS_NO_MEM

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

#endif
