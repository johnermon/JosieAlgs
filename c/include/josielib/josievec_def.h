#pragma once

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
  JosieVec_##T new_josievec_##T() { return (JosieVec_##T){NULL, 0, 0}; }       \
                                                                               \
  void allocate_internal_##T(JosieVec_##T *josievec, size_t cap) {             \
    if (josievec->ptr == NULL) {                                               \
      josievec->ptr = (T *)malloc(cap * sizeof(T));                            \
      return;                                                                  \
    }                                                                          \
    josievec->ptr = (T *)realloc((void *){josievec->ptr}, cap);                \
  }                                                                            \
                                                                               \
  void drop_josievec_##T(JosieVec_##T *josievec) {                             \
    for (size_t i = 0; i < josievec->len; i++)                                 \
      DROP_FN(&josievec->ptr[i]);                                              \
                                                                               \
    free((void *){josievec->ptr});                                             \
  }                                                                            \
                                                                               \
  void grow_ammortized_##T(JosieVec_##T *josievec) {                           \
    size_t new_cap = next_pw2(josievec->cap);                                  \
    allocate_internal_##T(josievec, new_cap);                                  \
    josievec->cap = new_cap;                                                   \
  }                                                                            \
                                                                               \
  JosieVec_##T with_capacity_##T(size_t cap) {                                 \
    JosieVec_##T temp = new_josievec_##T();                                    \
    allocate_internal_##T(&temp, cap);                                         \
    return temp;                                                               \
  }                                                                            \
                                                                               \
  void reserve_##T(JosieVec_##T *josievec, size_t elems) {                     \
    size_t elems_reserve = josievec->len + elems;                              \
    if (josievec->cap < elems_reserve) {                                       \
      /*want elems_reserve - 1 here so dont overallocate */                    \
      /*when reserving for exactly power of two*/                              \
      elems_reserve = next_pw2(elems_reserve - 1);                             \
      allocate_internal_##T(josievec, elems_reserve);                          \
      josievec->cap = elems_reserve;                                           \
    }                                                                          \
  }                                                                            \
                                                                               \
  void reserve_exact_##T(JosieVec_##T *josievec, size_t elems) {               \
    size_t elems_reserve = josievec->len + elems;                              \
    if (josievec->cap < elems_reserve) {                                       \
      allocate_internal_##T(josievec, elems_reserve);                          \
      josievec->cap = elems_reserve;                                           \
    }                                                                          \
  }                                                                            \
                                                                               \
  void push_##T(JosieVec_##T *josievec, T element) {                           \
    if (josievec->len == josievec->cap)                                        \
      grow_ammortized_##T(josievec);                                           \
                                                                               \
    josievec->ptr[josievec->len] = element;                                    \
    josievec->len++;                                                           \
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
  option_##T remove_##T(JosieVec_##T *josievec, size_t index) {                \
    if (index > josievec->len) {                                               \
      fprintf(stderr, "Tried to remove past bounds of JosieVec_##T");          \
      return (option_##T){false};                                              \
    }                                                                          \
    T out = josievec->ptr[index];                                              \
    size_t tail_len = josievec->len - index;                                   \
    memmove(josievec->ptr + index, josievec->ptr + index + 1, tail_len);       \
    josievec->len -= 1;                                                        \
    return (option_##T){true, out};                                            \
  }\
