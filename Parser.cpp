/*******************************************************************************
    File: Parser.cpp

    Authors: Gustavo Pedroso UIN: 423002834
             Levi Clark      UIN: 520007880
             Terry Chen      UIN: 121007055
             Daniel He       UIN: 620006827

            Department of Computer Science
            Texas A&M University
    Date  : 2/2/2014

    Formatting: * 80 pt width is used for code, for the most part
                * Hungarian naming convention is used for variables
                * Comments are applied for explanations
                * Spacing and brackets are applied for readability

	This file contains the implementation for the parser
*******************************************************************************/

#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Parser.h"
using namespace std;

/*******************************************************************************

*******************************************************************************/
bool Parser::readFromFile()
{
    ifstream fhIn; //file handler
    string sFilenameIn; //Declaring string for holding filename from the user
    string sLineIn; //Hold the line that is read off file
    int iCount = 0;

    //Output for gathering filename from the user
    printf("\n\n");
    printf("|--------------------------------------");
    printf("-----------------------------------------\n");
    printf("| Enter the filename: ");
    getline(cin, sFilenameIn);

    //Open the file and validate it opened properly
    fhIn.open(sFilenameIn.c_str());

    if (!fhIn)
    { 
        //Output error message
        printf("|--------------------------------------");
        printf("-----------------------------------------\n");
        printf("| ERROR, file did not open, exiting...\n"); 
        return false; //Ends function
    }

    //Reading the first line from the file
    getline(fhIn, sLineIn, ';');

    //Formatting
    printf("\n|--------------------------------------");
    printf("-----------------------------------------\n");

    //Loop to read in file information
    while(!fhIn.eof())
    {
        int *ptrTemp;

        //Parse the line of text and interpret it
        parse(sLineIn);

        //Prepare to loop again, read in next record & update
        getline(fhIn, sLineIn, '\n');

        //Increase the counter
        iCount++;
    }

    //Close the file
    fhIn.close();
}

/*******************************************************************************

*******************************************************************************/
void Parser::parse(string sLineIn)
{
    //Declare and initialize variables
    int iPosStart, iPosEnd; 
    string sTemp;
    printf("%s\n", sLineIn.c_str());

}