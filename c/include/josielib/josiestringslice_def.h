#pragma once

#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char *ptr;
  size_t len;
} josie_string_slice;

void josie_print_slice(josie_string_slice slice) {
  char prev = slice.ptr[slice.len];
  slice.ptr[slice.len] = '\0';
  printf("%s", slice.ptr);
  slice.ptr[slice.len] = prev;
}

char *josie_copy_string_slice(josie_string_slice source, char *destination) {
  char prev = source.ptr[source.len];
  char *output = memcpy(destination, source.ptr, source.len);
  return output;
}
