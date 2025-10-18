#include <stddef.h>

typedef struct {
  char *ptr;
  size_t len;
} JosieStringSlice;

void josie_print_slice(JosieStringSlice slice);

char *josie_copy_slice(JosieStringSlice source, char *destination);
