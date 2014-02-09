/*******************************************************************************
    File: Engine.cpp

    Authors: Gustavo Pedroso UIN: 423002834
             Levi Clark      UIN:
             Terry Chen      UIN: 121007055
             Daniel He       UIN: 620006827

            Department of Computer Science
            Texas A&M University
    Date  : 2/2/2014

    Formatting: * 80 pt width is used for code, for the most part
                * Hungarian naming convention is used for variables
                * Comments are applied for explanations
                * Spacing and brackets are applied for readability

	This file contains the implementation for the engine
*******************************************************************************/

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Engine.h"
using namespace std;

/*******************************************************************************
  This function will take in a vector of column names and trailing primary keys,
  and an integer specifying how many columns are in the vector.
*******************************************************************************/
void Engine::createTable(string sTableNameIn, 
  vector< tuple<string,string> > vColumnNamesIn)
{
  Table t(sTableNameIn);

  for (int i = 0; i < vColumnNamesIn.size(); ++i)
  {
    string sColumnNameIn = get<0>(vColumnNamesIn[i]);
    string sColumnTypeIn = get<1>(vColumnNamesIn[i]);
    t.addColumn(make_tuple(i,sColumnNameIn), sColumnTypeIn);
  }
  vTableList.push_back(t);

}

/*******************************************************************************
  Remove a table from the list
*******************************************************************************/
void Engine::dropTable(string sTableNameIn)
{
  for (int i = 0; i < vTableList.size(); ++i)
  {
    if (vTableList[i].getTableName() == sTableNameIn)
    {
      vTableList.erase(vTableList.begin() + 1);
    }
  }
}

/*******************************************************************************
  Selects the tuples in a relation that satisfy a particular condition.
  sTableNameIn is going to be the existing table we are working with.
  sTableNameOut is the name we will give the newly created table.
  sOperator will be the operator to be used on sColumn and sAttribute
*******************************************************************************/
void Engine::selection(string sTableNameIn, string sTableNameOut, 
                        string sOperator, string sColumn, string sAttribute)
{
  //Create a new table to send back 
  Table tNewTable(sTableNameOut);
  vector<string> vColumnValues;

  for (int i = 0; i < vTableList.size(); ++i)
  { 
    Table tCurrentTable = vTableList[i];

    //Execute if the table is found in the list
    if (tCurrentTable.getTableName() == sTableNameIn)
    {
      //Input the column names and types into the new table, then determine
      //the rows to copy over
      vector< tuple<int,string> > vNames = tCurrentTable.getColumnNames();
      vector<string> vTypes = tCurrentTable.getColumnTypes();

      for (int i = 0; i < vNames.size(); ++i)
      {
        //Add column to new table
        tNewTable.addColumn(vNames[i], vTypes[i]);
      }
      
      //See if the column exists in the table
      tuple<int,string> tCurrentColumn = tCurrentTable.getColumnIndex(sColumn);
      int iColumnIndex = get<0>(tCurrentColumn);

      if (iColumnIndex == -1)
      {
        printf("| The column does not exist.\n");
      }
      else
      {
        vColumnValues = tCurrentTable.getColumnValues(iColumnIndex);

        if (sOperator == "==")
        {
          for (int x = 0; x < vColumnValues.size(); ++x)
          {
            //Execute if the attribute satisfies the condition
            if (sAttribute == vColumnValues[x])
            {
              //push back the row into the new table
              tNewTable.addRow(tCurrentTable.getRow(x));

            }
          }
        }
        else if (sOperator == ">=")
        {
          for (int x = 0; x < vColumnValues.size(); ++x)
          {
            //Execute if the attribute satisfies the condition
            if (sAttribute >= vColumnValues[x])
            {
              //push back the row into the new table
              tNewTable.addRow(tCurrentTable.getRow(x));

            }
          }
        }
        else if (sOperator == "<=")
        {
          for (int x = 0; x < vColumnValues.size(); ++x)
          {
            //Execute if the attribute satisfies the condition
            if (sAttribute <= vColumnValues[x])
            {
              //push back the row into the new table
              tNewTable.addRow(tCurrentTable.getRow(x));

            }
          }
        }
        else if (sOperator == ">")
        {
          for (int x = 0; x < vColumnValues.size(); ++x)
          {
            //Execute if the attribute satisfies the condition
            if (sAttribute > vColumnValues[x])
            {
              //push back the row into the new table
              tNewTable.addRow(tCurrentTable.getRow(x));

            }
          }
        }
        else if (sOperator == "<")
        {
          for (int x = 0; x < vColumnValues.size(); ++x)
          {
            //Execute if the attribute satisfies the condition
            if (sAttribute < vColumnValues[x])
            {
              //push back the row into the new table
              tNewTable.addRow(tCurrentTable.getRow(x));

            }
          }
        }
        else
        {
          printf("| ERROR, invalid operator.\n");
        }
      }
    }
  }

  vTableList.push_back(tNewTable);
} 

































