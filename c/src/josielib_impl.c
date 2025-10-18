#include "josiehelpers.h"
#include "josieoption.h"
#include "josiestringslice.h"
#include "josievec_def.h"

// creates options
OPTION(int)
OPTION(char)

// josievec int is simple data with no drop function
DEFINE_JOSIEVEC(int, drop_noop)
DEFINE_JOSIEVEC(char, drop_noop)
