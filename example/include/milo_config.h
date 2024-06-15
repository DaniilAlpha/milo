
#include <time.h>

#ifndef MILO_TIME_H
# define MILO_TIME_H

char const *milo_timestamp(char const *const fmt);

#endif

// not really nesessary, but makes this mess at least a bit prettier
#define MILO_TIME (milo_timestamp("%D %H:%M:%S"))

// be careful not to include parentheses in these two definitions, as they rely
// on string concatenation
#define MILO_PREFIX_FORMAT                                                     \
  MILO_TA_CLEAR                                                                \
  "\n"                                                                         \
  "\e[0;35m"      /* custom TA for timestamp */                                \
  "%s"            /* {timestamp} */                                            \
    MILO_TA_CLEAR /* clear custom TA */                                        \
  " - "                                                                        \
  "%s:%i: "       /* {file}&{line} */                                          \
  "%s"            /* {attr} */                                                 \
  "%s"            /* {lvl} */                                                  \
    MILO_TA_CLEAR /* clear TA */                                               \
  " in function "                                                              \
  "\e[0;37m"      /* custom TA for function */                                 \
  "%s"            /* {function} */                                             \
    MILO_TA_CLEAR /* clear custom TA */                                        \
  "\n"
#define milo_prefix_args(attr, lvl)                                            \
  MILO_TIME, MILO_FILE, MILO_LINE, (attr), (lvl), MILO_FUNC
