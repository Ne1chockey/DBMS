/*******************************************************************************
    File: Engine.cpp

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
  compare two tables
*******************************************************************************/
bool Engine::compareTables(string sT1Name, string sT2Name)
{
  for (int i = 0; i < vTableList.size(); ++i)
  {
    Table t1 = vTableList[i];

    //Execute if the first table is found in the list
    if (t1.getTableName() == sT1Name)
    {
      for (int x = 0; x < vTableList.size(); ++x)
      {
        Table t2 = vTableList[x];

        //Execute if the second table is found
        if (t2.getTableName() == sT2Name)
        {
          //Get the columns and types for the tables
          vector< tuple<int,string> > vT1columns = t1.getColumnNames();
          vector< tuple<int,string> > vT2columns = t2.getColumnNames();
          vector<string> vT1types = t1.getColumnTypes();
          vector<string> vT2types = t2.getColumnTypes();

          if (vT1columns.size() != vT2columns.size())
          {
            return false;
          }

          for (int y = 0; y < vT1columns.size(); ++y)
          {
            int iCurrentT1ColIndex = get<0>(vT1columns[y]);
            string sCurrentT1ColName = get<1>(vT1columns[y]);
            
            for (int z = 0; z < vT2columns.size(); ++z)
            {
              int iCurrentT2ColIndex = get<0>(vT2columns[z]);
              string sCurrentT2ColName = get<1>(vT2columns[z]);

              if (iCurrentT1ColIndex == iCurrentT2ColIndex)
              {
                if ((sCurrentT1ColName != sCurrentT2ColName) && (vT1types[y] != vT2types[z]))
                {
                  return false;
                }
                break;
              }
            }
          }
        }
      }
    }
  }
  return true;
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

/*******************************************************************************
  Select of a subset of the attributes of a relation
*******************************************************************************/
void Engine::projection(string sTableNameIn, vector<string> sColumnNamesIn)
{
  //Create a new table to send back 
  Table tNewTable(sTableNameIn + " projection");

  for (int i = 0; i < vTableList.size(); ++i)
  {
    Table tCurrentTable = vTableList[i];

    //Execute if the table is found
    if (tCurrentTable.getTableName() == sTableNameIn)
    {
      //Get the current column names and types and rows
      vector<string> vColTypes = tCurrentTable.getColumnTypes();
      vector< tuple<int,string> > vColNames = tCurrentTable.getColumnNames();
      vector< vector< tuple<int,string> > > vRows = tCurrentTable.getRows();

      for (int x = 0; x < vColNames.size(); ++x)
      {
        int iCurrentColIndex = get<0>(vColNames[x]);
        string sCurrentColName = get<1>(vColNames[x]);

        for (int y = 0; y < sColumnNamesIn.size(); ++y)
        {
          //Execute if the column is found
          if (sCurrentColName == sColumnNamesIn[y])
          {
            //Add the column to the new table
            tNewTable.addColumn(vColNames[x], vColTypes[x]);
            break;
          }
        }
      }

      for (int a = 0; a < vRows.size(); ++a)
      {
        //current row from list of rows
        vector< tuple<int, string> > vCurrentRow = vRows[a];
        vector< tuple<int,string> > vNewRow;
        vector< tuple<int,string> > vNewCol = tNewTable.getColumnNames();
        for (int p = 0; p < vNewCol.size(); ++p)
        {
          int iNewIndex = get<0>(vNewCol[p]);

          for (int b = 0; b < vCurrentRow.size(); ++b)
          {
            //current attribute from row
            int iAttributeIndex = get<0>(vCurrentRow[b]);
            string sAttributeName = get<1>(vCurrentRow[b]);

            //Execute if the index of the attribute matches the row index
            if (iAttributeIndex == iNewIndex)
            {
              vNewRow.push_back(vCurrentRow[b]);
            }
          }
        }

        //Add the row to the new table
        tNewTable.addRow(vNewRow);
      }
    }
  }

  vTableList.push_back(tNewTable);
}

/*******************************************************************************
  rename the attributes in a relation
*******************************************************************************/
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

/*******************************************************************************
 compute the union of two relations; the relations must be union-compatible.
*******************************************************************************/
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
  bool exists = false;
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

/*******************************************************************************
compute the set diff of two relations and the relations must be union compatible
*******************************************************************************/
void Engine::setDifference(string sT1Name, string sT2Name)
{
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
    cout << "Difference not possible! Tables are not comparable." << endl;
    return;
  }
  if (workingT1.getColumnTypes() != workingT2.getColumnTypes()) 
  {
    cout << "Difference not possible! Tables are not comparable." << endl;
    return;
  }
  
  string sDiffTableName = workingT1.getTableName() + " and "
    + workingT2.getTableName() + " difference";
  vector< tuple<int, string> > vColNames = workingT1.getColumnNames();
  vector<string> vColTypes = workingT1.getColumnTypes();
  
  // Create a new table, using column names from the supplied table. 
  Table differenced(sDiffTableName);
  for (int i = 0; i < vColNames.size(); i++) 
  {
    string sColumnNameIn = get<1>(vColNames[i]);
    string sColumnTypeIn = vColTypes[i];
    differenced.addColumn(make_tuple(i,sColumnNameIn), sColumnTypeIn);
  }

  // Copy row elements from working table 1.
  vector< vector< tuple<int,string> > > vRows1 = workingT1.getRows();

  // Ghetto way of adding working table 2 without the duplicates
  vector< vector< tuple<int,string> > > vRows2 = workingT2.getRows();
  bool exists = false;
  for (int i = 0; i < vRows1.size(); i++) 
  {
    exists = false;
    for (int j = 0; j < vRows2.size(); j++)
    {
      if (vRows1[i] == vRows2[j]) {
        exists = true;
        break;
      }
    }
    if (!exists)
    {
      differenced.addRow(vRows1[i]);
    }
  }
    
  vTableList.push_back(differenced);
}

