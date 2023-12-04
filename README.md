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

// define this in your main file to allow milo to implement itself
#define MILO_IMPL 

// ...other includes...

#define MILO_LVL MILO_LVL_TRACE
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

Available `MILO_LVL`s:
- `MILO_LVL_TRACE` (alias `MILO_LVL_ALL`)
- `MILO_LVL_INFO` 
- `MILO_LVL_WARN` 
- `MILO_LVL_ERROR`
- `MILO_LVL_FATAL`
- `MILO_LVL_NONE` (alias `MILO_LVL_SILENT`)

By default `MILO_LVL` is `MILO_LVL_INFO`, but can be changed by redefining `MILO_DEFAULT_LVL` at build level (more on that later).

### Different log levels for different files

It is possible to use different `MILO_LVL`s for different files, for example:

```c
// bar.c

// ...other includes...

#include "foo.c" // example from above

// this two lines should be undef all other incldes to prevent shadowing
#define MILO_LVL MILO_LVL_ERROR
#include <milo.h>

void bar() {
  error("example error"); // will print an error
  info("example nothing"); // won't do anything
  foo(); // will print all messages as expected
}
```

### Shadowing

Because MiLo "functions" are actually function-like macros, they will always shadow variables and functions with same names, to MiLo provides a `MILO_USE_SHORTCUTS` definition. It is enabled by default, but you may change it: 

```c
#define MILO_USE_SHORTCUTS (0) 
#define MILO_LVL MILO_LVL_WARN
#include <milo.h>

int check_unwanted_condition() {
  int error = 0;

  if (unwanted_condition) {
    // now functions from milo are called like this
    milo_error("unexpected unwanted condition!"); 
    error = 1;
  }

  // ...

  return error;
}
```

Same as `MILO_LVL`, this is separate for each time you include the library.

## Customization

There are quite a lot options to customize:
| definition                | default value                                          | description                        |
| ---                       | ---                                                    | ---                                |
|`milo_printf(fmt, ...)`    |`printf(fmt, ...)`                                      | Used in `trace`, `info` and `warn` |
|`milo_eprintf(fmt, ...)`   |`fprintf(stderr, fmt, ...)`                             | Used in `error` and `fatal`        |
|`MILO_DEFAULT_LVL`         |`MILO_LVL_INFO`                                         | Used if `MILO_LVL` is not defined  |
|`MILO_NO_TA`               |                                                        | Disables text attributes           |
|`MILO_TA_TRACE`            | clear all, blue                                        | Text attribute for `trace`         |
|`MILO_TA_INFO`             | clear all, green                                       | Text attribute for `info`          |
|`MILO_TA_WARN`             | clear all, bright yellow                               | Text attribute for `warn`          |
|`MILO_TA_ERROR`            | clear all, red                                         | Text attribute for `error`         |
|`MILO_TA_FATAL`            | clear all, bold, red                                   | Text attribute for `fatal`         |
|`MILO_TA_FILE`             | clear all, faded                                       | Text attribute for filename        |
|`MILO_TA_CLEAR`            | clear all                                              | Text attribute for everything else |
|`MILO_LVL_NAME_TRACE`      |`"trc"`                                                 | Log level name for `trace`         |
|`MILO_LVL_NAME_INFO`       |`"inf"`                                                 | Log level name for `info`          |
|`MILO_LVL_NAME_WARN`       |`"wrn"`                                                 | Log level name for `warn`          |
|`MILO_LVL_NAME_ERROR`      |`"err"`                                                 | Log level name for `error`         |
|`MILO_LVL_NAME_FATAL`      |`"ftl"`                                                 | Log level name for `fatal`         |
|`MILO_PREFIX_FORMAT`       |`"(atcl)[{at}{lvl}(atcl) (atfile){file}:{line}(atcl)] "`| Default format for the log prefix  |
|`milo_prefix_args(at, lvl)`|`at, lvl, MILO_FILE, MILO_LINE`                         | Arguments for the log prefix       |

> `MILO_TA_FILE`, `MILO_TA_CLEAR`, `MILO_PREFIX_FORMAT` and `milo_prefix_args` mustn't include parenthesis, because they rely on string concatenation and other tricks.

