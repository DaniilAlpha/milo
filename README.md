# MiLo (Micro Logging)

Plain macro zero-dependency single-file library to get rid of complex logging libraries and boilerplate logging code while keeping logs pretty.


## Output example

Default output looks like this (screen from VSCode terminal):

![example output](https://raw.githubusercontent.com/DaniilAlpha/milo/main/example.png)

Though the library is [highly customizable](#customization).


## Usage example

### Basic usage

```c
// foo.c

// ...other includes...

#include <milo.h>

void foo() {
  trace("won't show because of default logging level");
  info("example info");

  for (int i = 0; i < 3; i++) 
    warn("example warn #%i", i);

  error("example %s", "error");
  fatal("%10s", "say hello! the rest is ignored");
}
```

Default logging level is set to `info`, but you can modify it by redefining `MILO_DEFAULT_LVL` at the build level. More on this below.


### Different log levels for different translation units

It is possible to use different logging levels for different files, for example:

```c
// bar.c

// ...other includes...

#include "foo.c" // example from above

// this should be blow all other incldes 
#define MILO_LVL MILO_LVL_ERROR
#include <milo.h>

void bar() {
  info("won't do anything"); 
  error("example error"); // will print an error
  foo(); // will print all messages as expected
}
```

Available `MILO_LVL`s:
- `MILO_LVL_TRACE` (aliased `MILO_LVL_ALL`)
- `MILO_LVL_INFO` 
- `MILO_LVL_WARN` 
- `MILO_LVL_ERROR`
- `MILO_LVL_FATAL`
- `MILO_LVL_NONE` (aliased `MILO_LVL_SILENT`)


### Shadowing

Because `milo` "functions" are actually function-like macros, they will always shadow variables and functions with the same name. MiLo provides a `MILO_USE_SHORTCUTS` definition to adress that situation. It is enabled by default, but can be changed when necessary: 

```c
#define MILO_USE_SHORTCUTS (0) 
#define MILO_LVL MILO_LVL_WARN
#include <milo.h>

int check_unwanted_condition() {
  int error = 0;

  if (unwanted_condition) {
    // now milo functions from are called like this
    milo_error("unexpected unwanted condition!"); 
    error = 1;
  }

  // ...

  return error;
}
```

It is separate for each inclusion of the library, exactly like `MILO_LVL`.


## Customization

There are a bunch of options to customize:

| definition                  | default value                                          | description                        |
| ---                         | ---                                                    | ---                                |
|`milo_printf(fmt, ...)`      |`fprintf(stdout, fmt, ...), fflush(stdout)`             | Used in `trace`, `info` and `warn` |
|`milo_eprintf(fmt, ...)`     |`fprintf(stderr, fmt, ...), fflush(stderr)`             | Used in `error` and `fatal`        |
|`MILO_DEFAULT_LVL`           |`MILO_LVL_INFO`                                         | Used if `MILO_LVL` is not defined  |
|`MILO_NO_TA`                 |                                                        | Disables text attributes           |
|`MILO_TA_TRACE`              | clear all, blue                                        | Text attribute for `trace`         |
|`MILO_TA_INFO`               | clear all, green                                       | Text attribute for `info`          |
|`MILO_TA_WARN`               | clear all, bright yellow                               | Text attribute for `warn`          |
|`MILO_TA_ERROR`              | clear all, red                                         | Text attribute for `error`         |
|`MILO_TA_FATAL`              | clear all, bold, red                                   | Text attribute for `fatal`         |
|`MILO_TA_FILE`               | clear all, faded                                       | Text attribute for filename        |
|`MILO_TA_CLEAR`              | clear all                                              | Text attribute for everything else |
|`MILO_LVL_NAME_TRACE`        |`"trc"`                                                 | Log level name for `trace`         |
|`MILO_LVL_NAME_INFO`         |`"inf"`                                                 | Log level name for `info`          |
|`MILO_LVL_NAME_WARN`         |`"wrn"`                                                 | Log level name for `warn`          |
|`MILO_LVL_NAME_ERROR`        |`"err"`                                                 | Log level name for `error`         |
|`MILO_LVL_NAME_FATAL`        |`"ftl"`                                                 | Log level name for `fatal`         |
|`MILO_PREFIX_FORMAT`         |`"[{attr}{lvl} {file}:{line}] "`                        | Default format for the log prefix  |
|`MILO_PREFIX_ARGS(attr, lvl)`|`attr, lvl, MILO_FILE, MILO_LINE`                       | Arguments for the log prefix       |
|`MILO_SUFFIX_FORMAT`         |`"\n"`                                                  | Default format for the log suffix  |

> `MILO_TA_FILE`, `MILO_TA_CLEAR`, `MILO_PREFIX_FORMAT` and `MILO_PREFIX_ARGS` must not include parentheses since they rely on string concatenation and other macro tricks.

> `MILO_TA_TRACE`, `MILO_TA_INFO`, `MILO_TA_WARN`, `MILO_TA_ERROR`, `MILO_TA_FATAL`, `MILO_TA_FILE` and `MILO_TA_CLEAR` are redefined together. If this group is defined, `MILO_NO_TA` has no effect.

> `MILO_LVL_NAME_TRACE`, `MILO_LVL_NAME_INFO`, `MILO_LVL_NAME_WARN`, `MILO_LVL_NAME_ERROR`, `MILO_LVL_NAME_FATAL` are only redefined together.

> If `milo_printf` is defined, but `milo_eprintf` is not, it will be the same as `milo_printf`.

---

All definitions must be globally defined to ensure proper functionality. Otherwise, inconsistencies may arise.
```bash
# because this is bash, "FOO" becomes FOO in C, so we need additional quotes
gcc -o main main.c foo.c bar.c   \
-D 'MILO_LVL_NAME_TRACE="TRACE"' \
-D 'MILO_LVL_NAME_INFO="INFO"'   \
-D 'MILO_LVL_NAME_WARN="WARN"'   \
-D 'MILO_LVL_NAME_ERROR="ERROR"' \
-D 'MILO_LVL_NAME_FATAL="FATAL"'
```

Writing a lot of definitions in build scripts is not very efficent, so MiLo provides another way of doing this: `MILO_CONFIG` macro. You only need to define it, all other settings go there. 

```c
// milo_config.h

#define MILO_TA_TRACE ("\033[0;2;36m")  // made slightly faded
#define MILO_TA_INFO  ("\033[0;32m")    // default
#define MILO_TA_WARN  ("\033[0;95m")    // yellow changed to purple
#define MILO_TA_ERROR ("\033[0;31m")    // default
#define MILO_TA_FATAL ("\033[0;1;41m")  // color background instead of text

#define MILO_TA_FILE "\033[0;3;2m"  // made italic
#define MILO_TA_CLEAR "\033[0;3m"   // all text except level names and filenames made italic
```

```bash
gcc -o main main.c foo.c bar.c -D 'MILO_CONFIG="milo_config.h"'
```

In both cases, this will look similar to this:

![example output with custom text attributes](https://raw.githubusercontent.com/DaniilAlpha/milo/main/example_custom_ta.png)


### Customizing format

This part is not so obvious, so here is an example:

```c
#ifndef MILO_CONFIG_H
#define MILO_CONFIG_H

#include <time.h>
static char buf[32] = {0};
static inline char const *milo_timestamp(char const *const fmt) {
    time_t const t = time(NULL);
    strftime(buf, sizeof(buf), fmt, localtime(&t));
    return buf;
}

#define MILO_TA_TRACE ("\033[0;30m")
#define MILO_TA_INFO  ("\033[0;37m")
#define MILO_TA_WARN  ("\033[0;93m")
#define MILO_TA_ERROR ("\033[0;31m")
#define MILO_TA_FATAL ("\033[0;41;30m")

#define MILO_TA_FILE  "\033[0;2m"
#define MILO_TA_CLEAR "\033[0m"

// be careful not to include parentheses in these two, as they rely heavily on
// string concatenation
#define MILO_PREFIX_FORMAT                                                     \
    MILO_TA_CLEAR                                                              \
    "%s"       /* {attr} */                                                    \
    "%s"       /* {timestamp} */                                               \
    " %s %s: " /* {file}:{line} {func} */
#define MILO_PREFIX_ARGS(attr, lvl)                                            \
    (attr), milo_timestamp("%b %d %H:%M:%S"), MILO_FILE, MILO_FUNC

#endif
```

This is trying to immitate a format similar to `journalctl` output, and does this quite well.

#### Happy logging!
