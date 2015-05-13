#ifndef PIOTR_MATH_ARGUMENT_COLLECTION
#define PIOTR_MATH_ARGUMENT_COLLECTION

#include "argument.h"

namespace Piotr
{
#define PMA_EQUAL 0
#define PMA_DIFFERENT 1
#define PMA_SAME_TYPE 0
#define PMA_DIFFERENT_TYPE 2
#define PMA_SAME_SIZE 0
#define PMA_DIFFERENT_SIZE 4
#define PMA_BULLSHIT 0xFFFF
	namespace Math
	{
		class ArgumentCollection
		{
		public:
			ArgumentCollection();
			ArgumentCollection(int size);
			void set(int it, FunctionArgument* arg);
			FunctionArgument* const get(int it) const;
			FunctionArgument* getEditable(int it);
			void recycle();

			int getSize() const;

			ArgumentCollection clone() const;
			void copyFrom(const ArgumentCollection& ac);

			friend int compare(const ArgumentCollection& l, const ArgumentCollection& r);

			System::String^ toString();
		private:
			FunctionArgument** mArguments;
			int mSize;
		};
	}
}

#endif
