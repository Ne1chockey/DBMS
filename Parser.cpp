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
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Parser.h"
#include "Engine.h"
using namespace std;

const int CREATE_TABLE_SIZE = 12;
const int INSERT_INTO_SIZE = 11;
const int WRITE_CLOSE_SIZE = 5;
const int DELETE_FROM_SIZE = 11;
const int UPDATE_SIZE = 5;
const int WHERE_SIZE = 5;
const int SET_SIZE = 3;
const int OPEN_EXIT_SHOW_SIZE = 4;
const int SINGLE_OP_SIZE = 1;
const int DOUBLE_OP_SIZE = 2;
const int VALUES_FROM_SIZE = 11;
const int VAL_FROM_REL_SIZE = 20;
const int PRIMARY_KEY_SIZE = 11;

//Array of String identifiers for non-symbolic operations
static const string expr[] = 
{"select", "project", "rename", "natural-join"};

//Array of String identifiers for symbolic comparisons
static const string operant[] =
{ "==", "!=", "<=", ">=" , "<" , ">" };

//Array of Char identifiers for symbolic operations
static const char symExpr[] =
{ '+', '-', '*' };

//Array of all symbols
static const string allOp[] =
{ "==", "!=", "<=", ">=" , "<" , ">" , "+", "-", "*"};

const string sError = "ERR:: INVALID INPUT";

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
    while(!fhIn.eof() /*&& iCount < 20*/)
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

    //Output the line we are working with so we know we have the parsing correct
    printf("%s\n", sLineIn.c_str());
    if (checkParenthesis(sLineIn))
    {
        if (findCreateTable(sLineIn))
        {
            printf("| CREATE TABLE was found in this line, executed.\n");
        }
        else if (findInsertInto(sLineIn))
        {
            printf("| INSERT INTO was found in this line, executed.\n");
        }
        else if (findDeleteFrom(sLineIn))
        {
            printf("| DELETE FROM was found in this line, executed.\n");
        }
        else if (findUpdate(sLineIn))
        {
            printf("| UPDATE was found in this line, executed.\n");
        }
        else if (findShow(sLineIn))
        {
            printf("| SHOW was found in this line, executed.\n");
        }
        else if (findWrite(sLineIn))
        {
            printf("| WRITE was found in this line, executed.\n");
        }
        else if (findOpen(sLineIn))
        {
            printf("| OPEN was found in this line, executed.\n");
        }
        else if (findClose(sLineIn))
        {
            printf("| CLOSE was found in this line, executed.\n");
        }
        else if (findExit(sLineIn))
        {
            printf("| EXIT was found in this line, executed.\n");
        }
        else if (findArrow(sLineIn))
        {
            printf("| <- was found in this line, executed.\n");
        }
        else
        {
            printf("| None of the lines executed\n");
        }
    }
    else
    {
        printf("| The line is incorrect\n");
    }
    
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
        vReturn.push_back(sLineIn.substr(iPosStart,iPosEnd-iPosStart));
        iPosStart = iPosEnd+1;
        iCount++;
    }

    //clean up the words that were seperated out
    for (int i = 0; i < vReturn.size(); ++i)
    {
        vReturn[i] = cleanSpaces(vReturn[i]);
    }

    return vReturn;
}

/*******************************************************************************
Takes in a string, parses it, and creates a vector of strings to send back
*******************************************************************************/   
vector< tuple<int, string> > Parser::createRowVector (string sLineIn)
{
    vector< tuple<int, string> > vRowOut;
    vector<string> vRowAttributes = createVector(sLineIn);

    for (int i = 0; i < vRowAttributes.size(); i++)
    {
        int iColIndex = i;
        string sName = vRowAttributes[i];

        vRowOut.push_back(make_tuple(iColIndex, sName));
    }
    return vRowOut;
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
        if (isalnum(sLineIn[i]) || sLineIn[i] == '_')
        {
            sOut += sLineIn[i];
        }
    }

    return sOut;
}

