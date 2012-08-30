#!/bin/sh

set -x

CXXFLAGS="-O2 -g -Wall -Wno-deprecated"
export CXXFLAGS
g++ -I .. $CXXFLAGS -o thread_test.out thread_test.cc thread.cc -pthread
