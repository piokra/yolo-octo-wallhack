#ifndef PIO_MATH_ARGUMENT_H
#define PIO_MATH_ARGUMENT_H

#include "../Utill/type.h"
#include <string>
#include <memory>
namespace Piotr
{
	namespace Math
	{
		using namespace Utill;
		using namespace System;
		class FunctionArgument;
		using ManagedArgument = std::shared_ptr < FunctionArgument > ;
		class FunctionArgument
		{
		public:
			virtual ~FunctionArgument();
			virtual const Type& getType() = 0;
			virtual ManagedArgument clone() = 0;
			virtual void toString(std::string& str) = 0;

			virtual int getSize();

			virtual ManagedArgument operator+(ManagedArgument r) = 0;
			virtual ManagedArgument operator*(ManagedArgument r) = 0;
			virtual ManagedArgument operator-(ManagedArgument r) = 0;
			virtual ManagedArgument operator/(ManagedArgument r) = 0;
			virtual ManagedArgument operator^(ManagedArgument r) = 0;
			virtual ManagedArgument operator=(ManagedArgument r) = 0;
			virtual ManagedArgument operator[](int i);
		};

	}
}



#endif