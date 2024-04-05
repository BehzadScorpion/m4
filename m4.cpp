/*
* FILE : m4.cpp
* PROJECT : SENG1000 - Major Assignment #4
* PROGRAMMER : Behzad Afrasiabi
* FIRST VERSION : 2024-04-04
* DESCRIPTION :
*	FILL LATER
*	FILL LATER
*	FILL LATER
*	FILL LATER
*	FILL LATER
*/


#include<stdio.h>
#pragma warning(disable: 4996)

//GLOBAL CONSTANTS
#define SOURCE_FILE_NAME "flights.txt"
#define STRUCT_ARRAY_SIZE 21
#define MAX_LINE_SIZE 41
//exceptions
#define SUCCESS 0
#define FAILURE -1
#define OPEN_TEXT_FILE_ERROR -2

//Structs
struct FlightData
{
	char source[STRUCT_ARRAY_SIZE] = { "" };
	char destination[STRUCT_ARRAY_SIZE] = { "" };
	char airline[STRUCT_ARRAY_SIZE] = { "" };
	double fare = 0;
};

//Prototypes
int parseLine(char* pSource, char* pDestination, double* pFare, char* pLineData);
int processFlight(char filename[], struct FlightData flights[], int* pNumberOfFlights);


//MAIN
int main(void)
{
	int totalFlightsCount = 0;
	FILE* pSourceFile = NULL;
	struct FlightData allFlightData[] = { { } }; //creating the struct array initialized with default struct values at index 0
	char line[MAX_LINE_SIZE] = { "" }; //line read from source file
	char sourceString[MAX_LINE_SIZE] = { "" }; //stored string from each line read

	pSourceFile = fopen(SOURCE_FILE_NAME, "r");
	if (pSourceFile == NULL) //checks if text file was opened successfully
	{//exception
		printf("Error opening source file.");
		return OPEN_TEXT_FILE_ERROR;
	}
	else
	{//main else block

		// getting each file name from the source file
		while (fgets(line, sizeof line, pSourceFile) != NULL)
		{
			if (feof(pSourceFile)) //end of file?
			{
				break; //end of file reached
			}

			if (ferror(pSourceFile))
			{//exception
				printf("Error reading source file.\n");
				break;
			}

			//Assuming line was read successfully, it is time to parse:
			if (sscanf(line, " %s \n", sourceString) != 1)
			{
				processFlight(sourceString, allFlightData, &totalFlightsCount);
			}

		}//while loop end

	}//main else block END
	return SUCCESS;
}//MAIN end


//
// FUNCTION : parseLine()
// DESCRIPTION :
//	This function reads and parses all of the info from the flight-info line read by processFlight().
//	It does so according to the specific format requirements, and then stores the data using the pointers
//	to the single specific FlightData object.  
// PARAMETERS :
//	char* pSource: pointer to the "source" field under the FlightData object
//	char* pDestination: pointer to the "destination" field under the FlightData object
//	double* pFare: pointer to the "fare" field under the FlightData object
//	char* pLineData: pointer to the line data passed from processFlight()
// RETURNS : //CHECK LATER
//	int: 0 if operation was successfull
//	int: -1 if operation was a failure
//	
int parseLine(char* pSource, char* pDestination, double* pFare, char* pLineData)
{
	if (sscanf(pLineData, "%[^ -]", &inputNumber) != 1)
	{
		return INVALID;
	}
}


//
// FUNCTION : processFlight()
// DESCRIPTION :
//	This function reads and parses all of the info from the prescribed flight-info file, 
//	according to the specific format requirements. It stores each saved data unto an array entry
//	from the passed array (check parameters.)
// PARAMETERS :
//	char filename[]: The name of the file that lists all the flight data (the flight-info file.)
//	struct FlightData flights[]: array of structs that serves to save the parsed flight data.
//	int* pNumberOfFlights: pointer to total number of flights read and saved.
// RETURNS : //NEEDS CHANGE
//	int: 0 if the function operations were a success //NEEDS CHANGE
//	int: -2 if textfile was not opened successfully  //NEEDS CHANGE
//	
int processFlight(char filename[], struct FlightData flights[], int* pNumberOfFlights)
{
	FILE* pFlightsFile = NULL;
	char flightLine[MAX_LINE_SIZE] = { "" }; //line read from flights file
	char flightString[MAX_LINE_SIZE] = { "" }; //stored string from each line read

	pFlightsFile = fopen(filename, "r");
	if (pFlightsFile == NULL) //checks if text file was opened successfully
	{//exception
		printf("Error opening flight file.");
	}
	else
	{//main else block

		while (fgets(flightLine, sizeof flightLine, pFlightsFile) != NULL)
		{
			if (feof(pFlightsFile)) //end of file?
			{
				break; //end of file reached
			}

			if (ferror(pFlightsFile))
			{//exception
				printf("Error reading source file.\n");
				break;
			}

			//Assuming line was read successfully, it is time to parse:
			FlightData currentData = flights[*pNumberOfFlights]; //getting current array entry by derefrencing
			parseLine(currentData.source, currentData.destination, &currentData.fare, flightLine);
			(*pNumberOfFlights)++; //incrementing source value to keep track of flight count for array indices

		}//while loop end

	}//main else block end

	return SUCCESS;
}