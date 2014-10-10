/*
 * balde-utils: A general purpose utility library for C.
 * Copyright (C) 2014 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#ifndef _BALDE_UTILS__STRING_UTILS_H
#define _BALDE_UTILS__STRING_UTILS_H

#include <stdbool.h>

#define B_STRING_CHUNK_SIZE 128

typedef struct _b_string_t {
    char *str;
    size_t len;
    size_t allocated_len;
} b_string_t;

char* b_strdup(const char *s);
char* b_strndup(const char *s, size_t n);
char* b_strdup_printf(const char *format, ...);
bool b_str_starts_with(const char *str, const char *prefix);
bool b_str_ends_with(const char *str, const char *suffix);

b_string_t* b_string_new(void);
char* b_string_free(b_string_t *str, bool free_str);
b_string_t* b_string_append_len(b_string_t *str, const char *suffix, size_t len);
b_string_t* b_string_append(b_string_t *str, const char *suffix);

#endif /* _BALDE_UTILS__STRING_UTILS_H */
