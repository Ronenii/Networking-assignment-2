#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include <string.h>
#include <time.h>

enum class ClientInput {
	GET_TIME = 1,
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
	EXIT

};

char* getTime();

ClientInput parseInput(char* input);
