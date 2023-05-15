#include "milo.h"

#include <string.h>

const char *milo_get_filename(const char *filepath) {
  const char *result = strrchr(filepath, '\\');
  if (result == NULL) result = strrchr(filepath, '/');
  return result == NULL ? filepath : result + 1;
}