#!/bin/sh

set -x

CXXFLAGS="-O2 -g -Wall"
export CXXFLAGS
g++ -I .. $CXXFLAGS -o sort_test.out sort_test.cc
g++ -I .. $CXXFLAGS -o hashtable_test.out hashtable_test.cc
