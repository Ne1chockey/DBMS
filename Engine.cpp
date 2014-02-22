/*******************************************************************************
    File: Engine.cpp

    Authors: Gustavo Pedroso UIN: 423002834
             Levi Clark      UIN: 520007880
             Terry Chen      UIN: 121007055
             Daniel He       UIN: 620006827

            Department of Computer Science
            Texas A&M University
    Date  : 2014-02-18

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
void Engine::createTable(std::string sTableNameIn,
    std::vector<std::tuple<std::string, std::string, bool> > vColumnNamesIn,
    std::vector<std::string> vKeys)
{
  Table t(sTableNameIn);

  for (int i = 0; i < vColumnNamesIn.size(); ++i)
  {
    string sName = get < 0 > (vColumnNamesIn[i]);
    string sType = get < 1 > (vColumnNamesIn[i]);
    bool bKey = get < 2 > (vColumnNamesIn[i]);

    t.addColumn(make_tuple(i, sName, bKey, sType));
  }

  for (int i = 0; i < vKeys.size(); ++i)
  {
    t.setPrimaryKey(vKeys[i]);
  }

  //push table into the table list
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
      vTableList.erase(vTableList.begin() + i);
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
          vector < tuple<int, string, bool, string> > vT1columns =
              t1.getColumnNames();
          vector < tuple<int, string, bool, string> > vT2columns =
              t2.getColumnNames();

          if (vT1columns.size() != vT2columns.size())
          {
            return false;
          }

          for (int y = 0; y < vT1columns.size(); ++y)
          {
            int iCurrentT1ColIndex = get < 0 > (vT1columns[y]);
            string sCurrentT1ColName = get < 1 > (vT1columns[y]);
            string sCurrentT1ColType = get < 3 > (vT1columns[y]);

            for (int z = 0; z < vT2columns.size(); ++z)
            {
              int iCurrentT2ColIndex = get < 0 > (vT2columns[z]);
              string sCurrentT2ColName = get < 1 > (vT2columns[z]);
              string sCurrentT2ColType = get < 3 > (vT2columns[y]);

              if (iCurrentT1ColIndex == iCurrentT2ColIndex)
              {
                if ((sCurrentT1ColName != sCurrentT2ColName)
                    && (sCurrentT1ColType != sCurrentT2ColType))
                {
                  return false;
                }
                break;
              }
            }
          }
          break;
        }
      }
      break;
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
  vector < string > vColumnValues;
  int iColumnIndex = -1;
  string sColumnType;

  for (int i = 0; i < vTableList.size(); ++i)
  {
    Table tCurrentTable = vTableList[i];

    //Execute if the table is found in the list
    if (tCurrentTable.getTableName() == sTableNameIn)
    {
      //Input the column names and types into the new table, then determine
      //the rows to copy over
      vector < tuple<int, string, bool, string> > vNames =
          tCurrentTable.getColumnNames();

      for (int a = 0; a < vNames.size(); ++a)
      {
        if (a == get < 0 > (vNames[a]))
        {
          //Add column to new table
          tNewTable.addColumn(vNames[a]);
          if (get < 1 > (vNames[a]) == sColumn)
          {
            iColumnIndex = a;
            sColumnType = get < 3 > (vNames[a]);
          }
        }
      }

      //See if the column exists in the table
      if (iColumnIndex == -1)
      {
        printf("| The column does not exist.\n");
      }
      else
      {
        //get the values for the column
        vColumnValues = tCurrentTable.getColumnValues(iColumnIndex);

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
              //Execute if the attribute satisfies the condition and is a date
              if (sColumn == "Date")
              {
                string sMonth1 = sValueToBeTested.substr(0,2);
                string sDay1 = sValueToBeTested.substr(3,2);
                string sYear1 = sValueToBeTested.substr(5,4);
                string sMonth2 = sAttribute.substr(0,2);
                string sDay2 = sAttribute.substr(3,2);
                string sYear2 = sAttribute.substr(5,4);

                if (sMonth1 >= sMonth2 || sDay1 >= sDay2 || sYear1 >= sYear2)
                {
                  tNewTable.addRow(tCurrentTable.getRow(x));
                }
              }
              //Execute if not a date
              else if (sValueToBeTested >= sAttribute)
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
              //Execute if the attribute satisfies the condition and is a date
              if (sColumn == "Date")
              {
                int iPosStart = sValueToBeTested.find("/");
                int iPosEnd = sValueToBeTested.find("/",iPosStart+1);

                string sMonth1 = sValueToBeTested.substr(0,iPosStart);
                string sDay1 = sValueToBeTested.substr(iPosStart+1,iPosEnd-iPosStart-1);
                string sYear1 = sValueToBeTested.substr(iPosEnd+1,4);

                iPosStart = sAttribute.find("/");
                iPosEnd = sAttribute.find("/",iPosStart+1);

                string sMonth2 = sAttribute.substr(0,iPosStart);
                string sDay2 = sAttribute.substr(iPosStart+1,iPosEnd-iPosStart-1);
                string sYear2 = sAttribute.substr(iPosEnd+1,4);

                printf("%s <= %s, %s <= %s, %s <= %s\n", sMonth1.c_str(), sMonth2.c_str(), sDay1.c_str(), sDay2.c_str(), sYear1.c_str(), sYear2.c_str());
                if (sMonth1 <= sMonth2 || sDay1 <= sDay2 || sYear1 <= sYear2)
                {
                  tNewTable.addRow(tCurrentTable.getRow(x));
                }
              }
              //Execute if the attribute satisfies the condition
              else if (sValueToBeTested <= sAttribute)
              {
                printf("%s <= %s\n", sValueToBeTested.c_str(), sAttribute.c_str());
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
 Updates row elements for a relation based on an input condition
 comparison <oeprand, op, operand>
 *******************************************************************************/
