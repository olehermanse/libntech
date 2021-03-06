#!/bin/sh
set -e
set -x

cd $TRAVIS_BUILD_DIR || exit 1

if [ "$TRAVIS_OS_NAME" = osx ]
then
    ./autogen.sh --enable-debug --with-openssl="$(brew --prefix openssl)"
    gmake --version
    gmake CFLAGS="-Werror -Wall"
    gmake --debug -C tests/unit check
    exit
elif [ "$JOB_TYPE" = compile_and_unit_test_no_deps ]
then
    ./autogen.sh --enable-debug --with-pcre=no --with-openssl=no
    make CFLAGS="-Werror -Wall"
    make check
    exit
else
    NO_CONFIGURE=1 ./autogen.sh
    ./configure --enable-debug --prefix=$INSTDIR \
        `[ "x$COVERAGE" != xno ] && echo --enable-coverage`
fi

if [ "$JOB_TYPE" = compile_only ]
then
    make CFLAGS="-Werror" -k
elif [ "$JOB_TYPE" = compile_and_unit_test ]
then
    make CFLAGS="-Wall -Wextra -Werror -Wno-sign-compare"
    make -C tests/unit check
    exit
elif [ "$JOB_TYPE" = compile_and_unit_test_asan ]
then
    make CFLAGS="-Werror -Wall -fsanitize=address" LDFLAGS="-fsanitize=address"
    make -C tests/unit CFLAGS="-fsanitize=address" LDFLAGS="-fsanitize=address" check
    exit
else
    make
fi
