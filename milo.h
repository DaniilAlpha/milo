/*****************
 ** common part **
 *****************/

#if (!defined MILO_H)
#  define MILO_H

static inline char const *internal__milo_filename(char const *filepath_end) {
    while (filepath_end[0] != '/' && filepath_end[0] != '\\') filepath_end--;
    return filepath_end;
}

/*** defs ***/

// lvls

#  define MILO_LVL_ALL    MILO_LVL_TRACE
#  define MILO_LVL_TRACE  (5)
#  define MILO_LVL_INFO   (4)
#  define MILO_LVL_WARN   (3)
#  define MILO_LVL_ERROR  (2)
#  define MILO_LVL_FATAL  (1)
#  define MILO_LVL_SILENT MILO_LVL_NONE
#  define MILO_LVL_NONE   (0)

// formatting

#  if (defined __FILE_NAME__)
#    define MILO_FILE __FILE_NAME__
#  else
#    define MILO_FILE (milo_filename(__FILE__ + sizeof(__FILE__)))
#  endif
#  define MILO_LINE (__LINE__)
#  define MILO_FUNC (__func__)

/*** config ***/

#  ifdef MILO_CONFIG
#    include MILO_CONFIG
#  endif

#  ifndef MILO_DEFAULT_LVL
#    define MILO_DEFAULT_LVL MILO_LVL_INFO
#  endif

// `printf` and `eprintf`

#  if (!defined milo_printf)
#    if (defined milo_eprintf)
#      warning                                                                 \
          "Your `milo_eprintf` will be redefined by MiLo because `milo_printf` wasn't defined. Consider either removing your definition for `milo_eprintf` or adding one for `milo_printf`."
#    endif

