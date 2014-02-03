/*******************************************************************************
    File: main.cpp

    Authors: Gustavo Pedroso UIN: 423002834
    		 Levi Clark UIN:
    		 Terry Chen UIN:
    		 Daniel He UIN:

            Department of Computer Science
            Texas A&M University
    Date  : 2/2/2014

    Formatting: * 80 pt width is used for code, for the most part
				* Hungarian naming convention is used for variables
				* Comments are applied for explanations
				* Spacing and brackets are applied for readability

	This file contains the main file 
*******************************************************************************/

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "DBMS.h"
using namespace std;

int main() 
{
	DBMS d; //declaring class variable
	string sInput; //variable for gathering input
	bool bExit; //variable for exiting the loop

	d.printOperations(); //print operations list
	do
	{
		//gather user input
		cin >> sInput;
		bExit = false;

		if (toupper(sInput[0]) == 'A')
		{
			printf("| A was selected\n");
		}
		else if (toupper(sInput[0]) == 'B')
		{
			printf("| B was selected\n");
		}
		else if (toupper(sInput[0]) == 'C')
		{
			printf("| C was selected\n");
		}
		else if (toupper(sInput[0]) == 'D')
		{
			printf("| D was selected\n");
		}
		else if (toupper(sInput[0]) == 'E')
		{
			printf("| E was selected\n");
		}
		else if (toupper(sInput[0]) == 'F')
		{
			printf("| EXITING..\n");
			bExit = true;
		}
		else
		{
			printf("| ERROR, please enter a valid choice\n");
		}
	} while(!bExit);
	
	return 0;
}
