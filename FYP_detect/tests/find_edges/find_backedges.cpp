#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IR/Function.h"
#include "llvm/Analysis/CFG.h"
#include "llvm/IR/BasicBlock.h"

using namespace llvm;

/*
void FindFunctionBackedges(
    const Function &F,
    SmallVectorImpl<std::pair<const BasicBlock *, const BasicBlock *> > &
        Result);
*/

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
    SmallVector<std::pair<const BasicBlock *, const BasicBlock *> ,8 > Result;
    Function *f1 = Mod->getFunction("displayTree");
    FindFunctionBackedges(*f1, Result);
    for(SmallVectorImpl<std::pair<const BasicBlock *, const BasicBlock *> >::iterator 
            I = Result.begin(), E = Result.end(); I != E; I++){
        errs() << I->first->getName() << "->" << I->second->getName() << "\n";
    }
    errs() << "At the end of program.\n";
    return 0;
}


