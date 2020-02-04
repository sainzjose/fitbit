/*******************************************************************************************
* Programmer: Jose Sainz *
* Class: CptS 122, Spring, 2019; Lab Section 6 *
* Programming Assignment: Analyzing Fitbit Data *
* Date: January 23, 2019 *
* Description: THe program will be able to take a csv file full of Fitbit Data *
* and decompose it into smaller pieces in order to calculate certain things *
*******************************************************************************************/

#ifndef PA_1
#define _CRT_SECURE_NO_WARNINGS
#define PA_1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Used in order to find the users sleeping schedule
typedef enum sleep
{
 NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

// Struct that can hold all of the information in the csv file
typedef struct fitbit {

	char patient[10];
 	char minute[9];
 	double calories;
 	double distance;
 	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;

} FitbitData;

void readData (FILE* data, FitbitData fullDay[]);
int duplicateCheck (FitbitData fullDay[], int index);
void cleanData(char temp[]);
FitbitData copyData (char temp[]);
double totalCalories(FitbitData fullDay[]);
double totalDistance(FitbitData fullDay[]);
int totalFloors(FitbitData fullDay[]);
int totalSteps(FitbitData fullDay[]);
double avgHeartRate(FitbitData fullDay[]);
int maxSteps(FitbitData fullDay[]);
int consecutiveSleep(FitbitData fullDay[], char* start, char* end);

#endif 
