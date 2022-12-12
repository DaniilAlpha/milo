#define MILO_LVL_ALL 5
#define MILO_LVL_INFO 4
#define MILO_LVL_WARN 3
#define MILO_LVL_ERROR 2
#define MILO_LVL_FATAL 1
#define MILO_LVL_SILENT 0

#ifndef MILO_LVL
#define MILO_LVL MILO_LVL_INFO
#endif

#ifndef MILO_COLORED
#define MILO_COLORED 1
#endif

#if MILO_COLORED
#define MILO_TA_BLUE "\x1B[0;34m"
#define MILO_TA_GREEN "\x1B[0;32m"
#define MILO_TA_YELLOW "\x1B[0;33m"
#define MILO_TA_RED "\x1B[0;31m"
#define MILO_TA_CLEAR "\x1B[0m"
#else
#define MILO_BLUE_COLOR
#define MILO_GREEN_COLOR
#define MILO_YELLOW_COLOR
#define MILO_RED_COLOR
#define MILO_DEFAULT_COLOR
#endif

#define MILO_FILENAME (strrchr(__FILE__, '/') + 1)

#if MILO_LVL >= MILO_LVL_ALL
#define trace(fmt, ...) ({ printf("[%s:%i " MILO_TA_BLUE "trace" MILO_TA_CLEAR "] " fmt "\n", MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
#define trace(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_INFO
#define info(fmt, ...) ({ printf("[%s:%i " MILO_TA_GREEN "info" MILO_TA_CLEAR "] " fmt "\n", MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
#define info(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_WARN
#define warn(fmt, ...) ({ printf("[%s:%i " MILO_TA_YELLOW "warn" MILO_TA_CLEAR "] " fmt "\n", MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
#define warn(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_ERROR
#define error(fmt, ...) ({ printf("[%s:%i " MILO_TA_RED "error" MILO_TA_CLEAR "] " fmt "\n", MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
#define error(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_FATAL
#define fatal(fmt, ...) ({ printf("[%s:%i " MILO_TA_RED "fatal" MILO_TA_CLEAR "] " fmt "\n", MILO_FILENAME, __LINE__, ##__VA_ARGS__); })
#else
#define fatal(fmt, ...)
#endif

#ifndef MILO_LVL
#undef MILO_LVL
#endif
