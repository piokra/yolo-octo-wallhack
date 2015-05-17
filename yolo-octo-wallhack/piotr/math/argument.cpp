#include "argument.h"

namespace Piotr
{
	namespace Math
	{
		FunctionArgument::~FunctionArgument()
		{

		}

		ManagedArgument FunctionArgument::operator[](int i)
		{
			return clone();
		}

		int FunctionArgument::getSize()
		{
			return 1;
		}
	}
}