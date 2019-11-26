//
// Created by roland on 11/9/19.
//

#ifndef CS260_ASSIGNMENT2_ROLANDSHUM_TCPSOCKET_H
#define CS260_ASSIGNMENT2_ROLANDSHUM_TCPSOCKET_H

class SocketAddress;


class TCPSocket
{
public:
    ~TCPSocket();
    int Connect(const SocketAddress& inAddress);
    int Bind(const SocketAddress& inToAddress);
    int Listen(int inBackLog = 32);
    std::shared_ptr<TCPSocket> Accept(SocketAddress& inFromAddress);
    int Send(const void* inData, int inLen);
    int Receive(void* inBuffer, int inLen);

    void ShutDown();
    
    void SetBlocking(bool setBlocking);
private:
    friend class SocketUtil;
    explicit TCPSocket(SOCKET inSocket) : mSocket(inSocket){}
    SOCKET mSocket;
    bool isblockingMode = 0;
};
typedef std::shared_ptr<TCPSocket> TCPSocketPtr;


#endif //CS260_ASSIGNMENT2_ROLANDSHUM_TCPSOCKET_H
