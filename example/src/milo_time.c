#include "milo_config.h"

const char *milo_timestamp(const char *const fmt) {
  static char buf[32] = {0};
  static time_t t;

  time(&t);
  strftime(buf, 32, fmt, localtime(&t));
  return buf;
}
