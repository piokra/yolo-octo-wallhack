#include "sumoffunctions.h"
#include <algorithm>
namespace Piotr
{
	namespace Math
	{
		SumOfFunctions::SumOfFunctions(ManagedFunction left, ManagedFunction right) : mLeft(right), mRight(left)
		{
			setSize(std::max({ mLeft->getSize(), mRight->getSize() }));
		}

		ManagedArgument SumOfFunctions::operator()(ManagedArgument arg)
		{
			GenericMathFunction* leftf = (GenericMathFunction*)mLeft.get();
			GenericMathFunction* rightf = (GenericMathFunction*)mRight.get();
			
			ManagedArgument lefta = (*leftf)(arg);
			ManagedArgument righta = (*rightf)(arg);
			return (*lefta) + righta;
		}

		void SumOfFunctions::toString(std::string& str)
		{
			std::string tstr = "(";
			std::string tstr2 = "";
			mLeft->toString(tstr2);
			tstr += tstr2;
			tstr2 = "";
			tstr += "+";
			mRight->toString(tstr2);
			tstr += tstr2;
			tstr += ")";
			str += tstr;
		}
		ManagedArgument SumOfFunctions::clone()
		{
			return ManagedArgument(new SumOfFunctions(mLeft->clone(), mRight->clone()));
		}
	}
}