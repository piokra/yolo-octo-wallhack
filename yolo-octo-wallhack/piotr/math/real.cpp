#include "real.h"
#include <math.h>
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
		FunctionArgument* Real::clone()
		{
			Real* r = new Real;
			r->value = value;
			return r;
		}
		Real Real::operator + (const Real& r)
		{
			Real tr;
			tr.value = r.value + value;
			return tr;
		}
		Real Real::operator * (const Real& r)
		{
			Real tr;
			tr.value = r.value * value;
			return tr;
		}
		Real Real::operator - (const Real& r)
		{
			Real tr;
			tr.value = r.value - value;
			return tr;
		}
		Real Real::operator / (const Real& r)
		{
			Real tr;
			tr.value = r.value / value;
			return tr;
		}
		Real Real::operator ^ (const Real& r)
		{
			Real tr;
			tr.value = pow(value,r.value);
			return tr;
		}
		void Real::toString(System::String^& str)
		{
			/*
				@TODO PROPER CONVERSION
			*/
			System::Double t = value;
			str += t.ToString();
		}
	}
}