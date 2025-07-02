#define MILO_IMPL

#include "foo.h"

#define MILO_LVL MILO_LVL_ALL  // same as MILO_LVL_ALL
#include <milo.h>

int main() {
    trace("This is a trace.");
    info("This is an info.");
    warn("This is a warning!");
    error("This is an error!!");
    fatal("This is a fatal error!!!");

    foo();

    return 0;
}
