/*****************
 ** shared part **
 *****************/

#ifndef MILO_H
# define MILO_H

# ifdef __cplusplus
extern "C"
# endif
  /// @brief Extracts filename from filepath.
  /// @param filepath file path or name
  /// @return pointer to the first character after last occurence of `\\` or `/`
  const char *
  milo_filename(const char *const filepath);

# ifdef MILO_IMPL
const char *milo_filename(const char *const filepath) {
  const char *filename = filepath;
  for (const char *c = filepath; *c != '\0'; c++)
    if (*c == '\\' || *c == '/') filename = c + 1;
  return filename;
}
# endif

/** shared **/

// lvls

# define MILO_LVL_ALL    MILO_LVL_TRACE
# define MILO_LVL_TRACE  (5)
# define MILO_LVL_INFO   (4)
# define MILO_LVL_WARN   (3)
# define MILO_LVL_ERROR  (2)
# define MILO_LVL_FATAL  (1)
# define MILO_LVL_SILENT MILO_LVL_NONE
# define MILO_LVL_NONE   (0)

// formatting

# define MILO_FILE (milo_filename(__FILE__))
# define MILO_LINE (__LINE__)
# define MILO_FUNC (__func__)

/** config **/

# ifdef MILO_CONFIG
#  include MILO_CONFIG
# endif

// `printf` and `eprintf`

# if (!defined milo_printf)
#  if (defined milo_eprintf)
#   warning                                                                    \
     "Your `milo_eprintf` will be redefined by MiLo because `milo_printf` wasn't defined. Consider either removing your definition for `milo_eprintf` or adding one for `milo_printf`."
#  endif

#  include <stdio.h>
#  define milo_printf(format, ...)  printf(format, ##__VA_ARGS__)
#  define milo_eprintf(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
# elif (!defined milo_eprintf)
#  define milo_eprintf milo_printf
# endif

// default lvl

# ifndef MILO_DEFAULT_LVL
#  define MILO_DEFAULT_LVL MILO_LVL_INFO
# endif

// text attributes

# if (!defined MILO_TA_TRACE && !defined MILO_TA_INFO && !defined MILO_TA_WARN && !defined MILO_TA_ERROR && !defined MILO_TA_FATAL && !defined MILO_TA_CLEAR && !defined MILO_TA_FILE)
#  ifdef MILO_NO_TA
#   define MILO_TA_TRACE ("")
#   define MILO_TA_INFO  ("")
#   define MILO_TA_WARN  ("")
#   define MILO_TA_ERROR ("")
#   define MILO_TA_FATAL ("")

#   define MILO_TA_FILE
#   define MILO_TA_CLEAR
#  else
#   define MILO_TA_TRACE ("\x18[0;36m")
#   define MILO_TA_INFO  ("\x18[0;32m")
#   define MILO_TA_WARN  ("\x18[0;93m")
#   define MILO_TA_ERROR ("\x18[0;31m")
#   define MILO_TA_FATAL ("\x18[0;1;31m")

#   define MILO_TA_FILE  "\x18[0;2m"
#   define MILO_TA_CLEAR "\x18[0m"
#  endif
# endif

// level names

# if (!defined MILO_LVL_NAME_TRACE && !defined MILO_LVL_NAME_INFO && !defined MILO_LVL_NAME_WARN && !defined MILO_LVL_NAME_ERROR && !defined MILO_LVL_NAME_FATAL)
#  define MILO_LVL_NAME_TRACE ("trc")
#  define MILO_LVL_NAME_INFO  ("inf")
#  define MILO_LVL_NAME_WARN  ("wrn")
#  define MILO_LVL_NAME_ERROR ("err")
#  define MILO_LVL_NAME_FATAL ("ftl")
# endif

// prefix format

# if (!defined MILO_PREFIX_FORMAT && !defined milo_prefix_args)
#  define MILO_PREFIX_FORMAT                                                   \
     MILO_TA_CLEAR "[%s%s" MILO_TA_CLEAR " " MILO_TA_FILE                      \
                   "%s:%i" MILO_TA_CLEAR "] "  // space before log body
#  define milo_prefix_args(attr, lvl) (attr), (lvl), MILO_FILE, MILO_LINE
# endif

#else
# undef milo_trace
# undef milo_info
# undef milo_warn
# undef milo_error
# undef milo_fatal
#endif

/***************
 ** sole part **
 ***************/

#ifndef MILO_LVL
# define MILO_LVL MILO_DEFAULT_LVL
#endif

