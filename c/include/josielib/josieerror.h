
#pragma once

#include <stdbool.h>
#include <stdio.h>
typedef enum JosieError { OK, ALLOC_FAIL, OUT_OF_BOUNDS } JosieError;

int josie_handle_error(JosieError error);

static const inline bool josie_is_error(JosieError error) {
  return error != OK;
};
