#include "interpreter.h"
#include "real.h"
#include "../../Output.h"
#include <stack>
#include <queue>
#include <math.h>
#include "variable.h"
#include "constant.h"
#include "../../Graph.h"
namespace Piotr
{
	namespace Math
	{
		using CompilerFunction = void (StringInterpreter::*)(const std::string&);
		using ManagedArgument = std::shared_ptr < FunctionArgument >;
		using namespace System;
		using namespace yolo_octo_wallhack;
		StringInterpreter::StringInterpreter()
		{
			mKeywords["Real"] = &StringInterpreter::allocateReal; 
			mKeywords["MathFunction"] = &StringInterpreter::allocateFunction;
			mKeywords["Display"] = &StringInterpreter::display;
			mKeywords["Set"] = &StringInterpreter::set;
			mKeywords["Sete"] = &StringInterpreter::sete;
			mKeywords["Goto"] = &StringInterpreter::gotoLine;
			mKeywords["Label"] = &StringInterpreter::makeLabel;
			mKeywords["If"] = &StringInterpreter::ifStatement;
			mKeywords["Graph2D"] = &StringInterpreter::drawGraph2D;
			mKeywords["Alias"] = &StringInterpreter::makeAlias;
			mKeywords["Derivative"] = &StringInterpreter::countDerivative;
			//mKeywords["TaylorSeries"] = &StringInterpreter::expandTaylor;

			mOperators["+"] = &FunctionArgument::operator+;
			mOperators["*"] = &FunctionArgument::operator*;
			mOperators["-"] = &FunctionArgument::operator-;
			mOperators["/"] = &FunctionArgument::operator/;
			mOperators["^"] = &FunctionArgument::operator^;
			mOperators["="] = &FunctionArgument::operator=;
		}

		StringInterpreter::~StringInterpreter()
		{

		}

		void StringInterpreter::run()
		{
			
			mCurrentLine = 0;
			mCode = prepareCode();
			
			while (mCurrentLine < mCode.size())
			{
				compileLine(mCode[mCurrentLine]);
				mCurrentLine++;
			}
		}
		std::vector<std::string> StringInterpreter::prepareCode()
		{
			std::vector<std::string> ncode;
			for (int i = 0; i < mCode.size(); i++)
			{
				std::vector<std::string> t = seperateWords(mCode[i], ";", "");
				for (int j = 0; j < t.size(); j++)
				{
					ncode.push_back(t[j]);
				}
			}
			int ti = 0;
			while (ti < ncode.size())
			{
				if (ncode[ti] == "Start")
				{
					mCurrentLine = ti+1;
					break;
				}
				if (ncode[ti].find("Label") != std::string::npos)
				{
					int tti = mCurrentLine;
					mCurrentLine = ti;
					compileLine(ncode[ti]);
					mCurrentLine = tti;
				}
				ti++;
			}
			return ncode;
		}
		//@TODO
		void StringInterpreter::compileLine(const std::string& str)
		{
			if (str.size() < 1)
			{
				mLog.push_back("Empty line aborting.");
				return;
			}
			std::vector<std::string> words = seperateWords(str," ","");
			
			if (!isKeyword(words[0]))
			{
				mLog.push_back("First word not a keyword aborting");
				return;
			}
			
			CompilerFunction cf = mKeywords[words[0]];
			(this->*cf)(str);
		}
		void StringInterpreter::pushLine(const std::string& str)
		{
			mCode.push_back(str);
		}
		void StringInterpreter::showLog()
		{
			yolo_octo_wallhack::Output^ t = gcnew yolo_octo_wallhack::Output(mLog);
			t->Show();
		}

		void StringInterpreter::showResult()
		{
			yolo_octo_wallhack::Output^ t = gcnew yolo_octo_wallhack::Output(mResult);
			t->Show();
		}

		bool StringInterpreter::isKeyword(const std::string& str)
		{
			auto it = mKeywords.find(str);
			return (it != mKeywords.end());
		}

		std::string StringInterpreter::removeSpaces(const std::string& str)
		{

			
			std::string ret = "";
			int start=0;
			int end=0;
			while (end != std::string::npos)
			{
				start = str.find_first_not_of(" ", end);
				end = str.find_first_of(" ", end+1);
				if (start < end && start!=-1)
				{
					ret += str.substr(start, end-start);
				}
			}
			ret += str.substr(start, str.size() - start);
			
			return ret;
		}

