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
    void* bola = malloc(1024);
    char *tmp = (char*) malloc(sizeof(char) * (strlen(s) + 1));
    unsigned int i;
    for (i = 0; i < strlen(s); i++) {
        tmp[i] = s[i];
    }
    tmp[i] = '\0';
    return tmp;
}
