#ifndef PIOTR_MATH_CONSTANT_H
#define PIOTR_MATH_CONSTANT_H


#include "math_function.h"

namespace Piotr
{
	namespace Math
	{
		template<typename T>
		class Constant
		{
		public:
			Constant(int size) : mOutput(size)
			{
				
			};
			void set(int i, T* t)
			{
				mOutput.set(i, t);
			}
			void set(ArgumentCollection arg)
			{
				mOutput.recycle();
				mOutput = arg;
			}
			ArgumentCollection operator()(ArgumentCollection arg)
			{
				return mOutput;
			}

		private:
			ArgumentCollection mOutput;
		};
	}
}

#endif