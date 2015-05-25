#include "multiplictionoffunctions.h"

namespace Piotr
{
	namespace Math
	{
		MultiplicationOfFunctions::MultiplicationOfFunctions(ManagedFunction left, ManagedFunction right) : mLeft(right), mRight(left)
		{
			setSize(std::max({ mLeft->getSize(), mRight->getSize() }));
		}

		ManagedArgument MultiplicationOfFunctions::operator()(ManagedArgument arg)
		{
			GenericMathFunction* leftf = (GenericMathFunction*)mLeft.get();
			GenericMathFunction* rightf = (GenericMathFunction*)mRight.get();
			
			ManagedArgument lefta = (*leftf)(arg);
			ManagedArgument righta = (*rightf)(arg);
			return (*lefta) * righta;
		}

		void MultiplicationOfFunctions::toString(std::string& str)
		{
			std::string tstr = "(";
			std::string tstr2 = "";
			mLeft->toString(tstr2);
			tstr += tstr2;
			tstr2 = "";
			tstr += "*";
			mRight->toString(tstr2);
			tstr += tstr2;
			tstr += ")";
			str += tstr;
		}
		ManagedArgument MultiplicationOfFunctions::clone()
		{
			return ManagedArgument(new MultiplicationOfFunctions(mLeft->clone(), mRight->clone()));
		}
	}
}