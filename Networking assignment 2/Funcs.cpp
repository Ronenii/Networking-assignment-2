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

	strftime(ret, strlen(ret), "%H:%M:%S", localtime(&timer));

	return ret;
}

char* getTimeWithoutDateOrSeconds() {
	time_t timer;
	time(&timer);

	char* ret = new char[DEFAULT_BUFFER_SIZE];

	strftime(ret, strlen(ret), "%H:%M", localtime(&timer));

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

	strftime(ret, strlen(ret), "%U", localtime(&timer));

	return ret;
}

char* getDaylightSavings() {
	time_t timer;
	time(&timer);
	struct tm* tm_info = localtime(&timer);

	char* ret = new char[DEFAULT_BUFFER_SIZE];

	if (tm_info->tm_isdst > 0) {
		strcpy(ret, "Daylight Saving Time is in effect.\n");
	}
	else if (tm_info->tm_isdst == 0) {
		strcpy(ret, "Daylight Saving Time is not in effect.\n");
	}
	else {
		strcpy(ret, "Daylight Saving Time information is not available.\n");
	}

	return ret;
}

void setTimeZone(const char* timeZone) {
	// Set the time zone using _putenv_s
	_putenv_s("TZ", timeZone);
	_tzset();
}

char* getTimeInCity(CityInput city) {
	time_t utcTime;
	time(&utcTime);

	const int secondsInHour = 3600;
	int hourOffset = 0;

	switch (city) {
	case CityInput::DOHA:
		hourOffset = 3;
		break;
	case CityInput::PRAGUE:
		hourOffset = 1;
		break;
	case CityInput::NEW_YORK:
		hourOffset = -5;
		break;
	case CityInput::BERLIN:
		hourOffset = 1;
		break;
	}

	utcTime += hourOffset * secondsInHour;
	struct tm* timeInfo = gmtime(&utcTime);

	char* ret = new char[DEFAULT_BUFFER_SIZE];
	strftime(ret, DEFAULT_BUFFER_SIZE, "%H:%M:%S", timeInfo);

	return ret; // Return formatted time string
}

ClientInput* parseInput(char* input) {
	char* firstParam = strtok(input, " ");
	char* secondParam = strtok(NULL, " ");
	ClientInput* userInput = new ClientInput;
	userInput->clientInput = static_cast<MenuInput>(atoi(firstParam));
	if (secondParam != nullptr) {
		userInput->cityInput = static_cast<CityInput>(atoi(secondParam));
	}

	return userInput;
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
