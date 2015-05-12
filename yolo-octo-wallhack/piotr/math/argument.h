#ifndef PIO_MATH_ARGUMENT_H
#define PIO_MATH_ARGUMENT_H

#include "../Utill/type.h"

namespace Piotr
{
	namespace Math
	{
		using namespace Utill;
		using namespace System;
		class FunctionArgument
		{
		public:
			virtual const Type& getType() = 0;
			virtual FunctionArgument* clone() = 0;
			virtual void toString(String^& str) = 0;
		};

	}
}



#endif