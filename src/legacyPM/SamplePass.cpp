#define DEBUG_TYPE "samplepass"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {

    struct SamplePass : public ModulePass {
        static char ID;
        SamplePass() : ModulePass(ID) {}

        void getAnalysisUsage(AnalysisUsage &AU) const override{          
            //AU.addRequired<LoopInfoWrapperPass>();
        }

        // Main entry point - the name conveys what unit of IR this is to be run on.
        virtual bool runOnModule(llvm::Module &M) override {
          errs() << "<< runOnModule >> \n";
          errs() << "Name of the module " << M.getName() << "\n";

          for(auto iter = M.getFunctionList().begin(); iter != M.getFunctionList().end(); ++iter) {
	          errs() << "Function name : " << iter->getName() << "\n";
          }

          return false;
        }
    };

} // namespace

// The address of this variable is used to uniquely identify the pass. The
// actual value doesn't matter.
char SamplePass::ID = 0;
static RegisterPass<SamplePass>
    X("samplepass", "a Sample Pass",
      false, // This pass doesn't modify the CFG => true
      true // This pass is not a pure analysis pass => false
    );