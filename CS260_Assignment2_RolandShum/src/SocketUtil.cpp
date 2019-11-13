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

int SocketUtil::GetLastError(bool coutInfo)
{
    #ifdef _WIN32
	int error = WSAGetLastError();
	if(coutInfo)
		std::cout << "Error from WSA is : " << error << std::endl;
	return error;
    #else
	int error = errno;
	if (coutInfo)
		std::cout << "Err not done in linux yet xD";
    return error;
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
	u_long iMode = 1;
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

fd_set* SocketUtil::FillSetFromVector(fd_set& outSet, const std::vector< TCPSocketPtr >* inSockets, int& ioNaxNfds)
{
	if (inSockets)
	{
		FD_ZERO(&outSet);

		for (const TCPSocketPtr& socket : *inSockets)
		{
			FD_SET(socket->mSocket, &outSet);
#if !_WIN32
			ioNaxNfds = std::max(ioNaxNfds, socket->mSocket);
#endif
		}
		return &outSet;
	}
	else
	{
		return nullptr;
	}
}

void SocketUtil::FillVectorFromSet(std::vector< TCPSocketPtr >* outSockets, const std::vector< TCPSocketPtr >* inSockets, const fd_set& inSet)
{
	if (inSockets && outSockets)
	{
		outSockets->clear();
		for (const TCPSocketPtr& socket : *inSockets)
		{
			if (FD_ISSET(socket->mSocket, &inSet))
			{
				outSockets->push_back(socket);
			}
		}
	}
}

int SocketUtil::Select(const std::vector< TCPSocketPtr >* inReadSet,
	std::vector< TCPSocketPtr >* outReadSet,
	const std::vector< TCPSocketPtr >* inWriteSet,
	std::vector< TCPSocketPtr >* outWriteSet,
	const std::vector< TCPSocketPtr >* inExceptSet,
	std::vector< TCPSocketPtr >* outExceptSet)
{
	//build up some sets from our vectors
	fd_set read, write, except;

	int nfds = 0;

	fd_set* readPtr = FillSetFromVector(read, inReadSet, nfds);
	fd_set* writePtr = FillSetFromVector(write, inWriteSet, nfds);
	fd_set* exceptPtr = FillSetFromVector(except, inExceptSet, nfds);

	int toRet = select(nfds + 1, readPtr, writePtr, exceptPtr, nullptr);

	if (toRet > 0)
	{
		FillVectorFromSet(outReadSet, inReadSet, read);
		FillVectorFromSet(outWriteSet, inWriteSet, write);
		FillVectorFromSet(outExceptSet, inExceptSet, except);
	}
	return toRet;
}