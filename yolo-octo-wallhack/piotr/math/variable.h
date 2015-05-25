#ifndef PIOTR_MATH_VARIABLE_H
#define PIOTR_MATH_VARIABLE_H

#include "math_function.h"
#include "../../conversion.h"
namespace Piotr
{
	namespace Math
	{
		//@TODO refactorize
		class Variable : public GenericMathFunction
		{
		public:
			Variable(int size, int pos) : mPos(pos), mSize(size)
			{
				setSize(size);
			};

			virtual ManagedArgument operator()(ManagedArgument arg)
			{
				return arg->operator[](mPos);
				
			}
			/*virtual	ManagedArgument getInputFormat()
			{
				//ArgumentCollection ac;
				//return ac;
			}*/
			/*
			virtual ManagedArgument getOutputFormat()
			{
				return mOutput;
			}
		private:
			ManagedArgument mOutput;*/
		private:
			int mPos;
			int mSize;
			virtual ManagedArgument clone()
			{
				return ManagedArgument(new Variable(mSize, mPos));
			}
			virtual void toString(std::string& str)
			{
				str += "x";
				str += tostr(mPos);
			}
		};
	}
}

#endif