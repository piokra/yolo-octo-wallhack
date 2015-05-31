#ifndef PIOTR_CONVERSION_H
#define PIOTR_CONVERSION_H

#include <stdlib.h>

#include <string>
#include <string.h>
#include <iostream>
#include <sstream>

typedef unsigned int ui;



template <class T> std::string tostr( T val )
{
	std::ostringstream ss;
	ss << val;
	return ss.str();
}
inline int strtoint( const char* str )
{
	std::cout << "hello\n";
	int len = strlen( str );
	ui t = 1;
	int res = 0;
	for( int i = len - 1; i != -1; i-- )
	{
		res += ( str[i] - 48 ) * t;
		t *= 10;
	}

	return res;
}

inline int strtoint( std::string& str )
{
	return strtoint( str.c_str() );
}




#endif // CONVERSION_H

