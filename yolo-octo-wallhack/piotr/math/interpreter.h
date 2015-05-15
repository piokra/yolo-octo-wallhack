#ifndef PIOTR_MATH_INTERPRETER_H
#define PIOTR_MATH_INTERPRETER_H

#include <string>
#include <unordered_map>
#include <memory>
#include "argument.h"
#include "argument_collection.h"

namespace Piotr
{
	namespace Math
	{

		class StringInterpreter
		{
			friend void SITestFunction();
			using CompilerFunction = void (StringInterpreter::*)(const std::string&);
			using ManagedArgument = std::shared_ptr < FunctionArgument > ;
		public:
			StringInterpreter();

			void run();
			void showLog();
			void showResult();
			void pushLine(const std::string& str);

		protected:
			void compileLine(const std::string& str);
			bool isKeyword(const std::string& str);
			std::string removeSpaces(const std::string& str);
			std::string removeKeywords(const std::string& str);
			std::vector<std::string> seperateWords(const std::string& str, const std::string& toremove, const std::string& tokeep);

			
			void allocateReal(const std::string& str);
			void displayReal(const std::string& str);
			void setReal(const std::string& str);

			bool isNumber(const std::string& str);
			bool isVariable(const std::string& str);
			bool isOperator(const std::string& str);
			int getOperatorPrecedence(const std::string& str);
			bool isLeftAssociative(const std::string& left, const std::string& right);
			bool isRightAssociative(const std::string& left, const std::string& right);
			std::vector<std::string> toRPN(const std::string& str);
		private:
			std::vector<std::string> mCode;
			int mCurrentLine;
			std::unordered_map<std::string, CompilerFunction> mKeywords;
			std::unordered_map<std::string, ManagedArgument> mVariables;
			std::vector<std::string> mResult;
			std::vector<std::string> mLog;
		};
	}
}
#endif