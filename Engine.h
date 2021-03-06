/*******************************************************************************
 File: Engine.h

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

 This file contains the header for the engine
 *******************************************************************************/

#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Table.h"
using namespace std;

class Engine
{
private:
  //Declare private variables
  vector<Table> vTableList;

public:

  //Declare class methods
  Engine()
  {
  }
  ;

  void createTable(std::string sTableNameIn,
      std::vector<std::tuple<std::string, std::string, bool> > vColumnNamesIn,
      std::vector<std::string> vKeys);
  void dropTable(string sTableNameIn);
  bool compareTables(string sT1Name, string sT2Name);
  void renameTable(string sOldTableName, string sNewTableName);

  /*****************************************************************************
   Print out the table with the given name
   ****************************************************************************/
  void displayTable(string sTableNameIn)
  {
    for (int i = 0; i < vTableList.size(); ++i)
    {
      if (vTableList[i].getTableName() == sTableNameIn)
      {
        vTableList[i].displayTable();
        return;
      }
    }
    printf("| The table was not found\n");
  }

  /****************************************************************************
   Adds a row to the specified table
   ****************************************************************************/
  void addRow(string sTableNameIn, vector<tuple<int, string> > vRowIn)
  {
    for (int i = 0; i < vTableList.size(); ++i)
    {
      if (vTableList[i].getTableName() == sTableNameIn)
      {
        vTableList[i].addRow(vRowIn);
        return;
      }
    }
  }

  /****************************************************************************
   Removes a row to the specified table
   ****************************************************************************/
  void deleteRow(string sTableNameIn, vector<tuple<int, string> > vRowIn)
  {
    for (int i = 0; i < vTableList.size(); ++i)
    {
      if (vTableList[i].getTableName() == sTableNameIn)
      {
        vTableList[i].deleteRow(vRowIn);
        return;
      }
    }
  }

  /****************************************************************************
   Adds a column to the specified table with name, type, and key
   ***************************************************************************/
  void addColumn(string sTableNameIn, string sColNameIn, string sTypeIn,
      bool bPrimaryKey)
  {
    for (int i = 0; i < vTableList.size(); ++i)
    {
      if (vTableList[i].getTableName() == sTableNameIn)
      {
        //get the amount of columns, to get accurate index
        int iAmtOfCol = vTableList[i].getColumnNames().size();
        vTableList[i].addColumn(
            make_tuple(iAmtOfCol, sColNameIn, bPrimaryKey, sTypeIn));
        return;
      }
    }
  }

  /****************************************************************************
   Sets the primary key of the specified table
   ***************************************************************************/
  void setPrimaryKey(string sTableNameIn, string sPrimaryKey)
  {
    for (int i = 0; i < vTableList.size(); ++i)
    {
      if (vTableList[i].getTableName() == sTableNameIn)
      {
        vTableList[i].setPrimaryKey(sPrimaryKey);
        return;
      }
    }
  }

  /****************************************************************************
   Removes a primary key from the specified table
   ***************************************************************************/
  void removePrimaryKey(string sTableNameIn, string sPrimaryKey)
  {
    for (int i = 0; i < vTableList.size(); ++i)
    {
      if (vTableList[i].getTableName() == sTableNameIn)
      {
        vTableList[i].removePrimaryKey(sPrimaryKey);
        return;
      }
    }
  }

  void selection(string sTableNameIn, string sTableNameOut, string sOperator,
      string sColumn, string sAttribute);
  void update(vector<string> vColumnNames, vector<string> vNewVals,
      string sTableNameIn, vector<tuple<string, string, string> > comparison);
  void projection(string sTableNameIn, string sTableNameOut,
      vector<string> sColumnNamesIn);
  void reNaming(string sTableName, string sTableNameOut,
      vector<string> vNewNames);
  void setUnion(string sT1Name, string sT2Name, string sNewName);
  void setDifference(string sT1Name, string sT2Name, string sNewName);
  void crossProduct(string sT1Name, string sT2Name, string sNewName);
  void naturalJoin(string sT1Name, string sT2Name);
  bool columnCheck(string sT1Name, string sT2Name);

  /****************************************************************************
   Getter for the table list vector, returns the list of tables
   ***************************************************************************/
  vector<Table> getTableList()
  {
    return vTableList;
  }

  /*****************************************************************************
   Print out the table with the given name
   ****************************************************************************/
  Table getTable(string sTableNameIn)
  {
    Table temp;
    for (int i = 0; i < vTableList.size(); ++i)
    {
      if (vTableList[i].getTableName() == sTableNameIn)
      {
        temp = vTableList[i];
      }
    }
    return temp;
  }
};

#endif
