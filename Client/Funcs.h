#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define MAX_INPUT_LENGTH 3
#define DEFAULT_BUFFER_SIZE 255

#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h> 
#include <string.h>
#include <time.h>
#include <sysinfoapi.h>

enum class MenuInput {
	EXIT,
	GET_TIME,
	GET_TIME_WITHOUT_DATE,
	GET_TIME_SINCE_EPOCH,
	GET_CLIENT_TO_SERVER_DELAY_ESTIMATION,
	MEASURE_RTT,
	GET_TIME_WITHOUT_DATE_OR_SECONDS,
	GET_YEAR,
	GET_MONTH_AND_DAY,
	GET_SECONDS_SINCE_BEGINNING_OF_MONTH,
	GET_WEEK_OF_YEAR,
	GET_DAYLIGHT_SAVINGS,
	GET_TIME_WITHOUT_DATE_IN_CITY,
	MEASURE_TIME_LAP,
};

void sendMessageAndRecieveResult(SOCKET& connSocket, sockaddr_in& server, char* message);

void sendMessageNoOutput(SOCKET& connSocket, sockaddr_in& server, char* message);

char * getResultNoOutput(SOCKET& connSocket);

void getClientToServerDelayEstimation(SOCKET& connSocket, sockaddr_in& server);

void measureRTT(SOCKET& connSocket, sockaddr_in& server);

MenuInput parseInput();

void printMenu();

void printCitiesMenu();

void getTimeInCity(SOCKET& connSocket, sockaddr_in& server);
