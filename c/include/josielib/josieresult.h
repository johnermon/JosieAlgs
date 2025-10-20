#pragma once

#define JOSIERESULT(T)                                                         \
  typedef struct JosieResult_##T {                                             \
    JosieError error;                                                          \
    T result;                                                                  \
  } JosieResult_##T;
