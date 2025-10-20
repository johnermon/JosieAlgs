#include "josieerror.h"
#include "josievec.h"
#include <stddef.h>
#include <stdio.h>

JOSIEVEC(char)

static inline bool valid_intersecting_brackets(const char *input) {
  JosieVec_char stack = new_josievec_char();
  bool valid;

  for (const char *p = input; *p; p++) {
    char curr = *p;

    if (curr == '(' || curr == '{' || curr == '[' || curr == '<') {
      JosieError result = push_char(&stack, curr);
      if (josie_is_error(result))
        goto cleanup;

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

    // failure case, did not find corresponding bracket
    valid = false;
    goto cleanup;
  continue_outer:;
  }

  // if the stack is empty at the end of algorithm then algorithm is successful,
  // if not, it has failed
  valid = stack.len == 0;

cleanup:
  drop_josievec_char(&stack);
  return valid;
}
