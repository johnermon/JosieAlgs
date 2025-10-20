#pragma once

#include <stdbool.h>
#include <stdio.h>
typedef enum JosieError { OK, ALLOC_FAIL, OUT_OF_BOUNDS } JosieError;

bool josie_is_error(JosieError error) {
  switch (error) {
  case ALLOC_FAIL:
    fprintf(stderr, "[JosieError] Failed Allocation\n");
    return true;
  case OUT_OF_BOUNDS:
    fprintf(stderr, "[JosieError] Out of Bounds Error\n");
    return true;
  case OK:
    return false;
  }
}
