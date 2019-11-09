#pragma once
#include <WinSock2.h>
#include <string>
#include <iostream>
#include "UDPSocket.h"

class SocketUtil
{
public:
	static void Init();

	static void DeInit();


	static void ReportError(std::string str);

	static int GetLastError();

	static UDPSocket CreateUDPSocket();


private:
	static SOCKET CreateSocket(int af, int type);
};

inline void SocketUtil::Init()
{
	WSADATA wsaData;
	//Initialize winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult)
	{
		std::cout << "Winsock intialisation failure" << std::endl;
		WSACleanup();
		return;
	}
}

inline void SocketUtil::DeInit()
{
	WSACleanup();
}

inline void SocketUtil::ReportError(std::string str)
{
	std::cout << "Socket Error :" << str << std::endl;
}

inline int SocketUtil::GetLastError()
{
	int error = WSAGetLastError();
	std::cout << "Error from WSA is : " << error << std::endl;
	return error;
}

inline UDPSocket SocketUtil::CreateUDPSocket()
{
	return UDPSocket(CreateSocket(AF_INET, SOCK_DGRAM));
}

inline SOCKET SocketUtil::CreateSocket(int af, int type)
{
	return socket(af, type, 0);
}
