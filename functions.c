/*******************************************************************************************
* Programmer: Jose Sainz *
* Class: CptS 122, Spring, 2019; Lab Section 6 *
* Programming Assignment: Analyzing Fitbit Data *
* Date: January 23, 2019 *
* Description: THe program will be able to take a csv file full of Fitbit Data *
* and decompose it into smaller pieces in order to calculate certain things *
*******************************************************************************************/

#include "header.h"

/* Function: readData()
 * Date: 1/23
 * Description: iterates through functions in order to check for duplicated/clean the data and the it copies everything into the struct 1440 times
 */
void readData (FILE* data, FitbitData fullDay[]) {

	int i = 0;
	char temp[100]; // can store up to 100 characters / will be used to read each line as strings

	fgets(temp, 100, data); // reads the first place holder line

	strcpy(temp, " "); // cleaning the string

	for(; i < 1440; i++) {

		fgets(temp, 100, data); // each time the loop iterates it will copy the data into temp
		
		i = duplicateCheck(fullDay, i); // will decrement the index if there is a duplicate found 

		cleanData(temp);
		fullDay[i] = copyData(temp); // using the temp line, all the information will be copied down in its correct data type
	}
}

/* Function: duplicateCheck()
 * Date: 1/23
 * Description: checks if there are duplicate minutes in the data
 */
int duplicateCheck (FitbitData fullDay[], int index) {

	if (index && !strcmp(fullDay[index].minute, fullDay[index - 1].minute)) { // checks if the minutes prior to the idex were a duplicate

		index--;
	}

	return index;
}

/* Function: cleanData()
 * Date: 1/23
 * Description: before copying the data it checks if there is any flaws in the data line and if there is it replaces it with a 0
 */
void cleanData(char temp [] ) {

	
	char newString[75];
	int j = 0;

	for (int i = 0; i < strlen(temp) ; i++)
	{

		if (temp[i] == '\n') { // once the line ends it will exit the loop
			
			newString[j] = '\0'; // terminates the string to prevent garbage values
			break;
		}
		else if (temp[i] == ',' && temp[i + 1] == ',') 
		{
			// we have a double comma
			newString[j] = ',';
				j++;
			newString[j] = '0';
		}
		else if (temp[i] == ',' && temp[i + 1] == '\n')
		{
			// we have a new line and a comma
			newString[j] = ',';
				j++;
			newString[j] = '0';
		}
		else
		{
			newString[j] = temp[i];
		}

		j++;
	}
	
	strcpy(temp, newString); // types this out on the terminal just to check if everything works
	
	
}

/* Function: copyData()
 * Date: 1/23
 * Description: this function stores a line of data into each corresponding data type inside of
 * the struct. it then returns the data so it can be copied elsewhere.
*/
FitbitData copyData (char temp[]) {

	char* tempLine = temp, * tokenStr;

	FitbitData newLine = {" ", " ", 0, 0, 0, 0, 0, 0};

	tokenStr = strtok(tempLine, ",");
	strcpy(newLine.patient, tokenStr); // strcpy to store the token inside of the struct

	tokenStr = strtok(NULL, ",");
	strcpy(newLine.minute, ",");

	tokenStr = strtok(NULL, ",");
	sscanf(tokenStr, "%lf", &(newLine.calories)); // using sscanf to store string values as doubles/ints

	tokenStr = strtok(NULL, ",");
	sscanf(tokenStr, "%lf", &(newLine.distance));

	tokenStr = strtok(NULL, ",");
	sscanf(tokenStr, "%u", &(newLine.floors));

	tokenStr = strtok(NULL, ",");
	sscanf(tokenStr, "%u", &(newLine.heartRate));

	tokenStr = strtok(NULL, ",");
	sscanf(tokenStr, "%u", &(newLine.steps));

	tokenStr = strtok(NULL, ",");
	sscanf(tokenStr, "%d", &(newLine.sleepLevel));

	return newLine;
}

/* Function: totalCalories()
 * Date: 1/23
 * Description: calculates the total calories burned in a day
*/
double totalCalories(FitbitData fullDay[]) {

	int i = 0;
	double calories = 0;

	for(; i < 1440; i++) {
		
		if (fullDay[i].calories > 0) { // checks if he burned calories if so it adds them to itself
			
			calories += fullDay[i].calories;
		}
	}
	return calories;
}


/* Function: totalDistance()
 * Date: 1/23
 * Description: calculates the total distance traveled in a day
*/
double totalDistance(FitbitData fullDay[]) {

	int i = 0;
	double distance = 0;

	for(; i < 1440; i++) {
		
		if (fullDay[i].distance > 0) { // checks if he traveled any distance if so it adds it to itself
			
			distance += fullDay[i].distance;
		}
	}
	return distance;
}

/* Function: totalFloors()
 * Date: 1/23
 * Description: calculates the total amount of floors 
*/
int totalFloors(FitbitData fullDay[]) {

	int i = 0, floors = 0;

	for(; i < 1440; i++) {

		if (fullDay[i].floors > 0) { // checks for floors if so it gets added to itself

			floors += fullDay[i].floors;
		}
	}
	return floors;
}

/* Function: totalSteps()
 * Date: 1/23
 * Description: calculates the total amount of steps taken throughout the day
*/
int totalSteps(FitbitData fullDay[]) {

		int i = 0, steps = 0;

	for(; i < 1440; i++) {

		if (fullDay[i].steps > 0) { // checks for steps taken in a minute if there is any it will add it to itself

			steps += fullDay[i].steps;
		}
	}
	return steps;
}

/* Function: avgHeartRate()
 * Date: 1/23
 * Description: calculates the average heart rate throughout the day
*/
double avgHeartRate(FitbitData fullDay[]) {

	int i = 0, counter = 0;
	int totalRate = 0;

	for (; i < 1440; i++) {

		if (fullDay[i].heartRate > 0) { // checks for heart rate throughout each minute

			
			totalRate += fullDay[i].heartRate;
			counter++;
		}
	}
	return (double)totalRate / counter; // returns the average heart rate
}

/* Function: maxSteps()
 * Date: 1/23
 * Description: calculates the max amount of steps taken in a minute
*/
int maxSteps(FitbitData fullDay[]) {

	int i = 0, max = 0;

	for(; i < 1440; i++) {

		if (fullDay[i].steps > max) { // everytime a new max is encountered it will be stored in the variable max

			max = fullDay[i].steps;
		}
	}
	return max;
}

/* Function: consecutiveSleep()
 * Date: 1/23
 * Description: figures out when the largest span of poor sleep is and then adds it to each other to get the total amount of poor sleep
*/
int consecutiveSleep(FitbitData fullDay[], char* start, char* end) {

	int i = 0, max = 0, counter = 0, check = 0;
	

	for (; i < 1440; i++){// traverses through each minute in the day
		
		if (fullDay[i].sleepLevel > ASLEEP) { // using the enum type to describe 1
		
			counter = 1; // this is a counter for the span of time the person went with bad sleep

			for (; fullDay[i + counter].sleepLevel > ASLEEP; counter++) { // using loop
				
				check += fullDay[i].sleepLevel;

				if (check > max) {

					max = counter;
					strcpy(start, fullDay[i].minute);
					strcpy(end, fullDay[i + counter - 1].minute);
				}
			}
		}
	}
	return check;
}
