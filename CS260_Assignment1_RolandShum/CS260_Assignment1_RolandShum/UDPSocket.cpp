#include "UDPSocket.h"
#include "SocketAddress.h"
#include "SocketUtil.h"

UDPSocket::~UDPSocket()
{
	closesocket(mSocket);
}

int UDPSocket::Bind(const SocketAddress& inToAddress)
{
	int err = bind(mSocket, &inToAddress.mSockaddr, inToAddress.GetSize());
	if(err != 0)
	{
		SocketUtil::ReportError("UDPSOCKET::Bind");
		return SocketUtil::GetLastError();
	}
	return NO_ERROR;
}

int UDPSocket::SendTo(void * inData, int inLen, const SocketAddress & inTo)
{
	int byteCountSent = sendto(mSocket, static_cast<const char *> (inData), inLen, 0,
		&inTo.mSockaddr, inTo.GetSize());

	if(byteCountSent > 0)
	{
		return byteCountSent;
	}
	else
	{
		SocketUtil::ReportError("UDPSocket::SendTo");
		return SocketUtil::GetLastError();
	}
	return 0;
}

int UDPSocket::ReceiveFrom(void * inBuffer, int inLen, SocketAddress & outFromAddress)
{
	int fromLength = outFromAddress.GetSize();
	int readByCount = recvfrom(mSocket, static_cast<char*>(inBuffer), inLen, 0,
		&outFromAddress.mSockaddr, &fromLength);
	if(readByCount >= 0)
	{
		return readByCount;
	}
	else
	{
		SocketUtil::ReportError("UDPSocket::ReceiveFrom");
		return SocketUtil::GetLastError();
	}
}

