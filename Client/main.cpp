#include "Funcs.h"

#define TIME_PORT	27015

void printMenu() {
	cout << "1.  Get Time" << endl;
	cout << "2.  Get Time Without Date" << endl;
	cout << "3.  Get Time Since Epoch" << endl;
	cout << "4.  Get Client To Server Delay Estimation" << endl;
	cout << "5.  MeasureRTT" << endl;
	cout << "6.  Get Time Without Date Or Seconds" << endl;
	cout << "7.  Get Year" << endl;
	cout << "8.  Get Month And Day" << endl;
	cout << "9.  Get Seconds Since Begining Of Month" << endl;
	cout << "10. Get Week Of Year" << endl;
	cout << "11. GetDaylightSavings" << endl;
	cout << "12. GetTimeWithoutDateInCity" << endl;
	cout << "13. MeasureTimeLap" << endl;
	cout << "0.  Exit " << endl;
}

void main()
{
	bool runFlag = true;

	// Initialize Winsock (Windows Sockets).
	WSAData wsaData;
	if (NO_ERROR != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Time Client: Error at WSAStartup()\n";
		return;
	}

	// Client side:
	// Create a socket and connect to an internet address.

	SOCKET connSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == connSocket)
	{
		cout << "Time Client: Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// For a client to communicate on a network, it must connect to a server.

	// Need to assemble the required data for connection in sockaddr structure.

	// Create a sockaddr_in object called server. 
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(TIME_PORT);

	int input;
	char reqeustValue[2];
	while (runFlag) {
		printMenu();
		cin >> input;
		itoa(input, reqeustValue, 10);
		if (input == 0) {
			break;
		}

		sendMessage(connSocket, server, reqeustValue);
	}

	// Closing connections and Winsock.
	cout << "Time Client: Closing Connection.\n";
	closesocket(connSocket);

	system("pause");
}