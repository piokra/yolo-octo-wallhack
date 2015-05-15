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
			tr.value = pow(value, r.value);
			return tr;
		}
		Real Real::operator = (const Real& r)
		{
			value = r.value;
			return *this;
		}
		void Real::toString(std::string& str)
		{
			str += tostr(value);
		}
	}
}