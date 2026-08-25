// SPDX-License-Identifier: GPL-2.0

#ifndef CORE_PROMPT_H
#define CORE_PROMPT_H

#include <stdio.h>
#include <sys/types.h>

/** Maximum number of characters stored in the shell prompt. */
#define PROMPT_MAX_LENGTH 256

/** Maximum number of characters stored in user input. */
#define USER_INPUT_MAX_LENGTH 4096

/** Default prompt displayed when no custom prompt is provided. */
#define PROMPT_DEFAULT "shell-x> "

struct prompt_struct {
    char prompt[PROMPT_MAX_LENGTH];
    char user_input[USER_INPUT_MAX_LENGTH];
};

// user interactive purpose
ssize_t get_user_input(char *, size_t);
void print_to_user(const char *);
void print(const char *, ...) __attribute__((format(printf, 1, 2)));

// handle prompt functions
void print_prompt(void);
void prompt_init(const char *prompt_str);
void clear_user_input(void);
void clear_prompt(void);
void reset_prompt(void);
int set_prompt(const char *);
int get_prompt(char *, size_t);

#endif /*CORE_PROMPT_H*/