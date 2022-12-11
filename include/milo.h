#define MILO_LVL_ALL 5
#define MILO_LVL_INFO 4
#define MILO_LVL_WARN 3
#define MILO_LVL_ERROR 2
#define MILO_LVL_FATAL 1
#define MILO_LVL_SILENT 0

#if MILO_LVL >= MILO_LVL_ALL
#define trace(fmt, ...) printf("[trace] " fmt "\n", ##__VA_ARGS__)
#else
#define trace(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_INFO
#define info(fmt, ...) printf("[info ] " fmt "\n", ##__VA_ARGS__)
#else
#define info(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_WARN
#define warn(fmt, ...) printf("[warn ] " fmt "\n", ##__VA_ARGS__)
#else
#define warn(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_ERROR
#define error(fmt, ...) printf("[error] " fmt "\n", ##__VA_ARGS__)
#else
#define error(fmt, ...)
#endif

#if MILO_LVL >= MILO_LVL_FATAL
#define fatal(fmt, ...) printf("[fatal] " fmt "\n", ##__VA_ARGS__)
#else
#define fatal(fmt, ...)
#endif
