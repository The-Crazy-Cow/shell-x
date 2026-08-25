// SPDX-License-Identifier: GPL-2.0

/**
 * @file      debug.c
 * @author    jd
 * @brief     Log level management.
 * @version   0.1
 * @date      2026-08-18
 *
 * @details
 * This file provides functions to get, set, enable, and disable
 * log levels using a bitmask.
 *
 * @copyright GNU General Public License v2.0
 */

#include "debug.h"

static unsigned int loglevel =
    (LOGLEVEL_FATAL | LOGLEVEL_WARN | LOGLEVEL_ERROR | LOGLEVEL_INFO |
     LOGLEVEL_DEBUG);

unsigned int get_loglevel(void)
{
    return loglevel;
}

unsigned int set_loglevel(const unsigned int newlevel)
{
    loglevel = newlevel;
    return loglevel;
}

unsigned int disable_loglevel(const unsigned int level)
{
    loglevel &= ~level;
    return loglevel;
}

unsigned int enable_loglevel(const unsigned int level)
{
    loglevel |= level;
    return loglevel;
}
