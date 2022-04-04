#define DEBUG_TYPE "dfapass"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/Module.h"
#include "../include/dfa-support.h"

using namespace llvm;
using namespace std;
namespace
{
  struct DFAPass : public ModulePass
  {
    static char ID;
    DFAPass() : ModulePass(ID) {}
    void getAnalysisUsage(AnalysisUsage &AU) const override
    {
      // AU.addRequired<LoopInfoWrapperPass>();
    }
    // Main entry point - the name conveys what unit of IR this is to be run on.
    virtual bool runOnModule(llvm::Module &M) override
    {
      errs() << "<< runOnModule >> \n";
      errs() << "Name of the module " << M.getName() << "\n";
      list<User *> discovered;
      for (auto &F : M)
      {
        int argSize = 0;
        errs() << "==============================================\n";
        errs() << "Name of the function " << F.getName() << "\n";
        for (auto &arg : F.args())
        {
          argSize++;
        }
        errs() << "this fuction has " << argSize << " args.\n\n";
        if (argSize > 0)
        {
          for (auto &use : F.getArg(0)->uses())
          {
            User *user = use.getUser();
            discovered.push_back(user);
            discovered = bfs(discovered);
          }
          errs() << "\n\n==============================\n";
          print_users(discovered);
        }
      }
      return false;
    }
    list<User *> bfs(list<User *> discovered)
    {
      User *first = discovered.front();
      Instruction *II = dyn_cast<Instruction>(first);
      // Expression test(II);
      if (II->getOpcode() == Instruction::Store)
      {
        discovered.pop_front();
        errs() << discovered.size() << "  Now Inst :: " << *II << "\n";
        for (auto &use : II->getOperand(1)->uses())
        {
          User *user = use.getUser();
          if (II == user){
            Expression* test = new Expression(II);
             errs() << test->toString() << "\n";
            continue;
          }
           
          errs() << *user << "\n\n";
          discovered.push_back(user);
         
        }
         discovered = bfs(discovered);
      }
      if (II->getOpcode() == Instruction::Load)
      {
        discovered.pop_front();
        errs() << discovered.size() << " Now Inst :: " << *II << "\n";
        Expression* test = new Expression(II);
        errs() << test->toString() << "\n";
        
        for (auto &use : II->uses())
        {        
          User *user = use.getUser();    
          errs() << *user << "\n\n";
          discovered.push_back(user);
          
        }
        discovered = bfs(discovered);
      }
      return discovered;
    }
    void print_users(list<User *> users)
    {
      for (auto &user : users)
      {
        user->print(errs());
        Instruction *II = dyn_cast<Instruction>(user);
        
        errs() << "\n\n";
      }
    }
  };
} // namespace

// The address of this variable is used to uniquely identify the pass. The
// actual value doesn't matter.
char DFAPass::ID = 0;
static RegisterPass<DFAPass>
    X("dfapass", "a simple DFA",
      false, // This pass doesn't modify the CFG => true
      true   // This pass is not a pure analysis pass => false
    );

// opt -load ./libDFApass.so --dfapass -enable-new-pm=0 ../../sample.ll
