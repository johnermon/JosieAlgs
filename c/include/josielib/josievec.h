#pragma once
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
  JosieVec_##T new_josievec_##T();                                             \
                                                                               \
  void allocate_internal_##T(JosieVec_##T *josievec, size_t cap);              \
                                                                               \
  void drop_josievec_##T(JosieVec_##T *josievec);                              \
                                                                               \
  void grow_ammortized_##T(JosieVec_##T *josievec);                            \
                                                                               \
  JosieVec_##T with_capacity_##T(size_t cap);                                  \
                                                                               \
  void reserve_##T(JosieVec_##T *josievec, size_t elems);                      \
                                                                               \
  void reserve_exact_##T(JosieVec_##T *josievec, size_t elems);                \
                                                                               \
  void push_##T(JosieVec_##T *josievec, T element);                            \
                                                                               \
  option_##T pop_##T(JosieVec_##T *josievec);                                  \
                                                                               \
  option_##T remove_##T(JosieVec_##T *josievec, size_t index);\
