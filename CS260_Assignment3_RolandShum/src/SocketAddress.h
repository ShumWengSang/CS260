#pragma once
class SocketAddress
{
public:
    SocketAddress(uint32_t inAddress, uint16_t inPort);
    SocketAddress(std::string_view ipAddress, uint16_t inPort);

    explicit SocketAddress(const sockaddr& inSockAddr);

    SocketAddress();

    bool operator==(const SocketAddress& inOther) const;

    size_t GetHash() const;

    uint32_t GetSize() const;

    std::string	ToString() const;

private:
    friend class UDPSocket;
    friend class TCPSocket;

    sockaddr mSockAddr = {};

    uint32_t& GetIP4Ref();
    uint32_t GetIP4Ref() const;

    sockaddr_in* GetAsSockAddrIn();
    const sockaddr_in* GetAsSockAddrIn()	const;

};

using SocketAddressPtr = std::shared_ptr< SocketAddress >;

