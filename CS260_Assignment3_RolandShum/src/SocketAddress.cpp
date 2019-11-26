#include "stdafx.h"
#include "SocketAddress.h"
#include "Utility.h"

size_t SocketAddress::GetHash() const
{
    return ( GetIP4Ref() ) |
           ( ( static_cast< uint32_t >( GetAsSockAddrIn()->sin_port ) ) << 13 ) |
           mSockAddr.sa_family;
}

bool SocketAddress::operator==(const SocketAddress &inOther) const
{
    return ( mSockAddr.sa_family == AF_INET &&
             GetAsSockAddrIn()->sin_port == inOther.GetAsSockAddrIn()->sin_port ) &&
           ( GetIP4Ref() == inOther.GetIP4Ref() );
}

SocketAddress::SocketAddress()
{
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetIP4Ref() = INADDR_ANY;
    GetAsSockAddrIn()->sin_port = 0;
}


uint32_t SocketAddress::GetSize() const
{
    return sizeof( sockaddr );
}

uint32_t SocketAddress::GetIP4Ref() const {
    #if _WIN32
    return *reinterpret_cast< const uint32_t* >( &GetAsSockAddrIn()->sin_addr.S_un.S_addr );
    #else
    return GetAsSockAddrIn()->sin_addr.s_addr;
    #endif
}

uint32_t &SocketAddress::GetIP4Ref()
{
    #if _WIN32
    return *reinterpret_cast< uint32_t* >( &GetAsSockAddrIn()->sin_addr.S_un.S_addr );
    #else
    return GetAsSockAddrIn()->sin_addr.s_addr;
    #endif
}

sockaddr_in *SocketAddress::GetAsSockAddrIn()
{
    return reinterpret_cast< sockaddr_in* >( &mSockAddr );
}

const sockaddr_in *SocketAddress::GetAsSockAddrIn() const
{
    return reinterpret_cast< const sockaddr_in* >( &mSockAddr );
}

SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inPort)
{
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetIP4Ref() = htonl( inAddress );
    GetAsSockAddrIn()->sin_port = htons( inPort );
}

SocketAddress::SocketAddress(std::string_view ipAddress, uint16_t inPort)
{
    inet_pton(AF_INET, ipAddress.data(), &(GetAsSockAddrIn()->sin_addr));
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetAsSockAddrIn()->sin_port = htons(inPort);
}

SocketAddress::SocketAddress(const sockaddr &inSockAddr) {
    memcpy( &mSockAddr, &inSockAddr, sizeof( sockaddr ) );
}

std::string SocketAddress::ToString() const
{
    const sockaddr_in* s = GetAsSockAddrIn();
    char destinationBuffer[ 128 ];
    #ifdef _WIN32
    InetNtop( s->sin_family, const_cast< in_addr* >( &s->sin_addr ), destinationBuffer, sizeof( destinationBuffer ) );
//    return Utility::Sprintf( "%s:%d",
//                                 destinationBuffer,
//                                 ntohs( s->sin_port ) );
    #elif __linux__
    inet_ntop( s->sin_family, const_cast< in_addr* >( &s->sin_addr ), destinationBuffer, sizeof( destinationBuffer ) );
    #endif
    return Utility::Sprintf( "%s:%d", destinationBuffer, ntohs( s->sin_port ) );
}
