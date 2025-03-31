/*
                  _   _ _       _     
                 | | (_) |     | |    
            _   _| |_ _| |___  | |__  
           | | | | __| | / __| | '_ \ 
           | |_| | |_| | \__ \_| | | |
            \__,_|\__|_|_|___(_)_| |_|


            Simple utilities for C
                by Filip Krol

    https://github.com/MightyPancake/utils
 
 */

#ifndef UTILS_H
#define UTILS_H
#ifndef UTILS_H_PICK
  #define UTILS_H_ALL
#endif

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

typedef struct darr{
  darr_len_t len;
  darr_len_t growth;
  void* ptr;
}darr;

darr darr_init(darr_len_t growth);
darr_bool_t darr_full(darr arr);
darr_bool_t darr_empty(darr arr);

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

#define darr_base_type(PT) __typeof__(* ( (PT) 0 ))
#define darr_ptr_type(T) __typeof__(T)*

#define darr_calc_cap(L, G) (((((L)-1)/(G))+1)*(G))

//Gets the capacity (number of elements the array can hold)
//of the underlying pointer of array A
//NOTE: The returned value is guaranteed to be at least as big as the actual capability!
#define darr_cap(A) darr_calc_cap((A).len, (A).growth)

//Resize underlying pointer of array A to size S
#define darr_resize(A, S) ((A).ptr = darr_realloc((A).ptr, S))

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
//end of types/macros
#if defined(UTILS_H_IMPLEMENTATION) || defined(UTILS_H_DARR_IMPLEMENTATION) //Implementation part only gets compiled once
//Declare variables here
//Initialize a new empty array
darr darr_init(darr_len_t growth){
  return (darr){
    .len=0,
    .growth=growth,
    .ptr=NULL
  };
}
//Check if array A is full and needs resizing for new elements
darr_bool_t darr_full(darr arr){
  return arr.len % arr.growth == 0;
}

//Check if array A empty
darr_bool_t darr_empty(darr arr){
  return !arr.len;
}

//end of variables
#endif //UTILS_H_DARR_IMPLEMENTATION

#endif //UTILS_H_ALL || UTILS_H_DARR

#endif //UTILS_H_DARR_H
/*
    Shamelessly copied from:
    https://stackoverflow.com/questions/40159892/using-asprintf-on-windows
    reply by Fonic (https://stackoverflow.com/users/1976617/fonic)
    based on reply by 7vujy0f0hy (https://stackoverflow.com/users/6314667/7vujy0f0hy)
*/
#ifndef UTILS_H_ASPRINTF_H
#define UTILS_H_ASPRINTF_H
#if defined(UTILS_H_ALL) || defined(UTILS_H_ASPRINTF) //Avoid defining if module was turned off

#if defined(__GNUC__) && ! defined(_GNU_SOURCE)
#define _GNU_SOURCE /* needed for (v)asprintf, affects '#include <stdio.h>' */
#endif
#include <stdio.h>  /* needed for vsnprintf    */
#include <stdlib.h> /* needed for malloc, free */
#include <stdarg.h> /* needed for va_*         */

/*
 * vscprintf:
 * MSVC implements this as _vscprintf, thus we just 'symlink' it here
 * GNU-C-compatible compilers do not implement this, thus we implement it here
 */
#ifdef _MSC_VER
#define vscprintf _vscprintf
#endif

//end of types
#if defined(UTILS_H_IMPLEMENTATION) || defined(UTILS_H_ASPRINTF_IMPLEMENTATION) //Implementation part only gets compiled once
//Declare variables here
#ifdef __GNUC__
int vscprintf(const char *format, va_list ap)
{
    va_list ap_copy;
    va_copy(ap_copy, ap);
    int retval = vsnprintf(NULL, 0, format, ap_copy);
    va_end(ap_copy);
    return retval;
}
#endif

/*
 * asprintf, vasprintf:
 * MSVC does not implement these, thus we implement them here
 * GNU-C-compatible compilers implement these with the same names, thus we
 * don't have to do anything
 */
#ifdef _MSC_VER
int vasprintf(char **strp, const char *format, va_list ap)
{
    int len = vscprintf(format, ap);
    if (len == -1)
        return -1;
    char *str = (char*)malloc((size_t) len + 1);
    if (!str)
        return -1;
    int retval = vsnprintf(str, len + 1, format, ap);
    if (retval == -1) {
        free(str);
        return -1;
    }
    *strp = str;
    return retval;
}

