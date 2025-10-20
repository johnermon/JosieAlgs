#pragma once

#include <stdbool.h>

#define OPTION(T)                                                              \
                                                                               \
  typedef struct option_##T {                                                  \
    bool exists;                                                               \
    T element;                                                                 \
  } option_##T;
