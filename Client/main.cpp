#include "Funcs.h"

#define TIME_PORT	27015
#define GET_DELAY 4
#define GET_RTT 5

void printMenu() {
	cout << "1.  Get time" << endl;
	cout << "2.  Get time without date" << endl;
	cout << "3.  Get time since epoch" << endl;
	cout << "4.  Get client to server delay estimation" << endl;
	cout << "5.  Measure RTT" << endl;
	cout << "6.  Get time without date or seconds" << endl;
	cout << "7.  Get year" << endl;
	cout << "8.  Get month and day" << endl;
	cout << "9.  Get seconds since begining of month" << endl;
	cout << "10. Get week of year" << endl;
	cout << "11. Get day light savings" << endl;
	cout << "12. Get time without date in city" << endl;
	cout << "13. Measure time lap" << endl;
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
	char reqeustValue[MAX_INPUT_LENGTH];
	while (runFlag) {
		printMenu();
		cout << "==> " << flush;
		cin >> input;
		snprintf(reqeustValue, MAX_INPUT_LENGTH, "%d", input);
		if (input == 0) {
			runFlag = false;
		}

		if (input != GET_DELAY && input != GET_RTT) {
			sendMessageAndRecieveResult(connSocket, server, reqeustValue);
		}
		else if (input == GET_DELAY) {
			getClientToServerDelayEstimation(connSocket, server);
		}
		else
		{
			measureRTT(connSocket, server);
		}
	}

	// Closing connections and Winsock.
	cout << "Time Client: Closing Connection.\n";
	closesocket(connSocket);

	system("pause");
}