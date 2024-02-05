#include "ClientFuncs.h"

void sendMessageAndRecieveResult(SOCKET& connSocket, sockaddr_in& server, const string& message) {
	int bytesSent = 0;
	int bytesRecv = 0;
	char recvBuff[DEFAULT_BUFFER_SIZE];

	bytesSent = sendto(connSocket, message.c_str(), static_cast<int>(message.length()), 0, reinterpret_cast<const sockaddr*>(&server), sizeof(server));
	cout << "**************************************************************" << endl;

	if (SOCKET_ERROR == bytesSent) {
		cout << "Time Client: Error at sendto(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return;
	}

	cout << "Time Client: Sent: " << bytesSent << "/" << message.length() << " bytes of \"" << message << "\" message.\n";

	bytesRecv = recv(connSocket, recvBuff, DEFAULT_BUFFER_SIZE, 0);
	if (SOCKET_ERROR == bytesRecv) {
		cout << "Time Client: Error at recv(): " << WSAGetLastError() << endl;
		closesocket(connSocket);
		WSACleanup();
		return;
	}

	recvBuff[bytesRecv] = '\0'; // add the null-terminating to make it a string
	cout << "Time Client: Received: " << bytesRecv << " bytes of \"" << recvBuff << "\" message.\n";
	cout << "**************************************************************" << endl << endl;
}

void sendMessageNoOutput(SOCKET& connSocket, sockaddr_in& server, const string& message) {
	int bytesSent = 0;

	bytesSent = sendto(connSocket, message.c_str(), static_cast<int>(message.length()), 0, reinterpret_cast<const sockaddr*>(&server), sizeof(server));

	if (SOCKET_ERROR == bytesSent) {
		closesocket(connSocket);
		WSACleanup();
		return;
	}
}

string getResultNoOutput(SOCKET& connSocket) {
	int bytesRecv = 0;
	char recvBuff[DEFAULT_BUFFER_SIZE];
	// Gets the server's answer using simple receive (no need to hold the server's address).
	bytesRecv = recv(connSocket, recvBuff, DEFAULT_BUFFER_SIZE, 0);
	if (SOCKET_ERROR == bytesRecv) {
		closesocket(connSocket);
		WSACleanup();
		return "";
	}

	recvBuff[bytesRecv] = '\0'; // add the null-terminating to make it a string
	return string(recvBuff);
}

void getClientToServerDelayEstimation(SOCKET& connSocket, sockaddr_in& server) {
	int sumOfDifferences = 0;
	int receivedTicks = 0;
	int prevTicks = 0;

	for (int i = 0; i < 100; i++) {
		sendMessageNoOutput(connSocket, server, "4");
	}

	for (int i = 0; i < 100; i++) {
		if (i > 0) {
			prevTicks = receivedTicks;
		}

		string result = getResultNoOutput(connSocket);
		receivedTicks = stoi(result);
		if (receivedTicks == 0) {
			cout << "Time Client: Error at getResultNoOutput(): " << WSAGetLastError() << endl;
			closesocket(connSocket);
			WSACleanup();
			return;
		}

		if (i > 0) {
			sumOfDifferences += (receivedTicks - prevTicks);
		}
	}

	cout << "**************************************************************" << endl;
	cout << "Client to server delay estimation: " << (((float)sumOfDifferences / 99.0f) / 10000.0f) << "ms" << endl;
	cout << "**************************************************************" << endl << endl;
}

void measureRTT(SOCKET& connSocket, sockaddr_in& server) {
	int ticksBeforeSending;
	int ticksAfterReceiving;
	int sumOfRTTs = 0;
	string result;

	for (int i = 0; i < 100; i++) {
		ticksBeforeSending = GetTickCount();
		sendMessageNoOutput(connSocket, server, "5");
		result = getResultNoOutput(connSocket);
		ticksAfterReceiving = GetTickCount();
		sumOfRTTs += ticksAfterReceiving - ticksBeforeSending;
	}

	cout << "**************************************************************" << endl;
	cout << "Client to server RTT Measurement: " << (((float)sumOfRTTs / 100.0f) / 10000.0f) << "ms" << endl;
	cout << "**************************************************************" << endl << endl;
}

void getTimeInCity(SOCKET& connSocket, sockaddr_in& server) {
	int input;
	cout << "==> " << flush;
	cin >> input;
	cout << endl;

	string message = to_string(12) + " " + to_string(input);
	sendMessageAndRecieveResult(connSocket, server, message);
}

MenuInput parseInput() {
	int intInput;
	cin >> intInput;
	cout << endl;

	if (intInput < static_cast<int>(MenuInput::INPUT_ERROR))
		return static_cast<MenuInput>(intInput);
	else
		return MenuInput::INPUT_ERROR;
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
	cout << "0. Other" << endl;
}

