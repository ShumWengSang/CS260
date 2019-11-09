#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include "UDPSocket.h"
#include "SocketUtil.h"
#include "SocketAddress.h"

// Including the winsock library.
#pragma comment (lib, "Ws2_32.lib")

// An PIv6 theoretically can hold 64kb
#define BUFFER_SIZE 64000

int main(int argc, char *argv[])
{
	SocketUtil::Init();
	// Store the message we are about to send.
	char buffer[BUFFER_SIZE] = {};

	// Get the name of the exe from argv
	strcpy(buffer, argv[0]);
	
	UDPSocket socket = SocketUtil::CreateUDPSocket();
	SocketAddress targetAddress("54.190.216.85", 8888);

	std::cout << "Sending string: " << buffer << std::endl;
	socket.SendTo(buffer, strlen(buffer), targetAddress);

	int readCount = socket.ReceiveFrom(buffer, sizeof(buffer), targetAddress);

	// Ending the line count.
	buffer[readCount + 1] = '0';

	// Convert the 
	
	// Print it out.
	std::cout << buffer << std::endl;
	system("PAUSE");
	SocketUtil::DeInit();
	return 1;
}