		std::string StringInterpreter::removeKeywords(const std::string& str)
		{
			std::string ret = "";
			std::vector<std::string> t = seperateWords(str," ","");
			for (int i = 0; i < t.size(); i++)
			{
				if (!isKeyword(t.at(i)))
				{
					ret += t.at(i);
					if (i != t.size() - 1)
						ret += " ";
				}
			}
			return ret;
		}
		
		std::vector<std::string> StringInterpreter::seperateWords(const std::string& str, const std::string& toremove, const std::string& tokeep)
		{
			std::vector<std::string> ret;
			std::string tf = tokeep + toremove;
			int npos, pos = 0;
			int start = 0;
			int end = 0;
			if (str.find_first_of(tokeep) == 0)
				ret.push_back(str.substr(0,1));
			while (end != std::string::npos)
			{
				start = str.find_first_not_of(tf, end);
				end = str.find_first_of(tf, end + 1);
				
				
				if (start < end && start != -1)
				{
					ret.push_back(str.substr(start, end - start));
				}

				if (end != std::string::npos)
					if (tokeep.find(str[end]) != std::string::npos)
					{
						ret.push_back(str.substr(end, 1));
					}
				
			}
			if (start!=std::string::npos)
			ret.push_back(str.substr(start, str.size() - start));
			return ret;
		}

		//Compiler functions

		void StringInterpreter::allocateReal(const std::string& str)
		{
			static const std::string TAG = "allocateReal: ";
			std::vector<std::string> t = seperateWords(str, " ", "");
			if (!checkSize(TAG, t, 2, 2)) return;
			mVariables[t[1]] = ManagedArgument(new Real);
		}

		void StringInterpreter::allocateFunction(const std::string& str)
		{
			static const std::string TAG = "allocateFunction: ";
			std::vector<std::string> t = seperateWords(str, " (),", "");
			if (!checkSize(TAG, t, 3, -1)) return;

			mLocalVariables[t[1]] = std::unordered_map < std::string, ManagedArgument >();
			
			for (int i = 2; i < t.size(); i++)
			{
				mLocalVariables[t[1]][t[i]] = ManagedArgument(new Variable(t.size() - 2, i - 2));
			}

			Constant* c = new Constant(t.size()-2);
			c->set(ManagedArgument(new Real));
			mVariables[t[1]] = ManagedArgument(c);
			
		}

		void StringInterpreter::display(const std::string& str)
		{
			static const std::string TAG = "display: ";
			std::vector<std::string> t = seperateWords(str," ", "");
			if (!checkSize(TAG, t, 2, -1)) return;
			std::string tstr = "";
			for (int i = 1; i < t.size(); i++)
				tstr += t[i];
			std::vector<std::string> rpn = toRPN(tstr,mVariables,false);
			ManagedArgument ma = resolveRPN(rpn,mVariables,false);
			tstr = "";
			if (ma == ManagedArgument())
			{
				mResult.push_back("Null reference");
				return;
			}
			ma->toString(tstr);
			mResult.push_back(tstr);
		}

		void StringInterpreter::set(const std::string& str)
		{
			static const std::string TAG = "set: ";
			std::vector<std::string> t = seperateWords(str, " ", "");
			if (t.size() < 3)
			{
				mLog.push_back(TAG + "Invalid size. Did not set.");
				return;
			}
			auto it = mVariables.find(t[1]);
			if (it == mVariables.end())
			{
				mLog.push_back(TAG + "No such variable.");
				return;
			}
			ManagedArgument right;
			std::vector<std::string> rpn;
			std::string rest = "";
			for (int i = 2; i < t.size(); i++)
				rest += t[i];
			
			auto table = mLocalVariables.find(t[1]);

			if (table != mLocalVariables.end())
			{
				
				rpn = toRPN(rest, mLocalVariables[t[1]] , false);
				right = resolveRPN(rpn, mLocalVariables[t[1]], false);
			}
			else
			{
				rpn = toRPN(rest, mVariables, false);
				right = resolveRPN(rpn, mVariables, false);
			}
			
		
			
			/*
			Output^ o = gcnew Output(rpn);
			o->Show();
			*/
			

			//@TODO test
			mVariables[t[1]] = right;
		}


