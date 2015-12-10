#!/bin/sh

#rm -f lex.yy.c

for infile in *.c; do
    if [ $infile != "lex.yy.c" ]; then
        clang -emit-llvm -c  $infile; 
    fi
done

llvm-link -f *.bc -o p.bc
