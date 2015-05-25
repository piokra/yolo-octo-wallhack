#include "math_function.h"
#include "sumoffunctions.h"
#include "poweroffunctions.h"
#include "multiplictionoffunctions.h"
#include "constant.h"
#include "real.h"
#include <exception>
namespace Piotr
{
	namespace Math
	{
		ManagedArgument GenericMathFunction::operator+(ManagedArgument r)
		{
			GenericMathFunction* t = new SumOfFunctions(clone(), tryCasting(r));
			return ManagedArgument(t);
		}
		ManagedArgument GenericMathFunction::operator*(ManagedArgument r)
		{
			GenericMathFunction* t = new MultiplicationOfFunctions(clone(), tryCasting(r));
			return ManagedArgument(t);
		}
		ManagedArgument GenericMathFunction::operator-(ManagedArgument r)
		{
			throw gcnew NotImplementedException();
			return ManagedArgument();
		}
		ManagedArgument GenericMathFunction::operator/(ManagedArgument r)
		{
			throw gcnew NotImplementedException();
			return ManagedArgument();
		}
		ManagedArgument GenericMathFunction::operator^(ManagedArgument r)
		{
			GenericMathFunction* t = new PowerOfFunctions(clone(), tryCasting(r));
			return ManagedArgument(t);
		}
		ManagedArgument GenericMathFunction::operator=(ManagedArgument r)
		{
			throw gcnew NotImplementedException();
			return ManagedArgument();
		}

		const Type& GenericMathFunction::getType()
		{
			const static Type type("MATH_FUNCTION");
			return type;
		}
		int GenericMathFunction::getSize()
		{
			return mSize;
		}

		void GenericMathFunction::setSize(int size)
		{
			mSize = size;
		}

		ManagedArgument GenericMathFunction::tryCasting(ManagedArgument arg)
		{
			const static Type real("MATH_REAL");
			const static Type func("MATH_FUNCTION");
			if (arg->getType() == func)
				return arg;
			if (arg->getType() == real)
			{
				//@todo does this actually work
				Constant* c = new Constant(1);
				c->set(arg);
				return ManagedArgument(c);
				
			}
		}
	}
}