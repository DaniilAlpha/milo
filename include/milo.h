#include <stdio.h>
#include <string.h>

#include "milo_lvl.h"
#include "milo_text_attr.h"
#include "milo_filename.h"

#ifndef MILO_LVL
#define MILO_LVL MILO_LVL_INFO
#endif

#ifndef MILO_LABEL
#define MILO_LABEL ""
#endif

// if already defined - undefine to get rid of compiler warnings
#ifndef _INC_MILO
#define _INC_MILO
#else
#undef trace
#undef info
#undef warn
#undef error
#undef fatal
#undef MILO_LVL
#endif

#if MILO_LVL >= MILO_LVL_ALL
/// @brief Prints a trace message.
#define trace(fmt, ...) ({ printf("[%s:%i " MILO_TA_TRACE "trace" MILO_TA_CLEAR "] " MILO_LABEL fmt "\n", MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
#define trace(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_INFO
/// @brief Prints an info message.
#define info(fmt, ...) ({ printf("[%s:%i " MILO_TA_INFO "info" MILO_TA_CLEAR "] " MILO_LABEL fmt "\n", MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
#define info(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_WARN
/// @brief Prints a warning message.
#define warn(fmt, ...) ({ printf("[%s:%i " MILO_TA_WARN "warn" MILO_TA_CLEAR "] " MILO_LABEL fmt "\n", MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
#define warn(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_ERROR
/// @brief Prints an error message.
#define error(fmt, ...) ({ printf("[%s:%i " MILO_TA_ERROR "error" MILO_TA_CLEAR "] " MILO_LABEL fmt "\n", MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
#define error(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_FATAL
/// @brief Prints a fatal message.
#define fatal(fmt, ...) ({ printf("[%s:%i " MILO_TA_FATAL "fatal" MILO_TA_CLEAR "] " MILO_LABEL fmt "\n", MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
#define fatal(fmt, ...)
#endif

// undefine MILO_LVL and MILO_LABEL to get rid of compiler warnings
#undef MILO_LVL
#undef MILO_LABEL
