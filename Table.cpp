/*******************************************************************************
 File: Table.cpp

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

 This file contains the table implementation file
 *******************************************************************************/

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <fstream>
#include "Table.h"

const int COLUMN_WIDTH = 20;
std::fstream outputFile;

/*******************************************************************************
 Display the table
 *******************************************************************************/
void Table::displayTable()
{
  // Print the lines of the table for a pretty output
  std::cout << "\n ";

  for (int i = 0; i < vColumnName.size(); ++i)
  {
    std::cout << "-----------------------";
  }
  std::cout << "\n";

  std::cout << " | " << sTableName << "\n ";

  for (int i = 0; i < vColumnName.size(); ++i)
  {
    std::cout << "+----------------------";
  }
  std::cout << "\n";

  // Determine how far to space the column bars
  for (int i = 0; i < vColumnName.size(); ++i)
  {
    //get the column values for printing
    std::string sColName = std::get < 1 > (vColumnName[i]);
    bool bPrimaryKey = std::get < 2 > (vColumnName[i]);

    //see if it is a primary key, for formatting
    if (bPrimaryKey)
    {
      std::cout << " | " << std::setw(COLUMN_WIDTH) << std::left
          << "*" + sColName + "*";
    }
    else
    {
      std::cout << " | " << std::setw(COLUMN_WIDTH) << std::left << sColName;
    }

  }
  std::cout << "\n ";

  // Print the row dividers for the number of columns
  for (int i = 0; i < vColumnName.size(); ++i)
  {
    std::cout << "+----------------------";
  }
  std::cout << "\n";

  for (int i = 0; i < vRows.size(); ++i)
  {
    for (int a = 0; a < vColumnName.size(); ++a)
    {
      for (std::vector<std::tuple<int, std::string> >::iterator current =
          vRows[i].begin(); current != vRows[i].end(); ++current)
      {
        if (std::get < 0 > (*current) == std::get < 0 > (vColumnName[a]))
        {
          std::string sCurrent = std::get < 1 > (*current);
          if (sCurrent.size() > COLUMN_WIDTH)
          {
            sCurrent.resize(COLUMN_WIDTH);
          }
          std::cout << " | " << std::setw(COLUMN_WIDTH) << std::left
              << sCurrent;

          break;
        }
      }
    }

    std::cout << "\n ";
    for (int y = 0; y < vColumnName.size(); ++y)
    {
      std::cout << "+----------------------";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

/*******************************************************************************
 This function returns the index of the column or -1 if the column is not found
 and the type of the column
 *******************************************************************************/
std::tuple<int, std::string, bool, std::string> Table::getColumnIndex(
    std::string sColumnNameIn)
{
  for (int i = 0; i < vColumnName.size(); ++i)
  {
    //Execute if the column was found
    if (std::get < 1 > (vColumnName[i]) == sColumnNameIn)
    {
      int iColumnIndex = std::get < 0 > (vColumnName[i]);
      bool bColumnKey = std::get < 2 > (vColumnName[i]);
      std::string sColumnType = std::get < 3 > (vColumnName[i]);

      return std::make_tuple(iColumnIndex, sColumnType, bColumnKey, sColumnType);
    }
  }

  printf("| We didnt find it\n");
  //The column was not found
  return std::make_tuple(-1, "n/a", false, "n/a");
}

/*******************************************************************************
 This function takes the index of a column and returns the values of the column
 *******************************************************************************/
std::vector<std::string> Table::getColumnValues(int iIndex)
{
  //create a vector of strings to return column values
  std::vector < std::string > vReturn;

  for (int i = 0; i < vRows.size(); ++i)
  {
    for (std::vector<std::tuple<int, std::string> >::iterator current =
        vRows[i].begin(); current != vRows[i].end(); ++current)
    {
      //Execute if the column is found
      if (std::get < 0 > (*current) == std::get < 0 > (vColumnName[iIndex]))
      {
        vReturn.push_back(std::get < 1 > (*current));
        break;
      }
    }
  }

  return vReturn;
}

/*******************************************************************************
 This function takes the index of a column and returns the values of the column
 *******************************************************************************/
std::vector<std::tuple<int, std::string> > Table::getRow(int iIndex)
{
  std::vector < std::tuple<int, std::string> > vReturn;

  for (std::vector<std::tuple<int, std::string> >::iterator current =
      vRows[iIndex].begin(); current != vRows[iIndex].end(); ++current)
  {
    vReturn.push_back(
        std::make_tuple(std::get < 0 > (*current), std::get < 1 > (*current)));
  }

  return vReturn;
}

