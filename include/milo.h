#include "milo_lvl.h"
#include "milo_text_attr.h"

#ifndef MILO_LVL
#define MILO_LVL MILO_LVL_INFO
#endif

// faster way to include filename in log
#define _MILO_FILENAME (strrchr(__FILE__, '/') + 1)

#if MILO_LVL >= MILO_LVL_ALL
#define trace(fmt, ...) ({ printf("[%s:%i " MILO_TA_BLUE "trace" MILO_TA_CLEAR "] " fmt "\n", _MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
#define trace(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_INFO
#define info(fmt, ...) ({ printf("[%s:%i " MILO_TA_GREEN "info" MILO_TA_CLEAR "] " fmt "\n", _MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
#define info(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_WARN
#define warn(fmt, ...) ({ printf("[%s:%i " MILO_TA_YELLOW "warn" MILO_TA_CLEAR "] " fmt "\n", _MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
#define warn(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_ERROR
#define error(fmt, ...) ({ printf("[%s:%i " MILO_TA_RED "error" MILO_TA_CLEAR "] " fmt "\n", _MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
#define error(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_FATAL
#define fatal(fmt, ...) ({ printf("[%s:%i " MILO_TA_RED "fatal" MILO_TA_CLEAR "] " fmt "\n", _MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
#define fatal(fmt, ...)
#endif

// undefine all to get rid of compiler warnings

#ifdef MILO_LVL
#undef MILO_LVL
#endif

#undef trace
#undef info
#undef warn
#undef error
#undef fatal
