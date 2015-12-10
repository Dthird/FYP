#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Pass.h"
#include "llvm/PassManager.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IR/Function.h"
#include "llvm/Analysis/LoopInfo.h"

using namespace llvm;

//INITIALIZE_PASS_DEPENDENCY(LoopInfo)

class LoopDepth : public FunctionPass {
public:
    LoopDepth() : FunctionPass(ID) {  }
    
    //unsigned getX() { return x; }
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
        // By implementing this method, we can specify to the pass manager which
        // passes are required by this pass so it makes sure to run them in the
        // right order.
        AU.setPreservesAll();
        AU.addRequired<LoopInfo>();
    }
    

    virtual bool runOnFunction(Function &F) {
        errs() << "In runOnFunction.\n";
        LoopInfo *LI = &getAnalysis<LoopInfo>();
        for(Function::iterator I = F.begin(), E = F.end() ; I != E ; I++){
            errs() << LI->getLoopDepth(I) << "\n";
        }
        
        return false;
    }
    // The address of this member is used to uniquely identify the class. This is
    // used by LLVM's own RTTI mechanism.
    static char ID;
    //unsigned x;
};

char LoopDepth::ID = 0;

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

    Function *f1 = Mod->getFunction("ComputeSize");
    Function *f2 = Mod->getFunction("get_dimension");
    // Create a pass manager and fill it with the passes we want to run.
    
    FunctionPassManager *FPM = new FunctionPassManager(Mod.get());
    FPM->add(new LoopInfo());
    LoopDepth *LD = new LoopDepth();
    FPM->add(LD);
    //FPM->add(new LoopDepth());
    //PM.add(new );
    //PM.run(*Mod);
    FPM->run(*f1);
    errs() << "At the end of program.\n";
    //errs() << LD->getX() << "\n";
    FPM->run(*f2);
    return 0;
}