int asprintf(char **strp, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int retval = vasprintf(strp, format, ap);
    va_end(ap);
    return retval;
}
#endif
//end of variables
#endif //UTILS_H_ASPRINTF_IMPLEMENTATION

#endif //UTILS_H_ALL || UTILS_H_ASPRINTF

#endif // UTILS_H_ASPRINTF_H
/*

        STRing UtilS

  String manipulation and creation

*/

#ifndef UTILS_H_STRUS_H
#define UTILS_H_STRUS_H

#if defined(UTILS_H_ALL) || defined(UTILS_H_STRUS) //Avoid defining if module was turned off
//Define types/macros here
#ifndef strus_byte
	#define strus_byte char
#endif

#ifndef strus_sz
	#include <string.h>
	#define strus_sz size_t
#endif

#ifndef strus_len
	#include <string.h>
	#define strus_len(S) strlen(S)
#endif

#ifndef strus_cmp
	#include <string.h>
	#define strus_cmp(S1, S2) strcmp(S1, S2)
#endif

#ifndef strus_malloc
  #include <stdlib.h>
  #define strus_malloc(S) malloc(S)
#endif

#ifndef strus_realloc
  #include <stdlib.h>
  #define strus_realloc(P, S) realloc(P, S)
#endif

#ifndef strus_memcpy
  #include <string.h>
  #define strus_memcpy(D, S, SZ) memcpy(D, S, SZ)
#endif

#ifndef strus_asprintf
  #define strus_asprintf(D, FMT, ...) asprintf(D, FMT, __VA_ARGS__)
#endif

#ifndef strus_sprintf
  #define strus_sprintf(D, FMT, ...) sprintf(D, FMT, __VA_ARGS__)
#endif

#define strus_index(S, P) ((strus_sz)(strus_sz)(P-S))

#ifndef strus_find_ptr
	#include <string.h>
	#define strus_find_ptr(S, P) strstr(S, P)
#endif

#ifndef strus_find
	#define strus_find(S, P) ({ \
		strus_byte* strus_result = strus_find_ptr(S, P); \
		strus_result == NULL ? -1 : strus_index(S, strus_result); \
	})
#endif

#ifndef strus_err
	#define strus_return strus_returned_value
#endif


#define strus_new ({ \
	strus_byte* strus_result = (strus_byte*)strus_malloc(sizeof(strus_byte)*(1)); \
	strus_result[0] = '\0'; \
	strus_result; \
})

#define strus_newf(FMT, ...) ({ \
	strus_byte* strus_result; \
	strus_return = strus_asprintf(&strus_result, FMT, ##__VA_ARGS__); \
	strus_result; \
})

#define strus_copy(S) ({ \
	strus_sz strus_slen = strus_len(S); \
	strus_byte* strus_result = (strus_byte*)strus_malloc(sizeof(strus_byte)*(strus_slen+1)); \
	strus_memcpy(strus_result, S, sizeof(strus_byte)*(strus_slen+1)); \
	strus_result; \
})

#define strus_eq(S1, S2) (strus_cmp(S1, S2) == 0)

#define strus_cat(D, S) ({ \
	strus_sz strus_dlen = strus_len(D); \
	strus_sz strus_slen = strus_len(S); \
	D = (strus_byte*)strus_realloc(D, sizeof(strus_byte)*(strus_dlen+strus_slen+1)); \
	strus_memcpy(&(D[strus_dlen]), S, sizeof(strus_byte)*(strus_slen+1)); \
	D; \
})

#define for_str(I, V, S) \
	for(int I=0; I<strlen(S); I++) \
	for(int I##_STRUS_FOR_CONTROL=0; I##_STRUS_FOR_CONTROL==0;) \
	for(char V=S[I]; I##_STRUS_FOR_CONTROL==0; I##_STRUS_FOR_CONTROL=1)

#define strus_count(D, P) ({ \
	strus_sz strus_result = 0; \
	strus_byte* strus_lookat = D; \
	while((strus_lookat = strus_find_ptr(strus_lookat, P))){ \
		strus_lookat+=strus_len(P); \
		strus_result++; \
	} \
	strus_result; \
})

