#include "argument_collection.h"
#include "../../Input.h"
namespace Piotr
{
	namespace Math
	{

		//@todo remove
		inline std::string toStringFromManaged(System::String^ str)
		{
			std::string ret = "";

			for (int i = 0; i < str->Length; i++)
			{
				ret += str[i];
			}
			return ret;
		}
		ArgumentCollection::ArgumentCollection()
		{
			mSize = 0;
			mArguments = 0;
		}
		ArgumentCollection::ArgumentCollection(int size)
		{
			mSize = size;
			mArguments = new std::shared_ptr<FunctionArgument>[size];
			for (int i = 0; i < mSize; i++)
				mArguments[i] = 0;
		}
		void ArgumentCollection::recycle()
		{
			delete[] mArguments;
		}

		ManagedArgument ArgumentCollection::clone()
		{
			ArgumentCollection* r = new ArgumentCollection(mSize);
			for (int i = 0; i < mSize; i++)
				r->set(i, ManagedArgument(mArguments[i]->clone()));
			return ManagedArgument(r);
		}

		int ArgumentCollection::getSize()
		{
			return mSize;
		}

		void ArgumentCollection::copyFrom(const ArgumentCollection& ac)
		{
			if (ac.getSize() != mSize) return;
			for (int i = 0; i < mSize; i++)
			{
				set(i, ManagedArgument(ac.get(i)->clone()));
			}
		}

		ManagedArgument ArgumentCollection::operator+(ManagedArgument r)
		{
			ArgumentCollection ac(mSize);
			for (int i = 0; i < mSize; i++)
			{
				ac.set(i, mArguments[i]->operator+(r->operator[](i)));
			}
			return ManagedArgument(ac.clone());
		}
		ManagedArgument ArgumentCollection::operator*(ManagedArgument r)
		{
			ArgumentCollection ac(mSize);
			for (int i = 0; i < mSize; i++)
			{
				ac.set(i, mArguments[i]->operator*(r->operator[](i)));
			}
			return ManagedArgument(ac.clone());
		}
		ManagedArgument ArgumentCollection::operator-(ManagedArgument r)
		{
			ArgumentCollection ac(mSize);
			for (int i = 0; i < mSize; i++)
			{
				ac.set(i, mArguments[i]->operator-(r->operator[](i)));
			}
			return ManagedArgument(ac.clone());
		}
		ManagedArgument ArgumentCollection::operator/(ManagedArgument r)
		{
			return ManagedArgument(new ArgumentCollection(*this));
		}
		ManagedArgument ArgumentCollection::operator^(ManagedArgument r)
		{
			return ManagedArgument(new ArgumentCollection(*this));
		};
		ManagedArgument ArgumentCollection::operator=(ManagedArgument r)
		{
			(*this) = *(ArgumentCollection*)(r.get());
			return ManagedArgument(new ArgumentCollection(*this));
		}
		ManagedArgument ArgumentCollection::operator[](int i)
		{
			return mArguments[i];
		}
		int compare(const ArgumentCollection& l, const ArgumentCollection& r)
		{
			/*
			@TODO PROPER RETURN CODES
			*/
			int res = 0;
			if (l.mSize != r.mSize) return PMA_BULLSHIT;
			if (l.mArguments&&r.mArguments)
			for (int i = 0; i < l.mSize; i++)
			{
				if (!(l.mArguments[i]->getType() == r.mArguments[i]->getType()))
					res++;
			}
			if (res) return PMA_BULLSHIT;
			return PMA_SAME_TYPE;
		}
		ManagedArgument const ArgumentCollection::get(int it) const
		{
			if (mSize <= it) return 0;
			return mArguments[it];
		}
		ManagedArgument ArgumentCollection::getEditable(int it) 
		{
			if (mSize <= it) return 0;
			return mArguments[it];
		}

		void ArgumentCollection::set(int it, ManagedArgument arg)
		{
			if (mSize <= it) return;
			mArguments[it] = arg;
		}

		int ArgumentCollection::getSize() const
		{
			return mSize;
		}
		using namespace System;
		String^ ArgumentCollection::toString()
		{
			String^ t = L"[";
			for (int i = 0; i < mSize - 1; i++)
			{
				std::string ts = "";
				mArguments[i]->toString(ts);
				t += gcnew String(ts.c_str());
				t += L",";

			}
			std::string ts = "";
			mArguments[mSize-1]->toString(ts);
			t += gcnew String(ts.c_str());
			t += L"]";
			return t;
		}

		void ArgumentCollection::toString(std::string& str)
		{
			str += toStringFromManaged(toString());
		}

		const Type& ArgumentCollection::getType()
		{
			const static Type type("ARGUMENT_COLLECTION");
			return type;
		}

	}
}