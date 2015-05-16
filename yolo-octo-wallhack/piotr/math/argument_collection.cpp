#include "argument_collection.h"

namespace Piotr
{
	namespace Math
	{
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

		ArgumentCollection ArgumentCollection::clone() const
		{
			ArgumentCollection r(mSize);
			for (int i = 0; i < mSize; i++)
				r.set(i, ManagedArgument(mArguments[i]->clone()));
			return r;
		}

		void ArgumentCollection::copyFrom(const ArgumentCollection& ac)
		{
			if (ac.getSize() != mSize) return;
			for (int i = 0; i < mSize; i++)
			{
				set(i, ManagedArgument(ac.get(i)->clone()));
			}
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

	}
}