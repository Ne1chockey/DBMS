/*******************************************************************************
    File: DBMS.h

    Authors: Gustavo Pedroso UIN: 423002834
    		 Levi Clark UIN:
    		 Terry Chen UIN:
    		 Daniel He UIN:

            Department of Computer Science
            Texas A&M University
    Date  : 2/2/2014

    This file contains the header for the database management system
    Formatting: * 80 pt width is used for code, for the most part
				* Hungarian naming convention is used for variables
				* Comments are applied for explanations
				* Spacing and brackets are applied for readability
*******************************************************************************/

#ifndef DBMS_H
#define DBMS_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

class DBMS 
{
private:
	//Declare private variables

public:
	//Declare class methods
    DBMS(){};
    
    //engine functions

    //app functions
    void printOperations();
};

void DBMS::printOperations()
{
    printf("\n|---------------------------------------");
    printf("---------------------------------------|\n");
    printf("|                                 OPERATIONS");
    printf("                                   |\n");
    printf("| -----------------------------------------------");
    printf("----------------------------- |\n");
    printf("| A) operation                                    ");
    printf("                             |\n");
    printf("| B) operation                                    ");
    printf("                             |\n");
    printf("| C) operation                                    ");
    printf("                             |\n");
    printf("| D) operation                                    ");
    printf("                             |\n");
    printf("| E) operation                                    ");
    printf("                             |\n");
    printf("| F) operation                                    ");
    printf("                             |\n");
    printf("| F) EXIT                                         ");
    printf("                             |\n");
    printf("|---------------------------------------");
    printf("---------------------------------------|\n");
}

#endif
