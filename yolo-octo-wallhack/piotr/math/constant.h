#ifndef PIOTR_MATH_CONSTANT_H
#define PIOTR_MATH_CONSTANT_H


#include "math_function.h"

namespace Piotr
{
	namespace Math
	{
		//@TODO refactor
		class Constant : public GenericMathFunction
		{
			friend class Constant;
		public:
			Constant(int size) : mSize(size)
			{
				ArgumentCollection* ac = new ArgumentCollection(size);
				mOutput = ManagedArgument(ac);
			}
			void set(int i, ManagedArgument t)
			{
				ArgumentCollection* ac = (ArgumentCollection*)(mOutput.get());
				ac->set(i, t);
			}
			void set(ManagedArgument arg)
			{
				mOutput = arg;
			}
			virtual ManagedArgument operator()(ManagedArgument arg)
			{
				return mOutput;
			}
			virtual ArgumentCollection getInputFormat()
			{
				ArgumentCollection ac;
				return ac;
			}
			virtual ArgumentCollection getOutputFormat()
			{
				ArgumentCollection ac;
				return ac;
			}
			virtual ManagedArgument clone()
			{
				Constant* t = new Constant(mSize);
				t->mOutput = mOutput->clone();
				return ManagedArgument(t);
			}
			virtual void toString(std::string& str)
			{
				mOutput->toString(str);
			}
		private:
			int mSize;
			ManagedArgument mOutput;
		};
	}
}

#endif