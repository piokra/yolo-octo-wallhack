#ifndef PIOTR_MATH_MATH_FUNCTION_H
#define PIOTR_MATH_MATH_FUNCTION_H

#include "../utill/type.h"
#include "../template/function_template.h"
#include "argument.h"
#include "argument_collection.h"
#include <vector>
#include <algorithm>
#include <math.h>
namespace Piotr
{
	namespace Math
	{
		using namespace Template;
		class GenericMathFunction : public FunctionalObject<ManagedArgument(ManagedArgument)>, public FunctionArgument
		{
		public:
			//@TODO actually implement this
			//virtual ArgumentCollection getInputFormat() = 0;
			//virtual ArgumentCollection getOutputFormat() = 0;

			ManagedArgument tryCasting(ManagedArgument arg);

			virtual ManagedArgument operator+(ManagedArgument r);
			virtual ManagedArgument operator*(ManagedArgument r);
			virtual ManagedArgument operator-(ManagedArgument r);
			virtual ManagedArgument operator/(ManagedArgument r);
			virtual ManagedArgument operator^(ManagedArgument r);
			virtual ManagedArgument operator=(ManagedArgument r);

			virtual const Type& getType();
		
			virtual int getSize();
			virtual void setSize(int size);
		protected:
		private:
			int mSize;
		};
	}
}


#endif