#include "ClientFuncs.h"

#define TIME_PORT	27015

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

	while (runFlag) {
		printMenu();
		cout << "==> " << flush;
		MenuInput input = parseInput();

		string requestValue = to_string(static_cast<int>(input));

		switch (input) {
		case MenuInput::EXIT:
			runFlag = false;
			sendMessageAndRecieveResult(connSocket, server, requestValue);
			break;
		case MenuInput::GET_CLIENT_TO_SERVER_DELAY_ESTIMATION:
			getClientToServerDelayEstimation(connSocket, server);
			break;
		case MenuInput::MEASURE_RTT:
			measureRTT(connSocket, server);
			break;
		case MenuInput::GET_TIME_WITHOUT_DATE_IN_CITY:
			printCitiesMenu();
			getTimeInCity(connSocket, server);
			break;
		case MenuInput::INPUT_ERROR:
			cout << "invalid input!" << endl;
			break;
		default:
			sendMessageAndRecieveResult(connSocket, server, requestValue);
			break;
		}
	}

	// Closing connections and Winsock.
	cout << "Time Client: Closing Connection.\n";
	closesocket(connSocket);

	system("pause");
}
