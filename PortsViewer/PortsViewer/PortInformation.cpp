#include "StdAfx.h"
#include "PortInformation.h"
#include <map>

using namespace std;

//PortInformation::PortInformation(void)
//{
//}


//PortInformation::~PortInformation(void)
//{
//}

static map<DWORD, basic_string<TCHAR>> getStatesMap()
{
	static map<DWORD, basic_string<TCHAR>> m;
	if (m.empty())
	{
		m.insert(make_pair(MIB_TCP_STATE_CLOSED, TEXT("Closed")));
		m.insert(make_pair(MIB_TCP_STATE_LISTEN, TEXT("Listen")));
		m.insert(make_pair(MIB_TCP_STATE_SYN_SENT, TEXT("Sent")));
		m.insert(make_pair(MIB_TCP_STATE_SYN_RCVD, TEXT("Received")));
		m.insert(make_pair(MIB_TCP_STATE_ESTAB, TEXT("Established")));
		m.insert(make_pair(MIB_TCP_STATE_FIN_WAIT1, TEXT("Finishing Wait1")));
		m.insert(make_pair(MIB_TCP_STATE_FIN_WAIT2, TEXT("Finishing Wait2")));
		m.insert(make_pair(MIB_TCP_STATE_CLOSE_WAIT, TEXT("Closing Wait")));
		m.insert(make_pair(MIB_TCP_STATE_CLOSING,	TEXT("Closing")));
		m.insert(make_pair(MIB_TCP_STATE_LAST_ACK,	TEXT("Last ACK")));
		m.insert(make_pair(MIB_TCP_STATE_TIME_WAIT, TEXT("Time Wait")));
		m.insert(make_pair(MIB_TCP_STATE_DELETE_TCB,TEXT( "Delete TCB")));
	}
	return m;
}

std::basic_string<TCHAR> queryTcpState(DWORD state)
{
	auto m = getStatesMap();
	return m[state];
}
