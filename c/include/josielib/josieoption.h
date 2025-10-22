#pragma once

#include <stdbool.h>

#define JOSIEOPTION(T)                                                         \
                                                                               \
  typedef struct JosieOption_##T {                                             \
    T element;                                                                 \
    bool exists;                                                               \
  } JosieOption_##T;                                                           \
  typedef struct JosieOption_ptr_##T {                                         \
    T *element;                                                                \
    bool exists;                                                               \
  } JosieOption_ptr_##T;