		void StringInterpreter::sete(const std::string& str)
			{
				static const std::string TAG = "sete: ";
				std::vector<std::string> t = seperateWords(str, " ", "");
				if (t.size() < 3)
				{
					mLog.push_back(TAG + "Invalid size. Did not set.");
					return;
				}
				auto it = mVariables.find(t[1]);
				if (it == mVariables.end())
				{
					mLog.push_back(TAG + "No such variable.");
					return;
				}
				ManagedArgument left = toArgument(t[1], mVariables);
				std::string rest = "";
				for (int i = 2; i < t.size(); i++)
					rest += t[i];
				auto table = mLocalVariables.find(t[1]);
				VariableTable& vt = mVariables;
				if (table != mLocalVariables.end())
				{
					vt = table->second;
				}
			
			std::vector<std::string> rpn = toRPN(rest,vt, true);
			/*
			Output^ o = gcnew Output(rpn);
			o->Show();
			*/
			ManagedArgument right = resolveRPN(rpn,vt,true);

			//@TODO test
			mVariables[t[1]] = right->clone();



			
		}
		
		void StringInterpreter::makeLabel(const std::string& str)
		{
			static const std::string TAG = "Label: ";
			std::vector<std::string> t = seperateWords(str," ", "");
			if (t.size() != 2)
			{
				mLog.push_back(TAG + "Invalid size.");
				return;
			}

			mLabels[t[1]] = mCurrentLine;
		}

		void StringInterpreter::gotoLine(const std::string& str)
		{
			static const std::string TAG = "Goto: ";
			std::vector<std::string> t = seperateWords(str, " ", "");
			if (t.size() != 2)
			{
				mLog.push_back(TAG + "Invalid size.");
				return;
			}

			auto it = mLabels.find(t[1]);
			if (it != mLabels.end())
			{
				mCurrentLine = it->second;
			}
			else
			{
				mLog.push_back(TAG + "No such label.");
			}

		}

		void StringInterpreter::ifStatement(const std::string& str)
		{
			static const std::string TAG = "If: ";
			std::vector<std::string> t = seperateWords(str, " ", "");
			if (!checkSize(TAG, t, 4, -1)) return;
			std::string tstr = "";
			for (int i = 3; i < t.size(); i++)
				tstr += t[i];
			std::vector<std::string>& rpn = toRPN(tstr,mVariables,false);
			//Output^ output = gcnew Output(rpn);
			//output->Show();
			ManagedArgument ma = resolveRPN(rpn,mVariables,false);
			Real tr;
			if (!(ma->getType() == tr.getType()))
			{
				mLog.push_back(TAG + "Invalid type");
			}
			Real* trp = (Real*)(ma.get());
			if (trp->value<1e-12&&trp->value>-1e-12)
			{
				std::string tstr2;
				trp->toString(tstr2);
				//@TODO better goto
				//mLog.push_back(TAG + "trpval " + tstr2);
				//mLog.push_back("false");
				std::string tstr = "Goto " + t[2];
				compileLine(tstr);
			}
			else
			{
				std::string tstr2;
				trp->toString(tstr2);
				//@TODO better goto
				//mLog.push_back(TAG + "trpval " + tstr2);
				//mLog.push_back("true");
				std::string tstr = "Goto " + t[1];
				compileLine(tstr);
			}
		}

		void StringInterpreter::drawGraph2D(const std::string& str)
		{
			//@ rpn?
			static const std::string TAG = "drawGraph2D: ";
			std::vector<std::string> args = seperateWords(str, " ", "");
			if (!checkSize(TAG, args, 5, 5)) return;
			
			String^ lefts = gcnew String(args[2].c_str());
			String^ rights = gcnew String(args[3].c_str());
			String^ steps = gcnew String(args[4].c_str());

			double left;
			double right;
			double step; 

			bool leftr = System::Double::TryParse(lefts, left);
			bool rightr = System::Double::TryParse(rights, right);
			bool stepr = System::Double::TryParse(steps, step);

			if (!(leftr&&rightr&&stepr))
			{
				mLog.push_back(TAG + "Failed to cast doubles");
				return;
			}
			if (!isMathFunction(args[1]))
			{
				mLog.push_back(TAG + "Invalid funciton?");
				return;
			}

			Graph^ graph = gcnew Graph(toArgument(args[1], mVariables), left, right, step);
			graph->Show();
			
		}

		void StringInterpreter::makeAlias(const std::string& str)
		{
			const static std::string TAG = "makeAlias: ";
			std::vector<std::string> t = seperateWords(str, " ", "");
			if (!checkSize(TAG, t, 3, 3)) return;
			if (t[1] != t[2])
			{
				auto it = mKeywords.find(t[1]);
				if (it == mKeywords.end())
				{
					mKeywords[t[1]] = mKeywords[t[2]];
				}
			}
		}

