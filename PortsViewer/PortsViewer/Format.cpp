#include "StdAfx.h"
#include "Format.h"
#include <sstream>
#include <iterator>

using namespace std;

Format::Format(void)
{
}


Format::~Format(void)
{
}

basic_string<TCHAR> Format::toString(DWORD value)
{
	basic_stringstream<TCHAR> ss;
	ss << value;
	return ss.str();
}

basic_string<TCHAR> Format::toIP(DWORD value)
{
	in_addr address;
	address.S_un.S_addr = value;
	char* s = inet_ntoa(address);
	basic_string<TCHAR> ss;
	copy(s, s + strlen(s), back_inserter(ss));
	return ss;
}