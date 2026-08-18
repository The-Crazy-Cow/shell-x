// SPDX-License-Identifier: GPL-2.0

#ifndef INCLUDE_DEBUG_H
#define INCLUDE_DEBUG_H

#include <stdio.h>

/**
 * @brief Log levels used by the logging system.
 *
 * Each log level is represented by a bit flag and can be combined
 * using bitwise operations with loglevel define in include/debug.c.
 *
 * By default, all log levels are enabled in loglevel.
 *
 * @note The DEBUG log level is enabled only when DEBUG is defined.
 */

#define LOGLEVEL_FATAL 0x01
#define LOGLEVEL_WARN 0x02
#define LOGLEVEL_ERROR 0x04
#define LOGLEVEL_INFO 0x08
#define LOGLEVEL_DEBUG 0x10

/**
 * @brief Functions for managing the logging level mask.
 *
 * These functions allow retrieving, setting, enabling, and disabling
 * individual or multiple log levels using bitwise operations.
 *
 * @note Each log level is represented by a bit flag.
 */
unsigned int get_loglevel(void);
unsigned int set_loglevel(const unsigned int);
unsigned int disable_loglevel(const unsigned int);
unsigned int enable_loglevel(const unsigned int);

#ifdef DEBUG
#define log_debug(fmt, ...)                                                    \
    do {                                                                       \
        fprintf(                                                               \
            stderr,                                                            \
            "\n%s:%s:%d--|" fmt "\n",                                          \
            __func__,                                                          \
            __FILE__,                                                          \
            __LINE__,                                                          \
            ##__VA_ARGS__);                                                    \
        fflush(stderr);                                                        \
    } while (0)
#else
#define log_debug(...) ((void)0)
#endif /*DEBUG*/

#define pr_fatal(fmt, ...)                                                     \
    do {                                                                       \
        if (get_loglevel() & LOGLEVEL_FATAL)                                   \
            log_debug("[FATAL] " fmt, ##__VA_ARGS__);                          \
    } while (0)

#define pr_warn(fmt, ...)                                                      \
    do {                                                                       \
        if (get_loglevel() & LOGLEVEL_WARN)                                    \
            log_debug("[WARN] " fmt, ##__VA_ARGS__);                           \
    } while (0)

#define pr_error(fmt, ...)                                                     \
    do {                                                                       \
        if (get_loglevel() & LOGLEVEL_ERROR)                                   \
            log_debug("[ERR] " fmt, ##__VA_ARGS__);                            \
    } while (0)

#define pr_info(fmt, ...)                                                      \
    do {                                                                       \
        if (get_loglevel() & LOGLEVEL_INFO)                                    \
            log_debug("[INFO] " fmt, ##__VA_ARGS__);                           \
    } while (0)

#define pr_debug(fmt, ...)                                                     \
    do {                                                                       \
        if ((get_loglevel()) & LOGLEVEL_DEBUG)                                 \
            log_debug("[DEBUG] " fmt, ##__VA_ARGS__);                          \
    } while (0)

#endif /*INCLUDE_DEBUG_H*/