// SPDX-License-Identifier: GPL-2.0

#ifndef CORE_PROMPT_H
#define CORE_PROMPT_H

#include <stddef.h>
#include <stdio.h>

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

void print_prompt(void);
void prompt_init(const char *prompt_str);
int set_prompt(const char *);
size_t get_prompt(char *, size_t);
char *get_user_input(char *, size_t);
void print_to_user(const char *);

void clear_user_input(void);
void clear_prompt(void);
void reset_prompt(void);
void print(const char *, ...) __attribute__((format(printf, 1, 2)));

#endif /*CORE_PROMPT_H*/