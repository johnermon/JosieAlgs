#pragma once

#include <stdbool.h>
#include <stdio.h>
typedef enum JosieError { OK, ALLOC_FAIL, OUT_OF_BOUNDS } JosieError;

static const inline bool josie_is_error(JosieError error) {
  return error != OK;
};

int josie_handle_error(JosieError error) {
  switch (error) {
  case ALLOC_FAIL:
    fprintf(stderr, "[JosieError] Failed Allocation\n");
    return 1;
  case OUT_OF_BOUNDS:
    fprintf(stderr, "[JosieError] Out of Bounds Error\n");
    return 2;
  case OK:
    return 0;
  }
}
