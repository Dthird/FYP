#!/bin/tcsh

clang++ -g loop_depth_pass.cpp \
`llvm-config --libs core irreader linker option bitwriter support all-targets --cxxflags --ldflags` -lpthread -ldl -o test
