#include <stdbool.h>

#define OPTION(T)                                                              \
                                                                               \
  typedef struct {                                                             \
    bool exists;                                                               \
    T element;                                                                 \
  } option_##T;
