#pragma once
#include "stdafx.h"
#include "UDPSocket.h"
#include "TCPSocket.h"


enum SocketAddressFamily
{
    INET = AF_INET,
    INET6 = AF_INET6
};

class SocketUtil
{
public:
	static void Init();

	static void DeInit();


	static void ReportError(std::string str);

	static int GetLastError(bool coutInfo = true);

    static TCPSocketPtr CreateTCPSocket(SocketAddressFamily inFamily );
	static fd_set* FillSetFromVector(fd_set& outSet, const std::vector<TCPSocketPtr>* inSockets, int& ioNaxNfds);
	static int Select(const std::vector<TCPSocketPtr>* inReadSet, std::vector<TCPSocketPtr>* outReadSet,
	           const std::vector<TCPSocketPtr>* inWriteSet, std::vector<TCPSocketPtr>* outWriteSet,
	           const std::vector<TCPSocketPtr>* inExceptSet, std::vector<TCPSocketPtr>* outExceptSet);
	static void FillVectorFromSet(std::vector< TCPSocketPtr >* outSockets, const std::vector< TCPSocketPtr >* inSockets, const fd_set& inSet);
	
private:
	static SOCKET CreateSocket(int protocol);
};

