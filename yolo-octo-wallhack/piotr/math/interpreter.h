#ifndef PIOTR_MATH_INTERPRETER_H
#define PIOTR_MATH_INTERPRETER_H

#include <string>
#include <unordered_map>
#include "argument.h"
#include "argument_collection.h"

namespace Piotr
{
	namespace Math
	{
		
		class StringInterpreter
		{
			using CompilerFunction = void (StringInterpreter::*)(std::string);
		public:
			StringInterpreter();

			void compileLine(const std::string& str);

		protected:
			bool isKeyword(const std::string& str);
		private:
			std::unordered_map<std::string, CompilerFunction> mKeywords;
			std::unordered_map<std::string, FunctionArgument*> mVariables;
			std::vector<std::string> mResult;
			std::vector<std::string> mLog;
		};
	}
}
#endif