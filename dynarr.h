#define dynarr_base_type(PT) __typeof__(* ( (PT) 0 ))
#define dynarr_ptr_type(T) __typeof__(T)*

#ifndef dynarr_malloc
  #include <stdlib.h>
  #define dynarr_malloc(S) malloc(S)
#endif

#ifndef dynarr_realloc
  #include <stdlib.h>
  #define dynarr_realloc(P, S) realloc(P, S)
#endif

#ifndef dynarr_memcpy
  #include <string.h>
  #define dynarr_memcpy(D, S, SZ) memcpy(D, S, SZ)
#endif

#ifndef dynarr_bool_t
  #include <stdbool.h>
  #define dynarr_bool_t bool
#endif

#ifndef dynarr_size_t
  #include <stddef.h>
  #define dynarr_size_t size_t
#endif

#ifndef dynarr_len_t
  #define dynarr_len_t dynarr_size_t
#endif

typedef struct dynarr_t{
  dynarr_len_t len;
  dynarr_len_t growth;
  void* ptr;
}dynarr_t;

//Initialize a new empty array
dynarr_t dynarr_init(dynarr_len_t growth){
  return (dynarr_t){
    .len=0,
    .growth=growth,
    .ptr=NULL
  };
}

#define dynarr_calc_cap(L, G) (((((L)-1)/(G))+1)*(G))

//Gets the capacity (number of elements the array can hold)
//of the underlying pointer of array A
//NOTE: The returned value is guaranteed to be at least as big as the actual capability!
#define dynarr_cap(A) dynarr_calc_cap((A).len, (A).growth)

//Resize underlying pointer of array A to size S
#define dynarr_resize(A, S) ((A).ptr = dynarr_realloc((A).ptr, S))

//Check if array A is full and needs resizing for new elements
dynarr_bool_t dynarr_full(dynarr_t arr){
  return arr.len % arr.growth == 0;
}

//Check if array A empty
dynarr_bool_t dynarr_empty(dynarr_t arr){
  return !arr.len;
}

//Create a new array with type T and capacity growth G
#define dynarr_new(T, G) (dynarr_init(G))

//Element of array A of type T at I-th place
#define dynarr_at(T, A, I) (((dynarr_ptr_type(T))((A).ptr))[I])

//Pointer to the element of array A of type T at I-th place
#define dynarr_at_ptr(T, A, I) (&dyn_arr_at(T, A, I))

//Push element E to array A of type T
//Returns length of the array
#define dynarr_push(T, A, E) ({ \
  if (dynarr_full(A)) dynarr_resize(A, sizeof(T)*((A).len+(A).growth)); \
  dynarr_at(T, A, (A).len++) = E; \
  (A).len; \
})

//Pops the last element from array A of type T
#define dynarr_pop(T, A) (dynarr_at(T, A, --((A).len)))

//Inserts an element into array A of type T at index I
//This will automaticall resize it, so it's safe.
//For unsafe version one can use dynarr_at(T, A, I) = E;
#define dynarr_set(T, A, I, E) ({ \
  if (dynarr_cap(A) < dynarr_calc_cap(I+1, (A).growth)){ \
    (A).len = (I)+1; \
    dynarr_resize(A, sizeof(T)*((A).growth)*((I)/((A).growth)+1)); \
  } \
  dynarr_at(T, A, I) = E; \
  E; \
})

//Get the pointer to element of array A of type T at index I.
//Return NULL for index out of range.
#define dynarr_get(T, A, I) ((I) < (A).len ? dynarr_at(T, A, I) : NULL)

//Resizes the underlying pointer of array A of type T to current length
#define dynarr_fit(T, A) dynarr_resize(A, dynarr_cap(A)*sizeof(T))

//Make a dynamic array of type T and growth G from a pointer V of type T
#define dynarr_copy(T, V, G) ({ \
  dynarr_t dynarr_NEW_ARR = dynarr_init(G); \
  dynarr_NEW_ARR.len = sizeof(V)/sizeof(T); \
  dynarr_NEW_ARR.ptr = dynarr_malloc(dynarr_cap(dynarr_NEW_ARR)*sizeof(T)); \
  dynarr_memcpy(dynarr_NEW_ARR.ptr, V, sizeof(V)); \
  dynarr_NEW_ARR; \
})

#define for_dynarr(T, IT, A) for (dynarr_size_t IT ## NUMERIC_ITER = 0; IT ## NUMERIC_ITER < (A).len; IT ## NUMERIC_ITER)

//Free the dynamic array A
#define dynarr_free(A) free((A).ptr)
