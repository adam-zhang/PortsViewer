#pragma once

#include <string>

class Format
{
private:
	Format(void);
	~Format(void);
public:
	static std::basic_string<TCHAR> toString(DWORD);
	static std::basic_string<TCHAR> toIP(DWORD);
};

