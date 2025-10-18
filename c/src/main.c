#include "josieoption.h"
#include "josievec.h"
#include "valid_intersecting_brackets.h"
#include <stddef.h>
#include <stdio.h>

// import option int and also josievec int
OPTION(int)
JOSIEVEC(int)

int main() {

  printf("Valid intersecting Brackets\n\n");
  const char *brackets[4] = {"{{}<[>]}", "{{", "]]", "<<{>{[}>(}])"};

  for (size_t i = 0; i < 4; i++) {
    const char *string = brackets[i];
    if (valid_intersecting_brackets(string)) {
      printf("%s is a valid input\n", string);
    } else {
      printf("%s is a invalid input\n", string);
    }
  }
  printf("Pushing\n");

  JosieVec_int josievec = new_josievec_int();
  for (int i = 0; i <= 10; i++) {
    push_int(&josievec, i);
    printf("cap is %zu \n", josievec.cap);
  }

  printf("Popping\n");

  for (int i = 0; i <= 14; i++) {
    option_int out = pop_int(&josievec);
    if (out.exists) {
      printf("%d\n", out.element);
    } else {
      printf("Popped none at %d \n", i);
    }
  }

  printf("Dropping\n");
  drop_josievec_int(&josievec);
}
