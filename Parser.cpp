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
{ "select", "project", "rename", "natural-join" };

//Array of String identifiers for symbolic comparisons
static const string operant[] =
{ "==", "!=", "<=", ">=", "<", ">" };

//Array of Char identifiers for symbolic operations
static const char symExpr[] =
{ '+', '-', '*' };

//Array of all symbols
static const string allOp[] =
{ "==", "!=", "<=", ">=", "<", ">", "+", "-", "*" };

const string sError = "ERR:: INVALID INPUT";

/*******************************************************************************
 Read a file and call parse function on each line read
 *******************************************************************************/
bool Parser::readFromFile(string sFileName)
{
  ifstream fhIn; //file handler
  string sLineIn; //Hold the line that is read off file
  int iCount = 0;

  //Open the file and validate it opened properly
  fhIn.open(sFileName.c_str());

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
  while (!fhIn.eof() /*&& iCount < 20*/)
  {
    //Keep a record of lines for writing to file
    vValuesRead.push_back(sLineIn);

    //Parse the line of text and interpret it
    parse(sLineIn);

    //Prepare to loop again, read in next record & update
    getline(fhIn, sLineIn, ';');

    //Increase the counter
    iCount++;
  }

  //Close the file
  fhIn.close();
  return true;
}

/*******************************************************************************
 Parse the line in and call the appropiate functions
 *******************************************************************************/
