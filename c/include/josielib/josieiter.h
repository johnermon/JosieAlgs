#pragma once

#define JOSIEITER(T)                                                           \
  typedef struct JosieIter_##T {                                               \
    T *curr;                                                                   \
    T const *end;                                                              \
  } JosieIter_##T;                                                             \
                                                                               \
  JosieOption_ptr_##T josieiter_next_##T(JosieIter_##T *restrict josieiter);

#define JosieIterate(T, elem, iter)                                            \
  JosieOption_ptr_##T elem = josieiter_next_##T(iter);                         \
  elem.exists;                                                                 \
  elem = josieiter_next_##T(iter)
