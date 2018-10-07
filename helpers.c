/******************************************************************************
** Student name: 	Darcy Morgan
** Student number: 	S3659847
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "helpers.h"

void readRestOfLine()
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}/*obviously, this gives a "safe" string: no buffer overflows.*/
char* getStringSafe(int stringMaxLength){
	char* delim;
	char* choice = malloc(stringMaxLength*sizeof(char));
	delim = "\n\0";
	fgets(choice, stringMaxLength + EXTRA_SPACES, stdin);
	if(strcmp(delim, &choice[strlen(choice)-1])==0){
		choice[strlen(choice)-1]=0;
	}	
	else{
		choice="4";
		/*
		4 is an invalid input for all stages, so I use it as
		an indicator for invalid input 
		to be handled by the calling function
		*/
		readRestOfLine();
	}
	return choice;
}
