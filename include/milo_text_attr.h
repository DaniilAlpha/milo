#ifndef _INC_MILO_TEXT_ATTR
#define _INC_MILO_TEXT_ATTR

#ifndef MILO_USE_TA
#define MILO_USE_TA 1
#endif

#if MILO_USE_TA
#define MILO_TA_TRACE "\x1B[0;36m"
#define MILO_TA_INFO "\x1B[0;32m"
#define MILO_TA_WARN "\x1B[0;33m"
#define MILO_TA_ERROR "\x1B[0;31m"
#define MILO_TA_FATAL "\x1B[1;31m"
#define MILO_TA_CLEAR "\x1B[0m"
#else
#define MILO_TA_TRACE 
#define MILO_TA_INFO 
#define MILO_TA_WARN 
#define MILO_TA_ERROR 
#define MILO_TA_FATAL 
#define MILO_TA_CLEAR 
#endif

#endif
