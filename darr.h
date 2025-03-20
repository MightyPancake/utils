/***********************
  DARR - Dynamic ARRays
 ***********************/

#ifndef UTILS_NO_DARR
#define darr_base_type(PT) __typeof__(* ( (PT) 0 ))
#define darr_ptr_type(T) __typeof__(T)*

#ifndef darr_malloc
  #include <stdlib.h>
  #define darr_malloc(S) malloc(S)
#endif

#ifndef darr_realloc
  #include <stdlib.h>
  #define darr_realloc(P, S) realloc(P, S)
#endif

#ifndef darr_memcpy
  #include <string.h>
  #define darr_memcpy(D, S, SZ) memcpy(D, S, SZ)
#endif

#ifndef darr_bool_t
  #include <stdbool.h>
  #define darr_bool_t bool
#endif

#ifndef darr_size_t
  #include <stddef.h>
  #define darr_size_t size_t
#endif

#ifndef darr_len_t
  #define darr_len_t darr_size_t
#endif

typedef struct darr{
  darr_len_t len;
  darr_len_t growth;
  void* ptr;
}darr;

//Initialize a new empty array
darr darr_init(darr_len_t growth){
  return (darr){
    .len=0,
    .growth=growth,
    .ptr=NULL
  };
}

#define darr_calc_cap(L, G) (((((L)-1)/(G))+1)*(G))

//Gets the capacity (number of elements the array can hold)
//of the underlying pointer of array A
//NOTE: The returned value is guaranteed to be at least as big as the actual capability!
#define darr_cap(A) darr_calc_cap((A).len, (A).growth)

//Resize underlying pointer of array A to size S
#define darr_resize(A, S) ((A).ptr = darr_realloc((A).ptr, S))

//Check if array A is full and needs resizing for new elements
darr_bool_t darr_full(darr arr){
  return arr.len % arr.growth == 0;
}

//Check if array A empty
darr_bool_t darr_empty(darr arr){
  return !arr.len;
}

//Create a new array with type T and capacity growth G
#define darr_new(T, G) (darr_init(G))

//Element of array A of type T at I-th place
#define darr_at(T, A, I) (((darr_ptr_type(T))((A).ptr))[I])

//First element of array A of type T
#define darr_first(T, A) darr_at(T, A, 0)

//Last element of array A of type T
#define darr_last(T, A) darr_at(T, A, (A).len-1)

//Pointer to the element of array A of type T at I-th place
#define darr_at_ptr(T, A, I) (&dyn_arr_at(T, A, I))

//Push element E to array A of type T
//Returns length of the array
#define darr_push(T, A, E) ({ \
  if (darr_full(A)) darr_resize(A, sizeof(T)*((A).len+(A).growth)); \
  darr_at(T, A, (A).len++) = E; \
  (A).len; \
})

//Pops the last element from array A of type T
#define darr_pop(T, A) (darr_at(T, A, --((A).len)))

//Inserts an element into array A of type T at index I
//This will automaticall resize it, so it's safe.
//For unsafe version one can use darr_at(T, A, I) = E;
#define darr_set(T, A, I, E) ({ \
  if (darr_cap(A) < darr_calc_cap(I+1, (A).growth)){ \
    (A).len = (I)+1; \
    darr_resize(A, sizeof(T)*((A).growth)*((I)/((A).growth)+1)); \
  } \
  darr_at(T, A, I) = E; \
  E; \
})

//Get the pointer to element of array A of type T at index I.
//Return NULL for index out of range.
#define darr_get(T, A, I) ((I) < (A).len ? darr_at(T, A, I) : NULL)

//Resizes the underlying pointer of array A of type T to current length
#define darr_fit(T, A) darr_resize(A, darr_cap(A)*sizeof(T))

//Make a dynamic array of type T and growth G from a pointer V of type T
#define darr_copy(T, V, G) ({ \
  darr darr_NEW_ARR = darr_init(G); \
  darr_NEW_ARR.len = sizeof(V)/sizeof(T); \
  darr_NEW_ARR.ptr = darr_malloc(darr_cap(darr_NEW_ARR)*sizeof(T)); \
  darr_memcpy(darr_NEW_ARR.ptr, V, sizeof(V)); \
  darr_NEW_ARR; \
})

#define for_darr(I, T, E, A) \
  for (darr_size_t I=0; I<(A).len; I++) \
  for (int E##_DARR_CONTROL=0;E##_DARR_CONTROL==0;) \
  for (T E=darr_at(T, A, I);E##_DARR_CONTROL==0;E##_DARR_CONTROL=1) \

#define for_darr_elems(T, V, A) for (darr_ptr_type(T) V=(A).ptr; V<=&darr_last(T, A); V++)

//Free the dynamic array A
#define darr_free(A) free((A).ptr)

#endif
