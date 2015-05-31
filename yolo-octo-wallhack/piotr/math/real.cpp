#include "real.h"
#include <math.h>
#include "../../conversion.h"
#include "poweroffunctions.h"
namespace Piotr
{
	namespace Math
	{
		const Type Real::mType = Type("MATH_REAL");
		Real::Real()
		{
			value = 0;
		}
		Real::Real(double val)
		{
			value = val;
		}
		const Type& Real::getType()
		{
			return mType;
		}
		ManagedArgument Real::clone()
		{
			Real* r = new Real;
			r->value = value;
			return ManagedArgument(r);
		}
		ManagedArgument Real::operator+(ManagedArgument r)
		{
			const static Type func("MATH_FUNCTION");
			
			if (r->getType() == func)
			{
				return r->operator+(this->clone());
			}
			if (!(r->getType() == getType()))
				return ManagedArgument();
			Real* rr = (Real*)r.get();
			Real* tr = new Real;
			tr->value = rr->value + value;
			return ManagedArgument(tr);
		}
		ManagedArgument Real::operator*(ManagedArgument r)
		{
			const static Type func("MATH_FUNCTION");
			if (r->getType() == func)
			{
				return r->operator*(this->clone());
			}
			if (!(r->getType() == getType()))
				return ManagedArgument();
			Real* rr = (Real*)r.get();
			Real* tr = new Real;
			tr->value = rr->value * value;
			return ManagedArgument(tr);
		}
		ManagedArgument Real::operator-(ManagedArgument r)
		{
			const static Type func("MATH_FUNCTION");
			if (r->getType() == func)
			{
							
				ManagedArgument t = r->operator-(clone());
				t = t->operator*(ManagedArgument(new Real(-1)));
				return t;
			}
			if (!(r->getType() == getType()))
				return ManagedArgument();
			Real* rr = (Real*)r.get();
			Real* tr = new Real;
			tr->value = value - rr->value;
			return ManagedArgument(tr);
		}
		ManagedArgument Real::operator/(ManagedArgument r)
		{
			const static Type func("MATH_FUNCTION");
			if (r->getType() == func)
			{
				ManagedArgument t = r->operator/(clone());
				t = t->operator^(ManagedArgument(new Real(-1)));
				return t;
			}
			if (!(r->getType() == getType()))
				return ManagedArgument();
			Real* rr = (Real*)r.get();

			Real* tr = new Real;
			tr->value = value / rr->value;
			return ManagedArgument(tr);
		}
		ManagedArgument Real::operator^(ManagedArgument r)
		{
			const static Type func("MATH_FUNCTION");
			
			if (r->getType() == func)
			{
				return ManagedArgument(new PowerOfFunctions(GenericMathFunction::tryCasting(clone()), r));
			}
			if (!(r->getType() == getType()))
				return ManagedArgument();
			Real* rr = (Real*)r.get();

			Real* tr = new Real;
			tr->value = pow(value,rr->value);
			return ManagedArgument(tr);
		}
		ManagedArgument Real::operator=(ManagedArgument r)
		{
			if (!(r->getType() == getType()))
				return ManagedArgument();
			Real* rr = (Real*)r.get();

			value = rr->value;
			//This is invalid
			//return ManagedArgument(this);
			return ManagedArgument(new Real(value));
		}
		
		void Real::toString(std::string& str)
		{
			str += tostr(value);
		}
	}
}