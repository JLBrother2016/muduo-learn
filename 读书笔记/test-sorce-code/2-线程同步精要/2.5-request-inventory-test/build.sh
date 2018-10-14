#!/bin/sh

set -x

SOURCE_DIR=`pwd`
BUILD_DIR=${BUILD_DIR:-./build}
rm -r $BUILD_DIR

mkdir -p $BUILD_DIR \
  && cd $BUILD_DIR \
  && cmake $SOURCE_DIR \
  && make $*