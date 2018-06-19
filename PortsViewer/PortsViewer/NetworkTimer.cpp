#include "StdAfx.h"
#include "NetworkTimer.h"
#include "PortTables.h"
#include "PortInformation.h"
#include "CallbackWindows.h"
#include "Messages.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <IPHlpApi.h>
#include <Psapi.h>

using namespace std;

NetworkTimer::NetworkTimer(void)
	: timer_(0)
{
}


NetworkTimer::~NetworkTimer(void)
{
}

vector<shared_ptr<MIB_UDPROW_OWNER_PID>> getUdpTable()
{
	DWORD size = 0;
	auto ret = GetExtendedUdpTable(0, &size, TRUE, AF_INET, UDP_TABLE_OWNER_PID, 0);
	assert(ret == ERROR_INSUFFICIENT_BUFFER);
	vector<char> buffer(size);
	auto p = reinterpret_cast<MIB_UDPTABLE_OWNER_PID*>(&buffer[0]);
	ret = GetExtendedUdpTable(p, &size, TRUE, AF_INET, UDP_TABLE_OWNER_PID, 0);
	assert(ret == NO_ERROR);
	vector<shared_ptr<MIB_UDPROW_OWNER_PID>> v;
	for(DWORD i = 0; i < p->dwNumEntries; ++i)
		v.push_back(make_shared<MIB_UDPROW_OWNER_PID>(p->table[i]));
	return v;
}

static string ipToString(DWORD ip)
{
	auto chars = (char*)&ip;
	stringstream ss;
	ss << chars[0] << "." << chars[1] << "." << chars[2] << "." << chars[3];
	return ss.str();
}


static void fillUdpTable()
{
	auto v = getUdpTable();
	PortTables::instance().clearUdpTable();
	for_each(v.begin(), v.end(), [](const shared_ptr<MIB_UDPROW_OWNER_PID>& p)
	{
		PortTables::instance().addUdpItem(p);
	});

}

vector<shared_ptr<MIB_TCPROW_OWNER_PID>> getTcpTable()
{
	DWORD size = 0;
	auto ret = GetExtendedTcpTable(0, &size, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
	assert(ret == ERROR_INSUFFICIENT_BUFFER);
	vector<char*> buffer(size);
	auto p = reinterpret_cast<MIB_TCPTABLE_OWNER_PID*>(&buffer[0]);
	ret = GetExtendedTcpTable(p, &size, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
	assert(ret == NO_ERROR);
	vector<shared_ptr<MIB_TCPROW_OWNER_PID>> v;
	for(DWORD i = 0; i < p->dwNumEntries; ++i)
		v.push_back(make_shared<MIB_TCPROW_OWNER_PID>(p->table[i]));
	return v;
}

void fillTcpTable()
{
	auto v = getTcpTable();
	PortTables::instance().clearTcpTable();
	for_each(v.begin(), v.end(), [](const shared_ptr<MIB_TCPROW_OWNER_PID>& p)
	{
		PortTables::instance().addTcpItem(p);
	});
}


void CALLBACK timerProc(HWND, UINT, UINT_PTR, DWORD)
{
	fillUdpTable();
	fillTcpTable();
	PostMessage(CallbackWindows::instance().mainWindow()->m_hWnd, WM_USER_UPDATE, 0, 0);
}


void NetworkTimer::run()
{
	const DWORD interval = 1000;
	auto t = SetTimer(NULL, NULL, interval, timerProc);
	assert(t);
	timer_ = t;
}
