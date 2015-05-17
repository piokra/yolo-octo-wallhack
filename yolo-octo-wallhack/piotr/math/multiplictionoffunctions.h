#pragma once

#include "math_function.h"
#include <memory>
namespace Piotr
{
	namespace Math
	{
		using ManagedFunction = std::shared_ptr < FunctionArgument > ;
		class MultiplicationOfFunctions : public GenericMathFunction
		{
		public:

			MultiplicationOfFunctions(ManagedFunction left, ManagedFunction right);

			virtual ManagedArgument operator()(ManagedArgument arg);
			virtual ManagedArgument clone();
			virtual void toString(std::string& str);
		protected:
		private:
			ManagedFunction mLeft;
			ManagedFunction mRight;
		};
	}
}