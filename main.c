/*******************************************************************************************
* Programmer: Jose Sainz *
* Class: CptS 122, Spring, 2019; Lab Section 6 *
* Programming Assignment: Analyzing Fitbit Data *
* Date: January 23, 2019 *
* Description: THe program will be able to take a csv file full of Fitbit Data *
* and decompose it into smaller pieces in order to calculate certain things *
*******************************************************************************************/


#include "header.h"
	

int main () {

	FitbitData fullDay[1440]; // 1440 is the amount of minutes in a day
	// opening both files but the data one is mode read, while the results is in mode write
	FILE* result = fopen("results.csv", "w"), * data = fopen("FitbitData.csv", "r"); // 
	// checks to see both files successfully opened, if they didn't it will terminate the program

	char start[100],  end[100];
	int tSteps = 0,tFloors = 0, mSteps = 0, cSleep = 0;
	double tCalories = 0.0, tDistance = 0.0, avgRate = 0.0;

	if (data == NULL || result == NULL) {
		
		printf("*****FILE DID NOT OPEN SUCCESFULLY*****");
		
		return 1;
	}

	readData(data, fullDay);

	tSteps = totalSteps(fullDay);
	tFloors = totalFloors(fullDay);
	mSteps = maxSteps(fullDay);
	cSleep = consecutiveSleep(fullDay, &start, &end);
	tCalories = totalCalories(fullDay);
	tDistance = totalDistance(fullDay);
	avgRate = avgHeartRate(fullDay);

	fprintf(result, "Total Calories, Total Distance, Total Floors, Total Steps, AvgHeartrate, Max Steps, Sleep\n");
	fprintf(result, "%f, %f, %d, %d, %f, %d ,%d", tCalories, tDistance, tFloors, tSteps, avgRate, mSteps, cSleep);





	// closing both of the files 
	fclose(data);
	fclose(result);	

	return 0;
}