/*******************************************************************************
Function that sees if CREATE TABLE is in the string and executes the command
correct format = CREATE TABLE () PRIMARY KEY ()
*******************************************************************************/ 
bool Parser::findCreateTable(string sLineIn)
{
    size_t iPosStart = sLineIn.find("CREATE TABLE");
    
    if (iPosStart!=std::string::npos)
    {
        size_t iPosEnd = sLineIn.find("(",iPosStart+1);
        
        if (iPosEnd!=std::string::npos)
        {
            //get the table name
            string sTableName = sLineIn.substr(iPosStart+CREATE_TABLE_SIZE,
                iPosEnd-CREATE_TABLE_SIZE-1);
        
            iPosStart = iPosEnd;
            iPosEnd = sLineIn.find("PRIMARY KEY",iPosStart+1);
            
            if (iPosEnd!=std::string::npos)
            {
                //get the column names
                string sColumns = sLineIn.substr(iPosStart,
                    iPosEnd-CREATE_TABLE_SIZE-PRIMARY_KEY_SIZE+1);

                iPosStart = iPosEnd;
                iPosEnd = sLineIn.find(")",iPosStart+1);

                if (iPosEnd!=std::string::npos)
                {
                    //get the primary keys
                    string sPrimaryKeys = sLineIn.substr(iPosStart+PRIMARY_KEY_SIZE,
                    iPosEnd-PRIMARY_KEY_SIZE);

                    //remove the spaces from the name of the table
                    sTableName = cleanSpaces(sTableName);

                    //call the create table function after the helper functions
                    e.createTable(sTableName,createColVector(sColumns),
                        createVector(sPrimaryKeys));

                    return true;
                }
            }
        }
    }

    return false;
}

/*******************************************************************************
Function that sees if INSERT INTO is in the string and executes the command
handles both INSERT FROM and INSERT FROM RELATION
*******************************************************************************/ 
bool Parser::findInsertInto(string sLineIn)
{
    size_t iPosStart = sLineIn.find("INSERT INTO"); 

    if (iPosStart!=std::string::npos)                                       
    {
        size_t iPosEnd1 = sLineIn.find("VALUES FROM RELATION",iPosStart+1);
        size_t iPosEnd2 = sLineIn.find("VALUES FROM",iPosStart+1);

        //Execute if values from relation is found
        if (iPosEnd1!=std::string::npos)
        {
            //Get the name of the table from the string
            string sTableNameOut = sLineIn.substr(iPosStart+VAL_FROM_REL_SIZE,
                iPosEnd1-VAL_FROM_REL_SIZE-2);
            sTableNameOut = cleanSpaces(sTableNameOut);

            //reposition the iterators to get the row values
            iPosStart = iPosEnd1 + 1;
            iPosEnd1 = sLineIn.find("(");

            if (iPosEnd1!=std::string::npos)
            {
                //Get the row attributes from the string
                string sTableNameIn = sLineIn.substr(iPosStart+VAL_FROM_REL_SIZE,
                    iPosEnd1-VAL_FROM_REL_SIZE-2);
                sTableNameIn = cleanSpaces(sTableNameIn);

                printf("WE NEED TO WORK ON THIS PART\n");              //<-------------------------- tree
                //Clean up and add the row to the table
                //e.addRow(sTableNameOut, createRowVector(sRow));

                return false;
            }
        }
        //Execute if values from is found
        else if(iPosEnd2!=std::string::npos)
        {
            //Get the name of the table from the string
            string sTableName = sLineIn.substr(iPosStart+VALUES_FROM_SIZE,
                iPosEnd2-VALUES_FROM_SIZE-2);
            sTableName = cleanSpaces(sTableName);

            //reposition the iterators to get the row values
            iPosStart = iPosEnd2 + 1;
            iPosEnd2 = sLineIn.find(")");

            if (iPosEnd2!=std::string::npos)
            {
                //Get the row attributes from the string
                string sRow = sLineIn.substr(iPosStart+VALUES_FROM_SIZE,
                    iPosEnd2-VALUES_FROM_SIZE-2);
                
                //Clean up and add the row to the table
                e.addRow(sTableName, createRowVector(sRow));

                return true;
            }
        }
    }  

    return false;
}

