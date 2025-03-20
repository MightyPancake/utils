/***********************
  STRUS - STRing UtilS
 ***********************/

#ifndef UTILS_NO_STRUS

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

#define strus_new(S) ({ \
	strus_sz strus_slen = strus_len(S); \
	strus_byte* strus_result = (strus_byte*)strus_malloc(sizeof(strus_byte)*(strus_slen+1)); \
	strus_memcpy(strus_result, S, sizeof(strus_byte)*(strus_slen+1)); \
	strus_result; \
})

#define strus_cat(D, S) ({ \
	strus_sz strus_dlen = strus_len(D); \
	strus_sz strus_slen = strus_len(S); \
	D = (strus_byte*)strus_realloc(D, sizeof(strus_byte)*(strus_dlen+strus_slen+1)); \
	strus_memcpy(&(D[strus_dlen]), S, sizeof(strus_byte)*(strus_slen+1)); \
	D; \
})

#endif