void Engine::update(vector<string> vColumnNames, vector<string> vNewVals,
    string sTableNameIn, vector<tuple<string, string, string> > comparison)
{
  //find table of sTableNameIn in vTableList
  int iTableIndex = -1;
  Table tWorkingTable;

  for (int i = 0; i < vTableList.size(); i++)
  {
    if (sTableNameIn == vTableList[i].getTableName())
    {
      tWorkingTable = vTableList[i];
      iTableIndex = i;
      break;
    }
  }

  if (iTableIndex == -1)
  {
    cout << "No such table with name \"" << sTableNameIn << "\"" << endl;
    return;
  }

  //check that valid column names were given
  bool bValidColumns = true;
  vector < tuple<int, string, bool, string> > vAllColumnNames =
      tWorkingTable.getColumnNames();

  for (int i = 0; i < vColumnNames.size(); i++)
  {

    for (int j = 0; j < vAllColumnNames.size(); j++)
    {

      if (get < 1 > (vAllColumnNames[j]) == vColumnNames[i])
      {
        bValidColumns = true;
        break;
      }

      bValidColumns = false;
    }

    if (!bValidColumns)
    {
      cout << "There is not a column named \"" << vColumnNames[i] << "\""
          << endl;
      return;
    }
  }

  //update attributes
  //comparison || comparison || comparison... 
  //so if a comparison is true, it will update the item

  /*for(int i = 0; i<comparison.size(); i++)
   {

   string operand1 = get<0>(comparison[i]);
   string operand2 = get<2>(comparison[i]);
   string op = get<1>(comparison[i]);
   //== | != | < | > | <= | >=
   bool bValidOperand;
   for(int j = 0; j<vAllColumnNames.size(); j++)
   {
   bValidOperand = false;
   if(operand1 == vAllColumnNames[j])
   {
   bValidOperand = true;
   break;
   }
   }

   if(!bValidOperand)
   {
   cout << "There is not an attribute named \"" << operand1 << "\"" << endl;
   return;
   }


   }*/
  return;
}

/*******************************************************************************
 Select of a subset of the attributes of a relation
 *******************************************************************************/
