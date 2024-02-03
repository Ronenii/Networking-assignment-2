#pragma once
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include <sysinfoapi.h>

enum class ClientInput {
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

char * getTime();

char* getTimeWithoutDate();

char* getTimeWithoutDateOrSeconds();

char* getYear();

char* getTimeSinceEpoch();

char* getMonthAndDay();

char* getCurrentTicks();

ClientInput parseInput(char* input);
