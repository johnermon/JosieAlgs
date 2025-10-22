#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// drop noop is for when you want to initialize josievec without any drop code
// for trivial types

static void drop_noop(void *ptr) { (void)ptr; }

// calculates the next power of two greater than input
static size_t next_pw2(size_t x) {
  if (x == 0)
    return 1;

#if SIZE_MAX == 0xFFFFFFFFu
  return (size_t)(1 << (32 - __builtin_clz(x)));
#elif SIZE_MAX == 0xFFFFFFFFFFFFFFFFull
  return (size_t)(1 << (64 - __builtin_clzll(x)));
#else
  error "unsupported width"
#endif
}
