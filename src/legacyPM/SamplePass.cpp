#define DEBUG_TYPE "samplepass"

#include <list>
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;
using namespace std;

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

		  for (auto& F : M) {
          	  errs() << "Name of the function " << F.getName() << "\n";
			  errs() << "\n\n";
			  for (auto& arg : F.args()) {
          	  	errs() << "Name of the args " << arg.getArgNo() << "\n";
					for (auto& use : arg.uses()) {
						User *user = use.getUser();
						list<User*> discovered;
						discovered.push_back(user);
						discovered = dfs(discovered);
						print_users(discovered);
					}

			  }
          }

          return false;
        }

		list<User*> dfs(list<User*> discovered) {
			User *last = discovered.back();
			for (auto& use : last->uses()) {
				User *user = use.getUser();
				discovered.push_back(user);
				discovered = dfs(discovered);
			}
			return discovered;
		}

		void print_users(list<User*> users) {
			for (auto& user : users){
				user->print(errs());
				errs() << "\n\n";
			}
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
