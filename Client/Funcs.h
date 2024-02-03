#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_INPUT_LENGTH 2
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>

void sendMessageAndRecieveResult(SOCKET& connSocket, sockaddr_in& server, char* message);

void sendMessageNoOutput(SOCKET& connSocket, sockaddr_in& server, char* message);

char * getResultNoOutput(SOCKET& connSocket);

void getClientToServerDelayEstimation(SOCKET& connSocket, sockaddr_in& server);
