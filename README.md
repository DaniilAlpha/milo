# MiLo (Micro Logging)
(Almost) plain macro zero-dependency single-file library to get rid of boilerplate logging code although keet them pretty.

## Output example

Default output looks like this (screen from VSCode terminal):

<p>
  <img src="https://raw.githubusercontent.com/DaniilAlpha/milo/main/example.png" alt="example output" />
</p>

Although, library is fully customizable (see the section below).

## Usage example

### Basic usage

```c
// foo.c

// ...other includes...

#define MILO_LVL MILO_LVL_TRACE // same as MILO_LVL_ALL
#include <milo.h>

void foo() {
  trace("example trace");
  info("example info");

  for (int i = 0; i < 3; i++) 
    warn("example warn #%i", i);

  error("example %s", "error");
  fatal("%10s", "say hello! ignore");
}
```

It is possible to use different `MILO_LVL`s for different files, for example:

```c
// bar.c

// ...other includes...

#include "foo.c"

#define MILO_LVL MILO_LVL_ERROR
#include <milo.h>

void bar() {
  error("example error"); // will print an error
  info("example nothing"); // won't do anything
  foo(); // will print all messages as expected
}
```

By default `MILO_LVL` is `MILO_LVL_INFO`, but can be changed by redefining `MILO_DEFAULT_LVL`.

```c
// this is a one-off definition (see table at the bottom), so it should be before the first include
#define MILO_DEFAULT_LVL MILO_LVL_WARN
```

### Customizing text attributes

If you don't want to use text attributes (or they are not working), you can disable them by defining `MILO_NO_TA`:

```c
// this is also a one-off definition (see table at the bottom), so it should be before the first include
#define MILO_NO_TA
```

Text attributes can also be changed:

```c
// if you don't like some of colors, they can be changed, but only all at once
#define MILO_TA_TRACE ("\e[0;2;36m")  // made slightly faded
#define MILO_TA_INFO  ("\e[0;32m")    // default
#define MILO_TA_WARN  ("\e[0;95m")    // yellow changed to purple
#define MILO_TA_ERROR ("\e[0;31m")    // default
#define MILO_TA_FATAL ("\e[0;1;41m")  // color background instead of text

// be careful not to include parentheses in these two definitions, as they rely on string concatenation
#define MILO_TA_FILE "\e[0;2m"   // default
#define MILO_TA_CLEAR "\e[0;3m"  // all text except level names made italic
```

This will look like this:

<p>
  <img src="https://raw.githubusercontent.com/DaniilAlpha/milo/main/example_custom_ta.png" alt="example output with custom text attributes" />
</p>

### Customizing level names

You can also change level names, for example: 

```c
// if you like to make level names caps, or maybe you dont like abbreviations, you can redefine them but only all at once
#define MILO_LVL_NAME_TRACE ("TRACE")
#define MILO_LVL_NAME_INFO  ("INFO ")
#define MILO_LVL_NAME_WARN  ("WARN ")
#define MILO_LVL_NAME_ERROR ("ERROR")
#define MILO_LVL_NAME_FATAL ("FATAL")
```

### Customizing format

You can even customize format! This is quite complicated, but it is worth it:

```c
// main.c

#include <time.h>

// maybe i wanted timestamp to be included - no problem 
const char *milo_timestamp(const char *const fmt) {
  static char buf[32] = {0};
  static time_t t;

  time(&t);
  strftime(buf, 32, fmt, localtime(&t));
  return buf;
}

#define MILO_TIME (milo_timestamp("%D %H:%M:%S")) // not really nesessary, but makes this mess at least a bit prettier

// be careful not to include parentheses in these two definitions, as they rely on string concatenation
#define MILO_PREFIX_FORMAT \
MILO_TA_CLEAR "\n\e[35m%s" MILO_TA_CLEAR " - %s:%i: %s%s" MILO_TA_CLEAR " in function \e[37m%s" MILO_TA_CLEAR "\n"
#define milo_prefix_args(attr, lvl) \
  MILO_TIME, MILO_FILE, MILO_LINE, (attr), (lvl), MILO_FUNC
```

This will look like this:

<p>
  <img src="https://raw.githubusercontent.com/DaniilAlpha/milo/main/example_custom_format.png" alt="example output with custom format" />
</p>

### Customizing underlying functions

There is an opportunity to change the underlying `printf` and `eprintf` functions by redefining `milo_printf` and `milo_eprintf`:

```c
// this is also a one-off definition
// changes standard `printf` to the `fprintf` into some `logfile`
#define milo_printf(format, ...) fprintf(logfile, format, ##__VA_ARGS__)

// without this line `milo_eprintf` becomes same as `milo_printf`
#define milo_eprintf(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
```

## Recommendation

To manage all one-off definitions, it is recommended to create a separate file and include it at the top of main:

```c
// milo_settings.c

// ...definitions...
```
```c
// main.c

#include "milo_settings.h"

// ...
```

Because all functions `trace`, `info`, `warn`, `error`, `fatal` are actually function-like macros, they will always shadow variables and functions with same names, to MiLo provides a `MILO_USE_SHORTCUTS` definition. This is on by default, but you may change it: 

```c
#define MILO_USE_SHORTCUTS (0)

#include <milo.h>

int check_unwanted_condition() {
  int error = 0;

  if(unwanted_condition) {
    // now functions from milo are called like this
    milo_error("unexpected unwanted condition!"); 
    error = 1;
  }

  // ...

  return error;
}
```

And here is the list of all one-off definitions:
| definition                  | default value                                                  |
| ---                         | ---                                                            |
|`milo_printf(fmt, ...)`      |`printf(fmt, ...)`                                              |
|`milo_eprintf(fmt, ...)`     |`fprintf(stderr, fmt, ...)`                                     |
|`MILO_DEFAULT_LVL`           |`MILO_LVL_INFO`                                                 |
|`MILO_NO_TA`                 | -                                                              |
|`MILO_TA_TRACE`              | clear all, blue                                                |
|`MILO_TA_INFO`               | clear all, green                                               |
|`MILO_TA_WARN`               | clear all, bright yellow                                       |
|`MILO_TA_ERROR`              | clear all, red                                                 |
|`MILO_TA_FATAL`              | clear all, bold, red                                           |
|`MILO_TA_FILE`               | clear all, faded                                               |
|`MILO_TA_CLEAR`              | clear all                                                      |
|`MILO_LVL_NAME_TRACE`        |`"trc"`                                                         |
|`MILO_LVL_NAME_INFO`         |`"inf"`                                                         |
|`MILO_LVL_NAME_WARN`         |`"wrn"`                                                         |
|`MILO_LVL_NAME_ERROR`        |`"err"`                                                         |
|`MILO_LVL_NAME_FATAL`        |`"ftl"`                                                         |
|`MILO_PREFIX_FORMAT`         |`"[{arrt}{lvl}(clearattr) (fileattr){file}:{line}(clearattr)] "`|
|`milo_prefix_args(attr, lvl)`|`attr, lvl, MILO_FILE, MILO_LINE`                               |
|`MILO_USE_SHORTCUTS`         |`1`                                                             |