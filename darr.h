/*

        Dynamic ARRays

  An implementation of dynamic array

*/

#ifndef UTILS_H_DARR_H
#define UTILS_H_DARR_H

#if defined(UTILS_H_ALL) || defined(UTILS_H_DARR) //Avoid defining if module was turned off
//Define types/macros here

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

typedef struct darr_header {
    darr_size_t len;
    darr_size_t cap;
} darr_header;

#define darr_default_cap 8
#define darr_prefix_sz (sizeof(darr_header))

//Helpers
//Internal check if growth of array A is needed to fit in an extra element and resize if it is.
#define _darr_grow_if_needed(A) do { \
    if (!(A)) darr_init(A); \
    darr_header* _h = darr_get_header(A); \
    if (_h->len >= _h->cap) { \
        darr_size_t _new_cap = _h->cap * 2; \
        darr_resize(A, _new_cap); \
    } \
} while(0)

//Get header from array pointer
#define darr_get_header(A) ((darr_header*)((char*)(A) - darr_prefix_sz))

//Type used in declarations for dynamic array of type T
#define darr(T) T*

//Resize array A to hold NEW_CAP elements
#define darr_resize(A, NEW_CAP) do { \
    darr_header* _h = darr_get_header(A); \
    size_t _new_sz = darr_prefix_sz + (sizeof(*(A)) * (NEW_CAP)); \
    darr_header* _new_h = (darr_header*)realloc(_h, _new_sz); \
    if (_new_h) { \
        _new_h->cap = (NEW_CAP); \
        (A) = (void*)((char*)_new_h + darr_prefix_sz); \
    } \
} while(0)

//Create a new array of type T
#define darr_new(T, ...) ({ \
    struct { darr_size_t cap; darr_size_t len; void* src; } _opt = { \
        .cap = darr_default_cap, \
        .len = 0, \
        .src = NULL, \
        ##__VA_ARGS__ \
    }; \
    if (_opt.cap < _opt.len) _opt.cap = _opt.len; \
    size_t _total_sz = darr_prefix_sz + (sizeof(T) * _opt.cap); \
    darr_header* _raw = (darr_header*)malloc(_total_sz); \
    _raw->len = _opt.len; \
    _raw->cap = _opt.cap; \
    T* _data_ptr = (T*)((char*)_raw + darr_prefix_sz); \
    if (_opt.src) memcpy(_data_ptr, _opt.src, sizeof(T) * _opt.len); \
    _data_ptr; \
})
//Initialize array for variable A
#define darr_init(A) ((A) = darr_new(__typeof__(*(A))))

//Access
//Length of the array
#define darr_len(A) ((A) ? darr_get_header(A)->len : 0)

//Capacity of the array
#define darr_cap(A) ((A) ? darr_get_header(A)->cap : 0)

//Value of first element of the array A
#define darr_first(A) ((A)[0])

//Value of the last element of the array A
#define darr_last(A)  ((A)[darr_len(A) - 1])

//Push / pop
//Push element E to array A
#define darr_push(A, E) ({ \
    _darr_grow_if_needed(A); \
    (A)[darr_get_header(A)->len++] = (E); \
    E; \
})

//Pop element from array A
#define darr_pop(A) ({ \
    darr_get_header(A)->len--; \
    (A)[darr_get_header(A)->len]; \
})

//Free

//Free the array
#define darr_free(A) do { \
    if(A) free(darr_get_header(A)); \
    (A) = NULL; \
} while(0)

#define for_darr(I, E, A) \
  for (darr_size_t I=0; I<darr_len(A); I++) \
  for (int E##_DARR_CONTROL=0;E##_DARR_CONTROL==0;) \
  for (__typeof__((A)[0]) E=(A)[I];E##_DARR_CONTROL==0;E##_DARR_CONTROL=1) \

#define for_darr_elems(V, A) for (__typeof__(A) V = (A); V < (A) + darr_len(A); V++)

//end of types/macros
#if defined(UTILS_H_IMPLEMENTATION) || defined(UTILS_H_DARR_IMPLEMENTATION) //Implementation part only gets compiled once
//Declare variables here

//end of variables
#endif //UTILS_H_DARR_IMPLEMENTATION

#endif //UTILS_H_ALL || UTILS_H_DARR

#endif //UTILS_H_DARR_H
