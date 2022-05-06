#define DEBUG_TYPE "samplepass"

#include <queue>
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

				if (F.arg_size() >= 1){
					Argument *arg_0 = F.getArg(0);
          	  		errs() << "Name of the args " << arg_0->getArgNo() << "\n";

					queue<User*> discovered;
					discovered.push((User *)arg_0);

					while(1){
						User *def = discovered.front();
						def->print(errs());
						errs() << "\n\n";
						discovered.pop();
						for (auto& use : def->uses()) {
							User *user = use.getUser();
							
							User *new_def = user;
							if(strncmp(((Instruction *) new_def)->getOpcodeName(), "store", 6) == 0){
								User *user = (User *)new_def->getOperand(1);
								if (user != def){
									discovered.push(user);
								}
								else{
								//	errs() << "oohohoohoh";
								}
							}
							else{
								discovered.push(user);
							}
						}

						if(discovered.empty()){
							break;
						}
					}
				}
			}

		return false;
		}

/*
		list<User*> dfs(list<User*> discovered) {
			User *last = discovered.back();
			Instruction *inst = (Instruction *) last;
			errs() << "I am\n";
			last->print(errs());
			errs() << "\n";
			errs() << inst->getOpcodeName();
			errs() << "\n\n";

			// store case
			if(strncmp(inst->getOpcodeName(), "store", 6) == 0){
				errs() << "True\n";
				errs() << ((User *) last)->getNumOperands();
				errs() << "\n";
				User *operand_user = (User *) last->getOperand(1);
				discovered.push_back(operand_user);
				discovered = dfs(discovered);
			}
			else{
				errs() << "False\n";
				for (auto& use : last->uses()) {
					errs() << "I am dfs!\n";
					User *user = use.getUser();
					// Todo: check if operator is 'store' (such like memory operation), then we need to find specific operand."
					discovered.push_back(user);
					discovered = dfs(discovered);
				}
			}
			return discovered;
		}

		void print_users(list<User*> users) {
			for (auto& user : users){
				user->print(errs());
				errs() << "\n\n";
			}
		}
*/
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
