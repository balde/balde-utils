## Autotools settings

include balde-utils.mk

ACLOCAL_AMFLAGS = -I m4

AM_DISTCHECK_CONFIGURE_FLAGS = \
	--with-cmocka \
	--enable-examples


## File listings

EXTRA_DIST = \
	autogen.sh \
	.version \
	build-aux/git-version-gen \
	README.md

CLEANFILES =

BUILT_SOURCES = \
	.version

include_HEADERS = $(BALDE_UTILS_HEADERS_)

pkginclude_HEADERS = $(BALDE_UTILS_PKG_HEADERS_)

noinst_HEADERS =

lib_LTLIBRARIES = \
	src/libbalde_utils.la

noinst_LTLIBRARIES =

noinst_PROGRAMS =

check_PROGRAMS =

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = balde-utils.pc


## Build rules: libbalde_utils

src_libbalde_utils_la_SOURCES = $(BALDE_UTILS_SOURCES_)

src_libbalde_utils_la_CFLAGS = \
	$(AM_CFLAGS) \
	-I$(top_srcdir)/include

src_libbalde_utils_la_LIBADD =

src_libbalde_utils_la_LDFLAGS = \
	-version-info $(LIBBALDE_UTILS_LT_VERSION_INFO)


## Build rules: examples

if BUILD_EXAMPLES

noinst_PROGRAMS +=

#examples_hello_SOURCES = \
#	examples/hello.c

#examples_hello_CFLAGS = \
#	-I$(top_srcdir)/include

#examples_hello_LDFLAGS = \
#	-no-install

#examples_hello_LDADD= \
#	src/libbalde_utils.la

endif


## Build rules: tests

if USE_CMOCKA

check_PROGRAMS += \
	tests/check_string_utils \
	tests/check_slist \
	tests/check_trie

tests_check_string_utils_SOURCES = \
	tests/check_string_utils.c

tests_check_string_utils_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/include

tests_check_string_utils_LDFLAGS = \
	-no-install

tests_check_string_utils_LDADD = \
	$(CMOCKA_LIBS) \
	src/libbalde_utils.la

tests_check_slist_SOURCES = \
	tests/check_slist.c

tests_check_slist_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/include

tests_check_slist_LDFLAGS = \
	-no-install

tests_check_slist_LDADD = \
	$(CMOCKA_LIBS) \
	src/libbalde_utils.la

tests_check_trie_SOURCES = \
	tests/check_trie.c

tests_check_trie_CFLAGS = \
	$(CMOCKA_CFLAGS) \
	-I$(top_srcdir)/include

tests_check_trie_LDFLAGS = \
	-no-install

tests_check_trie_LDADD = \
	$(CMOCKA_LIBS) \
	src/libbalde_utils.la

endif

TESTS = \
	$(check_PROGRAMS)


## Helpers: Valgrind runners

if USE_VALGRIND
valgrind: all
	$(MAKE) check TESTS_ENVIRONMENT=" \
		$(VALGRIND) \
			--tool=memcheck \
			--leak-check=full \
			--leak-resolution=high \
			--num-callers=20 \
			--show-possibly-lost=no"

valgrind-ci: all clean-local
	$(MAKE) check TESTS_ENVIRONMENT=" \
		$(VALGRIND) \
			--tool=memcheck \
			--xml=yes \
			--xml-file=valgrind-%p.xml \
			--leak-check=full \
			--leak-resolution=high \
			--num-callers=20 \
			--show-possibly-lost=no"
endif


# Helpers: Git version

.version:
	echo $(VERSION) > $@-t && mv $@-t $@

dist-hook:
	echo $(VERSION) > $(distdir)/.tarball-version


# Helpers: Cleanup of helper files

clean-local:
	-rm -rf valgrind-*.xml


# Helpers: Documentation

if BUILD_DOCS
#doxygen: clean-local Doxyfile
#	$(DOXYGEN) Doxyfile

if PUBLISH_DOCS
#publish_docs: doxygen
#	$(GITHUB_PAGES_PUBLISH) --verbose \
#		--cname docs.balde.io \
#		. doc/build/html
endif
endif
