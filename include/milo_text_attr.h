#ifndef _INC_MILO_TEXT_ATTR
#define _INC_MILO_TEXT_ATTR

#include <stdbool.h>

#ifndef MILO_USE_TEXT_ATTR
#define MILO_USE_TEXT_ATTR (true)
#endif

#if MILO_USE_TEXT_ATTR
#define MILO_TEXT_ATTR_TRACE "\x1B[0;36m"
#define MILO_TEXT_ATTR_INFO "\x1B[0;32m"
#define MILO_TEXT_ATTR_WARN "\x1B[0;33m"
#define MILO_TEXT_ATTR_ERROR "\x1B[0;31m"
#define MILO_TEXT_ATTR_FATAL "\x1B[1;31m"
#define MILO_TEXT_ATTR_CLEAR "\x1B[0m"
#else
#define MILO_TEXT_ATTR_TRACE
#define MILO_TEXT_ATTR_INFO
#define MILO_TEXT_ATTR_WARN
#define MILO_TEXT_ATTR_ERROR
#define MILO_TEXT_ATTR_FATAL
#define MILO_TEXT_ATTR_CLEAR
#endif

#endif
