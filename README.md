# utils
A small collection of utils to use in C.

## How to use?
To use `utils.h` correctly, make sure to define this in one of the source files:
```c
#define UTILS_H_IMPLEMENTATION
#include "utils.h"
```
Make sure the `#include` directive is use *afterwards*, that's to ensure one inclusion will generate implementation that automatically generates when this macro is defined.

## Creating modules
To contribute your own module, please copy and adjust `template.h` file for your needs.
