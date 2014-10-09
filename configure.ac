AC_PREREQ([2.69])

AC_INIT([balde-utils], [m4_esyscmd(build-aux/git-version-gen .tarball-version)],
  [https://github.com/balde/balde-utils], [balde-utils], [http://balde.io])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# code changed: REVISION++.
# interface changed: CURRENT++, REVISION=0.
# interface changed (backwards compatible): AGE++, else AGE=0.
LIBBALDE_UTILS_CURRENT=0
LIBBALDE_UTILS_AGE=0
LIBBALDE_UTILS_REVISION=0

LIBBALDE_UTILS_LT_VERSION_INFO="$LIBBALDE_UTILS_CURRENT:$LIBBALDE_UTILS_REVISION:$LIBBALDE_UTILS_AGE"
AC_SUBST(LIBBALDE_UTILS_LT_VERSION_INFO)

AM_INIT_AUTOMAKE([1.13 foreign dist-bzip2 dist-xz subdir-objects serial-tests])
AC_CONFIG_HEADERS([config.h])
AM_SILENT_RULES([yes])
AM_MAINTAINER_MODE([enable])

LT_INIT

AC_PROG_CC_C99
AS_IF([test "x$ac_cv_prog_cc_c99" = "xno"], [
  AC_MSG_ERROR([no C99 compiler found, balde-utils requires a C99 compiler.])
])

AC_ARG_ENABLE([examples], AS_HELP_STRING([--enable-examples], [build examples]))
AS_IF([test "x$enable_examples" = "xyes"], [
  build_examples=yes
  EXAMPLES="enabled"
], [
  build_examples=no
  EXAMPLES="disabled"
])
AM_CONDITIONAL([BUILD_EXAMPLES], [test "x$build_examples" = "xyes"])

AC_ARG_WITH([doxygen], AS_HELP_STRING([--without-doxygen],
            [ignore presence of doxygen and disable documentation build]))
AS_IF([test "x$with_doxygen" != "xno"], [
  AC_PATH_PROG([doxygen], [doxygen])
  AS_IF([test "x$ac_cv_path_doxygen" = "x"], [
    have_doxygen=no
  ], [
    have_doxygen=yes
  ])
  AC_PATH_PROG([github_pages_publish], [github-pages-publish])
])
AS_IF([test "x$have_doxygen" = "xyes"], , [
  AS_IF([test "x$with_doxygen" = "xyes"], [
    AC_MSG_ERROR([doxygen requested but not found])
  ])
])

AM_CONDITIONAL([BUILD_DOCS], [test "x$have_doxygen" = "xyes"])
AM_CONDITIONAL([PUBLISH_DOCS], [test "x$ac_cv_path_github_pages_publish" != "x"])

DOXYGEN="$ac_cv_path_doxygen"
GITHUB_PAGES_PUBLISH="$ac_cv_path_github_pages_publish"

AC_SUBST(DOXYGEN)
AC_SUBST(GITHUB_PAGES_PUBLISH)


AC_ARG_WITH([cmocka], AS_HELP_STRING([--without-cmocka],
            [ignore presence of cmocka. this will disable tests]))
AS_IF([test "x$with_cmocka" != "xno"], [
  PKG_PROG_PKG_CONFIG
  PKG_CHECK_MODULES([CMOCKA], [cmocka], [
    have_cmocka=yes
  ], [
    have_cmocka=no
  ])
])
AS_IF([test "x$have_cmocka" = "xyes"], , [
  AS_IF([test "x$with_cmocka" = "xyes"], [
    AC_MSG_ERROR([cmocka requested but not found])
  ])
])
AM_CONDITIONAL([USE_CMOCKA], [test "x$have_cmocka" = "xyes"])

AC_ARG_WITH([valgrind], AS_HELP_STRING([--without-valgrind],
            [ignore presence of valgrind]))
AS_IF([test "x$with_valgrind" != "xno"], [
  AC_PATH_PROG([valgrind], [valgrind])
  AS_IF([test "x$ac_cv_path_valgrind" = "x"], [
    have_valgrind=no
  ], [
    have_valgrind=yes
  ])
])
AS_IF([test "x$have_valgrind" = "xyes"], , [
  AS_IF([test "x$with_valgrind" = "xyes"], [
    AC_MSG_ERROR([valgrind requested but not found])
  ])
])
AM_CONDITIONAL([USE_VALGRIND], [test "x$have_valgrind" = "xyes"])
VALGRIND="$ac_cv_path_valgrind"
AC_SUBST(VALGRIND)

AC_CONFIG_FILES([
    Makefile
    balde-utils.pc
])
AC_OUTPUT

AS_ECHO("
        ==== ${PACKAGE_STRING} ====

        prefix:       ${prefix}
        exec_prefix:  ${exec_prefix}
        bindir:       ${bindir}

        compiler:     ${CC}
        cflags:       ${CFLAGS}
        ldflags:      ${LDFLAGS}

        examples:     ${EXAMPLES}

        doxygen:      ${DOXYGEN}
        valgrind:     ${VALGRIND}
")
