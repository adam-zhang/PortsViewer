#include "StdAfx.h"
#include "ProcessHelper.h"
#include <vector>
#include <Psapi.h>
using namespace std;

ProcessHelper::ProcessHelper(void)
{
}


ProcessHelper::~ProcessHelper(void)
{
}


basic_string<TCHAR> ProcessHelper::processName(DWORD pid)
{
	auto handle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
	if (handle == 0)
		return basic_string<TCHAR>();
	vector<TCHAR> buffer(MAX_PATH);
	auto ret = GetProcessImageFileName(handle, &buffer[0], MAX_PATH);
	return basic_string<TCHAR>(buffer.begin(), buffer.begin() + ret);
}
