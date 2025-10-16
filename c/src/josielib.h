#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef void (*drop_type)(void *);

static inline void drop_noop(void *ptr) { (void)ptr; }

static inline size_t clz_size(size_t x) {
  if (x == 0) {
    return (size_t)(8 * sizeof(size_t));
  }
#if SIZE_MAX == 0xFFFFFFFFu
  return (size_t)__builtin_clz((size_t)x);
#elif SIZE_MAX == 0xFFFFFFFFFFFFFFFFull
  return (size_t)__builtin_clzll((size_t)x);
#else
  error "unsupported width"
#endif
}

#define DEFINE_JOSIEVEC(T)                                                     \
                                                                               \
  typedef struct {                                                             \
    T *ptr;                                                                    \
    size_t len;                                                                \
    size_t cap;                                                                \
  } JosieVec_##T;                                                              \
                                                                               \
  JosieVec_##T new_josievec_##T() { return (JosieVec_##T){NULL, 0, 0}; }       \
                                                                               \
  static inline void allocate_internal_##T(JosieVec_##T *josievec,             \
                                           size_t cap) {                       \
    if (josievec->ptr == NULL) {                                               \
      josievec->ptr = (T *)malloc(cap * sizeof(T));                            \
      return;                                                                  \
    }                                                                          \
    josievec->ptr = (T *)realloc((void *){josievec->ptr}, cap);                \
  }                                                                            \
                                                                               \
  static inline void drop_josievec_##T(JosieVec_##T *josievec,                 \
                                       drop_type drop) {                       \
    for (size_t i = 0; i < josievec->len; i++) {                               \
      drop(&josievec->ptr[i]);                                                 \
    }                                                                          \
    free((void *){josievec->ptr});                                             \
  }                                                                            \
                                                                               \
  static inline void grow_ammortized_##T(JosieVec_##T *josievec) {             \
    size_t new_cap = clz_size(josievec->cap);                                  \
    allocate_internal_##T(josievec, new_cap);                                  \
  }                                                                            \
                                                                               \
  static inline JosieVec_##T with_capacity_##T(size_t cap) {                   \
    JosieVec_##T temp = new_josievec_##T();                                    \
    allocate_internal_##T(&temp, cap);                                         \
    return temp;                                                               \
  }                                                                            \
                                                                               \
  static inline void reserve_##T(JosieVec_##T *josievec, size_t elems) {       \
    size_t elems_reserve = josievec->len + elems;                              \
    while (elems_reserve > josievec->cap) {                                    \
      grow_ammortized_##T(josievec);                                           \
    }                                                                          \
  }                                                                            \
                                                                               \
  static inline void reserve_exact_##T(JosieVec_##T *josievec, size_t elems) { \
    size_t elems_reserve = josievec->len + elems;                              \
    if (elems_reserve > josievec->cap) {                                       \
      allocate_internal_##T(josievec, elems_reserve);                          \
    }                                                                          \
  }                                                                            \
                                                                               \
  static inline void push_##T(JosieVec_##T *josievec, T element) {             \
    if (josievec->len == josievec->cap) {                                      \
      grow_ammortized_##T(josievec);                                           \
    }                                                                          \
    josievec->ptr[josievec->len] = element;                                    \
    josievec->len++;                                                           \
  }                                                                            \
                                                                               \
  typedef struct {                                                             \
    bool exists;                                                               \
    union {                                                                    \
      T element;                                                               \
      unsigned char raw[sizeof(T)];                                            \
    };                                                                         \
  } option_##T;                                                                \
                                                                               \
  static inline option_##T pop_##T(JosieVec_##T *josievec) {                   \
    if (josievec->len == 0) {                                                  \
      return (option_##T){false};                                              \
    }                                                                          \
    josievec->len--;                                                           \
    return (option_##T){true, josievec->ptr[josievec->len]};                   \
  }\