void Parser::parse(string sLineIn)
{
  //Declare and initialize variables
  string sTemp;

  //Output the line we are working with so we know we have the parsing correct
  printf("\n%s\n", sLineIn.c_str());

  if (sLineIn[0] == '\n')
  {
    sLineIn.erase(0, 1);
  }

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
 Writes the relation information to a file
 *******************************************************************************/
bool Parser::writeToFile(string sFilename)
{
  std::fstream outputFile;
  //open the file and write the contents of the class vector in there
  outputFile.open(sFilename + ".db");
  for (int i = 0; i < vValuesRead.size(); ++i)
  {
    outputFile << vValuesRead[i] << '\n';
  }
  outputFile.close();
  return true;
}

/*******************************************************************************
 Takes in a string, parses it, and creates a vector of columns to send back
 *******************************************************************************/
vector<tuple<string, string, bool> > Parser::createColVector(string sLineIn)
{
  //<type, name, primarykey>
  vector < tuple<string, string, bool> > vColVectorOut;
  vector < string > vCol = createVector(sLineIn);

  for (int i = 0; i < vCol.size(); i++)
  {
    string sType, sName;

    //See what type of column it is and create a tuple with the name & type
    size_t iVar = vCol[i].find("VARCHAR");

    if (iVar != std::string::npos)
    {
      sType = "string";
      sName = vCol[i].substr(0, iVar);
    }

    size_t iInt = vCol[i].find("INTEGER");

    if (iInt != std::string::npos)
    {
      sType = "int";
      sName = vCol[i].substr(0, iInt);
    }

    //push the newly created column into the vector to send back
    vColVectorOut.push_back(make_tuple(sName, sType, false));

  }
  return vColVectorOut;
}

/*******************************************************************************
 Takes in a string, parses it, and creates a vector of strings to send back
 *******************************************************************************/
vector<string> Parser::createVector(string sLineIn)
{
  vector < string > vReturn;
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
    iPosEnd = sLineIn.find(",", iPosStart + 1);
    vReturn.push_back(sLineIn.substr(iPosStart, iPosEnd - iPosStart));
    iPosStart = iPosEnd + 1;
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
vector<tuple<int, string> > Parser::createRowVector(string sLineIn)
{
  vector < tuple<int, string> > vRowOut;
  vector < string > vRowAttributes = createVector(sLineIn);

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
string Parser::cleanSpaces(string sLineIn)
{
  string sOut = "";
  for (int i = 0; i < sLineIn.length(); ++i)
  {
    //Append the value from the string into the return string, if its alpha
    if (isalnum(sLineIn[i]) || sLineIn[i] == '_' || sLineIn[i] == '/')
    {
      sOut += sLineIn[i];
    }
  }

  return sOut;
}

/*******************************************************************************
 Remove any additional spaces from the string
 *******************************************************************************/
string Parser::removeSpaces(string sLineIn)
{
  string sOut = "";
  for (int i = 0; i < sLineIn.length(); ++i)
  {
    //Apend any values that are not spaces
    if (sLineIn[i] != ' ')
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

  //Execute if create table was found in the string
  if (iPosStart != std::string::npos)
  {
    size_t iPosEnd = sLineIn.find("(", iPosStart + 1);

    //execute if '(' was found in the string
    if (iPosEnd != std::string::npos)
    {
      //get the table name
      string sTableName = sLineIn.substr(iPosStart + CREATE_TABLE_SIZE,
          iPosEnd - CREATE_TABLE_SIZE - 1);

      //reposition the position values
      iPosStart = iPosEnd;
      iPosEnd = sLineIn.find("PRIMARY KEY", iPosStart + 1);

      //Execute if primary key was found in string
      if (iPosEnd != std::string::npos)
      {
        //get the column names
        string sColumns = sLineIn.substr(iPosStart,
            iPosEnd - CREATE_TABLE_SIZE - PRIMARY_KEY_SIZE + 1);

        //reposition the position values
        iPosStart = iPosEnd;
        iPosEnd = sLineIn.find(")", iPosStart + 1);

        //execute if ')' was found in the string
        if (iPosEnd != std::string::npos)
        {
          //get the primary keys
          string sPrimaryKeys = sLineIn.substr(iPosStart + PRIMARY_KEY_SIZE,
              iPosEnd - PRIMARY_KEY_SIZE);

          //remove the spaces from the name of the table
          sTableName = cleanSpaces(sTableName);

          //call the create table function after the helper functions
          e.createTable(sTableName, createColVector(sColumns),
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

  if (iPosStart != std::string::npos)
  {
    size_t iPosEnd1 = sLineIn.find("VALUES FROM RELATION", iPosStart + 1);
    size_t iPosEnd2 = sLineIn.find("VALUES FROM", iPosStart + 1);

    //Execute if values from relation is found
    if (iPosEnd1 != std::string::npos)
    {
      //Get the name of the table from the string
      string sTableNameOut = sLineIn.substr(iPosStart + VAL_FROM_REL_SIZE,
          iPosEnd1 - VAL_FROM_REL_SIZE);
      sTableNameOut = cleanSpaces(sTableNameOut);
      cout << sTableNameOut << endl;

      //reposition the iterators to get the row values
      iPosStart = iPosEnd1 + 1;
      iPosEnd1 = sLineIn.find("(");

      if (iPosEnd1 != std::string::npos)
      {
        //Get the row attributes from the string
        string sTableNameIn = sLineIn.substr(iPosStart + VAL_FROM_REL_SIZE,
            iPosEnd1 - VAL_FROM_REL_SIZE - 2);
        sTableNameIn = cleanSpaces(sTableNameIn);

        iPosStart = iPosEnd1;

        string sRestOfLine = sLineIn.substr(iPosStart, iPosEnd1);

        sRestOfLine = removeSpaces(sRestOfLine);

        //WE NEED THE TREE HERE!!!!!!!!!

        //Clean up and add the row to the table
        //e.addRow(sTableNameOut, createRowVector(sRow));

        return false;
      }
    }
    //Execute if values from is found
    else if (iPosEnd2 != std::string::npos)
    {
      //Get the name of the table from the string
      string sTableName = sLineIn.substr(iPosStart + VALUES_FROM_SIZE,
          iPosEnd2 - VALUES_FROM_SIZE);
      sTableName = cleanSpaces(sTableName);
      cout << sTableName << endl;

      //reposition the iterators to get the row values
      iPosStart = iPosEnd2 + 1;
      iPosEnd2 = sLineIn.find(")");

      if (iPosEnd2 != std::string::npos)
      {
        //Get the row attributes from the string
        string sRow = sLineIn.substr(iPosStart + VALUES_FROM_SIZE,
            iPosEnd2 - VALUES_FROM_SIZE - 2);

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

  vector < string > vTokens = makeTokens(sLineIn);
  vector < string > vCondition;

  //getting conditional expression from tokens;
  for (int i = 0; i < vTokens.size(); i++)
  {
    if (vTokens[i] == "WHERE")
    {
      i++;
      while (i < vTokens.size())
      {
        vCondition.push_back(vTokens[i]);
        i++;
      }
    }
  }
  removeBlankTokens (vCondition);
  //printing conditional tokens for bug testing;
  /*for(int i =0; i<vCondition.size(); i++)
   {
   cout << vCondition[i] << " ";
   }*/

  if (iPosStart != std::string::npos)
  {
    size_t iPosEnd = sLineIn.find("WHERE", iPosStart + 1);

    if (iPosEnd != std::string::npos)
    {
      //get the table name
      string sTableName = sLineIn.substr(iPosStart + DELETE_FROM_SIZE,
          iPosEnd - DELETE_FROM_SIZE - 1);

      sTableName = cleanSpaces(sTableName);

      iPosStart = iPosEnd;

      string sRestOfLine = sLineIn.substr(iPosStart + WHERE_SIZE,
          iPosEnd - WHERE_SIZE);

      sRestOfLine = removeSpaces(sRestOfLine);

      vector < string > vCheck = makeTokens(sRestOfLine);
      if (vCheck[2] == "==")
      {
        sRestOfLine = vCheck[0] + vCheck[1] + "!=" + vCheck[3] + vCheck[4];
      }
      else if (vCheck[2] == "<=")
      {
        sRestOfLine = vCheck[0] + vCheck[1] + ">" + vCheck[3] + vCheck[4];
      }
      else if (vCheck[2] == ">=")
      {
        sRestOfLine = vCheck[0] + vCheck[1] + "<" + vCheck[3] + vCheck[4];
      }
      else if (vCheck[2] == ">")
      {
        sRestOfLine = vCheck[0] + vCheck[1] + "<=" + vCheck[3] + vCheck[4];
      }
      else if (vCheck[2] == "<")
      {
        sRestOfLine = vCheck[0] + vCheck[1] + ">=" + vCheck[3] + vCheck[4];
      }

      select(sTableName, "select" + sRestOfLine + sTableName);

      //WE NEED THE TREE HERE!!!!!!!

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

  vector < string > vTokens = makeTokens(sLineIn);
  vector < string > vCondition;

  //getting conditional expression from tokens;
  for (int i = 0; i < vTokens.size(); i++)
  {
    if (vTokens[i] == "WHERE")
    {
      i++;
      while (i < vTokens.size())
      {
        vCondition.push_back(vTokens[i]);
        i++;
      }
    }
  }
  removeBlankTokens (vCondition);
  //printing conditional tokens for bug testing;
  /*for(int i =0; i<vCondition.size(); i++)
   {
   cout << vCondition[i] << " ";
   }*/

  if (iPosStart != std::string::npos)
  {
    size_t iPosEnd = sLineIn.find("SET", iPosStart + 1);

    if (iPosEnd != std::string::npos)
    {
      //get the table name
      string sTableName = sLineIn.substr(iPosStart + UPDATE_SIZE + 1,
          iPosEnd - UPDATE_SIZE - SET_SIZE);

      sTableName = cleanSpaces(sTableName);

      iPosStart = iPosEnd;
      size_t iPosEnd = sLineIn.find("WHERE", iPosStart + 1);

      if (iPosEnd != std::string::npos)
      {
        //Get the values
        string sValues = sLineIn.substr(iPosStart + UPDATE_SIZE - 1,
            iPosEnd - UPDATE_SIZE - SET_SIZE - WHERE_SIZE - 5);
        sValues = removeSpaces(sValues);
        iPosStart = iPosEnd;

        //Get the condition
        string sCondition = sLineIn.substr(iPosStart + UPDATE_SIZE,
            iPosEnd - UPDATE_SIZE - SET_SIZE - WHERE_SIZE);
        sCondition = removeSpaces(sCondition);

        //WE NEED THE TREE HERE!!!!!

        return true;
      }
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

  if (iPosStart != std::string::npos)
  {
    //Get the name of the table from the string
    string sTableName = sLineIn.substr(iPosStart + OPEN_EXIT_SHOW_SIZE);
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

  if (iPosStart != std::string::npos)
  {
    //Get the name of the table from the string
    string sTableName = sLineIn.substr(iPosStart + WRITE_CLOSE_SIZE);
    sTableName = cleanSpaces(sTableName);

    //call the function to display table
    writeToFile(sTableName);

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

  if (iPosStart != std::string::npos)
  {
    //Get the name of the table from the string
    string sTableName = sLineIn.substr(iPosStart + WRITE_CLOSE_SIZE);
    sTableName = cleanSpaces(sTableName);

    //call the function to display table
    readFromFile(sTableName + ".db");

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

  if (iPosStart != std::string::npos)
  {
    //Get the name of the table from the string
    string sTableName = sLineIn.substr(iPosStart + WRITE_CLOSE_SIZE);
    sTableName = cleanSpaces(sTableName);

    vValuesRead.clear();

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

  if (iPosStart != std::string::npos)
  {
    printf("Exiting.. \n");

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

  if (iPosStart != std::string::npos)
  {
    string sTableNameOut = sLineIn.substr(0, iPosStart);
    sTableNameOut = cleanSpaces(sTableNameOut);

    string sRestOfLine = sLineIn.substr(iPosStart + DOUBLE_OP_SIZE);
    sRestOfLine = removeSpaces(sRestOfLine);

    op(sTableNameOut, sRestOfLine);
    select(sTableNameOut, sRestOfLine);
    projection(sRestOfLine, sTableNameOut);
    rename(sRestOfLine, sTableNameOut);

    //WE NEED THE TREE HERE!!!!!!!

    return true;
  }
  else
  {
    return false;
  }
}

/*******************************************************************************
 Handle the operation from the query
 *******************************************************************************/
void Parser::op(string sNewTableName, string sRestOfLine)
{
  size_t iPosAdd = sRestOfLine.find("+");
  size_t iPosSub = sRestOfLine.find("-");
  size_t iPosMul = sRestOfLine.find("*");

  if (iPosAdd != std::string::npos)
  {
    string sFirst = sRestOfLine.substr(0, iPosAdd);
    sFirst = cleanSpaces(sFirst);

    string sLast = sRestOfLine.substr(iPosAdd + 1);
    sLast = removeSpaces(sLast);

    e.setUnion(sFirst, sLast, sNewTableName);
  }
  else if (iPosSub != std::string::npos)
  {
    string sFirst = sRestOfLine.substr(0, iPosSub);
    sFirst = cleanSpaces(sFirst);

    string sLast = sRestOfLine.substr(iPosSub + 1);
    sLast = removeSpaces(sLast);

    e.setDifference(sFirst, sLast, sNewTableName);
  }
  else if (iPosMul != std::string::npos)
  {
    string sFirst = sRestOfLine.substr(0, iPosMul);
    sFirst = cleanSpaces(sFirst);

    string sLast = sRestOfLine.substr(iPosMul + 1);
    sLast = removeSpaces(sLast);
    e.crossProduct(sFirst, sLast, sNewTableName);
  }
}

/*******************************************************************************
 Function that does the projection
 *******************************************************************************/
void Parser::projection(string sRestOfLine, string sTableNameOut)
{
  size_t iPos = sRestOfLine.find("project");

  if (iPos != std::string::npos)
  {
    size_t iParenth1 = sRestOfLine.find("(");
    size_t iParenth2 = sRestOfLine.find(")", iParenth1 + 1);
    string sColNames = sRestOfLine.substr(iParenth1, iParenth2 - iParenth1);
    string sTableNameIn = cleanSpaces(sRestOfLine.substr(iParenth2 + 1));
    vector < string > vColVector = createVector(sColNames);
    e.projection(sTableNameIn, sTableNameOut, vColVector);
  }
}

/*******************************************************************************
 Function that does the rename
 *******************************************************************************/
void Parser::rename(string sRestOfLine, string sTableNameOut)
{
  size_t iPos = sRestOfLine.find("rename");

  if (iPos != std::string::npos)
  {
    size_t iParenth1 = sRestOfLine.find("(");
    size_t iParenth2 = sRestOfLine.find(")", iParenth1 + 1);
    string sColNames = sRestOfLine.substr(iParenth1, iParenth2 - iParenth1);
    string sTableNameIn = cleanSpaces(sRestOfLine.substr(iParenth2 + 1));
    vector < string > vColVector = createVector(sColNames);
    e.reNaming(sTableNameIn, sTableNameOut, vColVector);
  }
}

/*******************************************************************************
 Function that does the select
 *******************************************************************************/
void Parser::select(string sNewTableName, string sRestOfLine)
{
  size_t iPos = sRestOfLine.find("select");

  if (iPos != std::string::npos)
  {
    size_t iParenth1 = sRestOfLine.find("(");
    size_t iParenth2 = sRestOfLine.find(")", iParenth1 + 1);
    string sValues = removeSpaces(
        sRestOfLine.substr(iParenth1 + 1, iParenth2 - iParenth1));
    string sTableNameIn = cleanSpaces(sRestOfLine.substr(iParenth2 + 1));
    vector < string > vValues = makeTokens(sValues);

    if (sTableNameIn == sNewTableName)
    {
      if (vValues[0] == "Date")
      {
        e.selection(sNewTableName, sTableNameIn + " 2", vValues[1], vValues[0],
            vValues[2] + vValues[3] + vValues[4] + vValues[5] + vValues[6]);
      }
      else
      {
        e.selection(sNewTableName, sTableNameIn + " 2", vValues[1], vValues[0],
            vValues[2]);
      }

      //delete old table
      e.dropTable(sTableNameIn);

      //rename new table to old name
      e.renameTable(sTableNameIn + " 2", sNewTableName);
    }
    else
    {
      if (vValues[0] == "Date")
      {
        e.selection(sTableNameIn, sNewTableName, vValues[1], vValues[0],
            vValues[2] + vValues[3] + vValues[4] + vValues[5] + vValues[6]);
      }
      else
      {
        e.selection(sTableNameIn, sNewTableName, vValues[1], vValues[0],
            vValues[2]);
      }

    }
  }
}

/*******************************************************************************
 Function that finds the <- and returns the string of everything after it.
 *******************************************************************************/
/*
 string Parser::getAfterArrow(string sLineIn)
 {
 size_t iPosStart = sLineIn.find("<-");
 if (iPosStart!=std::string::npos)
 {
 string sAfterArrow = sLineIn.substr(iPosStart + 2);
 sAfterArrow = removeSpaces(sAfterArrow);
 printf("THE PARAMETERS ARE %s\n", sAfterArrow.c_str());
 return sAfterArrow;
 }
 else
 {
 return sError;
 }
 }
 */
/*******************************************************************************
 Function that inserts everything after <- into a tree.
 *******************************************************************************/
//Update function may need another function to parse because <- operator is not 
//present
//and there can be cases of multiple conditions. May modify this function later 
//for that case
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
  vector < string > someTokens;
  string sTemp = "";
  string sSymTemp = "";
  for (int i = 0; i < sLineIn.size(); i++)
  {
    if (isalnum(sLineIn[i]) || sLineIn[i] == '_')
    {
      if (sSymTemp != "")
      {
        someTokens.push_back(sSymTemp);
        sSymTemp = "";
      }
      sTemp = sTemp + sLineIn[i];
    }
    if (!isalnum(sLineIn[i]) && sLineIn[i] != '_')
    {
      if (sTemp != "")
      {
        someTokens.push_back(sTemp);
        sTemp = "";
      }
      if (sLineIn[i] == ')' || sLineIn[i] == '(')
      {
        if (sSymTemp != "")
          someTokens.push_back(sSymTemp);
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
/*
 void Parser::traversal(treeNode *start)
 {
 if( start != NULL ){
 traversal(start->leftChild);	//Visits Left subtree
 cout << start->data;  // Displays Data
 traversal(start->rightChild);    //Visits Right Subtree
 }

 }
 */

void Parser::removeBlankTokens(vector<string> & vTokens)
{
  vector < string > vTemp;
  for (int i = 0; i < vTokens.size(); i++)
  {
    string sTemp = removeSpaces(vTokens[i]);
    if (sTemp != "")
      vTemp.push_back(sTemp);
  }

  vTokens = vTemp;
}

bool isColumnName(string sIn, Table & t);

void comparison(vector<string> & vTokens, int & iTokenIndex, Table & relation)
{
  string operand0;
  string operand1;
  string op;

  string tableName = relation.getTableName();

  if (vTokens[iTokenIndex] == "(")
  {
    iTokenIndex++;
  }

  operand0 = vTokens[iTokenIndex];
  iTokenIndex++;

  op = vTokens[iTokenIndex];
  iTokenIndex++;

  operand1 = vTokens[iTokenIndex];
  iTokenIndex++;

  cout << endl << operand0 << " " << op << " " << operand1 << endl;

  //attribute name and literal
  if (isColumnName(operand0, relation) && !isColumnName(operand1, relation))
  {

    /*e.selection(tableName, tableName + "2", op,  operand0, operand1)
     e.dropTable(tableName);

     //rename new table to old name
     e.renameTable(sTableNameIn + " 2", sNewTableName);*/
  }
  //void Engine::selection(string sTableNameIn, string sTableNameOut,
  // string sOperator, string sColumn, string sAttribute)

}

void Parser::evalCondition(vector<string> vTokens, string relationName)
{
  int iTokenIndex = 0;

  removeBlankTokens(vTokens);
  Table relation = e.getTable(relationName);

  //starting with conjunction
  comparison(vTokens, iTokenIndex, relation);
}

bool isColumnName(string sIn, Table & t)
{
  std::vector < std::tuple<int, std::string, bool, std::string> > vColumnName;

  vColumnName = t.getColumnNames();

  for (int i = 0; i < vColumnName.size(); i++)
  {
    if (get < 1 > (vColumnName[i]) == sIn)
      return true;
  }

  return false;
}
