/******************************************************************************
** Student name: 	Darcy Morgan
** Student number: 	S3659847
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "carboard.h"
void chooseMenu();
void showMenu();
char* choice = "";



const size_t blah = 3;

int main()
{
	while(1)
	{
		showMenu();
		if(strcmp("3",choice)==0){goto exit;}
	}
	exit: return EXIT_SUCCESS;
}
void chooseMenu()
{
	choice = malloc(3 * sizeof(char));
	printf("Please enter your choice:");


	choice = getStringSafe(1);

	if(strcmp("1",choice)==0){playGame();}
	else if(strcmp("2",choice)==0){showStudentInformation();}
	else if(strcmp("3",choice)==0){}
		else {printf("Invalid input.\n");}\
}

void showMenu()
{		
	printf("Welcome to Car Board\n");
	printf("--------------------\n");
	printf("1. Play Game\n");
	printf("2. Show Student\'s Information\n");
	printf("3. Quit\n");
	chooseMenu();
}

void showStudentInformation()
{
	printf("----------------------------------\n");
	printf("Name: %s\n", STUDENT_NAME);
	printf("No: %s\n", STUDENT_ID);
	printf("Email: %s\n", STUDENT_EMAIL);
	printf("----------------------------------\n");
	chooseMenu();
}
