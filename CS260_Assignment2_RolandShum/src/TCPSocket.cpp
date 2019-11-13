//
// Created by roland on 11/9/19.
//
#include "stdafx.h"
#include "SocketUtil.h"
#include "TCPSocket.h"
#include "SocketAddress.h"

int TCPSocket::Connect(const SocketAddress &inAddress)
{
	int err = connect(mSocket, &inAddress.mSockAddr, inAddress.GetSize());
	
	if (err < 0)
	{
		SocketUtil::ReportError("TCPSocket::Connect");
		return -SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

int TCPSocket::Listen(int inBackLog)
{
    int err = listen(mSocket, inBackLog);

    if(err < 0)
    {
        SocketUtil::ReportError("TCPSocket::Listen");
        return -SocketUtil::GetLastError();
    }
    return NO_ERROR;
}

std::shared_ptr<TCPSocket> TCPSocket::Accept(SocketAddress &inFromAddress)
{
    socklen_t length = inFromAddress.GetSize();
    SOCKET newSocket = accept(mSocket, &inFromAddress.mSockAddr, &length);

    if(newSocket != INVALID_SOCKET)
    {
        return TCPSocketPtr(new TCPSocket(newSocket));
    }
    else
    {
        SocketUtil::ReportError("TCPSocket::Accept");
        return nullptr;
    }
}

int TCPSocket::Send(const void *inData, int inLen)
{
    int bytesSentCount = send(mSocket, static_cast<const char*>(inData), inLen, 0);

    if(bytesSentCount < 0)
    {
        SocketUtil::ReportError("TCPSocket::Send");
        return -SocketUtil::GetLastError();
    }
    return bytesSentCount;
}

int TCPSocket::Receive(void *inData, int inLen)
{
	int bytesReceivedCount = recv(mSocket, static_cast<char*>(inData), inLen, 0);
	if (bytesReceivedCount < 0)
	{
		int error = SocketUtil::GetLastError(false);
		if(error == WSAEWOULDBLOCK)
		{
			return -WSAEWOULDBLOCK;
		}
		
		SocketUtil::ReportError("TCPSocket::Receive, error");
		return -error;
	}
	return bytesReceivedCount;
}

void TCPSocket::ShutDown()
{
	// If we are in non-blocking, set it back to blocking.
	if (isblockingMode)
	{
        SetBlocking(false);
	}
	shutdown(mSocket, SD_SEND);

	char LeftOverBuffer[1000] = {};
	int countsReceived = this->Receive(&LeftOverBuffer, sizeof(LeftOverBuffer));
	if(countsReceived < 0)
	{
		SocketUtil::ReportError("Shutdown not graceful.");
		// Graceful exit not possible.
	}
	
}

int TCPSocket::Bind( const SocketAddress& inBindAddress )
{
    int error = bind( mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize() );
    if( error != 0 )
    {
        SocketUtil::ReportError( "TCPSocket::Bind" );
        return SocketUtil::GetLastError();
    }

    return NO_ERROR;
}

void TCPSocket::SetBlocking(bool setBlocking)
{
	// Prob win32
	isblockingMode = setBlocking;
#ifdef _WIN32
	long iResult = ioctlsocket(mSocket, FIONBIO, (u_long*)(&isblockingMode));
#elif __linux__
    long iResult = fcntl(mSocket, F_SETFL, O_NONBLOCK);
#endif
	if (iResult != NO_ERROR)
		printf("ioctlsocket failed with error: %ld\n", iResult);
}

TCPSocket::~TCPSocket()
{	
#if _WIN32
    closesocket( mSocket );
#else
    close( mSocket );
#endif
}