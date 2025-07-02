#include "foo.h"

#define MILO_LVL MILO_LVL_WARN
#include <milo.h>

void foo() { warn("This is a warning from another translation unit!"); }
