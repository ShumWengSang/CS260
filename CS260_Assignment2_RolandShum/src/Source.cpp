#include "stdafx.h"
#include "UDPSocket.h"
#include "SocketUtil.h"
#include "SocketAddress.h"

// An PIv6 theoretically can hold 64kb
#define BUFFER_SIZE 64000

int main(int argc, char *argv[])
{
	SocketUtil::Init();
	// Store the message we are about to send.
	char buffer[BUFFER_SIZE] = {};

	// Get the name of the exe from argv
	strcpy(buffer, argv[0]);
	
	SocketAddress targetAddress("54.190.216.85", 8888);
	TCPSocketPtr socket = SocketUtil::CreateTCPSocket(INET);

	if(socket->Connect(targetAddress) != 0)
	{
		// Error
		std::cout << "Error." << std::endl;
		exit(0);
	}

	if(socket->Send(buffer, strlen(buffer)) == -1)
	{
		// Error
		std::cout << "Error." << std::endl;
	}

	int readCount = 0;
	int currentRead = 0;
	while((currentRead = socket->Receive(buffer + readCount, sizeof(buffer)) - readCount) != 0)
	{
		readCount += currentRead;
		// Empty
	}
	buffer[readCount + 1] = '\0';
	
	// Print it out.
	std::cout << buffer << std::endl;
	system("PAUSE");
	SocketUtil::DeInit();
	return 1;
}