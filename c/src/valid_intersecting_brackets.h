#import "josieoption.h"
#import "josiestringslice.h"
#import "josievec.h"
#include <stddef.h>
#include <stdio.h>

OPTION(char)
JOSIEVEC(char)

static inline bool valid_intersecting_brackets(const char *input) {
  JosieVec_char stack = new_josievec_char();
  bool result = false;
  for (const char *p = input; *p; p++) {
    char curr = *p;

    if (curr == '(' || curr == '{' || curr == '[' || curr == '<') {
      push_char(&stack, curr);
      continue;
    }

    char open;
    switch (curr) {
    case ')':
      open = '(';
      break;
    case '}':
      open = '{';
      break;
    case ']':
      open = '[';
      break;
    case '>':
      open = '<';
      break;
    default:
      continue;
    }

    for (size_t i = stack.len; i-- > 0;) {
      char character = stack.ptr[i];
      if (character == open) {
        remove_char(&stack, i);
        goto continue_outer;
      }
    }

    goto cleanup;
  continue_outer:;
  }

  result = stack.len == 0;
cleanup:

  drop_josievec_char(&stack);
  return result;
}
