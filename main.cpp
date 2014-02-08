/*******************************************************************************
    File: main.cpp

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

	This file contains the main file 
*******************************************************************************/

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include "Engine.h"
using namespace std;

int main() 
{
  vector<string> vColumnNames;
  vector< tuple<int, string> > vTemp;
  vector< tuple<int, string> > vTemp2;
  vector< tuple<int, string> > vTemp3;
  Engine e;

  vColumnNames.push_back("Name");
  vColumnNames.push_back("Age");
  vColumnNames.push_back("Phone Number");
  vColumnNames.push_back("Address");

  e.createTable("Table 1", vColumnNames);

  vTemp.push_back(make_tuple(0,"John Doe"));
  vTemp.push_back(make_tuple(1,"23"));
  vTemp.push_back(make_tuple(2,"8175555555"));
  vTemp.push_back(make_tuple(3,"123 Something St. Ft Worth TX 76137"));

  vTemp2.push_back(make_tuple(0,"Jane Smith"));
  vTemp2.push_back(make_tuple(1,"25"));
  vTemp2.push_back(make_tuple(2,"8171231234"));
  vTemp2.push_back(make_tuple(3,"456 That St. Ft Worth TX 76137"));

  vTemp3.push_back(make_tuple(0,"Sorry Gus"));
  vTemp3.push_back(make_tuple(1,"23"));
  vTemp3.push_back(make_tuple(2,"8171231234"));
  vTemp3.push_back(make_tuple(3,"999 Elm St. Ft Worth TX 76137"));

  e.getTable(0)->addRow(vTemp);
  e.getTable(0)->addRow(vTemp2);
  e.getTable(0)->addRow(vTemp3);

  e.addTable(e.selection("Table 1", "Table 2", "==","Age","23"));
  e.displayTable(1);

  return 0;
}
