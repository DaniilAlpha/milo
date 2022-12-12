#ifndef _INC_TEXT_ATTR
#define _INC_TEXT_ATTR

#ifndef MILO_USE_TA
#define MILO_USE_TA 1
#endif

#if MILO_USE_TA
#define MILO_TA_BLUE "\x1B[0;35m"
#define MILO_TA_GREEN "\x1B[0;32m"
#define MILO_TA_YELLOW "\x1B[0;33m"
#define MILO_TA_RED "\x1B[0;31m"
#define MILO_TA_CLEAR "\x1B[0m"
#else
#define MILO_TA_BLUE
#define MILO_TA_GREEN
#define MILO_TA_YELLOW
#define MILO_TA_RED
#define MILO_TA_CLEAR
#endif

#endif