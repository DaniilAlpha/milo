#define MILO_IMPL

#include "foo.h"

#define MILO_LVL MILO_LVL_ALL  // same as MILO_LVL_ALL
#include <milo.h>

int main() {
  trace("hello!!");

  foo();

  return 0;
}
