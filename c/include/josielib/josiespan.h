#pragma once

#include <stddef.h>

#define JOSIESPAN(T)                                                           \
  typedef struct {                                                             \
    T *ptr;                                                                    \
    size_t len;                                                                \
  } josiespan_##T;\
