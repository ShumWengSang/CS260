#include "stdafx.h"
#include "UDPSocket.h"
#include "SocketUtil.h"
#include "SocketAddress.h"

// An PIv6 theoretically can hold 64kb
constexpr int BUFFER_SIZE = 16000;

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

	// Switch to non-blocking socket
    socket->SetBlocking(true);

	long totalReadCount = 0;
	long currentReadCount = 0;
	do
	{
		currentReadCount = socket->Receive(buffer + totalReadCount, sizeof(buffer) - totalReadCount);
		if(currentReadCount == (-WSAEWOULDBLOCK))
		{
			std::cout << ".";
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			continue;
		}
		totalReadCount += currentReadCount;
	} while (currentReadCount != 0);
	buffer[totalReadCount + 1] = '\0';

	// Print it out.
	std::cout << buffer << std::endl;

	// Destroy
	socket->ShutDown();
	
	SocketUtil::DeInit();
	return 1;
}