		void StringInterpreter::countDerivative(const std::string& str)
		{
			const static std::string TAG = "countDerivative: ";
			std::vector<std::string> t = seperateWords(str, " ", "");
			if (!checkSize(TAG, t, 3, 3)) return;

			ManagedArgument f = toArgument(t[1],mVariables);
			if (!isMathFunction(t[1]))
			{
				mLog.push_back(TAG + "Not a function.");
				return;
			}
			
			VariableTable& vt = mLocalVariables[t[1]];
			auto it = vt.find(t[2]);
			if (it == vt.end())
			{
				mLog.push_back(TAG + "Failed to find variable " + t[2]);
				return;
			}

			ManagedArgument v = it->second;
			GenericMathFunction* gmc = (GenericMathFunction*)f.get();
			ManagedArgument tt = gmc->derivative(v);
			mVariables[t[1]] = tt;
		}

		//Helper functions

		bool StringInterpreter::isNumber(const std::string& str)
		{
			String^ gcs = gcnew String(str.c_str());
			double t;
			return Double::TryParse(gcs, t);

		}
		bool StringInterpreter::isVariable(const std::string& str,  const VariableTable& local)
		{

			bool res = false;
			auto it = local.find(str);
			res = res || (it != local.end());

			it = mVariables.find(str);
			res = res || (it != mVariables.end());
			return res;
		}
		bool StringInterpreter::isMathFunction(const std::string& str)
		{
			auto it = mLocalVariables.find(str);
			return (it != mLocalVariables.end());
		}
		bool StringInterpreter::isOperator(const std::string& str)
		{
			static const std::string operators = "+-*/^";
			return (operators.find(str) != std::string::npos);
		}
		int StringInterpreter::getOperatorPrecedence(const std::string& str)
		{

			static const std::string h = "^";
			static const std::string m = "*/";
			static const std::string l = "-+";
			static const std::string ll = "&|";


			if (h.find(str) != std::string::npos)
				return 4;

			if (m.find(str) != std::string::npos)
				return 3;

			if (l.find(str) != std::string::npos)
				return 2;

			if (ll.find(str) != std::string::npos)
				return 1;

		}

		bool StringInterpreter::isLeftAssociative(const std::string& left, const std::string& right)
		{
			//assuming left and right are operators
			//+ * - / ^

			// + +
			// + *
			// + -
			// + /
			// + ^
			if (left == "+")
			{

				if (right.find_first_of("+-") != std::string::npos)
					return true;

			}

			// * +
			// * *
			// * -
			// * /
			// * ^

			if (left == "*")
			{

				if (right.find_first_of("+-*/") != std::string::npos)
					return true;

			}

			// - +
			// - *
			// - -
			// - /
			// - ^

			if (left == "-")
			{

				if (right.find_first_of("+-") != std::string::npos)
					return true;

			}
			// / +
			// / *
			// / -
			// / /
			// / ^

			if (left == "/")
			{

				if (right.find_first_of("+-*/") != std::string::npos)
					return true;

			}
			return false;
			// ^ +
			// ^ *
			// ^ -
			// ^ /
			// ^ ^
			if (left == "^")
			{

				return true;

			}
		}

