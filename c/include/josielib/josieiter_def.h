#pragma once

#define DEFINE_JOSIEITER(T)                                                    \
  typedef struct JosieIter_##T {                                               \
    T *curr;                                                                   \
    T const *end;                                                              \
  } JosieIter_##T;                                                             \
                                                                               \
  JosieOption_ptr_##T josieiter_next_##T(                                      \
      JosieIter_##T *restrict josievec_iter) {                                 \
    T *restrict curr = josievec_iter->curr;                                    \
                                                                               \
    if (curr == josievec_iter->end) {                                          \
      josievec_iter->curr = NULL;                                              \
      josievec_iter->end = NULL;                                               \
      return (JosieOption_ptr_##T){.exists = false};                           \
    }                                                                          \
                                                                               \
    josievec_iter->curr++;                                                     \
    return (JosieOption_ptr_##T){.element = curr, .exists = true};             \
  }
