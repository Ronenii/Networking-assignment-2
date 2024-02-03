#include "Funcs.h"

char* getTime() {
	// Get the current time.
	time_t timer;
	time(&timer);
	char* ret = new char[DEFAULT_BUFFER_SIZE];
	strcpy(ret, ctime(&timer));

	// Remove the new-line from the created string.
	ret[strlen(ret) - 1] = '\0';

	return ret;
}

char* getTimeWithoutDate() {
	time_t timer;
	time(&timer);

	char* ret = new char[DEFAULT_BUFFER_SIZE];

	strftime(ret, DEFAULT_BUFFER_SIZE, "%H:%M:%S", localtime(&timer));

	return ret;
}

char* getTimeWithoutDateOrSeconds() {
	time_t timer;
	time(&timer);

	char* ret = new char[DEFAULT_BUFFER_SIZE];

	strftime(ret, DEFAULT_BUFFER_SIZE, "%H:%M", localtime(&timer));

	return ret;
}

char* getYear() {
	time_t timer;
	time(&timer);

	char* ret = new char[DEFAULT_BUFFER_SIZE];
	int year = localtime(&timer)->tm_year;
	itoa(year + 1900, ret, BASE_10);

	return ret;
}

char* getTimeSinceEpoch() {
    time_t timer;
    time(&timer);

	char* ret = new char[DEFAULT_BUFFER_SIZE];

	itoa(timer, ret, BASE_10);

    return ret;
}

char* getMonthAndDay() {
	time_t timer;
	time(&timer);

	char* ret = new char[DEFAULT_BUFFER_SIZE];
	int day = localtime(&timer)->tm_mday;
	int month = localtime(&timer)->tm_mon + 1;
	
	sprintf(ret, "%d/%d", day, month);

	return ret;
}

char* getCurrentTicks() {
	char* ret = new char[DEFAULT_BUFFER_SIZE];
	itoa(GetTickCount(), ret, BASE_10);
	return ret;
}

char* getSecondsSinceBeginningOfTheMonth() {
	char* ret = new char[DEFAULT_BUFFER_SIZE];
	
	time_t now;
	time(&now);

	struct tm beg_month;
	beg_month = *localtime(&now);
	beg_month.tm_hour = 0;
	beg_month.tm_min = 0;
	beg_month.tm_sec = 0;
	beg_month.tm_mday = 1;

	double seconds = difftime(now, mktime(&beg_month));

	itoa((int)seconds, ret, BASE_10);
	return ret;
}

char* getWeekOfYear() {
	time_t timer;
	time(&timer);

	char* ret = new char[DEFAULT_BUFFER_SIZE];

	strftime(ret, DEFAULT_BUFFER_SIZE, "%U", localtime(&timer));

	return ret;
}

ClientInput parseInput(char* input) {
	int intInput = atoi(input);

	return static_cast<ClientInput>(intInput);
}

char* emptyString() {
	char* ret = new char[1];
	ret[0] = '\0';
	return ret;
}

char* invalidInputString() {
	char* ret = new char[DEFAULT_BUFFER_SIZE];
	strcpy(ret, "Invalid input");
	return ret;
}
