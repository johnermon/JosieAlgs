#pragma once

#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char *ptr;
  size_t len;
} josie_string_slice;

void josie_print_str_slice(josie_string_slice *str) {
  fwrite(str->ptr, str->len, 1, stdout);
}

char *josie_copy_string_slice(josie_string_slice source, char *destination) {
  char prev = source.ptr[source.len];
  return memcpy(destination, source.ptr, source.len);
}