/*******************************************************************************
Function that sees if DELETE FROM is in the string and executes the command
*******************************************************************************/ 
bool Parser::findDeleteFrom(string sLineIn)
{
    size_t iPosStart = sLineIn.find("DELETE FROM");
    
    if (iPosStart!=std::string::npos)
    {
        size_t iPosEnd = sLineIn.find("WHERE",iPosStart+1);
        
        if (iPosEnd!=std::string::npos)
        {
            //get the table name
            string sTableName = sLineIn.substr(iPosStart+DELETE_FROM_SIZE,
                iPosEnd-DELETE_FROM_SIZE-2);

            sTableName = cleanSpaces(sTableName);            //<----------------------------

            iPosStart = iPosEnd;

            return true;
        }
    }

    return false;
}

/*******************************************************************************
Function that sees if Update is in the string and executes the command
*******************************************************************************/ 
bool Parser::findUpdate(string sLineIn)
{
    size_t iPosStart = sLineIn.find("UPDATE");
    
    if (iPosStart!=std::string::npos)
    {
        size_t iPosEnd = sLineIn.find("SET",iPosStart+1);
        
        if (iPosEnd!=std::string::npos)
        {
            //get the table name
            string sTableName = sLineIn.substr(iPosStart+UPDATE_SIZE+1,
                iPosEnd-UPDATE_SIZE-SET_SIZE);

            sTableName = cleanSpaces(sTableName);   //<------------------------------------

            iPosStart = iPosEnd;

            return true;
        }
    }

    return false;
}

