#include "../include/Difference.h"

using namespace llvm;

/// Identify the function level similarity.
/// CDD(Centroid Difference Degree) is the normalized distance 
/// for each dimension of two function centroids.
double CDD(C_vector c1, C_vector c2){
    double m = 0;
    m = std::max(((std::abs(c1.x-c2.x))/(c1.x+c2.x)), ((std::abs(c1.w-c2.w))/(c1.w+c2.w)));
    if((c1.y + c2.y) != 0)
        m = std::max(m, ((std::abs(c1.y-c2.y))/(c1.y+c2.y)));
    if((c1.z + c2.z) != 0)
        m = std::max(m, ((std::abs(c1.x-c2.x))/(c1.x+c2.x)));
    return m;
}

/// Get the number of functions in a program.
unsigned getFunctionNumber(SmallVector<std::pair<std::string, C_vector>, PROGRAM_SMALL_VECTOR_SIZE>
                           p){
    unsigned count = 0;
    for(SmallVectorImpl<std::pair<std::string, C_vector> >::iterator 
            I = p.begin(), E = p.end(); I != E; I++){
        count++;
    }
    return count;
    
}


/// Identify the program level similarity.
/// ASD(Application Similarity Degree) measures the similarity between two programs.
/// ASD(a1, a2) = |a21|/|a2|, |a2| is the number of functions in a2, 
/// |a21| identifies how many functions in a2 is similar to a1's.
double ASD(SmallVector<std::pair<std::string, C_vector>, PROGRAM_SMALL_VECTOR_SIZE> p1, 
           SmallVector<std::pair<std::string, C_vector>, PROGRAM_SMALL_VECTOR_SIZE> p2){
    unsigned a2 = getFunctionNumber(p2), a21 = 0;
    for(SmallVectorImpl<std::pair<std::string, C_vector> >::iterator 
            I2 = p2.begin(), E2 = p2.end(); I2 != E2; I2++){

        for(SmallVectorImpl<std::pair<std::string, C_vector> >::iterator 
                I1 = p1.begin(), E1 = p1.end(); I1 != E1; I1++){
            if(CDD(I1->second, I2->second) <= FUNCTION_LEVEL_THRESHOLD){
                a21++;
                break;
            }
        }
    }

    return double(a21)/a2;
}
