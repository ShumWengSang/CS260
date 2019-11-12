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

	static int GetLastError();

    static TCPSocketPtr CreateTCPSocket(SocketAddressFamily inFamily );

private:
	static SOCKET CreateSocket(int protocol);
};

