#ifndef FITBIT_H
#define FITBIT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
}Sleep;

typedef struct fitbit
{
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
}Fitbit;

FILE *openCSV(char *file, char *mode); // opens file
int readCSV(FILE *file, char trash[2][56],char data[][50]); // reads lines and stores them in an array (file must be open)
int fixData(char data[][50], int numRecords); //looks for double commas and null values in the string and 'fixes' them
void tokthaString(char data[][50], int numData, Fitbit minData[1440]); //tokenizes the string an assigns to positions in an array
double totalCal(Fitbit minData[1440], int numData); // calculates the total calories in the day
double totalDist(Fitbit minData[1440], int numData); // calculates total distance travelled in miles
int sumFloors(Fitbit minData[1440], int numData); //calculates total floors climbed
int sumSteps(Fitbit minData[1440], int numData); // calculates the total steps taken
double avgHTR(Fitbit minData[1440], int numData, int numNull); // averages the heard rate
int maxSteps(Fitbit minData[1440],int numData); //calculates largest number of steps taken
int rangeSleep(Fitbit minData[1440], int numData); 


#endif // !FITBIT_H
