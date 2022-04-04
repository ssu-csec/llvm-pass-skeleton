
////////////////////////////////////////////////////////////////////////////////

#ifndef __DFA_SUPPORT_H__
#define __DFA_SUPPORT_H__

#include <string>
#include <vector>

#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

namespace llvm {
  using namespace std;
  std::string getShortValueName(Value * v);

  class Expression {
  public:
    std::string lhs;
    std::string rhs;
    Value* v1;
    Value* v2;
    Value* v;
    unsigned int op;
    
    Expression (Instruction * I);
    bool operator== (const Expression &e2) const;
    bool operator< (const Expression &e2) const;
    std::string toString() const;
    std::string makeRhs() const;
  };

  void printSet(std::vector<Expression> * x);
  void printStringSet(std::vector<string> * x);
}

#endif