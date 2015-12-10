#include "../include/Centroid.h"

using namespace llvm;

/// Analyze the specified function to find all of the edges in the
/// function and return them.  
/// The output is added to Result, as pairs of <from,to> edge info. 
void Centroid::findFunctionAllEdges(Function &F,
                          SmallVectorImpl<std::pair<BasicBlock*, BasicBlock*> > &Result) {

  	BasicBlock *BB = &F.getEntryBlock();
    if (succ_begin(BB) == succ_end(BB))
        return;

    for(Function::iterator I = F.begin(), E = F.end() ; I != E ; I++){
        for(succ_iterator SI = succ_begin(I), SE = succ_end(I) ; SI != SE ; SI++){
            BB = *SI;
            Result.push_back(std::make_pair((BasicBlock*)I, BB));
            //errs() << I->getName() << "->" << SI->getName() << "\n";
        }
    }
}

/// Get the number of outgoing edges of some basic block.
/// Take advantage of succ_iterator.
unsigned Centroid::getOutgoingEdgeNumber(BasicBlock *bb){

    unsigned count = 0;

    for (succ_iterator I = succ_begin(bb), E = succ_end(bb); I != E; I++) {
        count++;
    }

    return count;
}

/// Get the number of statements in a basic block.
unsigned Centroid::getStatementsNumber(BasicBlock *bb){
    return bb->size();
}

/// Get the sequence number of a basic block in its function.
unsigned Centroid::getSequenceNumber(Function &F, BasicBlock *bb){
    unsigned SN = 1;
    for(Function::iterator I = F.begin(), E = F.end() ; I != E ; I++){
        if ((BasicBlock *)I == bb){
            break;
        }
        SN++;
    }
    return SN;
}

/// List all the functions' name  and centroids of functions.
void Centroid::listProgram(){
    for(SmallVectorImpl<std::pair<std::string, C_vector> >::iterator 
            I = C_program.begin(), E = C_program.end(); I != E; I++){
        errs() << I->first << " : " << I->second.x << "\t" 
               << I->second.y << "\t" << I->second.z << "\t" << I->second.w << "\n";
    }
}

/// Get the private member C_program.
SmallVector<std::pair<std::string, C_vector>, PROGRAM_SMALL_VECTOR_SIZE> Centroid::getCentroids(){ 
    return C_program; 
} 
