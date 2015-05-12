#ifndef PIOTR_MATH_REAL_H
#define PIOTR_MATH_REAL_H

#include "../utill/type.h"
#include "argument.h"
namespace Piotr
{
	namespace Math
	{
		using namespace Utill;
		class Real : public FunctionArgument
		{
			const static Type mType;
		public:
			Real();
			Real(double x);
			double value;
			virtual const Type& getType();
			virtual FunctionArgument* clone();
			Real operator+(const Real& r);
			Real operator*(const Real& r);
			Real operator-(const Real& r);
			Real operator/(const Real& r);
			Real operator^(const Real& r);
			void toString(System::String^& str);
			
		};
		
	}

	
}

#endif