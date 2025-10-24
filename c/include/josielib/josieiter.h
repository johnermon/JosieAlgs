#pragma once

#define JosieIter(T) JosieIter_##T

#define USE_JOSIEITER(T)                                                       \
  typedef struct JosieIter_##T {                                               \
    T *curr;                                                                   \
    T const *end;                                                              \
  } JosieIter_##T;                                                             \
                                                                               \
  JosieOption_ptr_##T josieiter_next_##T(JosieIter_##T *restrict josieiter);

#define JosieIterate(T, elem, next_fn)                                         \
  JosieOption_ptr_##T elem = next_fn;                                          \
  elem.exists;                                                                 \
  elem = next_fn
