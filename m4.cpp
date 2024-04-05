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
	double price = 0;
};

//Prototypes
int processFlight(char filename[], struct FlightData flights[], int* pNumberOfFlights);




//MAIN
int main(void)
{
	int totalFlightsCount = 0;
	FILE* pSourceFile = NULL;
	struct FlightData allFlightData[] = { { } }; //creating the struct array initialized with default struct values at index 0
	char line[MAX_LINE_SIZE] = { "" }; //line read from file
	char storedString[MAX_LINE_SIZE] = { "" }; //stored string from each line read

	pSourceFile = fopen(SOURCE_FILE_NAME, "r");
	if (pSourceFile == NULL) //checks if text file was opened successfully
	{//exception
		printf("Error opening text file.");
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
			if (sscanf(line, " %s \n", storedString) != 1)
			{
				processFlight(storedString, allFlightData, &totalFlightsCount);
			}

		}//main else block END

	return SUCCESS;
}//MAIN end


//
// FUNCTION : processFlight()
// DESCRIPTION :
//	This function reads and parses all of the info from each files listed in the text file 
//	corresponding to the "filname" given as the parameter. It then stores the data unto 
//	an array of structs. 
// PARAMETERS :
//	char filename[]: The name of the file that lists all the flight data.
//	struct FlightData flights[]: array of structs that serves to save the parsed flight data.
//	int* pNumberOfFlights: pointer to total number of flights read and saved.
// RETURNS :
//	int: 0 if the function operations were a success
//	int: -2 if textfile was not opened successfully
//	
int processFlight(char filename[], struct FlightData flights[], int* pNumberOfFlights)
{
	FILE* 
}