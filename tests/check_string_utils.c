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


static void
test_string_new(void **state)
{
    b_string_t *str = b_string_new();
    assert_non_null(str);
    assert_null(str->str);
    assert_int_equal(str->len, 0);
    assert_int_equal(str->allocated_len, 0);
    assert_null(b_string_free(str, true));
}


static void
test_string_append_len(void **state)
{
    b_string_t *str = b_string_new();
    str = b_string_append_len(str, "guda", 4);
    assert_non_null(str);
    assert_string_equal(str->str, "guda");
    assert_int_equal(str->len, 4);
    assert_int_equal(str->allocated_len, B_STRING_CHUNK_SIZE);
    assert_null(b_string_free(str, true));
    str = b_string_new();
    str = b_string_append_len(str, "guda", 4);
    str = b_string_append_len(str, "bola", 4);
    assert_non_null(str);
    assert_string_equal(str->str, "gudabola");
    assert_int_equal(str->len, 8);
    assert_int_equal(str->allocated_len, B_STRING_CHUNK_SIZE);
    assert_null(b_string_free(str, true));
    str = b_string_new();
    str = b_string_append_len(str, "guda", 3);
    str = b_string_append_len(str, "bola", 4);
    assert_non_null(str);
    assert_string_equal(str->str, "gudbola");
    assert_int_equal(str->len, 7);
    assert_int_equal(str->allocated_len, B_STRING_CHUNK_SIZE);
    assert_null(b_string_free(str, true));
    str = b_string_new();
    str = b_string_append_len(str, "guda", 4);
    str = b_string_append_len(str,
        "cwlwmwxxmvjnwtidmjehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjidzkcw"
        "nnqhxhneolbwqlctcxmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtaxjiwa"
        "xfhfyzymtffusoqywaruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqvevaz"
        "dxrewtgapkompnviiyielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywhqcec"
        "hgrwzaglzogwjvqncjzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxjrsbc"
        "sbfvpylgjznsuhxcxoqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqdatnd"
        "dxntikgoqlidfnmdhxzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvwsrnr"
        "ftzfeyasjpxoevyptpdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsfnwtg"
        "okxhegoifakimxbbafkeannglvsxprqzfekdinssqymtfexf", 600);
    str = b_string_append_len(str, NULL, 0);
    str = b_string_append_len(str,
        "cwlwmwxxmvjnwtidmjehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjidzkcw"
        "nnqhxhneolbwqlctcxmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtaxjiwa"
        "xfhfyzymtffusoqywaruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqvevaz"
        "dxrewtgapkompnviiyielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywhqcec"
        "hgrwzaglzogwjvqncjzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxjrsbc"
        "sbfvpylgjznsuhxcxoqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqdatnd"
        "dxntikgoqlidfnmdhxzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvwsrnr"
        "ftzfeyasjpxoevyptpdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsfnwtg"
        "okxhegoifakimxbbafkeannglvsxprqzfekdinssqymtfexf", 600);
    assert_non_null(str);
    assert_string_equal(str->str,
        "gudacwlwmwxxmvjnwtidmjehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjid"
        "zkcwnnqhxhneolbwqlctcxmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtax"
        "jiwaxfhfyzymtffusoqywaruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqv"
        "evazdxrewtgapkompnviiyielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywh"
        "qcechgrwzaglzogwjvqncjzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxj"
        "rsbcsbfvpylgjznsuhxcxoqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqd"
        "atnddxntikgoqlidfnmdhxzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvw"
        "srnrftzfeyasjpxoevyptpdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsf"
        "nwtgokxhegoifakimxbbafkeannglvsxprqzfekdinssqymtfexfcwlwmwxxmvjnwtidm"
        "jehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjidzkcwnnqhxhneolbwqlctc"
        "xmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtaxjiwaxfhfyzymtffusoqyw"
        "aruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqvevazdxrewtgapkompnvii"
        "yielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywhqcechgrwzaglzogwjvqnc"
        "jzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxjrsbcsbfvpylgjznsuhxcx"
        "oqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqdatnddxntikgoqlidfnmdh"
        "xzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvwsrnrftzfeyasjpxoevypt"
        "pdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsfnwtgokxhegoifakimxbba"
        "fkeannglvsxprqzfekdinssqymtfexf");
    assert_int_equal(str->len, 1204);
    assert_int_equal(str->allocated_len, B_STRING_CHUNK_SIZE * 10);
    assert_null(b_string_free(str, true));
}


