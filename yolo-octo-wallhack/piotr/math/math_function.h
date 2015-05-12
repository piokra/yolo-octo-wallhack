#ifndef PIOTR_MATH_MATH_FUNCTION_H
#define PIOTR_MATH_MATH_FUNCTION_H

#include "../utill/type.h"
#include "../template/function_template.h"
#include "argument.h"
#include "argument_collection.h"
#include <vector>
namespace Piotr
{
	namespace Math
	{
		using namespace Template;
		class GenericMathFunction : public FunctionalObject<ArgumentCollection(ArgumentCollection)>//, public FunctionArgument
		{
			virtual ArgumentCollection getInputFormat() = 0;
			virtual ArgumentCollection getOutputFormat() = 0;
		};
	}
}


#endif