/*******************************************************************************
  compute the cartesian product of two relations
*******************************************************************************/
void Engine::crossProduct(string sT1Name, string sT2Name)
{
  //Create a new table to send back 
  Table tNewTable(sT1Name + " and " + sT2Name + " cross product");

  //Check to see if the tables are union compatible
  if(!compareTables(sT1Name, sT2Name))
  {
    printf("| The Tables are not union compatible\n");
    return;
  }

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
    cout << "| Could not find that first table!" << endl;
    return;
  }
  if (iT2Index == -1) 
  {
    cout << "| Could not find that second table!" << endl;
    return;
  }

  //Get the current column names and types and rows
  Table t1 = vTableList[iT1Index];
  Table t2 = vTableList[iT2Index];
  vector<string> vColTypes = t1.getColumnTypes();
  vector< tuple<int,string> > vColNames = t1.getColumnNames();

  int iCount = 0;
  int iAmtOfTables = 2;

  while (iCount < iAmtOfTables)
  {
    for (int c = 0; c < vColNames.size(); ++c)
    {
      int iCurrentColIndex = get<0>(vColNames[c]);
      string sCurrentColName = get<1>(vColNames[c]);

      if (iCount == 1)
      {
        //Add the column to the new table
        tNewTable.addColumn(make_tuple(c + vColNames.size(), 
          sCurrentColName), vColTypes[c]);
      }
      else
      {
        //Add the column to the new table
        tNewTable.addColumn(make_tuple(c,sCurrentColName), vColTypes[c]);
      }
    }
    iCount++;
  }
 
  vector< vector< tuple<int,string> > > vT1Rows = t1.getRows();
  vector< vector< tuple<int,string> > > vT2Rows = t2.getRows();

  for (int p = 0; p < vT1Rows.size(); ++p)
  {
    //current row from list of T2 rows
    vector< tuple<int, string> > vT1CurrentRow = vT1Rows[p];

    for (int a = 0; a < vT2Rows.size(); ++a)
    {
      //current row from list of T1 rows
      vector< tuple<int, string> > vNewRow;
      vector< tuple<int, string> > vT2Row = vT2Rows[a];

      for (int r = 0; r < vT1CurrentRow.size(); ++r)
      {
        //current attribute from t2 row
        string sT1Attribute = get<1>(vT1CurrentRow[r]);
        vNewRow.push_back(make_tuple(r,sT1Attribute));
      }
      
      for (int i = 0; i < vT2Row.size(); ++i)
      {
        string sT2Attribute = get<1>(vT2Row[i]);
        vNewRow.push_back(make_tuple(vColNames.size()+i,sT2Attribute));
      }
      //Add the row to the new table
      tNewTable.addRow(vNewRow);
    }
  }
  vTableList.push_back(tNewTable);
}

