/*
 * balde-utils: A general purpose utility library for C.
 * Copyright (C) 2014 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#include <string.h>
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
