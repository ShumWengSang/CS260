#pragma once
#include "stdafx.h"

class SocketAddress;

class UDPSocket
{
public:
	UDPSocket() = default;
	~UDPSocket();

	int Bind(const SocketAddress& inToAddress);
	int SendTo(void *inData, int inLen, const SocketAddress& inTo);
	int ReceiveFrom(void *inBuffer, int inLen, SocketAddress& outFrom);

private:
	friend class SocketUtil;
	UDPSocket(SOCKET inSocket) : mSocket(inSocket){}
	SOCKET mSocket;
};
using UDPSharedPtr = std::shared_ptr<UDPSocket>;
