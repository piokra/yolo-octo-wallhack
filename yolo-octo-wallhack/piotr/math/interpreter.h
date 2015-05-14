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

			void compileLine(const std::string& str);
			void showLog();
			void showResult();

		protected:
			bool isKeyword(const std::string& str);
			std::string removeSpaces(const std::string& str);
			std::string removeKeywords(const std::string& str);
			std::vector<std::string> seperateWords(const std::string& str);

			
			void allocateReal(const std::string& str);
			void displayReal(const std::string& str);
		private:
			std::unordered_map<std::string, CompilerFunction> mKeywords;
			std::unordered_map<std::string, ManagedArgument> mVariables;
			std::vector<std::string> mResult;
			std::vector<std::string> mLog;
		};
	}
}
#endif