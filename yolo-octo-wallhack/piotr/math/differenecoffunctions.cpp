#include "differenceoffunctions.h"
#include <algorithm>
namespace Piotr
{
	namespace Math
	{
		DifferenceOfFunctions::DifferenceOfFunctions(ManagedFunction left, ManagedFunction right) : mLeft(left), mRight(right)
		{
			setSize(std::max({ mLeft->getSize(), mRight->getSize() }));
		}

		ManagedArgument DifferenceOfFunctions::operator()(ManagedArgument arg)
		{
			GenericMathFunction* leftf = (GenericMathFunction*)mLeft.get();
			GenericMathFunction* rightf = (GenericMathFunction*)mRight.get();

			ManagedArgument lefta = (*leftf)(arg);
			ManagedArgument righta = (*rightf)(arg);
			return (*lefta) - righta;
		}

		void DifferenceOfFunctions::toString(std::string& str)
		{
			std::string tstr = "(";
			std::string tstr2 = "";
			mLeft->toString(tstr2);
			tstr += tstr2;
			tstr2 = "";
			tstr += "-";
			mRight->toString(tstr2);
			tstr += tstr2;
			tstr += ")";
			str += tstr;
		}
		ManagedArgument DifferenceOfFunctions::clone()
		{
			return ManagedArgument(new DifferenceOfFunctions(mLeft->clone(), mRight->clone()));
		}
		ManagedArgument DifferenceOfFunctions::derivative(ManagedArgument x)
		{
			GenericMathFunction* left = (GenericMathFunction*)mLeft.get();
			GenericMathFunction* right = (GenericMathFunction*)mRight.get();
			return ManagedArgument(new DifferenceOfFunctions(left->derivative(x), right->derivative(x)));
		}
	}
}