#include "stdafx.h"
#include "SocketUtil.h"
#include "SocketAddress.h"
#include "StringParser.h"

// An PIv6 theoretically can hold 64kb
constexpr int BUFFER_SIZE = 16000;

int main(int argc, char *argv[])
{
    SocketUtil::Init();
    // Store the message we are about to send.
    char buffer[BUFFER_SIZE] = {};

    // Get the name of the exe from argv
    strcpy(buffer, argv[0]);

    // Get the URL to connect to
    if(argc != 2)
    {
        printf("One arg needed!\n");
        exit(1);
    }

    std::string URL = std::string(argv[1]);

    // Parse the URL
    auto [hostname, localPath] = StringParser::ParseURL(URL);

    // We query the DNS for the ip address
    struct hostent * host_entry = gethostbyname(std::string(hostname).data());
    struct in_addr addr;
    addr.s_addr = *(u_long *) host_entry->h_addr_list[0];

    // Create the socket with the address
    SocketAddress targetAddress(inet_ntoa(addr), 80);
    TCPSocketPtr socket = SocketUtil::CreateTCPSocket(INET);

    if(socket->Connect(targetAddress) != 0)
    {
    	// Error
    	std::cout << "Error." << std::endl;
    	exit(0);
    }

    // Compose a GET command to the page.
    std::string sendMessage = StringParser::ComposeHTMLMessage("GET", std::string(hostname), std::string(localPath));
    if(socket->Send(sendMessage.data(), sendMessage.size()) == -1)
    {
    	// Error
    	std::cout << "Error." << std::endl;
    }

    // Receive and parse HTML message.
    std::string message = StringParser::ReceiveHTML(socket);

    // Print it out.
    std::cout << message << std::endl;

    // Destroy
    socket->ShutDown();
    
    SocketUtil::DeInit();
    return 1;
}
