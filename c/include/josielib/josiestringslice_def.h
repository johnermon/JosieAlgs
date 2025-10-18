
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char *ptr;
  size_t len;
} josie_string_slice;

void josie_print_slice(josie_string_slice slice) {
  char prev = slice.ptr[slice.len];
  slice.ptr[slice.len] = '\n';
  printf("%s", slice.ptr);
  slice.ptr[slice.len] = prev;
}

char *josie_copy_slice(josie_string_slice source, char *destination) {
  char prev = source.ptr[source.len];
  source.ptr[source.len] = '\n';
  char *output = strcpy(source.ptr, destination);
  source.ptr[source.len] = prev;
  return output;
}
