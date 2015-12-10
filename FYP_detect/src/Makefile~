LLVM_CONFIG = llvm-config  
LLVM_CXXFLAGS += $(shell $(LLVM_CONFIG) --cxxflags)  
LLVM_LDFLAGS := $(shell $(LLVM_CONFIG) --ldflags)  
LLVM_LIBS = $(shell $(LLVM_CONFIG) --libs core irreader linker option bitwriter support all-targets)  

llvm_model_src = main.cpp  


test:
#	clang++ -g $(llvm_model_src) $(LLVM_CXXFLAGS) $(LLVM_LIBS) $(LLVM_LDFLAGS) -lpthread -ldl -o test
	clang++ -g main.cpp Centroid.cpp Difference.cpp `llvm-config --libs core irreader option support all-targets --cxxflags --ldflags` -lpthread -ldl -o test

.PHONY:	clean
clean:
	rm -f *.o test
