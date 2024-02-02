#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>

void sendMessage(SOCKET& connSocket, sockaddr_in& server, char* message);