> `MILO_TA_TRACE`, `MILO_TA_INFO`, `MILO_TA_WARN`, `MILO_TA_ERROR`, `MILO_TA_FATAL`, `MILO_TA_FILE` and `MILO_TA_CLEAR` are only redefined together. If this group is defined, `MILO_NO_TA` has no effect.

> `MILO_LVL_NAME_TRACE`, `MILO_LVL_NAME_INFO`, `MILO_LVL_NAME_WARN`, `MILO_LVL_NAME_ERROR`, `MILO_LVL_NAME_FATAL` are only redefined together.

> If `milo_printf` is defined, but `milo_eprintf` isn't, it will be the same as `milo_printf`. 

---

All this definitions are shared between all includes, so should be redefined at global level to work properly. If definitions were at library level, they could be inconsistent across one project in multiple libraries. For example, let's make level names full words and in caps :

```bash
# because this is bash, "FOO" becomes FOO in C, so we need additional quotes
gcc -o main main.c foo.c bar.c   \
-D MILO_LVL_NAME_TRACE='"TRACE"' \
-D MILO_LVL_NAME_INFO='"INFO"'   \
-D MILO_LVL_NAME_WARN='"WARN"'   \
-D MILO_LVL_NAME_ERROR='"ERROR"' \
-D MILO_LVL_NAME_FATAL='"FATAL"'
```

Writing a lot of definitions in build scripts is not very efficent, so MiLo provides another way of doing this: `MILO_CONFIG` macro. You only need to define it, all other settings go there. 

```c
// milo_config.h

#define MILO_TA_TRACE ("\e[0;2;36m")  // made slightly faded
#define MILO_TA_INFO  ("\e[0;32m")    // default
#define MILO_TA_WARN  ("\e[0;95m")    // yellow changed to purple
#define MILO_TA_ERROR ("\e[0;31m")    // default
#define MILO_TA_FATAL ("\e[0;1;41m")  // color background instead of text

#define MILO_TA_FILE "\e[0;3;2m"  // made italic
#define MILO_TA_CLEAR "\e[0;3m"   // all text except level names and filenames made italic
```

```bash
gcc -o main main.c foo.c bar.c -D MILO_CONFIG='"milo_config.h"'
```

In both cases this will look like this:

<p>
  <img src="https://raw.githubusercontent.com/DaniilAlpha/milo/main/example_custom_ta.png" alt="example output with custom text attributes" />
</p>

### Customizing format

This part is not so obvious, so here is the small example:

```c
// milo_config.h

// in reality there will be a multiple definition error here except of some very
// simple projects, so should be sent to a .c file, but this is just an example
const char *milo_timestamp(const char *const fmt) {
  static char buf[32] = {0};
  static time_t t;

  time(&t);
  strftime(buf, 32, fmt, localtime(&t));
  return buf;
}

// not really nesessary, but makes this mess at least a bit prettier
#define MILO_TIME (milo_timestamp("%D %H:%M:%S")) 

// be careful not to include parentheses in these two definitions, as they rely on string concatenation
#define MILO_PREFIX_FORMAT                                                     \
  MILO_TA_CLEAR                                                                \
  "\n"                                                                         \
  "\e[0;35m"      /* custom TA for timestamp */                                \
  "%s"            /* {timestamp} */                                            \
    MILO_TA_CLEAR /* clear custom TA */                                        \
  " - "                                                                        \
  "%s:%i: "       /* {file}&{line} */                                          \
  "%s"            /* {attr} */                                                 \
  "%s"            /* {lvl} */                                                  \
    MILO_TA_CLEAR /* clear TA */                                               \
  " in function "                                                              \
  "\e[0;37m"      /* custom TA for function */                                 \
  "%s"            /* {function} */                                             \
    MILO_TA_CLEAR /* clear custom TA */                                        \
  "\n"
#define milo_prefix_args(attr, lvl)                                            \
  MILO_TIME, MILO_FILE, MILO_LINE, (attr), (lvl), MILO_FUNC
```

This will look like this:

<p>
  <img src="https://raw.githubusercontent.com/DaniilAlpha/milo/main/example_custom_format.png" alt="example output with custom format" />
</p>

### Happy logging!