static void
test_string_append(void **state)
{
    b_string_t *str = b_string_new();
    str = b_string_append(str, "guda");
    assert_non_null(str);
    assert_string_equal(str->str, "guda");
    assert_int_equal(str->len, 4);
    assert_int_equal(str->allocated_len, B_STRING_CHUNK_SIZE);
    assert_null(b_string_free(str, true));
    str = b_string_new();
    str = b_string_append(str, "guda");
    str = b_string_append(str, "bola");
    assert_non_null(str);
    assert_string_equal(str->str, "gudabola");
    assert_int_equal(str->len, 8);
    assert_int_equal(str->allocated_len, B_STRING_CHUNK_SIZE);
    assert_null(b_string_free(str, true));
    str = b_string_new();
    str = b_string_append(str, "guda");
    str = b_string_append(str,
        "cwlwmwxxmvjnwtidmjehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjidzkcw"
        "nnqhxhneolbwqlctcxmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtaxjiwa"
        "xfhfyzymtffusoqywaruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqvevaz"
        "dxrewtgapkompnviiyielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywhqcec"
        "hgrwzaglzogwjvqncjzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxjrsbc"
        "sbfvpylgjznsuhxcxoqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqdatnd"
        "dxntikgoqlidfnmdhxzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvwsrnr"
        "ftzfeyasjpxoevyptpdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsfnwtg"
        "okxhegoifakimxbbafkeannglvsxprqzfekdinssqymtfexf");
    str = b_string_append(str, NULL);
    str = b_string_append(str,
        "cwlwmwxxmvjnwtidmjehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjidzkcw"
        "nnqhxhneolbwqlctcxmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtaxjiwa"
        "xfhfyzymtffusoqywaruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqvevaz"
        "dxrewtgapkompnviiyielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywhqcec"
        "hgrwzaglzogwjvqncjzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxjrsbc"
        "sbfvpylgjznsuhxcxoqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqdatnd"
        "dxntikgoqlidfnmdhxzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvwsrnr"
        "ftzfeyasjpxoevyptpdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsfnwtg"
        "okxhegoifakimxbbafkeannglvsxprqzfekdinssqymtfexf");
    assert_non_null(str);
    assert_string_equal(str->str,
        "gudacwlwmwxxmvjnwtidmjehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjid"
        "zkcwnnqhxhneolbwqlctcxmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtax"
        "jiwaxfhfyzymtffusoqywaruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqv"
        "evazdxrewtgapkompnviiyielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywh"
        "qcechgrwzaglzogwjvqncjzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxj"
        "rsbcsbfvpylgjznsuhxcxoqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqd"
        "atnddxntikgoqlidfnmdhxzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvw"
        "srnrftzfeyasjpxoevyptpdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsf"
        "nwtgokxhegoifakimxbbafkeannglvsxprqzfekdinssqymtfexfcwlwmwxxmvjnwtidm"
        "jehzdeexbxjnjowruxjrqpgpfhmvwgqeacdjissntmbtsjidzkcwnnqhxhneolbwqlctc"
        "xmrsutolrjikpavxombpfpjyaqltgvzrjidotalcuwrwxtaxjiwaxfhfyzymtffusoqyw"
        "aruxpybwggukltspqqmghzpqstvcvlqbkhquihzndnrvkaqvevazdxrewtgapkompnvii"
        "yielanoyowgqhssntyvcvqqtfjmkphywbkvzfyttaalttywhqcechgrwzaglzogwjvqnc"
        "jzodaqsblcbpcdpxmrtctzginvtkckhqvdplgjvbzrnarcxjrsbcsbfvpylgjznsuhxcx"
        "oqbpxowmsrgwimxjgyzwwmryqvstwzkglgeezelvpvkwefqdatnddxntikgoqlidfnmdh"
        "xzevqzlzubvyleeksdirmmttqthhkvfjggznpmarcamacpvwsrnrftzfeyasjpxoevypt"
        "pdnqokswiondusnuymqwaryrmdgscbnuilxtypuynckancsfnwtgokxhegoifakimxbba"
        "fkeannglvsxprqzfekdinssqymtfexf");
    assert_int_equal(str->len, 1204);
    assert_int_equal(str->allocated_len, B_STRING_CHUNK_SIZE * 10);
    assert_null(b_string_free(str, true));
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
        unit_test(test_string_new),
        unit_test(test_string_append_len),
        unit_test(test_string_append),
    };
    return run_tests(tests);
}
