//
// Created by roland on 11/9/19.
//
#include "stdafx.h"
#include "UDPSocket.h"
#include "SocketUtil.h"


void SocketUtil::Init()
{
    #ifdef _WIN32
	WSADATA wsaData;
	//Initialize winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult)
	{
		std::cout << "Winsock intialisation failure" << std::endl;
		WSACleanup();
		return;
	}
    #else
    return;
    #endif
}

void SocketUtil::DeInit()
{
    #ifdef _WIN32
	WSACleanup();
    #else
	return;
    #endif
}

void SocketUtil::ReportError(std::string str)
{
	std::cout << "Socket Error :" << str << std::endl;
}

int SocketUtil::GetLastError()
{
    #ifdef _WIN32
	int error = WSAGetLastError();
	std::cout << "Error from WSA is : " << error << std::endl;
	return error;
    #else
    std::cout << "Err not done in linux yet xD";
    return 0;
    #endif
}

SOCKET SocketUtil::CreateSocket(int protocol)
{
    SOCKET result = INVALID_SOCKET;

    int type = SOCK_DGRAM;
    if(protocol == IPPROTO_TCP)
        type = SOCK_STREAM;
	return socket(AF_INET, type, protocol);
}

TCPSocketPtr SocketUtil::CreateTCPSocket(SocketAddressFamily inFamily )
{
    SOCKET s = socket( inFamily, SOCK_STREAM, IPPROTO_TCP );

    if( s != INVALID_SOCKET )
    {
        return TCPSocketPtr( new TCPSocket( s ) );
    }
    else
    {
        ReportError( "SocketUtil::CreateTCPSocket" );
        return nullptr;
    }
}
