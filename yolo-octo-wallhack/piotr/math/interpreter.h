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

		class StringInterpreter;
		using CompilerFunction = void (StringInterpreter::*)(const std::string&);
		using ManagedArgument = std::shared_ptr < FunctionArgument >;
		using OperatorPointer = ManagedArgument(FunctionArgument::*)(ManagedArgument);
		using VariableTable = std::unordered_map < std::string, ManagedArgument > ;

		class StringInterpreter
		{
			friend void SITestFunction();

		public:
			StringInterpreter();
			virtual ~StringInterpreter();

			void run();
			void showLog();
			void showResult();
			void pushLine(const std::string& str);

		protected:
			void compileLine(const std::string& str);
			bool isKeyword(const std::string& str);
			std::string removeSpaces(const std::string& str);
			std::string removeKeywords(const std::string& str);
			std::vector<std::string> prepareCode();
			std::vector<std::string> seperateWords(const std::string& str, const std::string& toremove, const std::string& tokeep);

			
			void allocateReal(const std::string& str);
			void display(const std::string& str);
			void set(const std::string& str);
			void sete(const std::string& str);
			void gotoLine(const std::string& str);
			void makeLabel(const std::string& str);
			void ifStatement(const std::string& str);
			void allocateFunction(const std::string& str);
			void drawGraph2D(const std::string& str);
			void expandTaylor(const std::string& str);
			void countDerivative(const std::string& str);
			void makeAlias(const std::string& str);

			////

			bool checkSize(const std::string& tag, const std::vector<std::string>& statement, unsigned minsize, unsigned maxsize);
			bool isNumber(const std::string& str);
			bool isVariable(const std::string& str, const VariableTable& local);
			bool isMathFunction(const std::string& str);
			bool isOperator(const std::string& str);
			int getOperatorPrecedence(const std::string& str);
			bool isLeftAssociative(const std::string& left, const std::string& right);
			bool isRightAssociative(const std::string& left, const std::string& right);
			
			ManagedArgument toArgument(const std::string& str, const VariableTable& local);
			OperatorPointer toOperatorPointer(const std::string& str);
			std::vector<std::string> toRPN(const std::string& str, const VariableTable& local, bool efunc);
			ManagedArgument resolveRPN(const std::vector<std::string>& rpn, const VariableTable& local, bool efunc);
		private:
			std::vector<std::string> mCode;
			int mCurrentLine;
			
			//@TODO implement
			std::vector<int> mJumps;

			//@TODO make static and constant?
			std::unordered_map<std::string, CompilerFunction> mKeywords;
			//@TODO make static and constant?
			std::unordered_map<std::string, OperatorPointer> mOperators;
			std::unordered_map<std::string, ManagedArgument> mVariables;

			std::unordered_map<std::string, VariableTable> mLocalVariables;

			std::unordered_map<std::string, int> mLabels;
			std::vector<std::string> mResult;
			std::vector<std::string> mLog;
		};
	}
}
#endif