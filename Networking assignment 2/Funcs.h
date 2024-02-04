#pragma once
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <string>
#include <time.h>
#include <sysinfoapi.h>

using namespace std;

# define DEFAULT_BUFFER_SIZE 255
# define BASE_10 10

enum class MenuInput {
	EXIT,
	GET_TIME,
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
};

enum class CityInput {
	DOHA,
	PRAGUE,
	NEW_YORK,
	BERLIN
};

struct ClientInput {
	MenuInput clientInput;
	CityInput cityInput;
};

string getTime();
string getTimeWithoutDate();
string getTimeWithoutDateOrSeconds();
string getYear();
string getTimeSinceEpoch();
string getMonthAndDay();
string getCurrentTicks();
string getSecondsSinceBeginningOfTheMonth();
string getWeekOfYear();
string getDaylightSavings();
void setTimeZone(const char* timeZone);
string getTimeInCity(CityInput city);
ClientInput* parseInput(string input);
