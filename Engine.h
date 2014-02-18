/*******************************************************************************
    File: Engine.h

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
  Engine::Engine() {};
  
  void Engine::createTable(std::string sTableNameIn, 
    std::vector<std::tuple<std::string,std::string,bool> > vColumnNamesIn, std::vector<std::string> vKeys); 
  void Engine::dropTable(string sTableNameIn);
  bool Engine::compareTables(string sT1Name, string sT2Name);
  void Engine::displayTable(string sTableNameIn)
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

  void Engine::writeTable(string sTableNameIn)
  {
    for (int i = 0; i < vTableList.size(); ++i)
    {
      if (vTableList[i].getTableName() == sTableNameIn)
      {
        vTableList[i].writeTable();
        return;
      }
    }
    printf("| The table was not found\n");
  }

  void Engine::openTable(string sTableNameIn)
  {
    for (int i = 0; i < vTableList.size(); ++i)
    {
      if (vTableList[i].getTableName() == sTableNameIn)
      {
        vTableList[i].openTable();
        return;
      }
    }
    printf("| The table was not found\n");
  }

  void Engine::closeTable(string sTableNameIn)
  {
    for (int i = 0; i < vTableList.size(); ++i)
    {
      if (vTableList[i].getTableName() == sTableNameIn)
      {
        vTableList[i].closeTable();
        return;
      }
    }
    printf("| The table was not found\n");
  }

  void Engine::addRow(string sTableNameIn, vector< tuple<int, string> > vRowIn)
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

  void Engine::addColumn(string sTableNameIn, string sColNameIn, string sTypeIn,
    bool bPrimaryKey)
  {
    for (int i = 0; i < vTableList.size(); ++i)
    {
      if (vTableList[i].getTableName() == sTableNameIn)
      {
        //get the amount of columns, to get accurate index
        int iAmtOfCol = vTableList[i].getColumnNames().size();
        vTableList[i].addColumn(make_tuple(iAmtOfCol,sColNameIn,bPrimaryKey,sTypeIn));
        return;
      }
    }
  }

  void Engine::setPrimaryKey(string sTableNameIn, string sPrimaryKey)
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

  void Engine::removePrimaryKey(string sTableNameIn, string sPrimaryKey)
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

  void Engine::selection(string sTableNameIn, string sTableNameOut, string sOperator,
    string sColumn, string sAttribute);
  void Engine::update(vector<string> vColumnNames, vector<string> vNewVals,
             string sTableNameIn, vector<tuple<string, string, string> > comparison);
  void Engine::projection(string sTableNameIn, vector<string> sColumnNamesIn);
  void Engine::reNaming(vector<string> vNewNames, string sTableName); 
  void Engine::setUnion(string sT1Name, string sT2Name); 
  void Engine::setDifference(string sT1Name, string sT2Name);
  void Engine::crossProduct(string sT1Name, string sT2Name);
  void Engine::naturalJoin(string sT1Name, string sT2Name);

  bool Engine::columnCheck(string sT1Name, string sT2Name);
  
  vector<Table> Engine::getTableList() {
    return vTableList;
  }
};

#endif
