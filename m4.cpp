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
#include<string.h>
#pragma warning(disable: 4996)

//GLOBAL CONSTANTS
#define SOURCE_FILE_NAME "flights.txt"
#define STRUCT_ARRAY_SIZE 21
#define MAX_LINE_SIZE 41
#define MAX_FLIGHT_DATA 100
//exceptions
#define SUCCESS 0
#define FLIGHT_PARSING_ERROR -1
#define OPEN_FLIGHT_FILE_ERROR -2
#define READ_FLIGHT_FILE_ERROR -3
#define OPEN_SOURCE_FILE_ERROR -4
#define READ_SOURCE_FILE_ERROR -5

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
void displayLeastFareDetails(struct FlightData flights[]); //LAST BUT NOT LEAST


//MAIN
int main(void)
{
	int totalFlightsCount = 0;
	FILE* pSourceFile = NULL;
	struct FlightData allFlightData[MAX_FLIGHT_DATA] = { { } }; //creating the struct array initialized with default struct values at index 0
	char line[MAX_LINE_SIZE] = { "" }; //line read from source file

	pSourceFile = fopen(SOURCE_FILE_NAME, "r");
	if (pSourceFile == NULL) //checks if text file was opened successfully
	{//exception
		printf("Error opening source file.");
		return OPEN_SOURCE_FILE_ERROR;
	}
	else
	{//main else block

		// getting each file name from the source file
		while (fgets(line, MAX_LINE_SIZE, pSourceFile) != NULL)
		{
			if (feof(pSourceFile)) //end of file?
			{
				break; //end of file reached
			}

			if (ferror(pSourceFile))
			{//exception
				printf("Error reading source file.\n");
				return READ_SOURCE_FILE_ERROR;
			}

			//Assuming line was read successfully, it is time to parse:
			size_t newlineIndex = strcspn(line, "\n");
			// Replace the newline character with the null terminator
			line[newlineIndex] = '\0';
			processFlight(line, allFlightData, &totalFlightsCount);
			

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
// RETURNS : 
//	int: 0 if operation was successfull
//	int: -1 if operation was a failure
//	
int parseLine(char* pSource, char* pDestination, double* pFare, char* pLineData)
{
	if (sscanf_s(pLineData, "%[^-] - %[^,], %lf", pSource, STRUCT_ARRAY_SIZE, pDestination, STRUCT_ARRAY_SIZE, pFare) != 3)
	{
		// Check if dash was found
		if (strchr(pLineData, '-') == NULL) {
			printf("Error: Missing dash '-' in %s.\n", pLineData);
		}
		// Check if comma was found
		if (strchr(pLineData, ',') == NULL) {
			printf("Error: Missing comma ',' in %s.\n", pLineData);
		}
		return FLIGHT_PARSING_ERROR;
	}
	return SUCCESS;
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
// RETURNS : 
//	int: 0 if the function operations were a success 
//	int: -2 if flight file was not opened successfully  
//	int: -3 if flight file was not read successfully
//	
int processFlight(char filename[], struct FlightData flights[], int* pNumberOfFlights)
{
	FILE* pFlightsFile = NULL;
	char flightLine[MAX_LINE_SIZE] = { "" }; //line read from flights file

	pFlightsFile = fopen(filename, "r");
	if (pFlightsFile == NULL) //checks if text file was opened successfully
	{//exception
		printf("Error opening flight file.");
		return OPEN_FLIGHT_FILE_ERROR;
	}
	else
	{//main else block

		while (fgets(flightLine, MAX_LINE_SIZE, pFlightsFile) != NULL)
		{
			if (feof(pFlightsFile)) //end of file?
			{
				break; //end of file reached
			}

			if (ferror(pFlightsFile))
			{//exception
				printf("Error reading flight file: %s\n", filename);
				return READ_FLIGHT_FILE_ERROR;
			}

			//Assuming line was read successfully, it is time to parse:
			FlightData currentData = flights[*pNumberOfFlights]; //getting current array entry by derefrencing
			//ascribing the valid portion of the filename to the airline field:
			sscanf_s(filename, "%[^.]", currentData.airline, STRUCT_ARRAY_SIZE); //assuming format is correct
			if (parseLine(currentData.source, currentData.destination, &currentData.fare, flightLine) == 0)
			{
				strcpy_s(flights[*pNumberOfFlights].source, STRUCT_ARRAY_SIZE, currentData.source);
				strcpy_s(flights[*pNumberOfFlights].destination, STRUCT_ARRAY_SIZE, currentData.destination);
				strcpy_s(flights[*pNumberOfFlights].airline, STRUCT_ARRAY_SIZE, currentData.airline);
				flights[*pNumberOfFlights].fare = currentData.fare;
				(*pNumberOfFlights)++; //incrementing source value to keep track of flight count for array indices
			}
			else
			{
				printf("Error reading flight data.\n");
			}
			

		}//while loop end

	}//main else block end

	return SUCCESS;
}