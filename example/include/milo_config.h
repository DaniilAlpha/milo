#ifndef MILO_CONFIG_H
#define MILO_CONFIG_H

#include <time.h>
static char buf[32] = {0};
static inline char const *milo_timestamp(char const *const fmt) {
    time_t const t = time(NULL);
    strftime(buf, sizeof(buf), fmt, localtime(&t));
    return buf;
}

#define MILO_TA_TRACE ("\033[0;30m")
#define MILO_TA_INFO  ("\033[0;37m")
#define MILO_TA_WARN  ("\033[0;93m")
#define MILO_TA_ERROR ("\033[0;31m")
#define MILO_TA_FATAL ("\033[0;41;30m")

#define MILO_TA_FILE  "\033[0;2m"
#define MILO_TA_CLEAR "\033[0m"

// be careful not to include parentheses in these two, as they rely heavily on
// string concatenation
#define MILO_PREFIX_FORMAT                                                     \
    MILO_TA_CLEAR                                                              \
    "%s"       /* {attr} */                                                    \
    "%s"       /* {timestamp} */                                               \
    " %s %s: " /* {file}:{line} {func} */
#define MILO_PREFIX_ARGS(attr, lvl)                                            \
    (attr), milo_timestamp("%b %d %H:%M:%S"), MILO_FILE, MILO_FUNC

#endif
