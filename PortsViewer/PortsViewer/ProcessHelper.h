#pragma once
#include <string>

class ProcessHelper
{
public:
	ProcessHelper(void);
	~ProcessHelper(void);
public:
	static std::basic_string<TCHAR> processName(DWORD);
};

