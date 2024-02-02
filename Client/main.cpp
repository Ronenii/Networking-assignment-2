#include "Funcs.h"

#define TIME_PORT	27015
enum class MenuOption {
	GET_TIME = 1,
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
	EXIT

};

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

MenuOption getInput() {
	int input;
	cin >> input;

	return static_cast<MenuOption>(input);
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


	MenuOption input;
	while (runFlag) {
		printMenu();
		input = getInput();

		switch (input) {
		case MenuOption::GET_TIME:
			sendWhatTime(connSocket, server);
			break;
		case MenuOption::GET_TIME_WITHOUT_DATE:
			break;
		case MenuOption::GET_TIME_SINCE_EPOCH:
			break;
		case MenuOption::GET_CLIENT_TO_SERVER_DELAY_ESTIMATION:
			break;
		case MenuOption::MEASURE_RTT:
			break;
		case MenuOption::GET_TIME_WITHOUT_DATE_OR_SECONDS:
			break;
		case MenuOption::GET_YEAR:
			break;
		case MenuOption::GET_MONTH_AND_DAY:
			break;
		case MenuOption::GET_SECONDS_SINCE_BEGINNING_OF_MONTH:
			break;
		case MenuOption::GET_WEEK_OF_YEAR:
			break;
		case MenuOption::GET_DAYLIGHT_SAVINGS:
			break;
		case MenuOption::GET_TIME_WITHOUT_DATE_IN_CITY:
			break;
		case MenuOption::MEASURE_TIME_LAP:
			break;
		case MenuOption::EXIT:
			runFlag = false;
			break;
		}
	}

	// Closing connections and Winsock.
	cout << "Time Client: Closing Connection.\n";
	closesocket(connSocket);

	system("pause");
}