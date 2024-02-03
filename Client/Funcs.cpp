#include "Funcs.h"

void sendMessageAndRecieveResult(SOCKET& connSocket, sockaddr_in& server, char* message) {
	int bytesSent = 0;
	int bytesRecv = 0;
	char recvBuff[DEFAULT_BUFFER_SIZE];

	// Asks the server what's the currnet time.
	// The send function sends data on a connected socket.
	// The buffer to be sent and its size are needed.
	// The fourth argument is an idicator specifying the way in which the call is made (0 for default).
	// The two last arguments hold the details of the server to communicate with. 
	// NOTE: the last argument should always be the actual size of the client's data-structure (i.e. sizeof(sockaddr)).
	bytesSent = sendto(connSocket, message, (int)strlen(message), 0, (const sockaddr*)&server, sizeof(server));

	cout << endl;
	cout << "**************************************************************" << endl;
	if (SOCKET_ERROR == bytesSent)
	{
		cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return;
	}
	cout << "Time Client: Sent: " << bytesSent << "/" << strlen(message) << " bytes of \"" << message << "\" message.\n";

	// Gets the server's answer using simple recieve (no need to hold the server's address).
	bytesRecv = recv(connSocket, recvBuff, DEFAULT_BUFFER_SIZE, 0);
	if (SOCKET_ERROR == bytesRecv)
	{
		cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return;
	}

	recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
	cout << "Time Client: Recieved: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
	cout << "**************************************************************" << endl << endl;
}

void sendMessageNoOutput(SOCKET& connSocket, sockaddr_in& server, const char* message) {
	int bytesSent = 0;

	// Asks the server what's the currnet time.
	// The send function sends data on a connected socket.
	// The buffer to be sent and its size are needed.
	// The fourth argument is an idicator specifying the way in which the call is made (0 for default).
	// The two last arguments hold the details of the server to communicate with. 
	// NOTE: the last argument should always be the actual size of the client's data-structure (i.e. sizeof(sockaddr)).
	bytesSent = sendto(connSocket, message, (int)strlen(message), 0, (const sockaddr*)&server, sizeof(server));

	if (SOCKET_ERROR == bytesSent)
	{
		closesocket(connSocket);
		WSACleanup();
		return;
	}
}

char* getResultNoOutput(SOCKET& connSocket) {
	int bytesRecv = 0;
	char* recvBuff = new char[DEFAULT_BUFFER_SIZE];
	// Gets the server's answer using simple recieve (no need to hold the server's address).
	bytesRecv = recv(connSocket, recvBuff, DEFAULT_BUFFER_SIZE, 0);
	if (SOCKET_ERROR == bytesRecv)
	{
		closesocket(connSocket);
		WSACleanup();
		return NULL;
	}

	recvBuff[bytesRecv] = '\0'; //add the null-terminating to make it a string
	return recvBuff;
}

void getClientToServerDelayEstimation(SOCKET& connSocket, sockaddr_in& server) {

	int sumOfDifferences = 0;
	int recievedTicks = NULL;
	int prevTicks;

	for (int i = 0; i < 100; i++) {
		sendMessageNoOutput(connSocket, server, "4");
	}

	for (int i = 0; i < 100; i++) {
		if (i > 0) {
			prevTicks = recievedTicks;
		}

		char* result = getResultNoOutput(connSocket);
		recievedTicks = atoi(result);
		if (recievedTicks == NULL) {
			cout << "Time Client: Error at getResultNoOutput(): " << WSAGetLastError() << endl;
			closesocket(connSocket);
			WSACleanup();
			return;
		}

		if (i > 0) {
			sumOfDifferences += (recievedTicks - prevTicks);
		}

		delete result;
	}

	cout << "**************************************************************" << endl;
	cout << "Client to server delay estimation: " << (((float)sumOfDifferences / 99.0f) / 10000.0f) << "ms" << endl;
	cout << "**************************************************************" << endl << endl;
}

void measureRTT(SOCKET& connSocket, sockaddr_in& server) {
	int ticksBeforeSending;
	time_t ticksAfterReceiving;
	int sumOfRTTs = 0;
	char* result;

	for (int i = 0; i < 100; i++) {
		ticksBeforeSending = GetTickCount();
		sendMessageNoOutput(connSocket, server, "5");
		result = getResultNoOutput(connSocket);
		ticksAfterReceiving = GetTickCount();
		sumOfRTTs += ticksAfterReceiving - ticksBeforeSending;

		delete result;
	}
	
	cout << "**************************************************************" << endl;
	cout << "Client to server RTT Measurement: " << (((float)sumOfRTTs / 100.0f) / 10000.0f) << "ms" << endl;
	cout << "**************************************************************" << endl << endl;
}

void getTimeInCity(SOCKET& connSocket, sockaddr_in& server) {
	int input;
	cout << "==> " << flush;
	cin >> input;

	char* message = new char[DEFAULT_BUFFER_SIZE];

	sprintf(message, "%d %d", 12, input);
	sendMessageAndRecieveResult(connSocket, server, message);

	delete message;
}

ClientInput parseInput() {
	int intInput;

	cin >> intInput;

	return static_cast<ClientInput>(intInput);
}

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

void printCitiesMenu() {
	cout << "1. Doha" << endl;
	cout << "2. Prague" << endl;
	cout << "3. New York" << endl;
	cout << "4. Berlin" << endl;
	cout << "5. Not listed" << endl;
}

