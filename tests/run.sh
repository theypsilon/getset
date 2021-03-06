#!/bin/bash
echo ""
echo "RUNNING TEST SUITE"
echo "=================="

cd tests

$CXX --version

echo ""
echo "UNIT TESTS"
echo "----------"

$CXX unit.cpp -std=c++11 -lm -lstdc++
./a.out

echo "COMPILER TESTS"
echo "--------------"

./compile_tester.sh
