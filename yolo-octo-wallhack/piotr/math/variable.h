#ifndef PIOTR_MATH_VARIABLE_H
#define PIOTR_MATH_VARIABLE_H

#include "math_function.h"

namespace Piotr
{
	namespace Math
	{
		template<typename T>
		class Variable : public GenericMathFunction
		{
		public:
			Variable(int size, int pos) : mOutput(size), mPos(pos)
			{
				for (int i = 0; i < size; i++)
					mOutput.set(i, new T);
			};

			ArgumentCollection operator()(ArgumentCollection arg)
			{
				mOutput.set(mPos, arg.get(mPos)->clone());
				return mOutput;
			}
			virtual ArgumentCollection getInputFormat()
			{
				ArgumentCollection ac;
				return ac;
			}
			virtual ArgumentCollection getOutputFormat()
			{
				return mOutput;
			}
		private:
			ArgumentCollection mOutput;
			int mPos;
		};
	}
}

#endif