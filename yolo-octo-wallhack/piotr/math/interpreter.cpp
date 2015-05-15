#include "interpreter.h"
#include "real.h"
#include "../../Output.h"
#include <stack>
#include <queue>
namespace Piotr
{
	namespace Math
	{
		using namespace System;
		StringInterpreter::StringInterpreter()
		{
			mKeywords["Real"] = &StringInterpreter::allocateReal;
			mKeywords["DisplayReal"] = &StringInterpreter::displayReal;
			mKeywords["Set"] = &StringInterpreter::setReal;
		}

		void StringInterpreter::run()
		{
			mCurrentLine = 0;
			while (mCurrentLine < mCode.size())
			{
				compileLine(mCode[mCurrentLine]);
				mCurrentLine++;
			}
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
			mLog.push_back("Compiled line properly.");
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
			std::vector<std::string> t = seperateWords(str," ","");
			if (t.size() != 2)
			{
				mLog.push_back(TAG + "Invalid size. Did not allocate real.");
				return;
			}

			mLog.push_back(TAG + "Allocated real. Name: " + t[1]);
			mVariables[t[1]] = ManagedArgument(new Real);
		}

		void StringInterpreter::displayReal(const std::string& str)
		{
			static const std::string TAG = "displayReal: ";
			std::vector<std::string> t = seperateWords(str," ", "");
			if (t.size() != 2)
			{
				mLog.push_back(TAG + "Invalid size. Did not display.");
				return;
			}
			auto it = mVariables.find(t[1]);
			if (it == mVariables.end())
			{
				mLog.push_back(TAG + "No such variable.");
				return;
			}
			mLog.push_back(TAG + "Displayed real. Name: " + t[1]);
			Real* real = (Real*)it->second.get();
			std::string ts;
			real->toString(ts);
			mResult.push_back(ts);
		}

		void StringInterpreter::setReal(const std::string& str)
		{
			static const std::string TAG = "setReal: ";
			std::vector<std::string> t = seperateWords(str," ", "");
			if (t.size() != 3)
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
			Real* real = (Real*)it->second.get();
			
			//try to find variable 2

			it = mVariables.find(t[2]);
			if (it == mVariables.end())
			{
				//try to cast to double
				//@TODO not managed cast

				double td;
				String^ tms = gcnew String(t[2].c_str());
				if (!Double::TryParse(tms, td))
				{
					mLog.push_back(TAG + "Failed to parse real. ");
					return;
				}
				mLog.push_back(TAG + "Parsed real properly.");
				real->value = td;
				return;

			}
			Real* real2 = (Real*)it->second.get();
			real->value = real2->value;
			mLog.push_back(TAG + "Ok.");
			//variable 2 found

			
		}

		bool StringInterpreter::isNumber(const std::string& str)
		{
			String^ gcs = gcnew String(str.c_str());
			double t;
			return Double::TryParse(gcs, t);

		}
		bool StringInterpreter::isVariable(const std::string& str)
		{
			auto it = mVariables.find(str);
			return (it != mVariables.end());
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


		std::vector<std::string> StringInterpreter::toRPN(const std::string& str)
		{
			//@TODO check for errors
			std::vector<std::string> e;
			std::vector<std::string> t = seperateWords(str, " ", "()+-*^/,");
			std::vector<std::string> exitqueue;
			std::stack<std::string> stack;
			
			for (int i = 0; i < t.size(); i++)
			{
				if (isNumber(t[i])||isVariable(t[i]))
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

	}

}