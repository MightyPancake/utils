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
