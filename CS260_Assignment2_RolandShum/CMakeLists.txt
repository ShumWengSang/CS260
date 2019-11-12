cmake_minimum_required(VERSION 3.14)
project(CS260_Assignment2_RolandShum)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(CS260_Assignment2_RolandShum
        src/SocketAddress.cpp
        src/SocketAddress.h
        src/SocketUtil.h
        src/Source.cpp
        src/stdafx.h
        src/SocketUtil.cpp src/TCPSocket.cpp src/TCPSocket.h src/Utility.cpp src/Utility.h)
