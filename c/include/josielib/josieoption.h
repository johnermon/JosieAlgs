#pragma once

#include <stdbool.h>

#define JOSIEOPTION(T)                                                         \
                                                                               \
  typedef struct JosieOption_##T {                                             \
    bool exists;                                                               \
    T element;                                                                 \
  } JosieOption_##T;
