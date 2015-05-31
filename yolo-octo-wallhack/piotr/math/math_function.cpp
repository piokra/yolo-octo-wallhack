#include "math_function.h"
#include "sumoffunctions.h"
#include "poweroffunctions.h"
#include "multiplictionoffunctions.h"
#include "differenceoffunctions.h"
#include "divisionoffunctions.h"
#include "constant.h"
#include "real.h"
#include "variable.h"
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
			GenericMathFunction* t = new DifferenceOfFunctions(clone(), tryCasting(r));
			return ManagedArgument(t);
		}
		ManagedArgument GenericMathFunction::operator/(ManagedArgument r)
		{
			GenericMathFunction* t = new DivisionOfFunctions(clone(), tryCasting(r));
			return ManagedArgument(t);
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
		ManagedArgument GenericMathFunction::derivative(ManagedArgument)
		{
#ifdef _DEBUG
			throw gcnew NotImplementedException();
#endif
			return ManagedArgument();
		}

		ManagedArgument GenericMathFunction::taylorSeries1D(ManagedArgument x, ManagedArgument items)
		{
			Real* itemc = (Real*)items.get();
			int i = itemc->value ;
			double factorial = 1;
			ManagedArgument t = this->operator()(x);
			ManagedArgument v = ManagedArgument(new Variable(1, 0));
			ManagedArgument tt = derivative(v);
			ManagedArgument ttt;
			ManagedArgument tttt;
			for (int j = 0; j < i; j++)
			{
				tttt = ManagedArgument(new PowerOfFunctions(ManagedArgument(new DifferenceOfFunctions(v, x)), ManagedArgument(new Real(i + 1))));
				ttt = (*tt).operator/(ManagedArgument(new Real(factorial)));
				ttt = (*ttt).operator*(tttt);
				t = (*t).operator+(ttt);
				factorial *= (i + 2.);
				GenericMathFunction* gmc = (GenericMathFunction*)tt.get();
				tt = gmc->derivative(v);
			}
			return t;

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