#pragma once

#include "josieerror.h"
#include "josieoption.h"
#include "josieresult.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// generic definition for josievec, T is generic type, DROP_FN is the function
// to call on drop.
#define DEFINE_JOSIEVEC(T, DROP_FN)                                            \
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
  JosieVec_##T new_josievec_##T() { return (JosieVec_##T){NULL, 0, 0}; }       \
                                                                               \
  void drop_josievec_##T(JosieVec_##T *josievec) {                             \
    T *ptr = josievec->ptr;                                                    \
    for (size_t i = 0; i < josievec->len; i++)                                 \
      DROP_FN(&ptr[i]);                                                        \
                                                                               \
    free((void *)ptr);                                                         \
    josievec->ptr = NULL;                                                      \
    josievec->len = 0;                                                         \
    josievec->cap = 0;                                                         \
  }                                                                            \
                                                                               \
  JosieError allocate_internal_##T(JosieVec_##T *josievec, size_t cap) {       \
    T *ptr = josievec->ptr;                                                    \
    if (ptr == NULL) {                                                         \
      ptr = malloc(cap * sizeof(T));                                           \
    } else {                                                                   \
      ptr = realloc(ptr, cap * sizeof(T));                                     \
    }                                                                          \
                                                                               \
    if (ptr == NULL)                                                           \
      return ALLOC_FAIL;                                                       \
                                                                               \
    josievec->ptr = ptr;                                                       \
    josievec->cap = cap;                                                       \
    return OK;                                                                 \
  }                                                                            \
                                                                               \
  JosieError grow_ammortized_##T(JosieVec_##T *josievec) {                     \
    JosieError result =                                                        \
        allocate_internal_##T(josievec, next_pw2(josievec->cap));              \
    return result;                                                             \
  }                                                                            \
                                                                               \
  JosieResult_JosieVec_##T with_capacity_##T(size_t cap) {                     \
    JosieVec_##T temp = new_josievec_##T();                                    \
    JosieError result = allocate_internal_##T(&temp, cap);                     \
    return (JosieResult_JosieVec_##T){result, temp};                           \
  }                                                                            \
                                                                               \
  JosieError reserve_##T(JosieVec_##T *josievec, size_t elems) {               \
    size_t elems_reserve = josievec->len + elems;                              \
    if (josievec->cap < elems_reserve) {                                       \
      /*want elems_reserve - 1 here so dont overallocate */ /*when reserving   \
                                                               for exactly     \
                                                               power of two*/  \
      JosieError result =                                                      \
          allocate_internal_##T(josievec, next_pw2(elems_reserve - 1));        \
                                                                               \
      return result;                                                           \
    }                                                                          \
    return OK;                                                                 \
  }                                                                            \
                                                                               \
  JosieError reserve_exact_##T(JosieVec_##T *josievec, size_t elems) {         \
    size_t elems_reserve = josievec->len + elems;                              \
    if (josievec->cap < elems_reserve) {                                       \
      JosieError result = allocate_internal_##T(josievec, elems_reserve);      \
                                                                               \
      return result;                                                           \
    }                                                                          \
    return OK;                                                                 \
  }                                                                            \
                                                                               \
  JosieError push_##T(JosieVec_##T *josievec, T element) {                     \
    if (josievec->len == josievec->cap) {                                      \
      JosieError result = grow_ammortized_##T(josievec);                       \
      if (result != OK)                                                        \
        return result;                                                         \
    }                                                                          \
                                                                               \
    josievec->ptr[josievec->len] = element;                                    \
    josievec->len++;                                                           \
    return OK;                                                                 \
  }                                                                            \
                                                                               \
  option_##T pop_##T(JosieVec_##T *josievec) {                                 \
    if (josievec->len == 0)                                                    \
      return (option_##T){false};                                              \
                                                                               \
    josievec->len--;                                                           \
    return (option_##T){true, josievec->ptr[josievec->len]};                   \
  }                                                                            \
                                                                               \
  JosieResult_##T remove_##T(JosieVec_##T *josievec, size_t index) {           \
    size_t len = josievec->len;                                                \
    T *ptr = josievec->ptr;                                                    \
    if (index >= len)                                                          \
      return (JosieResult_##T){                                                \
          OUT_OF_BOUNDS,                                                       \
      };                                                                       \
                                                                               \
    T out = ptr[index];                                                        \
    size_t tail_len = len - index - 1;                                         \
    memmove(ptr + index, ptr + index + 1, tail_len * sizeof(T));               \
    josievec->len -= 1;                                                        \
    return (JosieResult_##T){OK, out};                                         \
  }\
