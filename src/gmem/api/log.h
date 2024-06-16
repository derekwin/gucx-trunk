#ifndef LOG_H
#define LOG_H

typedef enum {
    LOG_LEVEL_ERROR,        /* Error is returned to the user */
    LOG_LEVEL_WARN,         /* Something's wrong, but we continue */
    LOG_LEVEL_INFO,         /* Information */
    LOG_LEVEL_DEBUG,        /* Low-volume debugging */
} log_level_t;


static const char *log_level_names[] = {
    [LOG_LEVEL_ERROR] = "ERROR",
    [LOG_LEVEL_WARN]  = "WARN",
    [LOG_LEVEL_INFO]  = "INFO",
    [LOG_LEVEL_DEBUG] = "DEBUG"
};

#define __log(_level, _fmt, ...) \
    do { \
        printf("%s: " _fmt "\n", log_level_names[_level], ## __VA_ARGS__); \
    } while (0)

#define log_error(_fmt, ...)        __log(LOG_LEVEL_ERROR, _fmt, ## __VA_ARGS__)
#define log_warn(_fmt, ...)         __log(LOG_LEVEL_WARN, _fmt,  ## __VA_ARGS__)
#define log_info(_fmt, ...)         __log(LOG_LEVEL_INFO, _fmt, ## __VA_ARGS__)
#define log_debug(_fmt, ...)        __log(LOG_LEVEL_DEBUG, _fmt, ##  __VA_ARGS__)

#endif /* LOG_H */