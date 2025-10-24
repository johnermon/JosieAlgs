#pragma once

#define JosieResult(T) JosieResult_##T

#define USE_JOSIERESULT(T)                                                     \
  typedef struct JosieResult_##T {                                             \
    T result;                                                                  \
    JosieError error;                                                          \
  } JosieResult_##T;                                                           \
  typedef struct JosieResult_ptr_##T {                                         \
    T *result;                                                                 \
    JosieError error;                                                          \
  } JosieResult_ptr_##T;
