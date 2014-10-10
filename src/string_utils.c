/*
 * balde-utils: A general purpose utility library for C.
 * Copyright (C) 2014 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <balde-utils/string_utils.h>


char*
b_strdup(const char *s)
{
    if (!s)
        return NULL;
    size_t l = strlen(s);
    char *tmp = malloc(l + 1);
    if (!tmp)
        return NULL;
    memcpy(tmp, s, l + 1);
    return tmp;
}


char*
b_strndup(const char *s, size_t n)
{
    if (!s)
        return NULL;
    size_t l = strlen(s);
    if (l > n)
        l = n;
    char *tmp = malloc(l + 1);
    if (!tmp)
        return NULL;
    memcpy(tmp, s, l + 1);
    tmp[l] = '\0';
    return tmp;
}


char*
b_strdup_printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int l = vsnprintf(NULL, 0, format, ap);
    va_end(ap);
    if (l < 0)
        return NULL;
    char *tmp = malloc(l + 1);
    if (!tmp)
        return NULL;
    va_start(ap, format);
    int l2 = vsnprintf(tmp, l + 1, format, ap);
    va_end(ap);
    if (l2 < 0)
        return NULL;
    return tmp;
}


bool
b_str_starts_with(const char *str, const char *prefix)
{
    int str_l = strlen(str);
    int str_lp = strlen(prefix);
    if (str_lp > str_l)
        return false;
    return strncmp(str, prefix, str_lp) == 0;
}


bool
b_str_ends_with(const char *str, const char *suffix)
{
    int str_l = strlen(str);
    int str_ls = strlen(suffix);
    if (str_ls > str_l)
        return false;
    return strcmp(str + str_l - str_ls, suffix) == 0;
}


b_string_t*
b_string_new(void)
{
    b_string_t* rv = malloc(sizeof(b_string_t));
    rv->str = NULL;
    rv->len = 0;
    rv->allocated_len = 0;
    return rv;
}


char*
b_string_free(b_string_t *str, bool free_str)
{
    char *rv = NULL;
    if (free_str)
        free(str->str);
    else
        rv = str->str;
    free(str);
    return rv;
}


b_string_t*
b_string_append_len(b_string_t *str, const char *suffix, size_t len)
{
    size_t old_len = str->len;
    str->len += len;
    if (str->len + 1 > str->allocated_len) {
        str->allocated_len = (((str->len + 1) / B_STRING_CHUNK_SIZE) + 1) * B_STRING_CHUNK_SIZE;
        str->str = realloc(str->str, str->allocated_len);
    }
    memcpy(str->str + old_len, suffix, len);
    str->str[str->len] = '\0';
    return str;
}
