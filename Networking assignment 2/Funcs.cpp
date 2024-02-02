#include "Funcs.h"

char* getTime() {

	char ret[255];
	// Get the current time.
	time_t timer;
	time(&timer);
	// Parse the current time to printable string.
	strcpy(ret, ctime(&timer));
	ret[strlen(ret) - 1] = '\0'; //to remove the new-line from the created string

	return ret;
}

ClientInput parseInput(char* input) {
	int intInput = atoi(input);
	
	return static_cast<ClientInput>(intInput);
}