#define strus_replace(D, P, S) ({ \
	strus_sz strus_pos = strus_find(D, P); \
	strus_sz strus_D_len; \
	strus_sz strus_P_len; \
	strus_sz strus_S_len; \
	strus_byte* strus_tmp; \
	if (strus_pos){ \
		strus_D_len = strus_len(D); \
		strus_P_len = strus_len(P); \
		strus_S_len = strus_len(S); \
		D[strus_pos] = '\0'; \
		if (strus_P_len<strus_S_len){ \
			strus_tmp = strus_malloc(sizeof(strus_byte)*(strus_D_len+strus_S_len-strus_P_len+1)); \
			strus_sprintf(strus_tmp, "%s%s%s", D, S, &(D[strus_pos+strus_P_len])); \
			free(D); \
			D = strus_tmp; \
		}else{ \
			strus_memcpy(&(D[strus_pos]), S, strus_S_len); \
			for (strus_sz strus_it=strus_pos+strus_S_len; strus_it<strus_D_len+1; strus_it++){ \
				D[strus_it] = D[strus_it+strus_P_len-strus_S_len]; \
			} \
		} \
	} \
	D; \
})

#define strus_switch(S, C1) if (strus_eq(S, C1))
#define strus_case(S, C1) else if (strus_eq(S, C1))

//end of types/macros
#if defined(UTILS_H_IMPLEMENTATION) || defined(UTILS_H_STRUS_IMPLEMENTATION) //Implementation part only gets compiled once
//Declare variables here

int strus_return = 0;

//end of variables
#endif //UTILS_H_STRUS_IMPLEMENTATION

#endif //UTILS_H_ALL || UTILS_H_STRUS

#endif //UTILS_H_STRUS_H
/*

        Ansii ESCape

  Collection of macros for ANSII escape codes for use in terminal programs
  ie. colors, blinking, erasing etc.

*/

#ifndef UTILS_H_AESC_H
#define UTILS_H_AESC_H

#if defined(UTILS_H_ALL) || defined(UTILS_H_AESC) //Avoid defining if module was turned off
//Define types here
#ifndef aesc_size_t
  #include <stdlib.h>
  #define aesc_size_t size_t
#endif

#ifndef aesc_printf
  #include <stdio.h>
  #define aesc_printf(FMT, ...) printf(FMT, ##__VAR_ARGS__)
#endif
#define aesc_do(C) aesc_printf(C)

#define aesc_seq(S) "\x1B"S
#define aesc_style(S) aesc_seq("["S"m")

// Colors
#define aesc_reset aesc_style("0")

#define aesc_black aesc_style("30")
#define aesc_red aesc_style("31")
#define aesc_green aesc_style("32")
#define aesc_yellow aesc_style("33")
#define aesc_blue aesc_style("34")
#define aesc_magenta aesc_style("35")
#define aesc_cyan aesc_style("36")
#define aesc_white aesc_style("37")
#define aesc_default aesc_style("39")

#define aesc_fg_color(V) aesc_seq("[38;5;"#V"m")

//Cursor
#define aesc_home aesc_seq("[H")
#define aesc_mv(X, Y) aesc_seq("[" #X ";" #Y "f")
#define aesc_up(V) aesc_seq("[" #V "A")
#define aesc_down(V) aesc_seq("[" #V "B")
#define aesc_right(V) aesc_seq("[" #V "C")
#define aesc_left(V) aesc_seq("[" #V "D")

//Erase
#define aesc_clear aesc_seq("[J")
#define aesc_erase aesc_seq("[K")

//Map
#define aesc_map(I, S) aesc_seq("[" I ";" S ";p")

