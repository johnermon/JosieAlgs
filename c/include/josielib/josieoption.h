#include <stdbool.h>

#define OPTION(T)                                                              \
                                                                               \
  typedef struct {                                                             \
    bool exists;                                                               \
    union {                                                                    \
      T element;                                                               \
      unsigned char raw[sizeof(T)];                                            \
    };                                                                         \
  } option_##T;
