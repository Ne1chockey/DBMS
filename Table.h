/*******************************************************************************
 File: Table.h

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

 This file contains the header for the table attributes
 *******************************************************************************/

#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>

class Table
{
private:
  std::vector<std::tuple<int, std::string, bool, std::string> > vColumnName;
  std::vector<std::vector<std::tuple<int, std::string> > > vRows;
  std::string sTableName;

public:
  //constructors
  Table()
  {
  }
  ;

  Table(std::string sTableNameIn)
  {
    sTableName = sTableNameIn;
  }

  //Display function
  void displayTable();

  //Setters
  void setPrimaryKey(std::string sKeyIn)
  {
    for (int i = 0; i < vColumnName.size(); ++i)
    {
      if (std::get < 1 > (vColumnName[i]) == sKeyIn)
      {
        std::get < 2 > (vColumnName[i]) = true;
        return;
      }
    }

    printf("| Primary Key was not set\n");
  }

  void removePrimaryKey(std::string sKeyIn)
  {
    for (int i = 0; i < vColumnName.size(); ++i)
    {
      if (std::get < 1 > (vColumnName[i]) == sKeyIn)
      {
        std::get < 2 > (vColumnName[i]) = false;
        return;
      }
    }

    printf("| Primary Key was not removed\n");
  }

  void addColumn(std::tuple<int, std::string, bool, std::string> s)
  {
    vColumnName.push_back(s);
  }

  void addRow(std::vector<std::tuple<int, std::string> > v)
  {
    vRows.push_back(v);
  }

  //Getters
  std::string getTableName()
  {
    return sTableName;
  }

  std::vector<std::tuple<int, std::string, bool, std::string> > getColumnNames()
  {
    return vColumnName;
  }

  std::vector<std::vector<std::tuple<int, std::string> > > getRows()
  {
    return vRows;
  }

  std::tuple<int, std::string, bool, std::string> getColumnIndex(
      std::string sColumnNameIn);

  std::vector<std::tuple<int, std::string> > getRow(int iIndex);

  std::vector<std::string> getColumnValues(int iIndex);

};

#endif