#ifndef MILO_USE_SHORTCUTS
# define MILO_USE_SHORTCUTS (1)
#endif

#if (MILO_LVL) >= (MILO_LVL_ALL)
/// @brief Prints a trace message.
/// @param format
/// @return the same as underlying
# define milo_trace(format, ...)                                               \
   milo_printf(                                                                \
     MILO_PREFIX_FORMAT format "\n",                                           \
     milo_prefix_args(MILO_TA_TRACE, MILO_LVL_NAME_TRACE),                     \
     ##__VA_ARGS__                                                             \
   )

# if (MILO_USE_SHORTCUTS)
/// @brief Prints a trace message.
/// @param format
/// @return the same as underlying
#  define trace milo_trace
# endif
#else
/// @brief Does nothing.
/// @return void
# define milo_trace(...)

# if (MILO_USE_SHORTCUTS)
/// @brief Does nothing.
/// @return void
#  define trace milo_trace
# endif
#endif

#if (MILO_LVL) >= (MILO_LVL_INFO)
/// @brief Prints an info message.
/// @param format
/// @return the same as underlying
# define milo_info(format, ...)                                                \
   milo_printf(                                                                \
     MILO_PREFIX_FORMAT format "\n",                                           \
     milo_prefix_args(MILO_TA_INFO, MILO_LVL_NAME_INFO),                       \
     ##__VA_ARGS__                                                             \
   )

# if (MILO_USE_SHORTCUTS)
/// @brief Prints an info message.
/// @param format
/// @return the same as underlying
#  define info milo_info
# endif
#else
/// @brief Does nothing.
/// @return void
# define milo_info(...)

# if (MILO_USE_SHORTCUTS)
/// @brief Does nothing.
/// @return void
#  define info milo_info
# endif
#endif

#if (MILO_LVL) >= (MILO_LVL_WARN)
/// @brief Prints a warning message.
/// @param format
/// @return the same as underlying
# define milo_warn(format, ...)                                                \
   milo_printf(                                                                \
     MILO_PREFIX_FORMAT format "\n",                                           \
     milo_prefix_args(MILO_TA_WARN, MILO_LVL_NAME_WARN),                       \
     ##__VA_ARGS__                                                             \
   )

# if (MILO_USE_SHORTCUTS)
/// @brief Prints a warning message.
/// @param format
/// @return the same as underlying
#  define warn milo_warn
# endif
#else
/// @brief Does nothing.
/// @return void
# define milo_warn(...)

# if (MILO_USE_SHORTCUTS)
/// @brief Does nothing.
/// @return void
#  define warn milo_warn
# endif
#endif

#if (MILO_LVL) >= (MILO_LVL_ERROR)
/// @brief Prints an error message.
/// @param format
/// @return the same as underlying
# define milo_error(format, ...)                                               \
   milo_eprintf(                                                               \
     MILO_PREFIX_FORMAT format "\n",                                           \
     milo_prefix_args(MILO_TA_ERROR, MILO_LVL_NAME_ERROR),                     \
     ##__VA_ARGS__                                                             \
   )

# if (MILO_USE_SHORTCUTS)
/// @brief Prints an error message.
/// @param format
/// @return the same as underlying
#  define error milo_error
# endif
#else
/// @brief Does nothing.
/// @return void
# define milo_error(...)

# if (MILO_USE_SHORTCUTS)
/// @brief Does nothing.
/// @return void
#  define error milo_error
# endif
#endif

#if (MILO_LVL) >= (MILO_LVL_FATAL)
/// @brief Prints a fatal error message.
/// @param format
/// @return the same as underlying
# define milo_fatal(format, ...)                                               \
   milo_eprintf(                                                               \
     MILO_PREFIX_FORMAT format "\n",                                           \
     milo_prefix_args(MILO_TA_FATAL, MILO_LVL_NAME_FATAL),                     \
     ##__VA_ARGS__                                                             \
   )

# if (MILO_USE_SHORTCUTS)
/// @brief Prints a fatal error message.
/// @param format
/// @return the same as underlying
#  define fatal milo_fatal
# endif
#else
/// @brief Does nothing.
/// @return void
# define milo_fatal(...)

# if (MILO_USE_SHORTCUTS)
/// @brief Does nothing.
/// @return void
#  define fatal milo_fatal
# endif
#endif

// this should be unique for each file

#undef MILO_LVL
#undef MILO_USE_SHORTCUTS
