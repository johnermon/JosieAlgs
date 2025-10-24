#pragma once

#include <stdbool.h>

#define JosieOption(T) JosieOption_##T

#define USE_JOSIEOPTION(T)                                                     \
                                                                               \
  typedef struct JosieOption_##T {                                             \
    T element;                                                                 \
    bool exists;                                                               \
  } JosieOption_##T;                                                           \
  typedef struct JosieOption_ptr_##T {                                         \
    T *element;                                                                \
    bool exists;                                                               \
  } JosieOption_ptr_##T;
