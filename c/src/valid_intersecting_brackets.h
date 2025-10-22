#include "josieerror.h"
#include "josieresult.h"
#include "josievec.h"
#include <stddef.h>
#include <stdio.h>

JOSIEOPTION(char)
JOSIERESULT(char)
JOSIEITER(char)
JOSIEVEC(char)
JOSIERESULT(bool)

static inline JosieResult_bool valid_intersecting_brackets(const char *input) {
  JosieError result = OK;

  JosieVec_char stack = new_josievec_char();
  bool valid = false;

  for (const char *p = input; *p; p++) {
    char curr = *p;

    if (curr == '(' || curr == '{' || curr == '[' || curr == '<') {
      if (josie_try(push_char(&stack, curr), &result))
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
        // returns an error value but due to knowing invariants it is safe to
        // ignore
        remove_char(&stack, i);
        goto continue_outer;
      }
    }

    // failure case, did not find corresponding bracket
    goto cleanup;

  continue_outer:;
  }

  // if the stack is empty at the end of algorithm then algorithm is successful,
  // if not, it has failed
  valid = stack.len == 0;

cleanup:
  drop_josievec_char(&stack);
  return (JosieResult_bool){.error = result, .result = valid};
}