//end of types/macros
#if defined(UTILS_H_IMPLEMENTATION) || defined(UTILS_H_AESC_IMPLEMENTATION) //Implementation part only gets compiled once
//Declare variables here
#define A_FC(V) aesc_fg_color(V)
const char* aesc_colors[] = {
  A_FC(0), A_FC(1), A_FC(2), A_FC(3), A_FC(4), A_FC(5), A_FC(6), A_FC(7), A_FC(8), A_FC(9),
  A_FC(10), A_FC(11), A_FC(12), A_FC(13), A_FC(14), A_FC(15), A_FC(16), A_FC(17), A_FC(18), A_FC(19),
  A_FC(20), A_FC(21), A_FC(22), A_FC(23), A_FC(24), A_FC(25), A_FC(26), A_FC(27), A_FC(28), A_FC(29),
  A_FC(30), A_FC(31), A_FC(32), A_FC(33), A_FC(34), A_FC(35), A_FC(36), A_FC(37), A_FC(38), A_FC(39),
  A_FC(40), A_FC(41), A_FC(42), A_FC(43), A_FC(44), A_FC(45), A_FC(46), A_FC(47), A_FC(48), A_FC(49),
  A_FC(50), A_FC(51), A_FC(52), A_FC(53), A_FC(54), A_FC(55), A_FC(56), A_FC(57), A_FC(58), A_FC(59),
  A_FC(60), A_FC(61), A_FC(62), A_FC(63), A_FC(64), A_FC(65), A_FC(66), A_FC(67), A_FC(68), A_FC(69),
  A_FC(70), A_FC(71), A_FC(72), A_FC(73), A_FC(74), A_FC(75), A_FC(76), A_FC(77), A_FC(78), A_FC(79),
  A_FC(80), A_FC(81), A_FC(82), A_FC(83), A_FC(84), A_FC(85), A_FC(86), A_FC(87), A_FC(88), A_FC(89),
  A_FC(90), A_FC(91), A_FC(92), A_FC(93), A_FC(94), A_FC(95), A_FC(96), A_FC(97), A_FC(98), A_FC(99),
  A_FC(100), A_FC(101), A_FC(102), A_FC(103), A_FC(104), A_FC(105), A_FC(106), A_FC(107), A_FC(108), A_FC(109),
  A_FC(110), A_FC(111), A_FC(112), A_FC(113), A_FC(114), A_FC(115), A_FC(116), A_FC(117), A_FC(118), A_FC(119),
  A_FC(120), A_FC(121), A_FC(122), A_FC(123), A_FC(124), A_FC(125), A_FC(126), A_FC(127), A_FC(128), A_FC(129),
  A_FC(130), A_FC(131), A_FC(132), A_FC(133), A_FC(134), A_FC(135), A_FC(136), A_FC(137), A_FC(138), A_FC(139),
  A_FC(140), A_FC(141), A_FC(142), A_FC(143), A_FC(144), A_FC(145), A_FC(146), A_FC(147), A_FC(148), A_FC(149),
  A_FC(150), A_FC(151), A_FC(152), A_FC(153), A_FC(154), A_FC(155), A_FC(156), A_FC(157), A_FC(158), A_FC(159),
  A_FC(160), A_FC(161), A_FC(162), A_FC(163), A_FC(164), A_FC(165), A_FC(166), A_FC(167), A_FC(168), A_FC(169),
  A_FC(170), A_FC(171), A_FC(172), A_FC(173), A_FC(174), A_FC(175), A_FC(176), A_FC(177), A_FC(178), A_FC(179),
  A_FC(180), A_FC(181), A_FC(182), A_FC(183), A_FC(184), A_FC(185), A_FC(186), A_FC(187), A_FC(188), A_FC(189),
  A_FC(190), A_FC(191), A_FC(192), A_FC(193), A_FC(194), A_FC(195), A_FC(196), A_FC(197), A_FC(198), A_FC(199),
  A_FC(200), A_FC(201), A_FC(202), A_FC(203), A_FC(204), A_FC(205), A_FC(206), A_FC(207), A_FC(208), A_FC(209),
  A_FC(210), A_FC(211), A_FC(212), A_FC(213), A_FC(214), A_FC(215), A_FC(216), A_FC(217), A_FC(218), A_FC(219),
  A_FC(220), A_FC(221), A_FC(222), A_FC(223), A_FC(224), A_FC(225), A_FC(226), A_FC(227), A_FC(228), A_FC(229),
  A_FC(230), A_FC(231), A_FC(232), A_FC(233), A_FC(234), A_FC(235), A_FC(236), A_FC(237), A_FC(238), A_FC(239),
  A_FC(240), A_FC(241), A_FC(242), A_FC(243), A_FC(244), A_FC(245), A_FC(246), A_FC(247), A_FC(248), A_FC(249),
  A_FC(250), A_FC(251), A_FC(252), A_FC(253), A_FC(254), A_FC(255), A_FC(256), A_FC(257), A_FC(258), A_FC(259)
};

char* aesc_hue[] = {A_FC(196), A_FC(202), A_FC(208), A_FC(214), A_FC(220), A_FC(226), A_FC(190), A_FC(154), A_FC(118), A_FC(82), A_FC(46), A_FC(47), A_FC(48), A_FC(49), A_FC(50), A_FC(51), A_FC(45), A_FC(39), A_FC(33), A_FC(27), A_FC(21), A_FC(57), A_FC(93), A_FC(129), A_FC(165), A_FC(201), A_FC(200), A_FC(199), A_FC(198), A_FC(197)};
const aesc_size_t aesc_hue_len = (sizeof(aesc_hue)/sizeof(aesc_hue[0]));

#undef A_FC
//end of variables
#endif //UTILS_H_AESC_IMPLEMENTATION

#endif //UTILS_H_ALL || UTILS_H_AESC

#endif //UTILS_H_AESC_H
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
#endif //UTILS.H
