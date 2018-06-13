#include "fitbit.h"

FILE *openCSV(char *file, char *mode) // code was based on the examples provided by andy in class
{
	FILE *infile = NULL;

	infile = fopen(file, mode);


	if (infile != NULL)
	{
		//puts("open seasame bitches"); <- was being used to test if the input file was being opened
		return infile;
	}
	
}

int readCSV(FILE *file, char trash[2][56], char data[][50]) // code was based on the examples provided by andy in class
{
	int count = 0;

	while (!feof(file))
	{
		if (count == 0)
		{
			fgets(trash[0], 56, file);
			fgets(trash[1], 56, file);
		}
		fgets(data[count], 50, file);
		//puts(data[count]); < -for seeing the values being read-in
		
		++count;
	}
	
	return count;
}


/* i wound up having to resort to this after several failed attempts to use iterative means of shifting the data over. i understand that
it would not work for other cases, but in the case of the csv document we were given it has worked.*/
int fixData(char data[][50], int numRecords)
{
	char Temp = '\0';
	char temp = '\0';
	int count = 0;

	for (size_t i = 0; i < numRecords; i++)
	{
		for (size_t t = 0; t < 50; t++)
		{
			if ((data[i][t] == ',')&(data[i][t + 1] == '\n'))
			{
				data[i][t+1] = '0';
				data[i][t + 2] = '\n';
				
			}
			if ((data[i][t] == ',')&(data[i][t + 1] == ','))
			{
				data[i][t + 6] = '\n';
				data[i][t + 5] = data[i][t+4]; 
				data[i][t + 4] = data[i][t+3];
				data[i][t + 3] = data[i][t+2];
				data[i][t + 2] = data[i][t+1];
				data[i][t + 1] = '0';
				count++; // counting the number of heart rate values that are null are were fixed
			}
		}
		//puts(data[i]); <- for testing 
	}
	return count;
}

void tokthaString(char data[][50], int numData, Fitbit minData[1440]) // code was based on the examples provided by andy in class
{
	int count = 0;
	char *pToken = NULL;
	float temp = 0.0;
	int tempI = 0;
	Sleep tempE = NONE;

	while ((count) < numData)
	{
		pToken = strtok(data[count], ",");
		strcpy(minData[count].minute, pToken);
		
		pToken = strtok(NULL, ",");
		temp = atof(pToken);
		minData[count].calories = temp;
		
		pToken = strtok(NULL, ",");
		temp = atof(pToken);
		minData[count].distance = temp;

		pToken = strtok(NULL, ",");
		tempI = atoi(pToken);
		minData[count].floors = tempI;

		pToken = strtok(NULL, ",");
		tempI = atoi(pToken);
		minData[count].heartRate = tempI;

		pToken = strtok(NULL, ",");
		tempI = atoi(pToken);
		minData[count].steps = tempI;

		pToken = strtok(NULL, "\n");
		tempI = atoi(pToken);
		tempE = (Sleep)tempI;
		minData[count].sleepLevel = tempE;
		count++;
	}
}

double totalCal(Fitbit minData[1440], int numData)
{
	double totalCalories = 0.0;
	double data = 0.0;
	for (size_t i = 0; i < numData; i++)
	{
		data = minData[i].calories;
		totalCalories += data;
	}
	return totalCalories;

}

double totalDist(Fitbit minData[1440], int numData)
{
	double totalDistance = 0.0;
	double data = 0.0;
	for (size_t i = 0; i < numData; i++)
	{
		data = minData[i].distance;
		totalDistance += data;
	}
	return totalDistance;
}

int sumFloors(Fitbit minData[1440], int numData)
{
	int totalFloors = 0;
	int data = 0;
	for (size_t i = 0; i < numData; i++)
	{
		data = minData[i].floors;
		totalFloors += data;
	}
	return totalFloors;
}

int sumSteps(Fitbit minData[1440], int numData)
{
	int totalSteps = 0;
	int data = 0;
	for (size_t i = 0; i < numData; i++)
	{
		data = minData[i].steps;
		totalSteps = totalSteps + data;
	}
	return totalSteps;
}
/*in this function i am not using the total number of entries to calculate, rather i am using the number of entries that were not missing  
the heart rate value in the line (numData - numNull) */
double avgHTR(Fitbit minData[1440], int numData, int numNull)
{
	double avgHTR = 0.0;
	double totHTR = 0.0;
	double data = 0.0;
	for (size_t i = 0; i < numData; i++)
	{
		data = minData[i].heartRate;
		totHTR += data;
	}
	return avgHTR = (totHTR / (numData - numNull));
}

int maxSteps(Fitbit minData[1440], int numData)
{
	int temp = 0;
	int tempHigh = 0;
	int counter = 0;

	while (counter < numData)
	{
		temp = minData[counter].steps;

		if (temp > tempHigh)
			tempHigh = temp;
		counter++;
	}
	return tempHigh;
}

int rangeSleep(Fitbit minData[1440], int numData) //only returns a sum of the range 
{
	int count = 0;
	int temp1 = 0, temp2 = 0;
	Sleep sleepVal = NONE;
	
	while (count <numData)
	{
		if (minData[count].sleepLevel>1)
		{
			
			temp1 = temp1 + (int)minData[count].sleepLevel;
		}
		else if(minData[count].sleepLevel<1)
		{
			temp2 = temp1;
			temp1 = 0;
			
		}
		count++;
	}
	if (temp1 > temp2)
	{
		return temp1;
	}
	if (temp2 > temp1)
	{
		return temp2;
	}
	
}