		bool StringInterpreter::isRightAssociative(const std::string& left, const std::string& right)
		{
			//assuming left and right are operators
			//+ * - / ^

			// + +
			// + -
			// + /
			// + ^
			if (left == "+")
			{

				return true;

			}

			// * +
			// * *
			// * -
			// * /
			// * ^

			if (left == "*")
			{

				if (right.find_first_of("+-") == std::string::npos)
					return true;

			}

			// - +
			// - *
			// - -
			// - /
			// - ^

			if (left == "-")
			{

				return true;

			}

			// / +
			// / *
			// / -
			// / /
			// / ^

			if (left == "/")
			{

				if (right.find_first_of("+-") == std::string::npos)
					return true;

			}

			// ^ +
			// ^ *
			// ^ -
			// ^ /
			// ^ ^

			if (left == "^")
			{

	
			}

			return false;
		}
		bool StringInterpreter::checkSize(const std::string& tag, const std::vector<std::string>& statement, unsigned minsize, unsigned maxsize)
		{
			if (statement.size() < minsize || statement.size() > maxsize)
			{
				mLog.push_back(tag + "Invalid size.");
				return false;
			}
			return true;
		}
		ManagedArgument StringInterpreter::toArgument(const std::string& str, const VariableTable& local)
		{
			auto it = local.find(str);
			if (it != local.end())
			{

				return it->second;
			}
			auto it2 = mVariables.find(str);
			if (!(it2 == mVariables.end()))
			{

				return it2->second;
			}
			//try casting to a Real
			if (isNumber(str))
			{
				//@TODO proper conversion
				double val = Double::Parse(gcnew String(str.c_str()));
				ManagedArgument p = ManagedArgument(new Real(val));
				return p;
			}
			mLog.push_back(str+": Failed to convert.");

			return ManagedArgument();


		}
		std::vector<std::string> StringInterpreter::toRPN(const std::string& str, const VariableTable& local, bool efunc)
		{
			//@TODO check for errors
			std::vector<std::string> e;
			std::vector<std::string> t = seperateWords(str, " ", "()+-*^/,");
			std::vector<std::string> exitqueue;
			std::stack<std::string> stack;
			
			for (int i = 0; i < t.size(); i++)
			{
				if (isMathFunction(t[i])&&efunc)
				{
					stack.push(t[i]);
				}
				else
				if (isNumber(t[i])||isVariable(t[i],local))
				{
					exitqueue.push_back(t[i]);
				}
				else
				{
					if (!isOperator(t[i]))
					{
						if (t[i].find_first_of(",()") == std::string::npos)
						{
							stack.push(t[i]);
						}
						else
						{
							if (t[i] == ",")
							{
								if (stack.size()<2)
								{
									mLog.push_back("Missing elements.");
									return e;
								}
								while (stack.top() != "(")
								{
									exitqueue.push_back(stack.top());
									stack.pop();
									if (stack.empty())
									{
										mLog.push_back("( missing.");
										return e;
									}

								}
							}
							else
							if (t[i] == ")")
							{
								//@TODO check if proper
								while (stack.top() != "(")
								{
									exitqueue.push_back(stack.top());
									stack.pop();
								}
								stack.pop();
								if (!stack.empty())
								if (!isOperator(stack.top()))
								{
									if (stack.top().find_first_of("(),") == std::string::npos)
									{
										exitqueue.push_back(stack.top());
										stack.pop();
									}
								}
							}
							else
							if (t[i] == "(")
							{
								stack.push("(");

							}
						}
					}
					else
					{
						if (!stack.empty())
							while (isOperator(stack.top()) && ((isRightAssociative(t[i], stack.top()) && getOperatorPrecedence(t[i]) <= getOperatorPrecedence(stack.top() )) || (isLeftAssociative(t[i], stack.top()) && getOperatorPrecedence(t[i]) < getOperatorPrecedence(stack.top()))))
							{
								exitqueue.push_back(stack.top());
								stack.pop();
								if (stack.empty())
									break;
							}
						stack.push(t[i]);
					}
				}

			}
			while (!stack.empty())
			{
				exitqueue.push_back(stack.top());
				stack.pop();
			}
				
			return exitqueue;
		}
		OperatorPointer StringInterpreter::toOperatorPointer(const std::string& str)
		{
			return mOperators[str];
		}
		ManagedArgument StringInterpreter::resolveRPN(const std::vector<std::string>& rpn, const VariableTable& local, bool efunc)
		{

			ManagedArgument a, b;
			std::stack<ManagedArgument> stack;
			for (int i = 0; i < rpn.size(); i++)
			{
				
				if (isMathFunction(rpn[i])&&efunc)
				{
					ManagedArgument f = toArgument(rpn[i], mVariables);
					if (f == ManagedArgument())
					{
						mLog.push_back("Failed to resolve RPN.");
						return ManagedArgument();
					}
					int fsize = f->getSize();
					ArgumentCollection* ac = new ArgumentCollection(fsize);
					for (int i = 0; i < fsize; i++)
					{
						ManagedArgument ta = stack.top();
						stack.pop();
						ac->set(i, ta);
					}
					ManagedArgument mac = ManagedArgument(ac);
					GenericMathFunction* gmc = (GenericMathFunction*)f.get();
					stack.push(gmc->operator()(mac));

				}
				
				else
				if (isOperator(rpn[i]))
				{
					a = stack.top();
					stack.pop();
					b = stack.top();
					stack.pop();
					OperatorPointer op = toOperatorPointer(rpn[i]);
					stack.push(((*b).*op)(a));
					
				}
				else
				{
					//mLog.push_back(rpn[i]);
					stack.push(toArgument(rpn[i],local));
				}

				
			}
			if (stack.top() == ManagedArgument())
			{
				mLog.push_back("ResolveRPN: something went wrong. ");
				
			}
			return stack.top();
		}
	}

}