#define DEBUG_TYPE "samplepass"
#include <unistd.h>
#include <stack>
#include <string>
#include <algorithm>
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/ValueSymbolTable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
using namespace llvm;
using namespace std;

namespace
{
	struct valuetable
	{
		Instruction *I;
		bool isSymbol = false;
		int isConstantInt = -1;
		Value *op0;
		Value *op1 = NULL;
		int result = -1;
	} valuetable;

	string getShortValueName(Value *v);
	list<struct valuetable> worklist;

	struct SamplePass : public ModulePass
	{
		static char ID;
		SamplePass() : ModulePass(ID) {}

		void getAnalysisUsage(AnalysisUsage &AU) const override
		{
			// AU.addRequired<LoopInfoWrapperPass>();
		}
		// Main entry point - the name conveys what unit of IR this is to be run on.
		virtual bool runOnModule(llvm::Module &M) override
		{
			errs() << "<< runOnModule >> \n";
			errs() << "Name of the module " << M.getName() << "\n";
			for (auto &F : M)
			{
				errs() << "Name of the function " << F.getName() << "\n";
				errs() << "\n\n";
				for (auto &II : instructions(&F))
				{
					Value *temp = &II;
					Instruction *I = dyn_cast<Instruction>(&II);
					if (ConstantInt *CI = dyn_cast<ConstantInt>(I->getOperand(0)))
					{
						if ((&II)->getOpcode() == Instruction::Alloca || (&II)->getOpcode() == Instruction::Ret)
							continue;
						errs() << "Name of the var " << getShortValueName(temp) << "\n";
						errs() << getShortValueName(temp) << " constant value : " << *(CI) << "\n";
						struct valuetable temp;
						temp.I = &II;
						temp.isSymbol = true;
						temp.isConstantInt = CI->getSExtValue();

						if (I->getOpcode() == Instruction::Store)
						{
							if (ConstantInt *CI = dyn_cast<ConstantInt>(I->getOperand(0)))
							{
								struct valuetable temp;
								temp.I = (Instruction *)(I->getOperand(1));
								temp.isConstantInt = CI->getSExtValue();
								temp.isSymbol = true;
								temp.op0 = I->getOperand(0);
								temp.op1 = I->getOperand(1);
								temp.result = CI->getSExtValue();
								worklist.push_back(temp);

								for (auto &use : I->getOperand(1)->uses())
								{
									User *user = use.getUser();
									User *def = user;
									Instruction *UI = dyn_cast<Instruction>(user);
									if (UI->getOpcode() == Instruction::Load)
									{

										// errs() << *user << "\t->\t"
										// 	   << "store " << *CI << ", i32* " << getShortValueName(def) << ", align 4\n";
										errs() << *user << "\t->\t" << getShortValueName(def) << " = load i32, i32* " << *CI
											   << ", align 4\n\n";

										struct valuetable temp1;
										temp1.I = UI;
										temp1.isConstantInt = temp.isConstantInt;
										temp1.op0 = CI;
										temp1.result = temp.isConstantInt;
										worklist.push_back(temp1);
										ConstantPropagate(*UI, CI, *def);
									}
									if (UI->getOpcode() == Instruction::Store)
									{
										if (UI == def)
											continue;
										errs() << *user << "\t->\t"
											   << "store " << *CI << ", i32* " << getShortValueName(def) << ", align 4\n\n";
										ConstantPropagate(*UI, CI, *def);
									}
									if (UI->getOpcode() == Instruction::Add)
									{
										errs() << *user << "\t->\t"
											   << "store " << *CI << ", i32* " << getShortValueName(def) << ", align 4\n\n";
										ConstantPropagate(*UI, CI, *def);
									}
									if (UI->getOpcode() == Instruction::Ret)
									{
										continue;
									}
								}
							}
						}
					}
				}
				printValueTable(worklist);

				for(auto vt : worklist)
				{
					if(vt.I->getOpcode()==Instruction::Ret)
					{
						if(ConstantInt * tmp = dyn_cast<ConstantInt>(vt.op0))
						{

							auto ni = IRBuild(vt);
							BasicBlock::iterator ii(ni);
						//	ReplaceInstWithInst(vt.I->getParent()->getInstList(),ii,ni);
							errs()<<"replace done\n";
							//vt.I->replaceAllUsesWith(ni);
						}
					}
					//vt.I->removeFromParent();

				}





			}
			return false;
		}

		void printValueTable(list<struct valuetable> worklist)
		{
			errs() << "\n\n====================================================================\n\n";

			errs() << "vt.op0 vt.op1 *(vt.I)  "
				   << "\n\n";
			for (auto vt : worklist)
			{
				if (vt.op1 != NULL)
					errs() << getShortValueName(vt.op0) << " " << getShortValueName(vt.op1) << " " << *(vt.I) << " " << vt.result << "\n\n";
				else if (vt.op1 == NULL)
					errs() << getShortValueName(vt.op0) << " "
						   << "NULL"
						   << " " << *(vt.I) << " " << vt.result << "\n\n";
			}
			errs() << "====================================================================\n\n";
		}

