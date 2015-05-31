#ifndef PIOTR_MATH_VARIABLE_H
#define PIOTR_MATH_VARIABLE_H

#include "math_function.h"
#include "../../conversion.h"
#include "constant.h"
#include "real.h"
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

			virtual ManagedArgument clone()
			{
				return ManagedArgument(new Variable(mSize, mPos));
			}
			virtual void toString(std::string& str)
			{
				str += "x";
				str += tostr(mPos);
			}
			virtual ManagedArgument derivative(ManagedArgument x)
			{
				Variable* t = (Variable*)x.get();
				if (t->getPos() != mPos)
				{
					Constant* c = new Constant(1);
					c->set(ManagedArgument(new Real));
					return ManagedArgument(c);
				}
				Constant* c = new Constant(1);
				c->set(ManagedArgument(new Real(1)));
				return ManagedArgument(c);
			}
			virtual int getPos()
			{
				return mPos;
			}
		private:
			int mPos;
			int mSize;

		};
	}
}

#endif