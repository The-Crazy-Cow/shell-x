// SPDX-License-Identifier: GPL-2.0

/**
 * @file core.c
 * @author jd (jdj17180@gmail.com)
 * @brief Manage the shell internals.
 * @version 0.1
 * @date 2026-08-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "core.h"
#include "errors.h"



/** Current execution status of the shell. */
static unsigned int shell_status = RUNNING;

/**
 * @brief Get the current shell execution status.
 *
 * @return The current shell status, such as RUNNING or STOPPED.
 */
unsigned int get_shell_status(void)
{
    return shell_status;
}

/**
 * @brief Set the shell execution status.
 *
 * @param status New status value to store.
 * @return 1 on success, or -1 if status is outside the valid range.
 */
int set_shell_status(unsigned int status)
{
    if (status >= NSHELL_STATUS) {
        OUT_OF_RANGE;
        return -1;
    }

    shell_status = status;
    return 1;
}