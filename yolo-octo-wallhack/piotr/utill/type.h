#ifndef PIO_UTILL_TYPE_H
#define PIO_UTILL_TYPE_H

#include <string>

namespace Piotr
{
	namespace Utill
	{
		class Type
		{
		public:
			Type(const std::string& string);
			friend bool operator==(const Type& l, const Type& r);
		private:
			std::string mTypeString;
		};
	}
}




#endif