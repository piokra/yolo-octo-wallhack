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

			virtual ManagedArgument operator+(ManagedArgument r);
			virtual ManagedArgument operator*(ManagedArgument r);
			virtual ManagedArgument operator-(ManagedArgument r);
			virtual ManagedArgument operator/(ManagedArgument r);
			virtual ManagedArgument operator^(ManagedArgument r);
			virtual ManagedArgument operator=(ManagedArgument r);

			virtual void toString(std::string& str);
			
		};
		
	}

	
}

#endif