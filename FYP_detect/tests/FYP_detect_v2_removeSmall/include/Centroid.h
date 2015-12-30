#ifndef CENTROID_H
#define CENTROID_H

#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Pass.h"
#include "llvm/PassManager.h"
#include "llvm/Analysis/CFG.h"
#include "llvm/Analysis/LoopInfo.h"
#include "Difference.h"

using namespace llvm;

/// Centroid is a Function pass.
/// Centroid is access to getLoopDepth(BasicBlock*) function.
class Centroid : public FunctionPass {
 public:
	Centroid() : FunctionPass(ID){}
    ~Centroid(){
        C_program.clear();
    }

    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
        /// By implementing this method, we can specify to the pass manager which
        /// passes are required by this pass so it makes sure to run them in the
        /// right order.
        AU.setPreservesAll();
        AU.addRequired<LoopInfo>();
    }
    
    /// When FunctionPassManager invokes run(&Functon), this function is invoked.
    virtual bool runOnFunction(Function &F) {

        //errs() << F.getName() << "\n";        
        C_vector Cv;
        unsigned CxW = 0, CyW = 0, CzW = 0, W = 0;
        
        /// Process the case of CFG only has one basicblock.
        BasicBlock *BB = &F.getEntryBlock();
        if (succ_begin(BB) == succ_end(BB)){
            
            if(BB->size() < 8){
                smallFunctionNumber ++;
            }
            else{
                CxW = W = BB->size();
                //errs() << "CxW=" << CxW << "\tCyW=" << CyW << "\tCzW=" << CzW <<"\tW=" << W << "\n";
                Cv.x = (double)CxW/W;
                Cv.y = (double)CyW/W;
                Cv.z = (double)CzW/W;
                Cv.w = W;
                C_program.push_back(std::make_pair(F.getName(), Cv));
                //errs() << "Cx=" << Cv.x << "\tCy=" << Cv.y << "\tCz=" << Cv.z <<"\tw=" << Cv.w << "\n";
            }
            return false;
        }

        
        SmallVector<std::pair<BasicBlock*, BasicBlock*>, 20> edges;
        findFunctionAllEdges(F, edges);
        
        LoopInfo *LI = &getAnalysis<LoopInfo>();
        for(SmallVectorImpl<std::pair<BasicBlock *, BasicBlock *> >::iterator 
                I = edges.begin(), E = edges.end(); I != E; I++){
            //errs() << I->first->getName() << "->" << I->second->getName() << "\n";
            
            /// Compute the centroid of 3D-CFG
            unsigned w1 = getStatementsNumber(I->first);
            unsigned w2 = getStatementsNumber(I->second);
            W += w1 + w2;
            CxW += w1 * getSequenceNumber(F, I->first) + w2 * getSequenceNumber(F, I->second);
            CyW += w1 * getOutgoingEdgeNumber(I->first) + w2 * getOutgoingEdgeNumber(I->second);
            CzW += w1 * LI->getLoopDepth(I->first) + w2 * LI->getLoopDepth(I->second);
        }
        //errs() << "CxW=" << CxW << "\tCyW=" << CyW << "\tCzW=" << CzW <<"\tW=" << W << "\n";

        Cv.x = (double)CxW/W;
        Cv.y = (double)CyW/W;
        Cv.z = (double)CzW/W;
        Cv.w = W;
        C_program.push_back(std::make_pair(F.getName(), Cv));
        //errs() << "Cx=" << Cv.x << "\tCy=" << Cv.y << "\tCz=" << Cv.z <<"\tw=" << Cv.w << "\n";

        return false;
    }
    
    /// Analyze the specified function to find all of the edges in the
    /// function and return them.  
    /// The output is added to Result, as pairs of <from,to> edge info.    
    void findFunctionAllEdges(Function &F,
                              SmallVectorImpl<std::pair<BasicBlock*, BasicBlock*> > &Result);

    /// Get the number of outgoing edges of some basic block.
    /// Take advantage of succ_iterator.
    unsigned getOutgoingEdgeNumber(BasicBlock *bb);

    /// Get the number of statements in a basic block.
    unsigned getStatementsNumber(BasicBlock *bb);

    /// Get the sequence number of a basic block in its function.
    unsigned getSequenceNumber(Function &F, BasicBlock *bb);
    
    /// List all the functions' name  and centroids of functions.
    void listProgram();

    /// Get the private member C_program.
    SmallVector<std::pair<std::string, C_vector>, PROGRAM_SMALL_VECTOR_SIZE> getCentroids();

 private:
    /// The address of this member is used to uniquely identify the class. This is
    /// used by LLVM's own RTTI mechanism.
    static char ID;

    /// C_program stores all the functions' name and centroid.
    SmallVector<std::pair<std::string, C_vector>, PROGRAM_SMALL_VECTOR_SIZE> C_program ;

    int smallFunctionNumber = 0;
};

#endif