/*******************************************************************************
Function that sees if SHOW is in the string and executes the command
*******************************************************************************/ 
bool Parser::findShow(string sLineIn)
{
    size_t iPosStart = sLineIn.find("SHOW"); 

    if (iPosStart!=std::string::npos)                                       
    {
        //Get the name of the table from the string
        string sTableName = sLineIn.substr(iPosStart+OPEN_EXIT_SHOW_SIZE);
        sTableName = cleanSpaces(sTableName);
        
        //call the function to display table
        e.displayTable(sTableName);

        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
Function that sees if WRITE is in the string and executes the command
*******************************************************************************/ 
bool Parser::findWrite(string sLineIn)
{
    size_t iPosStart = sLineIn.find("WRITE"); 

    if (iPosStart!=std::string::npos)                                       
    {
        //Get the name of the table from the string
        string sTableName = sLineIn.substr(iPosStart+WRITE_CLOSE_SIZE);
        sTableName = cleanSpaces(sTableName);
        
        //call the function to display table
        e.writeTable(sTableName);

        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
Function that sees if OPEN is in the string and executes the command
*******************************************************************************/ 
bool Parser::findOpen(string sLineIn)
{
    size_t iPosStart = sLineIn.find("OPEN"); 

    if (iPosStart!=std::string::npos)                                       
    {
        //Get the name of the table from the string
        string sTableName = sLineIn.substr(iPosStart+WRITE_CLOSE_SIZE);
        sTableName = cleanSpaces(sTableName);
        
        //call the function to display table
        e.openTable(sTableName);        

        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
Function that sees if CLOSE is in the string and executes the command
*******************************************************************************/ 
bool Parser::findClose(string sLineIn)
{
    size_t iPosStart = sLineIn.find("CLOSE"); 

    if (iPosStart!=std::string::npos)                                       
    {
        //Get the name of the table from the string
        string sTableName = sLineIn.substr(iPosStart+WRITE_CLOSE_SIZE);
        sTableName = cleanSpaces(sTableName);
        
        //call the function to display table
        e.closeTable(sTableName);             

        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
Function that sees if EXIT is in the string and executes the command
*******************************************************************************/ 
bool Parser::findExit(string sLineIn)
{
    size_t iPosStart = sLineIn.find("EXIT"); 

    if (iPosStart!=std::string::npos)                                       
    {
        //WE HAVE TO EXIT SOMETHING HERE?
        printf("Exiting..\n");
        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
Function that sees if the parenthesis are balanced in a line
*******************************************************************************/ 
bool Parser::checkParenthesis(string sLineIn)
{
    int iBalance = 0;

    for (int i = 0; i < sLineIn.length(); ++i)
    {
        if (sLineIn[i] == '(')
        {
            iBalance++;
        }
        else if (sLineIn[i] == ')')
        {
            iBalance--;
        }
        if (iBalance < 0)
        {
            return false;
        }
    }

    if (iBalance == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
Function that sees if <- is in the string and executes the command
*******************************************************************************/ 
bool Parser::findArrow(string sLineIn)
{
    size_t iPosStart = sLineIn.find("<-"); 

    if (iPosStart!=std::string::npos)                                       
    {
        string sTableNameOut = sLineIn.substr(0, iPosStart);
        sTableNameOut = cleanSpaces(sTableNameOut);
        printf("THE TABLE NAME IS %s\n", sTableNameOut.c_str());
        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
Function that finds the <- and returns the string of everything after it.
*******************************************************************************/ 
string Parser::getAfterArrow(string sLineIn)
{
    size_t iPosStart = sLineIn.find("<-"); 
    if (iPosStart!=std::string::npos)                                       
    {
        string sAfterArrow = sLineIn.substr(iPosStart + 2);
        sAfterArrow = cleanSpaces(sAfterArrow);
        printf("THE PARAMETERS ARE %s\n", sAfterArrow.c_str());
        return sAfterArrow;
    }
    else
    {
        return sError;
    }
}

/*******************************************************************************
Function that inserts everything after <- into a tree.
*******************************************************************************/ 
//Update function may need another function to parse because <- operator is not present
//and there can be cases of multiple conditions. May modify this function later for that case
//if needs be.
/*Parser::treeNode * Parser::createTree(string sLineIn)
{
	string sParameters = getAfterArrow(sLineIn);
	treeNode *nodeStart;
	treeNode *nodeA;
	treeNode *nodeB;
	string sTemp;
	if( sParameters == sError ) //Invalid Input Checking
	{	
			cout << "Invalid Parameters" << endl;
			return NULL;
	}
	
	
	for(int i = 0; i < sLineIn.size(); i++)
	{
			if(isalpha(sLineIn[i]))
			{
				sTemp = sTemp + sLineIn[i];
			}
	}
			//Adding values to tree.... Needs work.
			//Need to first identify precedence... Which identifier should be done first
			//before the others. Least precedence would be name of table.

			//Highest precedence should be non-symbolic operations, such as selection,
			//followed by symbolic operations, then symbolic comparator, and then
			//values/names.
			
			//We will need multiple tree check functions in order to insert the values into
			//the tree in the right order...
			//There should be a separate function that for each operation that will be
			//looked for and then those values will be inserted into the tree first.
			
			//Need a function to determine whether or not a set of parenthesis are
			//part of an operation. Non-operational parenthesis will determine highest
			//precedence...
			
			return nodeStart;

	

}*/

vector<string> Parser::makeTokens(string sLineIn)
{
		vector<string> someTokens;
		string sTemp = "";
		string sSymTemp = "";
		for(int i = 0; i < sLineIn.size(); i++)
		{
				if(isalnum(sLineIn[i]) || sLineIn[i] == '_')
				{
						if(sSymTemp != "")
						{
								someTokens.push_back(sSymTemp);
								sSymTemp = "";
						}
						sTemp = sTemp + sLineIn[i];
						
				}
				if(!isalnum(sLineIn[i]) && sLineIn[i] != '_')
				{
						if(sTemp != "")
						{
						someTokens.push_back(sTemp);
						sTemp = "";
						}
						if(sLineIn[i] == ')' || sLineIn[i] == '(')
						{
								sSymTemp = sLineIn[i];
								someTokens.push_back(sSymTemp);
								sSymTemp = "";
						}
						else
						{
								sSymTemp = sSymTemp + sLineIn[i];
						}
						
				}
				
		}
		return someTokens;
}

/*******************************************************************************
Function that traverses the current tree and prints out values
*******************************************************************************/

void Parser::traversal(treeNode *start)
{
	if( start != NULL ){
		traversal(start->leftChild);	//Visits Left subtree
		cout << start->data;  // Displays Data
		traversal(start->rightChild);    //Visits Right Subtree
	}

}
















