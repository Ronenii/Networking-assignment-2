#include "Funcs.h"

void sendMessageAndRecieveResult(SOCKET& connSocket, sockaddr_in& server, char* message) {
	int bytesSent = 0;
	int bytesRecv = 0;
	char recvBuff[255];

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
	bytesRecv = recv(connSocket, recvBuff, 255, 0);
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
	char* recvBuff = new char[255];

	// Gets the server's answer using simple recieve (no need to hold the server's address).
	bytesRecv = recv(connSocket, recvBuff, 255, 0);
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

		recievedTicks = atoi(getResultNoOutput(connSocket));
		if (recievedTicks == NULL) {
			cout << "Time Client: Error at getResultNoOutput(): " << WSAGetLastError() << endl;
			closesocket(connSocket);
			WSACleanup();
			return;
		}

		if (i > 0) {
			sumOfDifferences += (recievedTicks - prevTicks);
		}
	}

	cout << "**************************************************************" << endl;
	cout << "Client to server delay estimation: " << ((float)(sumOfDifferences / 99) / 10000.0f) << "ms" << endl;
	cout << "**************************************************************" << endl << endl;
}