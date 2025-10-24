#include "josieerror.h"
#include "josieoption.h"
#include "josieresult.h"
#include "josievec.h"
#include "valid_intersecting_brackets.h"
#include <stddef.h>
#include <stdio.h>

USE_JOSIEOPTION(int)
USE_JOSIERESULT(int)
USE_JOSIEITER(int)
USE_JOSIEVEC(int)

int main() {
  JosieError result = OK;

  printf("Valid intersecting Brackets\n\n");
  const char *brackets[4] = {"{{}<[>]}", "{{", "]]", "<<{>{[}>(}])"};

  for (size_t i = 0; i < 4; i++) {
    const char *string = brackets[i];
    JosieResult(bool) output = valid_intersecting_brackets(string);
    if (josie_try(output.error, &result))
      goto end;

    if (output.result)
      printf("%s is a valid input\n", string);
    else
      printf("%s is a invalid input\n", string);
  }

  printf("Pushing\n");

  JosieVec(int) josievec = new_josievec_int();

  for (int i = 0; i <= 10; i++) {
    if (josie_try(push_int(&josievec, i), &result))
      goto cleanup;

    printf("cap is %zu \n", josievec.cap);
  }

  printf("Iterator\n");

  JosieResult(JosieIter_int) iter;
  if (iter = josievec_to_iter_int(&josievec, 0, josievec.len),
      josie_try(iter.error, &result))

    goto cleanup;

  for (JosieIterate(int, elem, josieiter_next_int(&iter.result)))
    printf("iterating! %d \n", *elem.element);

cleanup:
  drop_josievec_int(&josievec);
end:
  return josie_handle_error(result);
}
