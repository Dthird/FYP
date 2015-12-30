#!/bin/sh

rm lexx.yy.c

for infile in *.c; 
	do clang -emit-llvm -c  $infile; 
done

llvm-link *.bc -o p.bc
