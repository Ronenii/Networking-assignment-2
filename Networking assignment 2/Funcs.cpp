#include "Funcs.h"

char* getTime() {
	// Get the current time.
	time_t timer;
	time(&timer);
	char* ret = new char[255];
	strcpy(ret, ctime(&timer));

	// Remove the new-line from the created string.
	ret[strlen(ret) - 1] = '\0';

	return ret;
}

char* getTimeWithoutDate() {
	time_t timer;
	time(&timer);

	const size_t bufferSize = 9; // HH:MM:SS\0
	char* ret = new char[bufferSize];

	strftime(ret, bufferSize, "%H:%M:%S", localtime(&timer));

	return ret;
}

char* getTimeSinceEpoch() {
    time_t timer;
    time(&timer);

	char* ret = new char[255];

	itoa(timer, ret, 10);

    return ret;
}

ClientInput parseInput(char* input) {
	int intInput = atoi(input);

	return static_cast<ClientInput>(intInput);
}
