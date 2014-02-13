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
#include "Engine.h"
using namespace std;

const int CREATE_TABLE_SIZE = 12;
const int INSERT_INTO_SIZE = 11;
const int WRITE_CLOSE_SIZE = 5;
const int OPEN_EXIT_SHOW_SIZE = 4;
const int SINGLE_OP_SIZE = 1;
const int DOUBLE_OP_SIZE = 2;
const int VALUES_FROM_SIZE = 11;
const int PRIMARY_KEY_SIZE = 11;

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
    //CHANGE ICOUNT TO THE AMOUNT OF LINES YOU WANT TO SEE! FOR TESTING PURPOSES
    while(!fhIn.eof() && iCount != 20)
    {
        int *ptrTemp;

        //Parse the line of text and interpret it
        parse(sLineIn);

        //Prepare to loop again, read in next record & update
        getline(fhIn, sLineIn, ';');

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
    Engine e;
    //Declare and initialize variables
    //int iPosStart, iPosEnd; 
    string sTemp;
    printf("%s\n", sLineIn.c_str());

    size_t iPosStart = sLineIn.find("CREATE TABLE");

    if (iPosStart!=std::string::npos)
    {
        printf("CREATE TABLE found at %i\n", iPosStart);

        //get the table name
        size_t iPosEnd = sLineIn.find("(");
        string sTableName = sLineIn.substr(iPosStart+CREATE_TABLE_SIZE,iPosEnd-CREATE_TABLE_SIZE-2);
        printf("The name of the table is %s\n", sTableName.c_str());

        //get the column names
        iPosStart = iPosEnd;
        iPosEnd = sLineIn.find("PRIMARY KEY",iPosStart+1);
        string sColumns = sLineIn.substr(iPosStart,iPosEnd-CREATE_TABLE_SIZE-PRIMARY_KEY_SIZE+1);
        printf("The columns are %s\n", sColumns.c_str());

        //get the primary keys
        iPosStart = iPosEnd;
        iPosEnd = sLineIn.find(")",iPosStart+1);
        string sPrimaryKeys = sLineIn.substr(iPosStart+PRIMARY_KEY_SIZE,iPosEnd-PRIMARY_KEY_SIZE);
        printf("The primary keys are %s\n", sPrimaryKeys.c_str());

        //create a function to parse out the columns and primary keys and 
        //returns a vector of strings so we can call the create table function with them in parameters  <------------- TO DO

        //e.createTable(sTableName,createColVector(sColumns),createPrimaryVector(sPrimaryKeys));
    }

    iPosStart = sLineIn.find("INSERT INTO");

    if (iPosStart!=std::string::npos)
    {
        printf("INSERT INTO found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("WRITE");

    if (iPosStart!=std::string::npos)
    {
        printf("WRITE found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("CLOSE");

    if (iPosStart!=std::string::npos)
    {
        printf("CLOSE found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("EXIT");

    if (iPosStart!=std::string::npos)
    {
        printf("EXIT found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("VALUES FROM");

    if (iPosStart!=std::string::npos)
    {
        printf("VALUES FROM found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("OPEN");

    if (iPosStart!=std::string::npos)
    {
        printf("OPEN found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("SHOW");

    if (iPosStart!=std::string::npos)
    {
        printf("SHOW found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("<=");

    if (iPosStart!=std::string::npos)
    {
        printf("<= found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("==");

    if (iPosStart!=std::string::npos)
    {
        printf("== found at %i\n", iPosStart);
    }

    //Save the indicies of where each function was found, compare them and
    //execute the first function found and call parse recursively on rest of string

}