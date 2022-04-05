#define DEBUG_TYPE "samplepass"

#include <stack>
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
          	  		errs() << "%" << arg_0->getArgNo() << "\n";

					stack<User*> discovered;
					discovered.push((User *)arg_0);
					discovered = dfs(discovered, 0);
				}
			}

		return false;
		}

		stack<User*> dfs(stack<User*> discovered, int indent_count) {
			User *def = discovered.top();
			indent_count++;
			discovered.pop();

			for (auto& use : def->uses()) {
				User *user = use.getUser();
				User *new_def = user;

				if(strncmp(((Instruction *) new_def)->getOpcodeName(), "store", 6) == 0){
					User *user = (User *)new_def->getOperand(1);
					if (user != def){
						for(int i = 0; i < indent_count; i++){
							errs() << "  ";
						}
						errs() << "-> ";
						errs() << getShortValueName(user);
						for(int i = 0; i < 20-indent_count; i++){
							errs() << "  ";
						}
						errs() << "\t|\t";
						new_def->print(errs());
						errs() << "\n";
						discovered.push(user);
						discovered = dfs(discovered, indent_count);
					}
				}
				else if(strncmp(((Instruction *) new_def)->getOpcodeName(), "br", 2) == 0){
					continue;
				}
				else if(strncmp(((Instruction *) new_def)->getOpcodeName(), "ret", 3) == 0){
					User *user = (User *) new_def->getOperand(0);
					for(int i = 0; i < indent_count; i++){
						errs() << "  ";
					}
					errs() << "-> ret ";
					errs() << getShortValueName(user);
					for(int i = 0; i < 20-indent_count-2; i++){
						errs() << "  ";
					}
					errs() << "\t|\t";
					user->print(errs());
					errs() << "\n";
					continue;
				}
				else{
					for(int i = 0; i < indent_count; i++){
						errs() << "  ";
					}
					errs() << "-> ";
					errs() << getShortValueName(user);
					for(int i = 0; i < 20-indent_count; i++){
						errs() << "  ";
					}
					errs() << "\t|\t";
					user->print(errs());
					errs() << "\n";
					discovered.push(user);
					discovered = dfs(discovered, indent_count);
				}
			}
			indent_count--;
			return discovered;
		}
		
		string getShortValueName(Value *v) {
			if (v->getName().str().length() > 0){
				return "%" + v->getName().str();
			}
			else if (isa<Instruction>(v)){
				string s = "";
				raw_string_ostream *strm = new raw_string_ostream(s);
				v->print(*strm);
				string inst = strm->str();
				size_t idx1 = inst.find("%");
				size_t idx2 = inst.find(" ", idx1);
				if (idx1 != std::string::npos && idx2 != std::string::npos){
					return inst.substr(idx1, idx2 - idx1);
				}
				else{
					return "\"" + inst + "\"";
				}
			}
			else if (ConstantInt *cint = dyn_cast<ConstantInt>(v)){
				string s = "";
				raw_string_ostream *strm = new raw_string_ostream(s);
				cint->getValue().print(*strm, true);
				return strm->str();
			}
			else{
				string s = "";
				raw_string_ostream *strm = new raw_string_ostream(s);
				v->print(*strm);
				std::string inst = strm->str();
				return "\"" + inst + "\"";
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
