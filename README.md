# milo (micro logging)
A set of macros to prevent boilerplate logging code.

Format examples:
"[foo.c:76 <span style="color:red">error</span>] hello foo"
"[bar.c:54 <span style="color:yellow">warn</span>] hello foo"
"[main.c:32 <span style="color:green">info</span>] hello world"
"[qux_quux.h:10 <span style="color:blue">trace</span>] hello qux and quux"

Usage example (similar to printf()):
```c
// foo.c

// ...other includes...

#define MILO_LVL MILO_ALL
#include <milo.h>

int foo()
{
    trace("hello trace");
    info("hello info");

    for (int i = 0; i < 3; i++)
        warn("hello warn #%i", i);

    error("hello %s", "error");
    fatal("hello %.5s", "fatality");
}
```

It is possible to use different `MILO_LVL`s for different files, for example:
```c
// bar.c

// ...other includes...
#include "foo.c"

#define MILO_LVL MILO_ERROR
#include <milo.h>

void bar()
{
    foo(); // will print all messages
    error("hello bar"); // will print an error
    info("hello foo"); // will not do anything
}
```
