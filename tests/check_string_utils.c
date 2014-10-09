/*
 * balde-utils: A general purpose utility library for C.
 * Copyright (C) 2014 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the BSD License.
 * See the file COPYING.
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>

#include <balde-utils/string_utils.h>


static void
test_strdup(void **state)
{
    char *str = b_strdup("bola");
    assert_string_equal(str, "bola");
    free(str);
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_strdup),
    };
    return run_tests(tests);
}
