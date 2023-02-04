#include <stdio.h>
#include <string.h>

#include "milo_lvl.h"
#include "milo_text_attr.h"
#include "milo_current_file.h"

#ifndef MILO_LVL
#define MILO_LVL MILO_LVL_INFO
#endif

// if already defined, undefine to remove compiler warnings
#ifndef _INC_MILO
#define _INC_MILO
#else
#undef trace
#undef info
#undef warn
#undef error
#undef fatal
#endif

#if MILO_LVL >= MILO_LVL_ALL
/// @brief Prints a trace message.
/// @param format
/// @return void
#define trace(format, ...) ({ printf("[%s:%i " MILO_TEXT_ATTR_TRACE "trace" MILO_TEXT_ATTR_CLEAR "] " format "\n", MILO_CURRENT_FILE, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
/// @return void
#define trace(...)
#endif

#if MILO_LVL >= MILO_LVL_INFO
/// @brief Prints an info message.
/// @param format
/// @return void
#define info(format, ...) ({ printf("[%s:%i " MILO_TEXT_ATTR_INFO "info" MILO_TEXT_ATTR_CLEAR "] " format "\n", MILO_CURRENT_FILE, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
/// @return void
#define info(...)
#endif

#if MILO_LVL >= MILO_LVL_WARN
/// @brief Prints a warning message.
/// @param format
/// @return void
#define warn(format, ...) ({ printf("[%s:%i " MILO_TEXT_ATTR_WARN "warn" MILO_TEXT_ATTR_CLEAR "] " format "\n", MILO_CURRENT_FILE, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
/// @return void
#define warn(...)
#endif

#if MILO_LVL >= MILO_LVL_ERROR
/// @brief Prints an error message.
/// @param format
/// @return void
#define error(format, ...) ({ printf("[%s:%i " MILO_TEXT_ATTR_ERROR "error" MILO_TEXT_ATTR_CLEAR "] " format "\n", MILO_CURRENT_FILE, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
/// @return void
#define error(...)
#endif

#if MILO_LVL >= MILO_LVL_FATAL
/// @brief Prints a fatal message.
/// @param format
/// @return void
#define fatal(format, ...) ({ printf("[%s:%i " MILO_TEXT_ATTR_FATAL "fatal" MILO_TEXT_ATTR_CLEAR "] " format "\n", MILO_CURRENT_FILE, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
/// @param format
/// @return void
#define fatal(...)
#endif

// makes MILO_LVL unique for each file
#undef MILO_LVL
