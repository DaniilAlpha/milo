/*****************
 ** shared part **
 *****************/

#ifndef _INC_MILO
  #define _INC_MILO

const char *milo_get_filename(const char *filepath);

// use stdio's printf if not provided

  #ifndef milo_printf
    #include <stdio.h>
    #define milo_printf(format, ...) printf(format, ##__VA_ARGS__)
  #endif

// milo levels

  #define MILO_LVL_ALL    MILO_LVL_TRACE
  #define MILO_LVL_TRACE  (5)
  #define MILO_LVL_INFO   (4)
  #define MILO_LVL_WARN   (3)
  #define MILO_LVL_ERROR  (2)
  #define MILO_LVL_FATAL  (1)
  #define MILO_LVL_SILENT MILO_LVL_NONE
  #define MILO_LVL_NONE   (0)

// determine wheter to use text attributes

  #ifndef MILO_USE_TEXT_ATTR
    #ifdef MILO_NO_TEXT_ATTR
      #define MILO_USE_TEXT_ATTR (0)
    #else
      #define MILO_USE_TEXT_ATTR (1)
    #endif
  #endif

// setup text attributes

  #if MILO_USE_TEXT_ATTR
    #define MILO_TEXT_ATTR_TRACE "\x1B[0;36m"
    #define MILO_TEXT_ATTR_INFO  "\x1B[0;32m"
    #define MILO_TEXT_ATTR_WARN  "\x1B[0;33m"
    #define MILO_TEXT_ATTR_ERROR "\x1B[0;31m"
    #define MILO_TEXT_ATTR_FATAL "\x1B[1;31m"
    #define MILO_TEXT_ATTR_CLEAR "\x1B[0m"
  #else
    #define MILO_TEXT_ATTR_TRACE
    #define MILO_TEXT_ATTR_INFO
    #define MILO_TEXT_ATTR_WARN
    #define MILO_TEXT_ATTR_ERROR
    #define MILO_TEXT_ATTR_FATAL
    #define MILO_TEXT_ATTR_CLEAR
  #endif

  #define __MILO_FILENAME milo_get_filename(__FILE__)

#else  // undefine old macros
  #undef trace
  #undef info
  #undef warn
  #undef error
  #undef fatal
#endif

/***************
 ** sole part **
 ***************/

#ifndef MILO_LVL
  #define MILO_LVL MILO_LVL_INFO
#endif

#if MILO_LVL >= MILO_LVL_ALL
  /// @brief Prints a trace message.
  /// @param format
  /// @return void
  #define trace(format, ...)                                                   \
    milo_printf(                                                               \
      "[%s:%i " MILO_TEXT_ATTR_TRACE "trace" MILO_TEXT_ATTR_CLEAR "] " format  \
      "\n",                                                                    \
      __MILO_FILENAME,                                                         \
      __LINE__,                                                                \
      ##__VA_ARGS__                                                            \
    )
#else
  /// @brief Does nothing.
  /// @return void
  #define trace(...)
#endif

#if MILO_LVL >= MILO_LVL_INFO
  /// @brief Prints an info message.
  /// @param format
  /// @return void
  #define info(format, ...)                                                    \
    milo_printf(                                                               \
      "[%s:%i " MILO_TEXT_ATTR_INFO "info" MILO_TEXT_ATTR_CLEAR "] " format    \
      "\n",                                                                    \
      __MILO_FILENAME,                                                         \
      __LINE__,                                                                \
      ##__VA_ARGS__                                                            \
    )
#else
  /// @brief Does nothing.
  /// @return void
  #define info(...)
#endif

#if MILO_LVL >= MILO_LVL_WARN
  /// @brief Prints a warning message.
  /// @param format
  /// @return void
  #define warn(format, ...)                                                    \
    milo_printf(                                                               \
      "[%s:%i " MILO_TEXT_ATTR_WARN "warn" MILO_TEXT_ATTR_CLEAR "] " format    \
      "\n",                                                                    \
      __MILO_FILENAME,                                                         \
      __LINE__,                                                                \
      ##__VA_ARGS__                                                            \
    )
#else
  /// @brief Does nothing.
  /// @return void
  #define warn(...)
#endif

#if MILO_LVL >= MILO_LVL_ERROR
  /// @brief Prints an error message.
  /// @param format
  /// @return void
  #define error(format, ...)                                                   \
    milo_printf(                                                               \
      "[%s:%i " MILO_TEXT_ATTR_ERROR "error" MILO_TEXT_ATTR_CLEAR "] " format  \
      "\n",                                                                    \
      __MILO_FILENAME,                                                         \
      __LINE__,                                                                \
      ##__VA_ARGS__                                                            \
    )
#else
  /// @brief Does nothing.
  /// @return void
  #define error(...)
#endif

#if MILO_LVL >= MILO_LVL_FATAL
  /// @brief Prints a fatal message.
  /// @param format
  /// @return void
  #define fatal(format, ...)                                                   \
    milo_printf(                                                               \
      "[%s:%i " MILO_TEXT_ATTR_FATAL "fatal" MILO_TEXT_ATTR_CLEAR "] " format  \
      "\n",                                                                    \
      __MILO_FILENAME,                                                         \
      __LINE__,                                                                \
      ##__VA_ARGS__                                                            \
    )
#else
  /// @brief Does nothing.
  /// @param format
  /// @return void
  #define fatal(...)
#endif

// makes MILO_LVL unique for each file
#undef MILO_LVL
