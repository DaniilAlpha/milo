#include "milo_lvl.h"
#include "milo_text_attr.h"
#include "milo_filename.h"

#ifndef MILO_LVL
#define MILO_LVL MILO_LVL_INFO
#endif

// if already defined - undefine to get rid of compiler warnings
#ifdef MILO_DEFINED
#undef trace
#undef info
#undef warn
#undef error
#undef fatal
#endif

#if MILO_LVL >= MILO_LVL_ALL
/// @brief Prints trace.
#define trace(fmt, ...) ({ printf("[%s:%i " MILO_TA_BLUE "trace" MILO_TA_CLEAR "] " fmt "\n", _MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
#define trace(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_INFO
/// @brief Prints info.
#define info(fmt, ...) ({ printf("[%s:%i " MILO_TA_GREEN "info" MILO_TA_CLEAR "] " fmt "\n", _MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
#define info(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_WARN
/// @brief Prints warning.
#define warn(fmt, ...) ({ printf("[%s:%i " MILO_TA_YELLOW "warn" MILO_TA_CLEAR "] " fmt "\n", _MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
#define warn(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_ERROR
/// @brief Prints error.
#define error(fmt, ...) ({ printf("[%s:%i " MILO_TA_RED "error" MILO_TA_CLEAR "] " fmt "\n", _MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
#define error(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_FATAL
/// @brief Prints fatal error.
#define fatal(fmt, ...) ({ printf("[%s:%i " MILO_TA_RED "fatal" MILO_TA_CLEAR "] " fmt "\n", _MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
/// @brief Does nothing.
#define fatal(fmt, ...)
#endif

// a way to check if milo already defined
#define MILO_DEFINED

// undefine MILO_LVL to get rid of compiler warnings
#ifdef MILO_LVL
#undef MILO_LVL
#endif
