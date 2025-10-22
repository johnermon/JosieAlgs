#pragma once

#define DEFINE_JOSIEITER(T)                                                    \
  typedef struct JosieIter_##T {                                               \
    T *curr;                                                                   \
    T const *end;                                                              \
  } JosieIter_##T;                                                             \
                                                                               \
  JosieOption_ptr_##T josieiter_next_##T(JosieIter_##T *restrict josieiter) {  \
    T *restrict curr = josieiter->curr;                                        \
                                                                               \
    if (curr == josieiter->end) {                                              \
      josieiter->curr = NULL;                                                  \
      josieiter->end = NULL;                                                   \
      return (JosieOption_ptr_##T){.exists = false};                           \
    }                                                                          \
                                                                               \
    josieiter->curr++;                                                         \
    return (JosieOption_ptr_##T){.element = curr, .exists = true};             \
  }
