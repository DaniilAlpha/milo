# milo (micro logging)
Set of (only) macros to get rid of boilerplate logging code.

## example
<p>
    <img src="https://raw.githubusercontent.com/DaniilAlpha/milo/main/example.png" alt="example" />
</p>

## usage example (similar to printf()):
```c
// foo.c

// ...other includes...

#define MILO_LVL MILO_LVL_TRACE /* same as MILO_LVL_ALL */
#include <milo.h>

void foo()
{
    trace("hello trace");
    info("hello info");

    for (int i = 0; i < 3; i++)
        warn("hello warn #%i", i);

    error("hello %s", "error");
    fatal("hello %.5s", "fatal error");
}
```
It is possible to use different `MILO_LVLs` for different files, for example
```c
// bar.c

// ...other includes...

#include "foo.c"

#define MILO_LVL MILO_LVL_ERROR
#include <milo.h>

void bar()
{
    error("hello error"); // will print an error
    info("hello nothing"); // will not do anything
    
    foo(); // will print all messages, as expected
}
```
If you don't want to use text attributes (or they are not working), you can disable them by defining `MILO_USE_TEXT_ATTR` as 0, for example
```c
// main.c

// this is a one-off definition, so it should be before the first include
#define MILO_USE_TEXT_ATTR (0)

// ...other includes...

#include "bar.c"

#include <milo.h>

// ...code...
```
