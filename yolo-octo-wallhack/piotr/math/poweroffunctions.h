#pragma once

#include "math_function.h"
#include <memory>
namespace Piotr
{
	namespace Math
	{
		using ManagedFunction = std::shared_ptr < FunctionArgument > ;
		class PowerOfFunctions : public GenericMathFunction
		{
		public:

			PowerOfFunctions(ManagedFunction left, ManagedFunction right);

			virtual ManagedArgument operator()(ManagedArgument arg);
			virtual ManagedArgument clone();
			virtual void toString(std::string& str);
			virtual ManagedArgument derivative(ManagedArgument x);
		protected:
		private:
			ManagedFunction mLeft;
			ManagedFunction mRight;
		};
	}
}