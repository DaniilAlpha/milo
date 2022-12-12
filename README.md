# milo (micro logging)
A set of (only) macros to prevent boilerplate logging code.

Output examples:
<pre>
![output examples](https://raw.githubusercontent.com/DaniilAlpha/milo/main/example.png)
</pre>

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
