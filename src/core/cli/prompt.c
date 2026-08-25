// SPDX-License-Identifier: GPL-2.0

/**
 * @file prompt.c
 * @author jd (jdj17180@gmail.com)
 * @brief Manage the shell prompt and user input.
 * @version 0.1
 * @date 2026-08-24
 *
 * @copyright GNU General Public License v2.0
 *
 */

#include "prompt.h"
#include "debug.h"
#include "errors.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/** Prompt state kept private to this translation unit. */
static struct prompt_struct prompt;

static inline ssize_t user_input(size_t bytes_to_read)
{
    ssize_t n_read;

    if (bytes_to_read < 2 || bytes_to_read > USER_INPUT_MAX_LENGTH) {
        ER_INV_BUFFSIZE;
        return -1;
    }

    do {
        n_read = read(STDIN_FILENO, prompt.user_input, bytes_to_read - 1);
    } while (n_read == -1 && errno == EINTR);
    if (n_read == -1) {
        pr_error("user input()-> %d", errno);
        return -1;
    }
    prompt.user_input[n_read] = '\0';

    pr_debug("%zd bytes read", n_read);

    return n_read;
}

/**
 * @brief Store a new prompt string.
 *
 * The destination array limits the stored string to PROMPT_MAX_LENGTH - 1
 * characters and always keeps it null-terminated.
 *
 * @param prompt_str Prompt text to store.
 * @return 0 on success, or -1 if prompt_str is NULL.
 */
int set_prompt(const char *prompt_str)
{
    if (IS_NULL_PTR(prompt_str)) {
        return -1;
    } else if (strlen(prompt_str) >= PROMPT_MAX_LENGTH) {
        pr_warn(
            "Truncate prompt:assigned value exceeds maximum length of %d",
            PROMPT_MAX_LENGTH);
    }

    snprintf(prompt.prompt, PROMPT_MAX_LENGTH, "%s", prompt_str);
    return 0;
}

int get_prompt(char *buffer, size_t buffer_size)
{
    if (!buffer) {
        ER_NULL_PTR;
        return -1;
    } else if (buffer_size == 0) {
        ER_INV_BUFFSIZE;
        return -1;
    } else if (buffer_size < PROMPT_MAX_LENGTH) {
        WR_TRUNCATE_BUFFER;
    }
    snprintf(buffer, buffer_size, "%s", prompt.prompt);
    return 0;
}

/**
 * @brief Copy the stored user input into a caller-provided buffer.
 *
 * The caller-provided size is never increased, so a small buffer remains
 * protected from overflow.
 *
 * @param buffer Destination buffer.
 * @param buffer_size Size of the destination buffer in bytes.
 * @return buffer on success, or NULL if buffer is NULL.
 */
ssize_t get_user_input(char *buffer, size_t buffer_size)
{
    ssize_t n_read;
    size_t read_size = buffer_size;

    if (IS_NULL_PTR(buffer)) {
        return -1;
    }

    if (buffer_size < 2) {
        ER_INV_BUFFSIZE;
        return -1;
    }

    if (read_size > USER_INPUT_MAX_LENGTH) {
        read_size = USER_INPUT_MAX_LENGTH;
        WR_TRUNCATE_BUFFER;
    }

    n_read = user_input(read_size);
    if (n_read < 0) {
        return -1;
    }

    snprintf(buffer, buffer_size, "%s", prompt.user_input);
    return n_read;
}

/**
 * @brief Display a message to the shell user.
 *
 * @param msg Message to display.
 */
void print_to_user(const char *msg)
{
    if (!IS_NULL_PTR(msg)) {
        print("%s", msg);
    }
}

/** Display the current prompt. */
void print_prompt(void)
{
    print("%s", prompt.prompt);
    fflush(stdout);
}

/** Clear the stored user input. */
void clear_user_input(void)
{
    memset(prompt.user_input, 0, USER_INPUT_MAX_LENGTH);
}

/** Clear the stored prompt. */
void clear_prompt(void)
{
    memset(prompt.prompt, 0, PROMPT_MAX_LENGTH);
}

/** Clear both the stored prompt and the stored user input. */
void reset_prompt(void)
{
    clear_prompt();
    clear_user_input();
}

/**
 * @brief Initialize the prompt state.
 *
 * @param prompt_str Prompt text, or NULL to use PROMPT_DEFAULT.
 */
void prompt_init(const char *prompt_str)
{
    pr_info("Initializing prompt");

    if (!prompt_str) {
        set_prompt(PROMPT_DEFAULT);
    } else {
        set_prompt(prompt_str);
    }
}

/**
 * @brief Print formatted output for the shell user.
 *
 * @param format printf-compatible format string.
 * @param ... Values referenced by format.
 */
void print(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
