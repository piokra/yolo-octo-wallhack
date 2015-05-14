#include "interpreter.h"
#include "real.h"
#include "../../Output.h"
namespace Piotr
{
	namespace Math
	{
		StringInterpreter::StringInterpreter()
		{
			mKeywords["Real"] = &StringInterpreter::allocateReal;
			mKeywords["DisplayReal"] = &StringInterpreter::displayReal;
		}

		//@TODO
		void StringInterpreter::compileLine(const std::string& str)
		{
			if (str.size() < 1)
			{
				mLog.push_back("Empty line aborting.");
				return;
			}
			std::vector<std::string> words = seperateWords(str);
			
			if (!isKeyword(words[0]))
			{
				mLog.push_back("First word not a keyword aborting");
				return;
			}
			
			CompilerFunction cf = mKeywords[words[0]];
			(this->*cf)(str);
			mLog.push_back("Compiled line properly.");
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
			std::vector<std::string> t = seperateWords(str);
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

		std::vector<std::string> StringInterpreter::seperateWords(const std::string& str)
		{
			std::vector<std::string> ret;
			int npos, pos = 0;
			int start = 0;
			int end = 0;
			while (end != std::string::npos)
			{
				start = str.find_first_not_of(" ", end);
				end = str.find_first_of(" ", end + 1);
				if (start < end && start != -1)
				{
					ret.push_back(str.substr(start, end - start));
				}
			}
			ret.push_back(str.substr(start, str.size() - start));
			return ret;
		}

		//Compiler functions

		void StringInterpreter::allocateReal(const std::string& str)
		{
			static const std::string TAG = "allocateReal: ";
			std::vector<std::string> t = seperateWords(str);
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
			std::vector<std::string> t = seperateWords(str);
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

	}

}