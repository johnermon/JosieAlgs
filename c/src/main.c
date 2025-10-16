#include "josielib.h"
#include <stdio.h>

DEFINE_JOSIEVEC(size_t);

int main() {
  JosieVec_size_t josievec = new_josievec_size_t();
  printf("Pushing\n");
  for (size_t i = 0; i <= 10; i++) {
    push_size_t(&josievec, i);
  }

  printf("Popping\n");
  for (int i = 0; i <= 10; i++) {
    option_size_t out = pop_size_t(&josievec);
    if (out.exists) {
      printf("%zu\n", out.element);
    } else {
      break;
    }
  }

  printf("Dropping\n");
  drop_josievec_size_t(&josievec, drop_noop);
}