/*******************************************************************************
  compute the natural join of two relations (remove duplicate data)
*******************************************************************************/
void Engine::naturalJoin(string sT1Name, string sT2Name)
{
    //Create a new table to send back 
  Table tNewTable(sT1Name + " and " + sT2Name + " natural join");
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
    cout << "| Could not find that first table!" << endl;
    return;
  }
  if (iT2Index == -1) 
  {
    cout << "| Could not find that second table!" << endl;
    return;
  }
  
  //Get t1's info
  vector<string> vT1ColTypes = vTableList[iT1Index].getColumnTypes();
  vector< tuple<int,string> > vT1ColNames = vTableList[iT1Index].getColumnNames();
  vector< vector< tuple<int,string> > > vT1Rows = vTableList[iT1Index].getRows();


  //Get t2's info
  vector<string> vT2ColTypes = vTableList[iT2Index].getColumnTypes();
  vector< tuple<int,string> > vT2ColNames = vTableList[iT2Index].getColumnNames();
  vector< vector< tuple<int,string> > > vT2Rows = vTableList[iT2Index].getRows();
  
  //to know the indicies of the columns that are different
  vector<int> vT1Indicies;
  vector<int> vT2Indicies;

  for (int i = 0; i < vT1ColNames.size(); ++i)
  {
    //Get the T1 column and type and create them in new table
    tuple<int,string> tT1Column = vT1ColNames[i];
    string sT1Type = vT1ColTypes[i];

    tNewTable.addColumn(tT1Column, sT1Type);

  }

  for (int i = 0; i < vT2ColNames.size(); ++i)
  {
    //Get the T2 column and type and create them in new table if not already in
    string sT2ColumnName = get<1>(vT2ColNames[i]);
    string sT2Type = vT2ColTypes[i];
    bool bInput = true;
    int iInputCounter = vT1ColNames.size();

    for (int x = 0; x < vT1ColNames.size(); ++x)
    {
      //Get the T1 column and type
      string sT1ColumnName = get<1>(vT1ColNames[x]);
      string sT1Type = vT1ColTypes[x];

      if (sT1ColumnName == sT2ColumnName)
      {
        bInput = false;
      }
    }

    if (bInput)
    {
      tNewTable.addColumn(make_tuple(iInputCounter,sT2ColumnName), sT2Type);
      iInputCounter++;
    }
  }

  for (int i = 0; i < vT1Rows.size(); ++i)
  {
    vector< tuple<int,string> > vT1CurrentRow = vT1Rows[i];
    tNewTable.addRow(vT1CurrentRow);
  }

  for (int i = 0; i < vT2Rows.size(); ++i)
  {
    //get the current T2 row
    vector< tuple<int,string> > vT2CurrentRow = vT2Rows[i];
    bool bInput = true;

    for (int x = 0; x < vT1Rows.size(); ++x)
    {
      //get the current T1 row
      vector< tuple<int,string> > vT1CurrentRow = vT1Rows[x];
      if (vT1CurrentRow == vT2CurrentRow)
      {
        bInput = false;
      }
    }
    if (bInput)
    {
      tNewTable.addRow(vT2CurrentRow);
    }
  }

  vTableList.push_back(tNewTable);
}

/*******************************************************************************
  determines whether two tables have the same column names/types
*******************************************************************************/
bool Engine::columnCheck(string sT1Name, string sT2Name) 
{
  // Find the tables with the given names
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
    return false;
  }
  if (iT2Index == -1) 
  {
    cout << "Could not find that second table!" << endl;
    return false;
  }  
  
  Table workingT1 = vTableList[iT1Index];
  Table workingT2 = vTableList[iT2Index];
  
  // Get the actual vectors so we're not getting it so much later on
  vector< tuple<int, string> > vT1ColNames = workingT1.getColumnNames();
  vector< tuple<int, string> > vT2ColNames = workingT2.getColumnNames();
  vector< string > vT1ColTypes = workingT1.getColumnTypes();
  vector< string > vT2ColTypes = workingT2.getColumnTypes();
  
  
  // Check if the tables are identical.    
  if (vT1ColNames == vT2ColNames) 
  {
    if (vT1ColTypes == vT2ColTypes) 
    {
      return true;
    }
  }
  
  // Check if the tables have the same size
  if (vT1ColNames.size() != vT2ColNames.size()) 
  {
    return false;
  }
  if (vT1ColTypes.size() != vT2ColTypes.size()) 
  {
    return false;
  }
  // Check if the names have the same contents. 
  // Start by making a vector to match the types later
  vector< pair<int, int> > vIndexPairing;
  for (int i = 0; i < vT1ColNames.size(); i++) 
  {
    tuple<int, string> tRef = vT1ColNames[i];
    for (int j = 0; j < vT2ColNames.size(); j++) {
      if (tRef == vT2ColNames[j]) {
        pair<int, int> indexPair = make_pair(i, j);
        vIndexPairing.push_back(indexPair);
        break;
      }
    }
  }
  // Reject if the resulting pair list is not the same size
  if (vIndexPairing.size() != vT1ColNames.size()) {
    return false;
  }
  
  // Now using the pairs match up the types.
  for (int i = 0; i < vIndexPairing.size(); i++) {
    int iT1typeIndex = vIndexPairing[i].first;
    int iT2typeIndex = vIndexPairing[i].second;
    if (vT1ColTypes[iT1typeIndex] != vT2ColTypes[iT2typeIndex]) {
      return false;
    }
  }
  
  // We've exhausted all the checks. Therefore they're the same. 
  return true;
}











