#include "SocketAddress.h"
#include <WS2tcpip.h>


SocketAddress::SocketAddress(std::string ipAddress, uint16_t inPort)
{
	inet_pton(AF_INET, ipAddress.c_str(), &(GetAsSockAddrIn()->sin_addr));
	GetAsSockAddrIn()->sin_family = AF_INET;
	GetAsSockAddrIn()->sin_port = htons(inPort);
}

SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inPort)
{
	GetAsSockAddrIn()->sin_family = AF_INET;
	GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
	GetAsSockAddrIn()->sin_port = htons(inPort);
}

SocketAddress::SocketAddress(SocketAddress const& other)
{
	memcpy(&mSockaddr, &other, sizeof(sockaddr));
}

sockaddr SocketAddress::GetSocket() const
{
	return mSockaddr;
}
