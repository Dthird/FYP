#include <iostream>
#include <vector>
#include <llvm/IR/Module.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/CFG.h>
#include <llvm/Analysis/LoopInfo.h>
#include <llvm/PassAnalysisSupport.h>
#include <llvm/IR/BasicBlock.h>

#include <fcntl.h>
#include <errno.h>

using namespace llvm;

unsigned getSequenceNumber(Function &F, BasicBlock *bb){
    unsigned SN = 1;
    for(Function::iterator I = F.begin(), E = F.end() ; I != E ; I++){
        if ((BasicBlock *)I == bb){
            break;
        }
        SN++;
    }
    return SN;
}

/**
 * Create a std::unique_ptr<llvm::Module> from an IR file (binary or plain-text)
 */
std::unique_ptr<llvm::Module>	loadModuleFromBitcodeFile(const char *filename, llvm::LLVMContext& context){
	SMDiagnostic err;
    
    /*
    // Load the input module...
    std::unique_ptr<Module> M = parseIRFile(InputFilename, Err, Context);

    if (!M) {
    	Err.print(argv[0], errs());
    	return 1;
    }
    */

    /// If the given file holds a bitcode image, return a Module for it.
    /// Otherwise, attempt to parse it as LLVM Assembly and return a Module
    /// for it.
    ///std::unique_ptr<Module> parseIRFile(StringRef Filename, SMDiagnostic &Err,
    ///                                LLVMContext &Context);
    std::unique_ptr<llvm::Module>	mod(parseIRFile(filename, err, context));

    if (!mod){
		errs() << err.getMessage();
        mod = 0;
	}

    return mod;
}


int	main(int argc, char **argv){
    LLVMContext	&context = getGlobalContext();
 
    std::unique_ptr<Module> mainModule = loadModuleFromBitcodeFile("parser.bc", context);
    std::cout << "load，successfully\n" ; 
    Module::FunctionListType &fl = mainModule->getFunctionList();
    std::cout << "get function list.\n";
    Function *f1 = mainModule->getFunction("ComputeSize");
    if(f1 != NULL){
        std::cout << "ComputeSize get!\n";
    }
    //f1->viewCFG();
    std::cout << "\n\n";
    
    int x = 1;
    for(Function::iterator I = f1->begin(), E = f1->end() ; I != E ; I++){
        errs() << I->getName() << ":" << I->size() << "\t" << x << "\t" << getSequenceNumber(*f1, I) << "\n";
        x++;
    }

    errs() << "\n\n";
    
    
    /*Module::iterator it;
    int i=0;
    for(it = fl.begin(); it != fl.end() ; it++){
        //std::cout << i++ << "\n";
        //errs() << it->getName() << "\n";
    }
    */
    //Function::iterator it_f;

    // LoopInfoBase<BasicBlock, Loop> LI = BasicBlockPass::getAnalysis<LoopInfo>();

    /*template<typename AnalysisType>
        AnalysisType &Pass::getAnalysis(Function &F)
    */
    //LoopInfo *LI = &getAnalysis<LoopInfo>(f1);
    	//Pass *pass;
    	//LoopInfo *LI = &(pass->getAnalysis<LoopInfo>(*f1));
    //LI->runOnFunction(*f1);
    /*unsigned x = 0, y = 0;

    for(it_f = f1->begin(); it_f != f1->end() ; it_f++){
        errs() << it_f->getName() << "\t\tx:" << ++x << "\t";
        for (succ_iterator I = succ_begin(it_f), E = succ_end(it_f); I != E; I++) {
            y++;
        }
        errs() << "y:" << y << "\t";
        y = 0;

        errs() << "z:" << LI->getLoopDepth(it_f) << "\t";
        errs() << "w:" << it_f->size() << "\n";
        
    }
    */
    
    
	return 0;
}
