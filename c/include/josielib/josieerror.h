
#pragma once

#include <stdbool.h>
#include <stdio.h>
typedef enum JosieError { OK, ALLOC_FAIL, OUT_OF_BOUNDS } JosieError;

bool josie_is_error(JosieError error);
