#pragma once

#include "josieerror.h"
#include "josieiter.h"
#include "josieoption.h"
#include "josieresult.h"

// generic definition for josievec, T is generic type, DROP_FN is the function
// to call on drop.
#define JOSIEVEC(T)                                                            \
                                                                               \
  typedef struct {                                                             \
    T *ptr;                                                                    \
    size_t len;                                                                \
    size_t cap;                                                                \
  } JosieVec_##T;                                                              \
                                                                               \
  JOSIERESULT(JosieVec_##T)                                                    \
  JOSIERESULT(JosieIter_##T)                                                   \
                                                                               \
  JosieVec_##T static const inline new_josievec_##T() {                        \
    return (JosieVec_##T){.ptr = NULL, .len = 0, .cap = 0};                    \
  }                                                                            \
                                                                               \
  void drop_josievec_##T(JosieVec_##T *restrict josievec);                     \
                                                                               \
  JosieResult_JosieVec_##T with_capacity_##T(size_t cap);                      \
                                                                               \
  JosieError reserve_##T(JosieVec_##T *restrict josievec, size_t elems);       \
                                                                               \
  JosieError reserve_exact_##T(JosieVec_##T *restrict josievec, size_t elems); \
                                                                               \
  JosieError push_##T(JosieVec_##T *restrict josievec, T element);             \
                                                                               \
  JosieOption_##T pop_##T(JosieVec_##T *restrict josievec);                    \
                                                                               \
  JosieResult_##T remove_##T(JosieVec_##T *restrict josievec, size_t index);   \
                                                                               \
  JosieResult_JosieIter_##T josievec_to_iter_##T(                              \
      JosieVec_##T *restrict josievec, size_t start, size_t end);
\
