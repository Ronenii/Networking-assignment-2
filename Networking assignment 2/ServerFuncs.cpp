#include "ServerFuncs.h"

string getTime() {
	// Get the current time.
	time_t timer;
	time(&timer);
	string ret = ctime(&timer);

	// Remove the new-line from the created string.
	ret.pop_back();

	return ret;
}

string getTimeWithoutDate() {
	time_t timer;
	time(&timer);

	char buffer[DEFAULT_BUFFER_SIZE];
	strftime(buffer, DEFAULT_BUFFER_SIZE, "%H:%M:%S", localtime(&timer));

	return string(buffer);
}

string getTimeWithoutDateOrSeconds() {
	time_t timer;
	time(&timer);

	char buffer[DEFAULT_BUFFER_SIZE];
	strftime(buffer, DEFAULT_BUFFER_SIZE, "%H:%M", localtime(&timer));

	return string(buffer);
}

string getYear() {
	time_t timer;
	time(&timer);

	char buffer[DEFAULT_BUFFER_SIZE];
	int year = localtime(&timer)->tm_year;
	sprintf(buffer, "%d", year + 1900);

	return string(buffer);
}

string getTimeSinceEpoch() {
	time_t timer;
	time(&timer);

	char buffer[DEFAULT_BUFFER_SIZE];
	sprintf(buffer, "%ld", timer);

	return string(buffer);
}

string getMonthAndDay() {
	time_t timer;
	time(&timer);

	char buffer[DEFAULT_BUFFER_SIZE];
	int day = localtime(&timer)->tm_mday;
	int month = localtime(&timer)->tm_mon + 1;

	sprintf(buffer, "%d/%d", day, month);

	return string(buffer);
}

string getCurrentTicks() {
	char buffer[DEFAULT_BUFFER_SIZE];
	sprintf(buffer, "%ld", GetTickCount());
	return string(buffer);
}

string getSecondsSinceBeginningOfTheMonth() {
	char buffer[DEFAULT_BUFFER_SIZE];

	time_t now;
	time(&now);

	struct tm beg_month;
	beg_month = *localtime(&now);
	beg_month.tm_hour = 0;
	beg_month.tm_min = 0;
	beg_month.tm_sec = 0;
	beg_month.tm_mday = 1;

	double seconds = difftime(now, mktime(&beg_month));

	sprintf(buffer, "%d", (int)seconds);

	return string(buffer);
}

string getWeekOfYear() {
	time_t timer;
	time(&timer);

	char buffer[DEFAULT_BUFFER_SIZE];
	strftime(buffer, DEFAULT_BUFFER_SIZE, "%U", localtime(&timer));

	return string(buffer);
}

string getDaylightSavings() {
	time_t timer;
	time(&timer);
	struct tm* tm_info = localtime(&timer);

	string ret;

	if (tm_info->tm_isdst > 0) {
		ret = "Daylight Saving Time is in effect.";
	}
	else if (tm_info->tm_isdst == 0) {
		ret = "Daylight Saving Time is not in effect.";
	}
	else {
		ret = "Daylight Saving Time information is not available.";
	}

	return ret;
}

void setTimeZone(const char* timeZone) {
	// Set the time zone using _putenv_s
	_putenv_s("TZ", timeZone);
	_tzset();
}

string getTimeInCity(CityInput city) {
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

	char buffer[DEFAULT_BUFFER_SIZE];
	strftime(buffer, DEFAULT_BUFFER_SIZE, "%H:%M:%S", timeInfo);

	return string(buffer);
}

string measureTimeLap() {
	static bool isTimeLapStarted;
	static time_t timeStarted;
	const int threeMinutesInSeconds = 180;
	string ret = "";
	time_t timeEnded;

	if (!isTimeLapStarted) {
		ret = "Time lap measuring started at " + getTime();
		isTimeLapStarted = true;
		time(&timeStarted);
	}
	else {
		isTimeLapStarted = false;
		time(&timeEnded);
		int timePassed = timeEnded - timeStarted;
		if (timePassed < threeMinutesInSeconds) {
			ret = "Time lap measuring took " + to_string(timePassed) + " seconds";
		}
		else {
			ret = measureTimeLap(); // since more than 3 minutes passed starts the function again.

		}
	}

	return ret;
}

ClientInput* parseInput(string input) {
	size_t spacePos = input.find(' ');
	string firstParam = input.substr(0, spacePos);
	string secondParam = (spacePos != string::npos) ? input.substr(spacePos + 1) : "";

	ClientInput* userInput = new ClientInput;
	userInput->clientInput = static_cast<MenuInput>(stoi(firstParam));
	if (!secondParam.empty()) {
		userInput->cityInput = static_cast<CityInput>(stoi(secondParam));
	}

	return userInput;
}