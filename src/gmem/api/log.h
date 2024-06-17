#ifndef LOG_H
#define LOG_H
#include <stdio.h>

typedef enum {
    LOG_LEVEL_ERROR,        /* Error is returned to the user */
    LOG_LEVEL_WARN,         /* Something's wrong, but we continue */
    LOG_LEVEL_INFO,         /* Information */
    LOG_LEVEL_DEBUG,        /* Low-volume debugging */
} log_level_t;

#define __memlog(_level, _fmt, ...) \
    do { \
        printf("%s: " _fmt "\n", _level, ## __VA_ARGS__); \
    } while (0)

#define log_error(_fmt, ...)        __memlog("ERROR", _fmt, ## __VA_ARGS__)
#define log_warn(_fmt, ...)         __memlog("WARN", _fmt,  ## __VA_ARGS__)
#define log_info(_fmt, ...)         __memlog("INFO", _fmt, ## __VA_ARGS__)
#define log_debug(_fmt, ...)        __memlog("DEBUG", _fmt, ##  __VA_ARGS__)

#endif /* LOG_H */