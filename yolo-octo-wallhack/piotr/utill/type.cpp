/*
#ifdef _MSC_BUILD
#include "../../stdafx.h"
#endif
*/
#include "type.h"

namespace Piotr
{
	namespace Utill
	{
		Type::Type(const std::string& str) : mTypeString(str)
		{

		}

		bool operator==(const Type& l, const Type& r)
		{
			return l.mTypeString == r.mTypeString;
		}
	}
}