/*******************************************************************************
    File: Table.cpp

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

	This file contains the table implementation file 
*******************************************************************************/

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include "Table.h"
using namespace std;

const int COLUMN_WIDTH = 20;
/*******************************************************************************
  Display the table, need to put formatting for n/a
*******************************************************************************/
void Table::displayTable()
{
  cout << "\n ";

  for (int i = 0; i < vColumnName.size(); ++i)
  {
    cout << "-----------------------";
  }
  cout << "\n";

  cout << " | " << sTableName << "\n ";

  for (int i = 0; i < vColumnName.size(); ++i)
  {
    cout << "+----------------------";
  }
  cout << "\n";

  for (int i = 0; i < vColumnName.size(); ++i)
  {
    string sColName = get<1>(vColumnName[i]);
    bool bPrimaryKey = get<2>(vColumnName[i]);
    if (bPrimaryKey)
    {
      cout << " | " << setw(COLUMN_WIDTH) << left << "*" + sColName + "*";
    }
    else
    {
      cout << " | " << setw(COLUMN_WIDTH) << left << sColName;
    }
    
  }
  cout << "\n ";

  for (int i = 0; i < vColumnName.size(); ++i)
  {
    cout << "+----------------------";
  }
  cout << "\n";

  for (int i = 0; i < vRows.size(); ++i)
  {
    for (int a = 0; a < vColumnName.size(); ++a)
    {
      for (vector< tuple<int,string> >::iterator current = vRows[i].begin(); 
        current != vRows[i].end(); ++current)
      {
        if (get<0>(*current) == get<0>(vColumnName[a]))
        {
          string sCurrent = get<1>(*current);
          if (sCurrent.size() > COLUMN_WIDTH)
          {
            sCurrent.resize(COLUMN_WIDTH);
          }
          cout << " | " << setw(COLUMN_WIDTH) << left << sCurrent;
          
          break;
        }
      }
    }

    cout << "\n ";
    for (int y = 0; y < vColumnName.size(); ++y)
    {
      cout << "+----------------------";
    }
    cout << "\n";
  }
  cout << "\n";
}

/*******************************************************************************
  This function returns the index of the column or -1 if the column is not found
  and the type of the column
*******************************************************************************/
tuple<int,string,bool,string> Table::getColumnIndex(string sColumnNameIn)
{
  for (int i = 0; i < vColumnName.size(); ++i)
  {
    //Execute if the column was found
    if (get<1>(vColumnName[i]) == sColumnNameIn)
    {
      int iColumnIndex = get<0>(vColumnName[i]);
      bool bColumnKey = get<2>(vColumnName[i]);
      string sColumnType = get<3>(vColumnName[i]);

      return make_tuple(iColumnIndex, sColumnType, bColumnKey, sColumnType);
    }
  }

  printf("| We didnt find it\n");
  //The column was not found
  return make_tuple(-1,"n/a",false,"n/a");
}

/*******************************************************************************
  This function takes the index of a column and returns the values of the column
*******************************************************************************/
vector<string> Table::getColumnValues(int iIndex)
{
  //create a vector of strings to return column values
  vector<string> vReturn;

  for (int i = 0; i < vRows.size(); ++i)
  {
    for (vector< tuple<int,string> >::iterator current = vRows[i].begin(); 
      current != vRows[i].end(); ++current)
    {
      //Execute if the column is found
      if (get<0>(*current) == get<0>(vColumnName[iIndex]))
      {
        vReturn.push_back(get<1>(*current));
        break;
      }
    }
  }

  return vReturn;
}

/*******************************************************************************
  This function takes the index of a column and returns the values of the column
*******************************************************************************/
vector< tuple<int,string> > Table::getRow(int iIndex)
{
  vector< tuple<int,string> > vReturn;

  for (vector< tuple<int,string> >::iterator current = vRows[iIndex].begin(); 
    current != vRows[iIndex].end(); ++current)
  {
    vReturn.push_back(make_tuple(get<0>(*current), get<1>(*current)));
  }

  return vReturn;
}
