void Engine::projection(string sTableNameIn, string sTableNameOut, vector<string> sColumnNamesIn)
{
  //Create a new table to send back 
  Table tNewTable(sTableNameOut);

  for (int i = 0; i < vTableList.size(); ++i)
  {
    Table tCurrentTable = vTableList[i];

    //Execute if the table is found
    if (tCurrentTable.getTableName() == sTableNameIn)
    {
      //Get the current column names and types and rows
      vector < tuple<int, string, bool, string> > vColNames =
          tCurrentTable.getColumnNames();
      vector < vector<tuple<int, string> > > vRows = tCurrentTable.getRows();

      for (int x = 0; x < vColNames.size(); ++x)
      {
        int iCurrentColIndex = get < 0 > (vColNames[x]);
        string sCurrentColName = get < 1 > (vColNames[x]);

        for (int y = 0; y < sColumnNamesIn.size(); ++y)
        {
          //Execute if the column is found
          if (sCurrentColName == sColumnNamesIn[y])
          {
            //Add the column to the new table
            tNewTable.addColumn(vColNames[x]);
            break;
          }
        }
      }

      for (int a = 0; a < vRows.size(); ++a)
      {
        //current row from list of rows
        vector < tuple<int, string> > vCurrentRow = vRows[a];
        vector < tuple<int, string> > vNewRow;
        vector < tuple<int, string, bool, string> > vNewCol =
            tNewTable.getColumnNames();

        for (int p = 0; p < vNewCol.size(); ++p)
        {
          int iNewIndex = get < 0 > (vNewCol[p]);

          for (int b = 0; b < vCurrentRow.size(); ++b)
          {
            //current attribute from row
            int iAttributeIndex = get < 0 > (vCurrentRow[b]);
            string sAttributeName = get < 1 > (vCurrentRow[b]);

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
void Engine::reNaming(string sTableName, string sTableNameOut, vector<string> vNewNames)
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

  string sRenameTableName = sTableNameOut;
  vector < tuple<int, string, bool, string> > vColNames =
      workingTable.getColumnNames();
  Table reNamed(sRenameTableName);

  // Create a new table with the new supplied column names
  for (int i = 0; i < vNewNames.size(); i++)
  {
    string sColumnNameIn = vNewNames[i];
    bool bOldColKey = get < 2 > (vColNames[i]);
    string sOldColType = get < 3 > (vColNames[i]);

    reNamed.addColumn(make_tuple(i, sColumnNameIn, bOldColKey, sOldColType));
  }

  // Copy row elements from working table to the new renamed table
  vector < vector<tuple<int, string> > > vRows = workingTable.getRows();

  for (int i = 0; i < vRows.size(); i++)
  {
    reNamed.addRow(vRows[i]);
  }

  vTableList.push_back(reNamed);
}

/*******************************************************************************
 compute the union of two relations; the relations must be union-compatible.
 *******************************************************************************/
void Engine::setUnion(string sT1Name, string sT2Name, string sNewName)
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

  string sUnionTableName = sNewName;
  vector < tuple<int, string, bool, string> > vColNames =
      workingT1.getColumnNames();

  // Create a new table, using column names from the supplied table. 
  Table unioned(sUnionTableName);
  for (int i = 0; i < vColNames.size(); i++)
  {
    unioned.addColumn(vColNames[i]);
  }

  // Copy row elements from working table 1.
  vector < vector<tuple<int, string> > > vRows1 = workingT1.getRows();

  for (int i = 0; i < vRows1.size(); i++)
  {
    unioned.addRow(vRows1[i]);
  }

  // Ghetto way of adding working table 2 without the duplicates
  vector < vector<tuple<int, string> > > vRows2 = workingT2.getRows();
  bool exists = false;
  for (int i = 0; i < vRows2.size(); i++)
  {
    exists = false;
    for (int j = 0; j < vRows1.size(); j++)
    {
      if (vRows1[j] == vRows2[i])
      {
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
void Engine::setDifference(string sT1Name, string sT2Name, string sNewName)
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

  string sDiffTableName = sNewName;
  vector < tuple<int, string, bool, string> > vColNames =
      workingT1.getColumnNames();

  // Create a new table, using column names from the supplied table. 
  Table differenced(sDiffTableName);
  for (int i = 0; i < vColNames.size(); i++)
  {
    differenced.addColumn(vColNames[i]);
  }

  // Copy row elements from working table 1.
  vector < vector<tuple<int, string> > > vRows1 = workingT1.getRows();

  // Ghetto way of adding working table 2 without the duplicates
  vector < vector<tuple<int, string> > > vRows2 = workingT2.getRows();
  bool exists = false;
  for (int i = 0; i < vRows1.size(); i++)
  {
    exists = false;
    for (int j = 0; j < vRows2.size(); j++)
    {
      if (vRows1[i] == vRows2[j])
      {
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
void Engine::crossProduct(string sT1Name, string sT2Name, string sNewName)
{
  //Create a new table to send back 
  Table tNewTable(sNewName);

  //Check to see if the tables are union compatible
  if (!compareTables(sT1Name, sT2Name))
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
  vector < tuple<int, string, bool, string> > vColNames = t1.getColumnNames();

  int iCount = 0;
  int iAmtOfTables = 2;

  while (iCount < iAmtOfTables)
  {
    for (int c = 0; c < vColNames.size(); ++c)
    {
      int iCurrentColIndex = get < 0 > (vColNames[c]);
      string sCurrentColName = get < 1 > (vColNames[c]);
      bool bCurrentPrimaryKey = get < 2 > (vColNames[c]);
      string sCurrentColType = get < 3 > (vColNames[c]);

      if (iCount == 1)
      {
        //Add the column to the new table
        tNewTable.addColumn(
            make_tuple(c + vColNames.size(), sCurrentColName,
                bCurrentPrimaryKey, sCurrentColType));
      }
      else
      {
        //Add the column to the new table
        tNewTable.addColumn(
            make_tuple(c, sCurrentColName, bCurrentPrimaryKey,
                sCurrentColType));
      }
    }
    iCount++;
  }

  vector < vector<tuple<int, string> > > vT1Rows = t1.getRows();
  vector < vector<tuple<int, string> > > vT2Rows = t2.getRows();

  for (int p = 0; p < vT1Rows.size(); ++p)
  {
    //current row from list of T2 rows
    vector < tuple<int, string> > vT1CurrentRow = vT1Rows[p];

    for (int a = 0; a < vT2Rows.size(); ++a)
    {
      //current row from list of T1 rows
      vector < tuple<int, string> > vNewRow;
      vector < tuple<int, string> > vT2Row = vT2Rows[a];

      for (int r = 0; r < vT1CurrentRow.size(); ++r)
      {
        //current attribute from t2 row
        string sT1Attribute = get < 1 > (vT1CurrentRow[r]);
        vNewRow.push_back(make_tuple(r, sT1Attribute));
      }

      for (int i = 0; i < vT2Row.size(); ++i)
      {
        string sT2Attribute = get < 1 > (vT2Row[i]);
        vNewRow.push_back(make_tuple(vColNames.size() + i, sT2Attribute));
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
  vector < tuple<int, string, bool, string> > vT1ColNames =
      vTableList[iT1Index].getColumnNames();
  vector < vector<tuple<int, string> > > vT1Rows =
      vTableList[iT1Index].getRows();

  //Get t2's info
  vector < tuple<int, string, bool, string> > vT2ColNames =
      vTableList[iT2Index].getColumnNames();
  vector < vector<tuple<int, string> > > vT2Rows =
      vTableList[iT2Index].getRows();

  //to know the indicies of the columns that are different
  vector<int> vT1Indicies;
  vector<int> vT2Indicies;

  for (int i = 0; i < vT1ColNames.size(); ++i)
  {
    //Get the T1 column and type and create them in new table
    tuple<int, string, bool, string> tT1Column = vT1ColNames[i];
    tNewTable.addColumn(tT1Column);
  }

  for (int i = 0; i < vT2ColNames.size(); ++i)
  {
    //Get the T2 column and type and create them in new table if not already in
    string sT2ColumnName = get < 1 > (vT2ColNames[i]);
    bool bT2PrimaryKey = get < 2 > (vT2ColNames[i]);
    string sT2ColumnType = get < 3 > (vT2ColNames[i]);
    bool bInput = true;
    int iInputCounter = vT1ColNames.size();

    for (int x = 0; x < vT1ColNames.size(); ++x)
    {
      //Get the T1 column and type
      string sT1ColumnName = get < 1 > (vT1ColNames[x]);

      if (sT1ColumnName == sT2ColumnName)
      {
        bInput = false;
      }
    }

    if (bInput)
    {
      tNewTable.addColumn(
          make_tuple(iInputCounter, sT2ColumnName, bT2PrimaryKey,
              sT2ColumnType));
      iInputCounter++;
    }
  }

  for (int i = 0; i < vT1Rows.size(); ++i)
  {
    vector < tuple<int, string> > vT1CurrentRow = vT1Rows[i];
    tNewTable.addRow(vT1CurrentRow);
  }

  for (int i = 0; i < vT2Rows.size(); ++i)
  {
    //get the current T2 row
    vector < tuple<int, string> > vT2CurrentRow = vT2Rows[i];
    bool bInput = true;

    for (int x = 0; x < vT1Rows.size(); ++x)
    {
      //get the current T1 row
      vector < tuple<int, string> > vT1CurrentRow = vT1Rows[x];

      //INSTEAD OF CHECKING TO SEE IF ROWS ARE EQUAL, CHECK TO SEE IF KEYS ARE 
      //EQUAL AND PUSH ALL ROWS ATTRIBUTES FROM BOTH ROWS
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
/*
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
 vector< tuple<int,string,bool,string> > vT1ColNames = workingT1.getColumnNames();
 vector< tuple<int,string,bool,string> > vT2ColNames = workingT2.getColumnNames();

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
 tuple<int,string,bool,string> tRef = vT1ColNames[i];
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

 // We've exhausted all the checks. Therefore they're the same.
 return true;
 }
 */

