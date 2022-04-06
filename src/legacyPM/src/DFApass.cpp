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
    vector<Instruction *> dataFlow;
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
        startFunc();
        dataFlow.clear();
        int argSize = 0;
        errs() << "==============================================\n";
        errs() << "Name of the function is \"" << F.getName() << "\".   ";
        for (auto &arg : F.args())
        {
          argSize++;
        }
        errs() << "this fuction has " << argSize << " args.\n";

        if (argSize > 0)
        {
          errs() << "Starting " << getShortValueName(dyn_cast<Value>(F.getArg(0))) << "trace ... \n\n";
          errs() << "==============================================\n\n";
          for (auto &use : F.getArg(0)->uses())
          {
            User *user = use.getUser();
            Instruction *II = dyn_cast<Instruction>(user);
            Expression IE(II);
            discovered.push_back(user);
            discovered = bfs(discovered);
            for(int i=discovered.size(); i>0; i--){
              Instruction* Iter = dyn_cast<Instruction>(discovered.front());
              if(std::find(dataFlow.begin(), dataFlow.end(), Iter) == dataFlow.end())
                dataFlow.push_back(Iter);
              discovered.pop_front();
            }
          }
          errs() << "==============================================\n";
          // print_users(discovered);
          print_dataflow();
        }
      }
      return false;
    }

    list<User *> bfs(list<User *> discovered)
    {
      User *first = discovered.front();
      Instruction *II = dyn_cast<Instruction>(first);
      if(std::find(dataFlow.begin(), dataFlow.end(), II) == dataFlow.end())
        dataFlow.push_back(II);
      discovered.pop_front();
      errs() << discovered.size() << " Now Inst :: " << *II << "\n";
      if (II->getOpcode() == Instruction::Store)
      {
        for (auto &use : II->getOperand(1)->uses())
        {
          User *user = use.getUser();
          if (II == user )
            continue;
          errs() << *user << "\n\n";
          discovered.push_back(user);
        }
        discovered = bfs(discovered);
      }
      if (II->getOpcode() == Instruction::Load)
      {
        for (auto &use : II->uses())
        {
          User *user = use.getUser();
          errs() << *user << "\n\n";
          discovered.push_back(user);
        }
        discovered = bfs(discovered);
      }
      else
      {
        for (auto &use : II->uses())
        {
          User *user = use.getUser();
          errs() << *user << "\n\n";
          discovered.push_back(user);
          discovered = bfs(discovered);
        }
      }
      
      return discovered;
    }

    void print_users(list<User *> users)
    { 
      
      for (auto &user : users)
      {
        user->print(errs());
        errs() << "\n";
      }
    }

    void print_dataflow()
    {
      vector<Expression> userSet;
    //  dataFlow.unique();
      for (auto &II : dataFlow)
      {
        errs() << *II << "\n";
        userSet.push_back(Expression(II));
        errs() << "\n\n";
      }
      printSet(&userSet);
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
