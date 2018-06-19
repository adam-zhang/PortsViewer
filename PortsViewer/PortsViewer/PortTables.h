#pragma once
#include <vector>
#include <memory>
#include <map>
#include <Windows.h>
#include "Singleton.h"


//class PortInformation;

class PortTables : public Singleton<PortTables>
{
public:
	PortTables(void) {}
	~PortTables(void) {}
public:
	void addUdpItem(const std::shared_ptr<MIB_UDPROW_OWNER_PID>& item)
	{ udpTable_.push_back(item);}
	void addTcpItem(const std::shared_ptr<MIB_TCPROW_OWNER_PID>& item)
	{ tcpTable_.push_back(item);}
	void clearUdpTable()
	{ udpTable_.clear();}
	void clearTcpTable()
	{ tcpTable_.clear();}
	std::vector<std::shared_ptr<MIB_UDPROW_OWNER_PID>>& udpTable()
	{ return udpTable_;}
	std::vector<std::shared_ptr<MIB_TCPROW_OWNER_PID>>& tcpTable()
	{ return tcpTable_;}

private:
	std::vector<std::shared_ptr<MIB_UDPROW_OWNER_PID>> udpTable_;
	std::vector<std::shared_ptr<MIB_TCPROW_OWNER_PID>> tcpTable_;
};

