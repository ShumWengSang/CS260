cmake_minimum_required(VERSION 3.14)
project(CS260_Assignment2_RolandShum)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(CS260_Assignment2_RolandShum
        src/SocketAddress.cpp
        src/SocketAddress.h
        src/SocketUtil.h
        src/Source.cpp
        src/UDPSocket.cpp
        src/UDPSocket.h)
