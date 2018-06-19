#pragma once
#include <string>

//class PortInformation
//{
//public:
//	PortInformation(void);
//	~PortInformation(void);
//private:
//	DWORD pid_;
//	DWORD portNumber_;
//	std::basic_string<TCHAR> fullName_;
//	std::string ip_;
//public:
//	void setPID(DWORD pid)
//	{ pid_ = pid;}
//	const DWORD pid()const
//	{ return pid_;}
//	void setPortNumber(const DWORD number)
//	{ portNumber_ = number;}
//	DWORD portNumber()const
//	{  return portNumber_;}
//	void setFullName(const std::basic_string<TCHAR>& value)
//	{ fullName_ = value;}
//	const std::basic_string<TCHAR>& fullName()const
//	{ return fullName_;}
//	void setIP(const std::string& ip)
//	{ ip_ = ip;}
//	const std::string& ip()const
//	{ return ip_;}
//};

class UdpPortInfo : public MIB_UDPROW_OWNER_PID
{
};

class TcpPortInfo : public MIB_TCPROW_OWNER_PID
{
};

std::basic_string<TCHAR> queryTcpState(DWORD);