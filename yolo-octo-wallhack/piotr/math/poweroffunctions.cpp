#include "poweroffunctions.h"

namespace Piotr
{
	namespace Math
	{
		PowerOfFunctions::PowerOfFunctions(ManagedFunction left, ManagedFunction right) : mLeft(left), mRight(right)
		{
			setSize(std::max({ mLeft->getSize(), mRight->getSize() }));
		}

		ManagedArgument PowerOfFunctions::operator()(ManagedArgument arg)
		{
			GenericMathFunction* leftf = (GenericMathFunction*)mLeft.get();
			GenericMathFunction* rightf = (GenericMathFunction*)mRight.get();
			
			ManagedArgument lefta = (*leftf)(arg);
			ManagedArgument righta = (*rightf)(arg);
			return (*lefta) ^ righta;
		}

		void PowerOfFunctions::toString(std::string& str)
		{
			std::string tstr = "(";
			std::string tstr2 = "";
			mLeft->toString(tstr2);
			tstr += tstr2;
			tstr2 = "";
			tstr += "^";
			mRight->toString(tstr2);
			tstr += tstr2;
			tstr += ")";
			str += tstr;
		}
		ManagedArgument PowerOfFunctions::clone()
		{
			return ManagedArgument(new PowerOfFunctions(mLeft->clone(), mRight->clone()));
		}
		ManagedArgument PowerOfFunctions::derivative(ManagedArgument x)
		{
			throw gcnew NotImplementedException();
		}
	}
}