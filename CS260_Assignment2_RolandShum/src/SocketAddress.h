#pragma once
#include <cstdint>
#include <WinSock2.h>
#include <memory>
#include <string>

class SocketAddress
{
public:
	SocketAddress(std::string ipAddress, uint16_t inPort);

	SocketAddress(uint32_t inAddress, uint16_t inPort);


	SocketAddress(SocketAddress const& other);

	size_t GetSize() const;

	~SocketAddress() = default;

	sockaddr GetSocket() const;

private:
	sockaddr mSockaddr;
	sockaddr_in* GetAsSockAddrIn();
	friend class UDPSocket;
};

inline sockaddr_in* SocketAddress::GetAsSockAddrIn()
{
	return reinterpret_cast<sockaddr_in*>(&mSockaddr);
}

inline size_t SocketAddress::GetSize() const
{
	return sizeof(sockaddr);
}

using SocketAddressPtr = std::shared_ptr<SocketAddress>;
