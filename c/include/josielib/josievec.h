#pragma once

#include "josieerror.h"
#include "josieoption.h"
#include "josieresult.h"

#define JosieVecIterate(T, elem, iter)                                         \
  JosieOption_ptr_##T elem = josievec_iter_next_##T(&iter.result);             \
  elem.exists;                                                                 \
  elem = josievec_iter_next_##T(&iter.result)

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
  typedef struct JosieVecIter_##T {                                            \
    T *curr;                                                                   \
    T const *end;                                                              \
  } JosieVecIter_##T;                                                          \
                                                                               \
  JOSIEOPTION(T)                                                               \
  JOSIERESULT(T)                                                               \
  JOSIERESULT(JosieVec_##T)                                                    \
  JOSIERESULT(JosieVecIter_##T)                                                \
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
  JosieResult_JosieVecIter_##T to_iter_##T(JosieVec_##T *restrict josievec,    \
                                           size_t start, size_t end);          \
                                                                               \
  JosieOption_ptr_##T josievec_iter_next_##T(                                  \
      JosieVecIter_##T *restrict josievec_iter);\
