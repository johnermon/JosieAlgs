#pragma once

#include "josieerror.h"
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
  OPTION(T)                                                                    \
  JOSIERESULT(T)                                                               \
  JOSIERESULT(JosieVec_##T)                                                    \
                                                                               \
  JosieVec_##T new_josievec_##T();                                             \
                                                                               \
  void drop_josievec_##T(JosieVec_##T *josievec);                              \
                                                                               \
  JosieResult_JosieVec_##T with_capacity_##T(size_t cap);                      \
                                                                               \
  JosieError reserve_##T(JosieVec_##T *josievec, size_t elems);                \
                                                                               \
  JosieError reserve_exact_##T(JosieVec_##T *josievec, size_t elems);          \
                                                                               \
  JosieError push_##T(JosieVec_##T *josievec, T element);                      \
                                                                               \
  option_##T pop_##T(JosieVec_##T *josievec);                                  \
                                                                               \
  JosieResult_##T remove_##T(JosieVec_##T *josievec, size_t index);\
