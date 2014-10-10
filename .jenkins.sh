#!/bin/bash
#
# balde-utils test runner for Jenkins CI.
#
# depends on cmocka and valgrind

## balde-utils variables
BALDE_UTILS_SRC_DIR="$(pwd)"
BALDE_UTILS_BUILD_DIR="${BALDE_UTILS_SRC_DIR}/build"

rm -rf "${BALDE_UTILS_BUILD_DIR}"

./autogen.sh

mkdir -p "${BALDE_UTILS_BUILD_DIR}"
pushd "${BALDE_UTILS_BUILD_DIR}" > /dev/null
"${BALDE_UTILS_SRC_DIR}"/configure \
    --enable-examples \
    --with-cmocka \
    --with-valgrind
popd > /dev/null

make \
    -j"$(($(cat /proc/cpuinfo | grep processor | wc -l)+1))" \
    -C "${BALDE_UTILS_BUILD_DIR}" valgrind-ci
