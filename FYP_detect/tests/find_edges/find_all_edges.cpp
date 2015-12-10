#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IR/Function.h"
#include "llvm/Analysis/CFG.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/ADT/SmallVector.h"

using namespace llvm;

void findFunctionAllEdges(Function &F,
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

int main(int argc, char **argv) {
    if (argc < 2) {
        errs() << "Usage: " << argv[0] << " <IR file>\n";
        return 1;
    }
    // Parse the input LLVM IR file into a module.
    SMDiagnostic Err;
        std::unique_ptr<Module> Mod(parseIRFile(argv[1], Err, getGlobalContext()));
    if (!Mod) {
        Err.print(argv[0], errs());
        return 1;
    }
    
    //SmallVectorImpl<std::pair<const BasicBlock *, const BasicBlock *> > Result;
    SmallVector<std::pair<BasicBlock *, BasicBlock *> ,10 > Result;
    Function *f1 = Mod->getFunction("displayTree");
    //FindFunctionBackedges(*f1, Result);
    findFunctionAllEdges(*f1, Result);
    for(SmallVectorImpl<std::pair<BasicBlock *, BasicBlock *> >::iterator 
            I = Result.begin(), E = Result.end(); I != E; I++){
        errs() << I->first->getName() << "->" << I->second->getName() << "\n";
    }
    
    errs() << "At the end of program.\n";
    return 0;
}