		void ConstantPropagate(User &II, ConstantInt *CI, User &parent)
		{
			Value *temp = &II;
			Value *p = &parent;
			Instruction *I = dyn_cast<Instruction>(&II);

			for (auto &use : I->uses())
			{

				User *user = use.getUser();
				User *def = user;
				Instruction *UI = dyn_cast<Instruction>(user);
				if (UI->getOpcode() == Instruction::Load)
				{
					errs() << *user << "\t->\t"
						   << "store " << *CI << ", i32* " << getShortValueName(def) << ", align 4\n\n";
					struct valuetable tmp;
					tmp.I = (Instruction *)UI;
					tmp.op0 = CI;
					tmp.result = CI->getSExtValue();
					worklist.push_back(tmp);
					ConstantPropagate(*def, CI, *user);
				}

				if (UI->getOpcode() == Instruction::Store)
				{
					User *temp = (User *)UI->getOperand(1);
					if (p == UI)
						continue;
					errs() << *user << "\t->\t"
						   << "store " << *CI << ", i32* " << getShortValueName(UI->getOperand(1)) << ", align 4\n\n";
					struct valuetable tmp;
					tmp.op0 = CI;
					tmp.op1 = UI->getOperand(1);
					tmp.I = (Instruction *)UI;
					tmp.result = CI->getSExtValue();
					worklist.push_back(tmp);
					ConstantPropagate(*temp, CI, *user);
				}

				if (UI->getOpcode() == Instruction::Add)
				{

					User *temp = (User *)UI->getOperand(0);
					struct valuetable tmp;
					tmp.op0 = UI->getOperand(0);
					tmp.op1 = UI->getOperand(1);

					if (ConstantInt *op2 = dyn_cast<ConstantInt>(UI->getOperand(1)))
					{

						tmp.result = op2->getSExtValue() + CI->getSExtValue();

						tmp.op0 = CI;
						CI = CreateCI(UI, tmp.result);
						;

						errs() << *user << "\t->\t" << getShortValueName(def) << " = add nsw " << *CI << ", " << getShortValueName(op2) << "\n\n";
					}
					else
					{
						tmp.op1 = CI;
						tmp.result = CI->getSExtValue();
						if (p == UI->getOperand(0))
						{
							tmp.op0 = UI->getOperand(1);
							errs() << *user << "\t->\t" << getShortValueName(def) << " = add nsw " << getShortValueName(UI->getOperand(1)) << ", " << *CI << "\n\n";
						}
						else if (p == UI->getOperand(1))
						{
							tmp.op0 = UI->getOperand(0);
							errs() << *user << "\t->\t" << getShortValueName(def) << " = add nsw " << getShortValueName(UI->getOperand(0)) << ", " << *CI << "\n\n";
						}
					}
					for (auto vt = worklist.begin(), ve = worklist.end(); vt != ve; ++vt)
					{
						if (vt->I == UI)
						{
							if (ConstantInt *ci0 = dyn_cast<ConstantInt>(vt->op1))
							{
								tmp.op0 = vt->op1;
							}
							worklist.erase(vt);
							break;
						}
					}
					tmp.I = (Instruction *)UI;
					worklist.push_back(tmp);
					ConstantPropagate(*def, CI, *user);
				}
				if (UI->getOpcode() == Instruction::Ret)
				{
					errs() << *user << "\t->\t" << UI->getOpcodeName() << " " << *CI << "\n\n";
					struct valuetable tmp;
					tmp.I = (Instruction *)UI;
					for (auto vt = worklist.begin(), ve = worklist.end(); vt != ve; ++vt)
					{
						if (vt->I == UI && vt->I->getOperand(0) == tmp.I->getOperand(0))
						{
							worklist.erase(vt);
							break;
						}
					}
					tmp.op0 = CI;
					tmp.result = CI->getSExtValue();
					worklist.push_back(tmp);
					return;
				}
			}
		}

		ConstantInt *CreateCI(Instruction *UI, int CIvalue)
		{
			Type *i32int = IntegerType::get(UI->getContext(), 32);
			Constant *val = ConstantInt::getSigned(i32int, CIvalue);
			ConstantInt *newCI = dyn_cast<ConstantInt>(val);
			return newCI;
		}

		string getShortValueName(Value *v)
		{
			if (v->getName().str().length() > 0)
			{
				return "%" + v->getName().str();
			}
			else if (isa<Instruction>(v))
			{
				string s = "";
				raw_string_ostream *strm = new raw_string_ostream(s);
				v->print(*strm);
				string inst = strm->str();
				size_t idx1 = inst.find("%");
				size_t idx2 = inst.find(" ", idx1);
				if (idx1 != std::string::npos && idx2 != std::string::npos)
				{
					return inst.substr(idx1, idx2 - idx1);
				}
				else
				{
					return "\"" + inst + "\"";
				}
			}
			else if (ConstantInt *cint = dyn_cast<ConstantInt>(v))
			{
				string s = "";
				raw_string_ostream *strm = new raw_string_ostream(s);
				cint->getValue().print(*strm, true);
				return strm->str();
			}
			else
			{
				string s = "";
				raw_string_ostream *strm = new raw_string_ostream(s);
				v->print(*strm);
				std::string inst = strm->str();
				return "\"" + inst + "\"";
			}
		}

		Instruction *IRBuild(struct valuetable vt)
		{
			IRBuilder<> IRB(vt.I->getParent());
			Instruction *NI;
			switch (vt.I->getOpcode())
			{
			case Instruction::Alloca:
				NI = dyn_cast<Instruction>(IRB.CreateAlloca(IntegerType::get(vt.I->getContext(), 32)));
				errs()<<*NI<<"\n";
				return NI;
			case Instruction::Store:
				NI = dyn_cast<Instruction>(IRB.CreateStore(vt.op0, vt.op1));
				errs()<<*NI<<"\n";
				return NI;
			case Instruction::Load:
				NI = dyn_cast<Instruction>(IRB.CreateLoad(vt.op0));
				errs()<<*NI<<"\n";
				return NI;
			case Instruction::Add:
				NI = dyn_cast<Instruction>(IRB.CreateAdd(vt.op0, vt.op1));
				errs()<<*NI<<"\n";
				return NI;
			case Instruction::Ret:
				NI = dyn_cast<Instruction>(IRB.CreateRet(vt.op0));
				errs()<<*NI<<"\n";
				return NI;
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
	  true	 // This pass is not a pure analysis pass => false
	);
