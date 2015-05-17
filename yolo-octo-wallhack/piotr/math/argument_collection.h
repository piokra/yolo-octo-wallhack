#ifndef PIOTR_MATH_ARGUMENT_COLLECTION
#define PIOTR_MATH_ARGUMENT_COLLECTION

#include "argument.h"
#include <memory>

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
		using ManagedArguments = std::shared_ptr < FunctionArgument >* ;
		using ManagedArgument = std::shared_ptr < FunctionArgument > ;
		class ArgumentCollection : public FunctionArgument
		{
			//@done @TODO REPLACE WITH SHARED_PTRS
		public:
			ArgumentCollection();
			ArgumentCollection(int size);
			virtual int getSize();
			void set(int it, ManagedArgument arg);
			ManagedArgument const get(int it) const;
			ManagedArgument getEditable(int it);
			void recycle();

			int getSize() const;

			virtual ManagedArgument clone();
			void copyFrom(const ArgumentCollection& ac);

			friend int compare(const ArgumentCollection& l, const ArgumentCollection& r);

			System::String^ toString();
			void toString(std::string& str);

			//Standard argument operators
			virtual ManagedArgument operator+(ManagedArgument r);
			virtual ManagedArgument operator*(ManagedArgument r);
			virtual ManagedArgument operator-(ManagedArgument r);
			virtual ManagedArgument operator/(ManagedArgument r);
			virtual ManagedArgument operator^(ManagedArgument r);
			virtual ManagedArgument operator=(ManagedArgument r);
			virtual ManagedArgument operator[](int i);
			virtual const Type& getType();
		private:
			ManagedArguments mArguments;

			int mSize;
		};
	}
}

#endif
