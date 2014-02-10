/*******************************************************************************
    File: Engine.h

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
  Engine() {};
  
  void createTable(string sTableNameIn, 
    vector<tuple<string, string> > vColumnNamesIn); 
  void dropTable(string sTableNameIn);
  bool compareTables(string sT1Name, string sT2Name);
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

  void addRow(string sTableNameIn, vector< tuple<int, string> > vRowIn)
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

  void addColumn(string sTableNameIn, string sColNameIn, string sTypeIn)
  {
    for (int i = 0; i < vTableList.size(); ++i)
    {
      if (vTableList[i].getTableName() == sTableNameIn)
      {
        //get the amount of columns, to get accurate index
        int iAmtOfCol = vTableList[i].getColumnNames().size();
        vTableList[i].addColumn(make_tuple(iAmtOfCol, sColNameIn), sTypeIn);
        return;
      }
    }
  }

  void selection(string sTableNameIn, string sTableNameOut, string sOperator,
    string sColumn, string sAttribute); 
  void projection(string sTableNameIn, vector<string> sColumnNamesIn);
  void reNaming(vector<string> vNewNames, string sTableName); 
  void setUnion(string sT1Name, string sT2Name); 
  void setDifference(string sT1Name, string sT2Name);
  void crossProduct(string sT1Name, string sT2Name);
  void naturalJoin(string sT1Name, string sT2Name);


};

#endif
