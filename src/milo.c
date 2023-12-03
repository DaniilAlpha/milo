#include "../include/milo.h"

const char *milo_filename(const char *const filepath) {
  for (const char *c = filepath; *c != '\0'; c++)
    if (*c == '\\' || *c == '/') return c + 1;
  return filepath;
}
