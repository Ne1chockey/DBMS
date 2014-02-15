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
Read a file and call parse function on each line read
*******************************************************************************/
bool Parser::readFromFile()
{
    ifstream fhIn; //file handler
    string sFilenameIn; //Declaring string for holding filename from the user
    string sLineIn; //Hold the line that is read off file
    int iCount = 0;
    /*
    //Output for gathering filename from the user                       <------remember to uncomment this when submitting
    printf("\n\n");
    printf("|--------------------------------------");
    printf("-----------------------------------------\n");
    printf("| Enter the filename: ");
    getline(cin, sFilenameIn);
    
    //Open the file and validate it opened properly
    fhIn.open(sFilenameIn.c_str());*/
    fhIn.open("testInput.txt"); 
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
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    CHANGE ICOUNT TO THE AMOUNT OF LINES YOU WANT TO SEE! FOR TESTING PURPOSES
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    while(!fhIn.eof() && iCount != 10)
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
Parse the line in and call the appropiate functions
*******************************************************************************/
void Parser::parse(string sLineIn)
{
    //Declare and initialize variables
    string sTemp;

    printf("%s\n", sLineIn.c_str());

    size_t iPosStart = sLineIn.find("CREATE TABLE");

    if (iPosStart!=std::string::npos)
    {
        //get the table name
        size_t iPosEnd = sLineIn.find("(");
        string sTableName = sLineIn.substr(iPosStart+CREATE_TABLE_SIZE,iPosEnd-CREATE_TABLE_SIZE-2);

        //get the column names
        iPosStart = iPosEnd;
        iPosEnd = sLineIn.find("PRIMARY KEY",iPosStart+1);
        string sColumns = sLineIn.substr(iPosStart,iPosEnd-CREATE_TABLE_SIZE-PRIMARY_KEY_SIZE+1);

        //get the primary keys
        iPosStart = iPosEnd;
        iPosEnd = sLineIn.find(")",iPosStart+1);
        string sPrimaryKeys = sLineIn.substr(iPosStart+PRIMARY_KEY_SIZE,iPosEnd-PRIMARY_KEY_SIZE);

        //remove the spaces from the name of the table
        sTableName = cleanSpaces(sTableName);

        //call the create table function after the helper functions finish 
        e.createTable(sTableName,createColVector(sColumns),createVector(sPrimaryKeys));

        //Display table to see that it works
        e.displayTable(sTableName);
    }

    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    The if statments below should be implemented in the way the above if statement is.
    The sizes for the different constant values are declared global.
    There are more operations below that havent been added that need to be.
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    iPosStart = sLineIn.find("INSERT INTO"); 

    if (iPosStart!=std::string::npos)                                       //<------------- TO DO
    {
        printf("INSERT INTO found at %i\n", iPosStart);

        iPosStart = sLineIn.find("VALUES FROM");

        if (iPosStart!=std::string::npos)                                   //<------------- TO DO
        {
            printf("VALUES FROM found at %i\n", iPosStart);
        }
    }

    iPosStart = sLineIn.find("WRITE");

    if (iPosStart!=std::string::npos)                                       //<------------- TO DO
    {
        printf("WRITE found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("CLOSE");

    if (iPosStart!=std::string::npos)                                       //<------------- TO DO
    {
        printf("CLOSE found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("EXIT");

    if (iPosStart!=std::string::npos)                                       //<------------- TO DO
    {
        printf("EXIT found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("OPEN");

    if (iPosStart!=std::string::npos)                                       //<------------- TO DO
    {
        printf("OPEN found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("SHOW");

    if (iPosStart!=std::string::npos)                                       //<------------- TO DO
    {
        printf("SHOW found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("<=");

    if (iPosStart!=std::string::npos)                                       //<------------- TO DO
    {
        printf("<= found at %i\n", iPosStart);
    }

    iPosStart = sLineIn.find("==");

    if (iPosStart!=std::string::npos)                                       //<------------- TO DO
    {
        printf("== found at %i\n", iPosStart);
    }
    
    //There are more of these to add, like <, >, && and any others you can think of


    //Save the indicies of where each function was found, compare them and
    //execute the first function found and call parse recursively on rest of string
    //Still thinking about this part, after we implement the above cases
    //we can look more in depth into this

}

/*******************************************************************************
Takes in a string, parses it, and creates a vector of columns to send back
*******************************************************************************/ 
vector<tuple<string,string,bool> > Parser::createColVector(string sLineIn)                  
{
    //<type, name, primarykey>
    vector<tuple<string,string,bool> > vColVectorOut;
    vector<string> vCol = createVector(sLineIn);

    for (int i = 0; i < vCol.size(); i++)
    {
        printf("%s, and the size is %i\n", vCol[i].c_str(), vCol[i].length());
        string sType, sName;
        
        //See what type of column it is and create a tuple with the name & type
        size_t iVar = vCol[i].find("VARCHAR");

        if (iVar!=std::string::npos)
        {
            sType = "string";
            sName = vCol[i].substr(0,iVar);
        }

        size_t iInt = vCol[i].find("INTEGER");

        if (iInt!=std::string::npos)
        {
            sType = "int";
            sName = vCol[i].substr(0,iInt);
        }
        //printf("%s and %s\n", sType.c_str(), sName.c_str());
        //push the newly created column into the vector to send back
        vColVectorOut.push_back(make_tuple(sName,sType,false));

    }
    return vColVectorOut;
}

/*******************************************************************************
Takes in a string, parses it, and creates a vector of strings to send back
*******************************************************************************/ 
vector<string> Parser::createVector (string sLineIn)
{
    vector<string> vReturn;
    int iPosStart = 0;
    int iPosEnd = 0;
    int iCount = 0;
    int iAmountOfCommas = 0;

    printf("sLineIn is %s\n", sLineIn.c_str());
    //Check to see how many commas are in the string 
    for (int i = 0; i < sLineIn.length(); ++i)
    {
        //Execute if the comma is found and increment the counter
        if (sLineIn[i] == ',')
        {
            iAmountOfCommas++;
        }
    }

    //Loop to parser out the comma seperated values
    while (iCount <= iAmountOfCommas)
    {
        iPosEnd = sLineIn.find(",",iPosStart+1);
        printf("iPosStart is at %i and iPosEnd is at %i\n", iPosStart, iPosEnd);
        vReturn.push_back(sLineIn.substr(iPosStart,iPosEnd-iPosStart));
        iPosStart = iPosEnd+1;
        iCount++;
    }

    //clean up the words that were seperated out
    for (int i = 0; i < vReturn.size(); ++i)
    {
        vReturn[i] = cleanSpaces(vReturn[i]);
        printf("%s\n", vReturn[i].c_str());
    }

    return vReturn;
}

/*******************************************************************************
Takes in a string, parses it, and creates a vector of strings to send back
*******************************************************************************/    //<------------- TO DO
vector< tuple<int, string> > Parser::createRowVector (string sLineIn)
{

}

/*******************************************************************************
Remove any additional spaces from the string
*******************************************************************************/ 
string Parser::cleanSpaces (string sLineIn)
{
    string sOut = "";
    for (int i = 0; i < sLineIn.length(); ++i)
    {
        //Append the value from the string into the return string, if its alpha
        if (isalpha(sLineIn[i]))
        {
            sOut += sLineIn[i];
        }
    }

    return sOut;
}