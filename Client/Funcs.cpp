#include "Funcs.h"

void sendMessage(SOCKET& connSocket, sockaddr_in& server, char * message) {
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