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

      for (int a = 0; a < vNames.size(); ++a)
      {
        //Add column to new table
        tNewTable.addColumn(vNames[a], vTypes[a]);
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
        //get the values for the column
        vColumnValues = tCurrentTable.getColumnValues(iColumnIndex);

        //get the type of the column
        string sColumnType = vTypes[iColumnIndex];

        for (int x = 0; x < vColumnValues.size(); ++x)
        {
          int iValueToBeTested = atoi(vColumnValues[x].c_str());
          string sValueToBeTested = vColumnValues[x];
          int iAttribute = atoi(sAttribute.c_str());

          if (sOperator == "==")
          {
            if (sColumnType == "string")
            {
              //Execute if the attribute satisfies the condition
              if (sValueToBeTested == sAttribute)
              {
                //push back the row into the new table
                tNewTable.addRow(tCurrentTable.getRow(x));
              }
            }
            else if (sColumnType == "int")
            {
              //Execute if the attribute satisfies the condition
              if (iValueToBeTested == iAttribute)
              {
                //push back the row into the new table
                tNewTable.addRow(tCurrentTable.getRow(x));
              }
            }
            else
            {
              printf("| Type of column invalid\n");
            }
          }
          else if (sOperator == ">=")
          {
            if (sColumnType == "string")
            {
              //Execute if the attribute satisfies the condition
              if (sValueToBeTested >= sAttribute)
              {
                //push back the row into the new table
                tNewTable.addRow(tCurrentTable.getRow(x));
              }
            }
            else if (sColumnType == "int")
            {
              //Execute if the attribute satisfies the condition
              if (iValueToBeTested >= iAttribute)
              {
                //push back the row into the new table
                tNewTable.addRow(tCurrentTable.getRow(x));
              }
            }
            else
            {
              printf("| Type of column invalid\n");
            }
          }
          else if (sOperator == "<=")
          {
            if (sColumnType == "string")
            {
              //Execute if the attribute satisfies the condition
              if (sValueToBeTested <= sAttribute)
              {
                //push back the row into the new table
                tNewTable.addRow(tCurrentTable.getRow(x));
              }
            }
            else if (sColumnType == "int")
            {
              //Execute if the attribute satisfies the condition
              if (iValueToBeTested <= iAttribute)
              {
                //push back the row into the new table
                tNewTable.addRow(tCurrentTable.getRow(x));
              }
            }
            else
            {
              printf("| Type of column invalid\n");
            }
          }
          else if (sOperator == ">")
          {
            if (sColumnType == "string")
            {
              //Execute if the attribute satisfies the condition
              if (sValueToBeTested > sAttribute)
              {
                //push back the row into the new table
                tNewTable.addRow(tCurrentTable.getRow(x));
              }
            }
            else if (sColumnType == "int")
            {
              //Execute if the attribute satisfies the condition
              if (iValueToBeTested > iAttribute)
              {
                //push back the row into the new table
                tNewTable.addRow(tCurrentTable.getRow(x));
              }
            }
            else
            {
              printf("| Type of column invalid\n");
            }
          }
          else if (sOperator == "<")
          {
            if (sColumnType == "string")
            {
              //Execute if the attribute satisfies the condition
              if (sValueToBeTested < sAttribute)
              {
                //push back the row into the new table
                tNewTable.addRow(tCurrentTable.getRow(x));
              }
            }
            else if (sColumnType == "int")
            {
              //Execute if the attribute satisfies the condition
              if (iValueToBeTested < iAttribute)
              {
                //push back the row into the new table
                tNewTable.addRow(tCurrentTable.getRow(x));
              }
            }
            else
            {
              printf("| Type of column invalid\n");
            }
          }
          else
          {
            printf("| ERROR, invalid operator.\n");
          }
        }
      }
    }
  }

  vTableList.push_back(tNewTable);
} 

