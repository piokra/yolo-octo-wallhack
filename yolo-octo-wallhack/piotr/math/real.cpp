#include "real.h"
#include <math.h>
#include "../../conversion.h"
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
			if (!(r->getType() == getType()))
				return ManagedArgument();
			Real* rr = (Real*)r.get();
			Real* tr = new Real;
			tr->value = rr->value + value;
			return ManagedArgument(tr);
		}
		ManagedArgument Real::operator*(ManagedArgument r)
		{
			if (!(r->getType() == getType()))
				return ManagedArgument();
			Real* rr = (Real*)r.get();
			Real* tr = new Real;
			tr->value = rr->value * value;
			return ManagedArgument(tr);
		}
		ManagedArgument Real::operator-(ManagedArgument r)
		{
			if (!(r->getType() == getType()))
				return ManagedArgument();
			Real* rr = (Real*)r.get();
			Real* tr = new Real;
			tr->value = rr->value - value;
			return ManagedArgument(tr);
		}
		ManagedArgument Real::operator/(ManagedArgument r)
		{
			if (!(r->getType() == getType()))
				return ManagedArgument();
			Real* rr = (Real*)r.get();

			Real* tr = new Real;
			tr->value = rr->value / value;
			return ManagedArgument(tr);
		}
		ManagedArgument Real::operator^(ManagedArgument r)
		{
			if (!(r->getType() == getType()))
				return ManagedArgument();
			Real* rr = (Real*)r.get();

			Real* tr = new Real;
			tr->value = pow(value, rr->value);
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