#    include <stdio.h>
#    define milo_printf(format, ...)                                           \
        (fprintf(stdout, format, ##__VA_ARGS__), fflush(stdout), (void)0)
#    define milo_eprintf(format, ...)                                          \
        (fprintf(stderr, format, ##__VA_ARGS__), fflush(stderr), (void)0)
#  elif (!defined milo_eprintf)
#    define milo_eprintf milo_printf
#  endif

// text attributes

#  if (!defined MILO_TA_TRACE && !defined MILO_TA_INFO &&                      \
       !defined MILO_TA_WARN && !defined MILO_TA_ERROR &&                      \
       !defined MILO_TA_FATAL && !defined MILO_TA_CLEAR &&                     \
       !defined MILO_TA_FILE)
#    ifdef MILO_NO_TA
#      define MILO_TA_TRACE ("")
#      define MILO_TA_INFO  ("")
#      define MILO_TA_WARN  ("")
#      define MILO_TA_ERROR ("")
#      define MILO_TA_FATAL ("")

#      define MILO_TA_FILE
#      define MILO_TA_CLEAR
#    else
#      define MILO_TA_TRACE ("\033[0;36m")
#      define MILO_TA_INFO  ("\033[0;32m")
#      define MILO_TA_WARN  ("\033[0;93m")
#      define MILO_TA_ERROR ("\033[0;31m")
#      define MILO_TA_FATAL ("\033[0;1;31m")

#      define MILO_TA_FILE  "\033[0;2m"
#      define MILO_TA_CLEAR "\033[0m"
#    endif
#  endif

// level names

#  if (!defined MILO_LVL_NAME_TRACE && !defined MILO_LVL_NAME_INFO &&          \
       !defined MILO_LVL_NAME_WARN && !defined MILO_LVL_NAME_ERROR &&          \
       !defined MILO_LVL_NAME_FATAL)
#    define MILO_LVL_NAME_TRACE ("trc")
#    define MILO_LVL_NAME_INFO  ("inf")
#    define MILO_LVL_NAME_WARN  ("wrn")
#    define MILO_LVL_NAME_ERROR ("err")
#    define MILO_LVL_NAME_FATAL ("ftl")
#  endif

// prefix format

#  if (!defined MILO_PREFIX_FORMAT && !defined MILO_PREFIX_ARGS)
#    define MILO_PREFIX_FORMAT                                                 \
        MILO_TA_CLEAR "[%s%s" MILO_TA_CLEAR " " MILO_TA_FILE                   \
                      "%s:%i" MILO_TA_CLEAR "] "
#    define MILO_PREFIX_ARGS(attr, lvl) (attr), (lvl), MILO_FILE, MILO_LINE
#  endif
#  if (!defined MILO_SUFFIX_FORMAT)
#    define MILO_SUFFIX_FORMAT MILO_TA_CLEAR "\n"
#  endif

#else
#  undef milo_trace
#  undef milo_info
#  undef milo_warn
#  undef milo_error
#  undef milo_fatal
#endif

/***************
 ** unit part **
 ***************/

#ifndef MILO_LVL
#  define MILO_LVL MILO_DEFAULT_LVL
#endif

#ifndef MILO_USE_SHORTCUTS
#  define MILO_USE_SHORTCUTS (1)
#endif

#if (MILO_LVL) >= (MILO_LVL_ALL)
/// Prints a trace message.
#  define milo_trace(format, ...)                                              \
      milo_printf(                                                             \
          MILO_PREFIX_FORMAT format MILO_SUFFIX_FORMAT,                        \
          MILO_PREFIX_ARGS(MILO_TA_TRACE, MILO_LVL_NAME_TRACE),                \
          ##__VA_ARGS__                                                        \
      )
#  if (MILO_USE_SHORTCUTS)
/// Prints a trace message.
#    define trace milo_trace
#  endif
#else
/// Does nothing.
#  define milo_trace(...) ((void)0)
#  if (MILO_USE_SHORTCUTS)
/// Does nothing.
#    define trace milo_trace
#  endif
#endif

#if (MILO_LVL) >= (MILO_LVL_INFO)
/// Prints an info message.
#  define milo_info(format, ...)                                               \
      milo_printf(                                                             \
          MILO_PREFIX_FORMAT format MILO_SUFFIX_FORMAT,                        \
          MILO_PREFIX_ARGS(MILO_TA_INFO, MILO_LVL_NAME_INFO),                  \
          ##__VA_ARGS__                                                        \
      )
#  if (MILO_USE_SHORTCUTS)
/// Prints an info message.
#    define info milo_info
#  endif
#else
/// Does nothing.
#  define milo_info(...) ((void)0)
#  if (MILO_USE_SHORTCUTS)
/// Does nothing.
#    define info milo_info
#  endif
#endif

#if (MILO_LVL) >= (MILO_LVL_WARN)
/// Prints a warning message.
#  define milo_warn(format, ...)                                               \
      milo_printf(                                                             \
          MILO_PREFIX_FORMAT format MILO_SUFFIX_FORMAT,                        \
          MILO_PREFIX_ARGS(MILO_TA_WARN, MILO_LVL_NAME_WARN),                  \
          ##__VA_ARGS__                                                        \
      )
#  if (MILO_USE_SHORTCUTS)
/// Prints a warning message.
#    define warn milo_warn
#  endif
#else
/// Does nothing.
#  define milo_warn(...) ((void)0)
#  if (MILO_USE_SHORTCUTS)
/// Does nothing.
#    define warn milo_warn
#  endif
#endif

#if (MILO_LVL) >= (MILO_LVL_ERROR)
/// Prints an error message.
#  define milo_error(format, ...)                                              \
      milo_eprintf(                                                            \
          MILO_PREFIX_FORMAT format MILO_SUFFIX_FORMAT,                        \
          MILO_PREFIX_ARGS(MILO_TA_ERROR, MILO_LVL_NAME_ERROR),                \
          ##__VA_ARGS__                                                        \
      )
#  if (MILO_USE_SHORTCUTS)
/// Prints an error message.
#    define error milo_error
#  endif
#else
/// Does nothing.
#  define milo_error(...) ((void)0)
#  if (MILO_USE_SHORTCUTS)
/// Does nothing.
#    define error milo_error
#  endif
#endif

#if (MILO_LVL) >= (MILO_LVL_FATAL)
/// Prints a fatal error message.
#  define milo_fatal(format, ...)                                              \
      milo_eprintf(                                                            \
          MILO_PREFIX_FORMAT format MILO_SUFFIX_FORMAT,                        \
          MILO_PREFIX_ARGS(MILO_TA_FATAL, MILO_LVL_NAME_FATAL),                \
          ##__VA_ARGS__                                                        \
      )
#  if (MILO_USE_SHORTCUTS)
/// Prints a fatal error message.
#    define fatal milo_fatal
#  endif
#else
/// Does nothing.
#  define milo_fatal(...) ((void)0)
#  if (MILO_USE_SHORTCUTS)
/// Does nothing.
#    define fatal milo_fatal
#  endif
#endif

// these should be unique for each file
#undef MILO_LVL
#undef MILO_USE_SHORTCUTS
