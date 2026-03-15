#define UTILS_H_IMPLEMENTATION
#include "utils.h"
#include <stdio.h>

#define test_util_module(M) printf(#M" test:\n"); test_##M();

kenobi_new_struct_free(my_cool_struct,
  int a;
  int b;
  union {
    int  c;
    char d;
  };
  enum {
    my_cool_enum_0,
    my_cool_enum_1,
    my_cool_enum_2,
    my_cool_enum_3
  } e;
);

void test_kenobi(){
  my_cool_struct example = (my_cool_struct){
    .a=1,
    .b=2,
    .c=3,
    .e=my_cool_enum_3
  };
  //Notice how it called before being implemented; macro declares a free function.
  my_cool_struct_free(example);
}

void my_cool_struct_free(my_cool_struct mcs){
  printf("my_cool_struct is now free! Fly high my friend :)\n");
}

void test_darr(){
  // darr arr = darr_new(int, 8);
  darr(int) arr = darr_new(int, .cap=4, .src=(int[]){0,1,2,3});
  for (int i=4; i<10; i++)
    darr_push(arr, i*i);

  //Iterate index and value
  for_darr(i, v, arr)
    printf("%ld: %d\n", i, v);
  
  //Iterate over pointers to elements
  for_darr_elems(v, arr)
    printf("%d\n", *v);
  
  while(darr_len(arr) > 0)
    printf("Popped %d\n", darr_pop(arr));

  darr_free(arr);
}

void test_strus(){
  char* str = strus_copy("Hello");
  strus_cat(str, " World!");
  printf("%s\n", str);
  free(str);

  str = strus_newf("%s world, I like %d' music!", "Hello", 80);
  printf("%s\n", str);
  free(str);

  str = strus_new;
  strus_cat(str, "strus!");
  for_str(i, v, str)
    printf("%d. %c\n", i, v);

  str = strus_copy("ree tree three bree graeree");
  char* pattern = "ree";
  printf("'%s' has %ld '%s'\n", str, strus_count(str, pattern), pattern);

  str = strus_copy("Hello World, cool right?");
  strus_replace(str, "World", "and welcome to string utils");
  strus_replace(str, "string utils", "strus");
  printf("%s\n", str);
}

// #define CLAMP(MIN, VAL, MAX) (VAL < MIN ? MIN : (VAL > MAX ? MAX : VAL))

void test_aesc(){
  //Test colors
  printf("BASIC COLOR SUPPORT:\n");
  printf(aesc_black"black\n");
  printf(aesc_red"red\n");
  printf(aesc_green"green\n");
  printf(aesc_yellow"yellow\n");
  printf(aesc_blue"blue\n");
  printf(aesc_magenta"magenta\n");
  printf(aesc_cyan"cyan\n");
  printf(aesc_white"white\n");
  printf(aesc_default"default\n");
  printf(aesc_reset"reset\n");
  // int red[] = {5,5,5,5,5,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,5,5,5,5};
  // int grn[] = {0,1,2,3,4,5,5,5,5,5,5,5,5,5,5,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0};
  // int blu[] = {0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,5,5,5,5,5,5,5,5,5,5,4,3,2,1};

  // for (int i=0; i<sizeof(red)/sizeof(red[0]); i++){
  //   int r = red[i];
  //   int g = grn[i];
  //   int b = blu[i];
  //   int col = 16 + 36*CLAMP(0, r, 5) + 6*CLAMP(0, g, 5) + CLAMP(0, b, 5);
  //   printf("\x1B[38;5;%dm A_FC(%d),", col, col);
  // }
  printf("TRUE COLOR SUPPORT (RGB WAVE):\n");
  for (int i=0; i<aesc_hue_len; i++){
    printf("%s%d\n", aesc_hue[i], i);
  }
  printf(aesc_reset);
}

int main(){
  //Test kenobi
  test_util_module(kenobi);
  //Test darr
  test_util_module(darr);
	//Test aesc
  test_util_module(aesc);
  //Test strus
  test_util_module(strus);
}
