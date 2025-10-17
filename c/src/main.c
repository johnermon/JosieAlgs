#include "josieoption.h"
#include "josievec.h"
#include <stddef.h>
#include <stdio.h>

OPTION(int)
JOSIEVEC(int)

int main() {

  JosieVec_int josievec = new_josievec_int();
  printf("Pushing\n");

  for (int i = 0; i <= 10; i++) {
    push_int(&josievec, i);
    printf("cap is %zu \n", josievec.cap);
  }

  printf("Popping\n");

  for (int i = 0; i <= 10; i++) {
    option_int out = pop_int(&josievec);
    if (out.exists) {
      printf("%d\n", out.element);
    } else {
      break;
    }
  }

  printf("Dropping\n");
  drop_josievec_int(&josievec);
}
