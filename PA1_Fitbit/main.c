#include "fitbit.h"
/*
Programmer: Joey Waner
Assignment: Programming Assignment 1 - Fitbit Data
Due: 06/11/18
Purpose: analyze the csv file and calculate several sums and averages
06/12/18 i corrected an issue with calculating the average heart rate 
*/
int main()
{
	FILE *infile = NULL;
	FILE *outfile = NULL;//for results.csv
	int numData = 0;
	int count = 0;
	int maxStep = 0;
	int range = 0;
	int numNull = 0;
	double sumCal = 0.0, sumDist = 0.0, totFlr = 0.0, sumStep = 0.0, avgHRT = 0.0;
	char fitData[1440][50] = { {"\0"},{"\0"} };
	char trash[2][56] = { {"\0"} ,{"\0"} };
	Fitbit minuteData[1440] = { {"",0.0,0.0,0,0,0,NONE} };

	infile = openCSV("FitbitData.csv", "r"); 
	if (infile != NULL)//checks if input csv was opened
	{
		numData = readCSV(infile, trash, fitData);
		numNull = fixData(fitData, numData);
		tokthaString(fitData, numData, minuteData);
		
		sumCal = totalCal(minuteData, numData);
		sumDist = totalDist(minuteData, numData);
		totFlr = sumFloors(minuteData, numData);
		sumStep = sumSteps(minuteData, numData);
		avgHRT = avgHTR(minuteData, numData, numNull);
		maxStep = maxSteps(minuteData, numData);
		range = rangeSleep(minuteData, numData);
		outfile = fopen("Results.csv", "w");

		if (outfile!=NULL)// checks if output file was opened
		{
			fputs("Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n", outfile);
			fprintf(outfile, "%.2f, ", sumCal);
			fprintf(outfile, "%.2f, ", sumDist);
			fprintf(outfile, "%.2f, ", totFlr);
			fprintf(outfile, "%.2f, ", sumStep);
			fprintf(outfile, "%.2f, ", avgHRT);
			fprintf(outfile, "%d, ", maxStep);
			fprintf(outfile, "%d", range);

			puts("Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep");
			printf("%.2f, ", sumCal);
			printf("%.2f, ", sumDist);
			printf("%.2f, ", totFlr);
			printf("%.2f, ", sumStep);
			printf("%.2f, ", avgHRT);
			printf("%d, ", maxStep);
			printf("%d\n", range);

			
		}
	}
	
	fclose(infile);
	fclose(outfile);
	return 0;
}