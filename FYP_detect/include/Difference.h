#ifndef DIFFERENCE_H
#define DIFFERENCE_H

#include "llvm/ADT/SmallVector.h"
#include <cmath>

using namespace llvm;

#define PROGRAM_SMALL_VECTOR_SIZE 10
#define FUNCTION_LEVEL_THRESHOLD 0.00


/// Structure of function centroid.
/// x is about the sequence number in the CFG;
/// y is about the number of outgoing edges of some basic block;
/// z is about the depth of loop of some node in the CFG;
/// w is about the number of statements in a basic block.
typedef struct c_vector{
    double x;
    double y;
    double z;
    double w;
} C_vector;

/// Identify the function level similarity.
/// CDD(Centroid Difference Degree) is the normalized distance 
/// for each dimension of two function centroids.
double CDD(C_vector c1, C_vector c2);

/// Get the number of functions in a program.
unsigned getFunctionNumber(SmallVector<std::pair<std::string, C_vector>, PROGRAM_SMALL_VECTOR_SIZE>
                           p);

/// Identify the program level similarity.
/// ASD(Application Similarity Degree) measures the similarity between two programs.
/// ASD(a1, a2) = |a21|/|a2|, |a2| is the number of functions in a2, 
/// |a21| identifies how many functions in a2 is similar to a1's.
double ASD(SmallVector<std::pair<std::string, C_vector>, PROGRAM_SMALL_VECTOR_SIZE> p1, 
           SmallVector<std::pair<std::string, C_vector>, PROGRAM_SMALL_VECTOR_SIZE> p2);

#endif
