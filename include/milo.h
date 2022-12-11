#define MILO_ALL 5
#define MILO_INFO 4
#define MILO_WARNING 3
#define MILO_ERROR 2
#define MILO_FATAL 1
#define MILO_SILENT 0

#ifndef MILO_LVL
#define MILO_LVL MILO_SILENT
#endif

#if MILO_LVL >= MILO_ALL
#define deb(fmt, ...) printf("[deb] " fmt "\n", ##__VA_ARGS__)
#else
#define deb(fmt, ...)
#endif

#if MILO_LVL >= MILO_INFO
#define inf(fmt, ...) printf("[inf] " fmt "\n", ##__VA_ARGS__)
#else
#define inf(fmt, ...)
#endif

#if MILO_LVL >= MILO_WARNING
#define war(fmt, ...) printf("[war] " fmt "\n", ##__VA_ARGS__)
#else
#define war(fmt, ...)
#endif

#if MILO_LVL >= MILO_ERROR
#define err(fmt, ...) printf("[err] " fmt "\n", ##__VA_ARGS__)
#else
#define err(fmt, ...)
#endif

#if MILO_LVL >= MILO_FATAL
#define fatal(fmt, ...) printf("[fatal] " fmt "\n", ##__VA_ARGS__)
#else
#define fatal(fmt, ...)
#endif