void Engine::reNaming(vector<string> vNewNames, string sTableName) 
{
  // Find the table in vTableList
  int iTableIndex = -1;
  for (int i = 0; i < vTableList.size(); i++) 
  {
    if (vTableList[i].getTableName() == sTableName) 
    {
      iTableIndex = i;
      break;
    }
  }
  
  if (iTableIndex == -1) 
  {
    cout << "Could not find that table!" << endl;
    return;
  }
  
  Table workingTable = vTableList[iTableIndex];
  
  // Examine whether the supplied names will match the supplied table
  if (vNewNames.size() != workingTable.getColumnNames().size()) 
  {
    cout << "Supplied column names do not match selected table!" << endl;
    return;
  }
  
  string sRenameTableName = workingTable.getTableName() + " renamed";
  vector<string> vColTypes = workingTable.getColumnTypes();
  Table reNamed(sRenameTableName);
  
  // Create a new table with the new supplied column names
  for (int i = 0; i < vNewNames.size(); i++)
  {
    string sColumnNameIn = vNewNames[i];
    string sColumnTypeIn = vColTypes[i];
    reNamed.addColumn(make_tuple(i,sColumnNameIn), sColumnTypeIn);
  }
  
  // Copy row elements from working table to the new renamed table
  vector< vector< tuple<int,string> > > vRows = workingTable.getRows();
  
  for (int i = 0; i < vRows.size(); i++)
  {
    reNamed.addRow(vRows[i]);
  }
  
  vTableList.push_back(reNamed);
}

void Engine::setUnion(string sT1Name, string sT2Name)
{
  // Find the table in vTableList
  int iT1Index = -1;
  int iT2Index = -1;
  for (int i = 0; i < vTableList.size(); i++) 
  {
    if (vTableList[i].getTableName() == sT1Name) 
    {
      iT1Index = i;
    }
    if (vTableList[i].getTableName() == sT2Name) 
    {
      iT2Index = i;
    }
  }
  
  if (iT1Index == -1) 
  {
    cout << "Could not find that first table!" << endl;
    return;
  }
  if (iT2Index == -1) 
  {
    cout << "Could not find that second table!" << endl;
    return;
  }
  
  
  Table workingT1 = vTableList[iT1Index];
  Table workingT2 = vTableList[iT2Index];
  // Check if the tables are compatible/unionizable.   
  if (workingT1.getColumnNames() != workingT2.getColumnNames()) 
  {
    cout << "Union not possible! Tables are different." << endl;
    return;
  }
  if (workingT1.getColumnTypes() != workingT2.getColumnTypes()) 
  {
    cout << "Union not possible! Tables are different." << endl;
    return;
  }
  
  string sUnionTableName = workingT1.getTableName() + " and "
    + workingT2.getTableName() + " union";
  vector< tuple<int, string> > vColNames = workingT1.getColumnNames();
  vector<string> vColTypes = workingT1.getColumnTypes();
  
  // Create a new table, using column names from the supplied table. 
  Table unioned(sUnionTableName);
  for (int i = 0; i < vColNames.size(); i++) 
  {
    string sColumnNameIn = get<1>(vColNames[i]);
    string sColumnTypeIn = vColTypes[i];
    unioned.addColumn(make_tuple(i,sColumnNameIn), sColumnTypeIn);
  }

  // Copy row elements from working table 1.
  vector< vector< tuple<int,string> > > vRows1 = workingT1.getRows();
  
  for (int i = 0; i < vRows1.size(); i++)
  {
    unioned.addRow(vRows1[i]);
  }

  // Ghetto way of adding working table 2 without the duplicates
  vector< vector< tuple<int,string> > > vRows2 = workingT2.getRows();
  bool exists;
  for (int i = 0; i < vRows2.size(); i++) 
  {
    exists = false;
    for (int j = 0; j < vRows1.size(); j++)
    {
      if (vRows1[j] == vRows2[i]) {
        exists = true;
        break;
      }
    }
    if (!exists)
    {
      unioned.addRow(vRows2[i]);
    }
  }
  
  vTableList.push_back(unioned);
}