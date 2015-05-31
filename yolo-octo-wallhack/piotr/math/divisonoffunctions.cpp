#include "divisionoffunctions.h"
#include "sumoffunctions.h"
#include "poweroffunctions.h"
#include "real.h"
#include "multiplictionoffunctions.h"
#include "differenceoffunctions.h"
namespace Piotr
{
	namespace Math
	{
		DivisionOfFunctions::DivisionOfFunctions(ManagedFunction left, ManagedFunction right) : mLeft(left), mRight(right)
		{
			setSize(std::max({ mLeft->getSize(), mRight->getSize() }));
		}

		ManagedArgument DivisionOfFunctions::operator()(ManagedArgument arg)
		{
			GenericMathFunction* leftf = (GenericMathFunction*)mLeft.get();
			GenericMathFunction* rightf = (GenericMathFunction*)mRight.get();

			ManagedArgument lefta = (*leftf)(arg);
			ManagedArgument righta = (*rightf)(arg);
			return (*lefta) / righta;
		}

		void DivisionOfFunctions::toString(std::string& str)
		{
			std::string tstr = "(";
			std::string tstr2 = "";
			mLeft->toString(tstr2);
			tstr += tstr2;
			tstr2 = "";
			tstr += "/";
			mRight->toString(tstr2);
			tstr += tstr2;
			tstr += ")";
			str += tstr;
		}
		ManagedArgument DivisionOfFunctions::clone()
		{
			return ManagedArgument(new DivisionOfFunctions(mLeft->clone(), mRight->clone()));
		}
		ManagedArgument DivisionOfFunctions::derivative(ManagedArgument x)
		{
			GenericMathFunction* left = (GenericMathFunction*)mLeft.get();
			GenericMathFunction* right = (GenericMathFunction*)mRight.get();
			ManagedArgument ql = ManagedArgument(new MultiplicationOfFunctions(left->derivative(x), mRight));
			ManagedArgument qr = ManagedArgument(new MultiplicationOfFunctions(right->derivative(x),mLeft));
			ManagedArgument q = ManagedArgument(new DifferenceOfFunctions(ql,qr));
			ManagedArgument r = ManagedArgument(new MultiplicationOfFunctions(mRight,mRight));
			return ManagedArgument(new DivisionOfFunctions(q, r));
		}
	}
}