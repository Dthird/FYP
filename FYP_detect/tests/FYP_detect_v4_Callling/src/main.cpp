#include "../include/Centroid.h"
#include "../include/Difference.h"
#include <iostream>
#include "time.h"

using namespace llvm;

char Centroid::ID = 0;

int main(int argc, char **argv){
    /*
    clock_t start,finish;
    double totaltime;
    start=clock();
    */

    if (argc < 2) {
        errs() << "Usage: " << argv[0] << " <IR file>\n";
        return 1;
    }
    /// Parse the input LLVM IR file into a module.
    SMDiagnostic Err1;
    std::unique_ptr<Module> Mod1(parseIRFile(argv[1], Err1, getGlobalContext()));
    if (!Mod1) {
        Err1.print(argv[0], errs());
        return 1;
    }
    
    SMDiagnostic Err2;
    std::unique_ptr<Module> Mod2(parseIRFile(argv[2], Err2, getGlobalContext()));
    if (!Mod2) {
        Err2.print(argv[0], errs());
        return 1;
    }
    

    //Function *f1 = Mod->getFunction("ComputeSize");
    //Function *f2 = Mod->getFunction("yyset_out");

    /// Create a pass manager and fill it with the passes we want to run.
    
    FunctionPassManager *FPM1 = new FunctionPassManager(Mod1.get());
    FunctionPassManager *FPM2 = new FunctionPassManager(Mod2.get());
    FPM1->add(new LoopInfo());
    FPM2->add(new LoopInfo());
    Centroid *C1 = new Centroid();
    Centroid *C2 = new Centroid();
    FPM1->add(C1);
    FPM2->add(C2);

    //FPM->run(*f1);
    //FPM->run(*f2);
    
    Module::FunctionListType &fl1 = Mod1->getFunctionList();
    for(Module::iterator I = fl1.begin(), E = fl1.end() ; I != E ; I++){
        FPM1->run(*I);
    }
 
    Module::FunctionListType &fl2 = Mod2->getFunctionList();
    for(Module::iterator I = fl2.begin(), E = fl2.end() ; I != E ; I++){
        FPM2->run(*I);
    }
    
   
    
    //C->listProgram();

    SmallVector<std::pair<std::string, C_vector>, PROGRAM_SMALL_VECTOR_SIZE> pro1;
    SmallVector<std::pair<std::string, C_vector>, PROGRAM_SMALL_VECTOR_SIZE> pro2;
    pro1 = C1->getCentroids();
    pro2 = C2->getCentroids();
    
    //std::cout << "ASD:" << ASD(pro1, pro2) << "\n";
    std::cout << ASD(pro1, pro2);
    
    delete C1;
    delete C2;
    //errs() << "At the end of program.\n";

    /*
    finish = clock();
    totaltime = (double)(finish-start)/CLOCKS_PER_SEC;
    std::cout<<"times:"<<totaltime;
    */
    return 0;
}
