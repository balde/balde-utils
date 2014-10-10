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
    str = b_strdup(NULL);
    assert_null(str);
}


static void
test_strndup(void **state)
{
    char *str = b_strndup("bolaguda", 4);
    assert_string_equal(str, "bola");
    free(str);
    str = b_strndup("bolaguda", 30);
    assert_string_equal(str, "bolaguda");
    free(str);
    str = b_strndup("bolaguda", 8);
    assert_string_equal(str, "bolaguda");
    free(str);
    str = b_strdup(NULL);
    assert_null(str);
}


static void
test_strdup_printf(void **state)
{
    char *str = b_strdup_printf("bola");
    assert_string_equal(str, "bola");
    free(str);
    str = b_strdup_printf("bola, %s", "guda");
    assert_string_equal(str, "bola, guda");
    free(str);
}


static void
test_str_starts_with(void **state)
{
    assert_true(b_str_starts_with("bolaguda", "bola"));
    assert_true(b_str_starts_with("bola", "bola"));
    assert_false(b_str_starts_with("gudabola", "bola"));
    assert_false(b_str_starts_with("guda", "bola"));
    assert_false(b_str_starts_with("bola", "bolaguda"));
}


static void
test_str_ends_with(void **state)
{
    assert_true(b_str_ends_with("bolaguda", "guda"));
    assert_true(b_str_ends_with("bola", "bola"));
    assert_false(b_str_ends_with("gudabola", "guda"));
    assert_false(b_str_ends_with("guda", "bola"));
    assert_false(b_str_ends_with("bola", "gudabola"));
}


int
main(void)
{
    const UnitTest tests[] = {
        unit_test(test_strdup),
        unit_test(test_strndup),
        unit_test(test_strdup_printf),
        unit_test(test_str_starts_with),
        unit_test(test_str_ends_with),
    };
    return run_tests(tests);
}
