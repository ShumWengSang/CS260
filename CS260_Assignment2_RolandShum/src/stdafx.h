//
// Created by roland on 11/9/19.
//

#ifndef CS260_ASSIGNMENT2_ROLANDSHUM_STDAFX_H
#define CS260_ASSIGNMENT2_ROLANDSHUM_STDAFX_H

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <winerror.h>
// Including the winsock library.
#pragma comment (lib, "Ws2_32.lib")

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#endif

#ifdef __linux__
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <errno.h>
using SOCKET = int;
const int INVALID_SOCKET = -1;
const int WSAECONNRESET = ECONNRESET;
const int WSAEWOULDBLOCK = EAGAIN;
const int SOCKET_ERROR = -1;
const int NO_ERROR = 0;

// Functions in linux as windows
#define ioctlsocket ioctl

#endif


// The rest of the files
#include <string>
#include <cstring>
#include <iostream>
#include <cstdint>
#include <memory>
#include <iostream>
#include <string_view>
#include <cstdarg>
#include <vector>
#include <chrono>
#include <thread>
#endif //CS260_ASSIGNMENT2_ROLANDSHUM_STDAFX_H
