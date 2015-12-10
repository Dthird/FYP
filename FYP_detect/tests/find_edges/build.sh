#!/bin/tcsh

clang++ -g find_all_edges.cpp \
`llvm-config --libs core irreader option support all-targets --cxxflags --ldflags` -lpthread -ldl -o test
