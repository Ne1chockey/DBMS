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
  vector< tuple<string, string> > vColumnNames;
  vector< tuple<int, string> > vRow;
  vector< tuple<int, string> > vRow2;
  vector< tuple<int, string> > vRow3;
  Engine e;

  vColumnNames.push_back(make_tuple("Name","string"));
  vColumnNames.push_back(make_tuple("Age","int"));
  vColumnNames.push_back(make_tuple("Phone Number","string"));
  vColumnNames.push_back(make_tuple("Address","string"));

  e.createTable("Table 1", vColumnNames);

  vRow.push_back(make_tuple(0,"John Doe"));
  vRow.push_back(make_tuple(1,"23"));
  vRow.push_back(make_tuple(2,"8175555555"));
  vRow.push_back(make_tuple(3,"123 Something St. Ft Worth TX 76137"));

  vRow2.push_back(make_tuple(0,"Jane Smith"));
  vRow2.push_back(make_tuple(1,"25"));
  vRow2.push_back(make_tuple(2,"8171231234"));
  vRow2.push_back(make_tuple(3,"456 That St. Ft Worth TX 76137"));

  vRow3.push_back(make_tuple(0,"This Dude"));
  vRow3.push_back(make_tuple(1,"23"));
  vRow3.push_back(make_tuple(2,"8171231234"));
  vRow3.push_back(make_tuple(3,"999 Elm St. Ft Worth TX 76137"));

  e.addRow("Table 1", vRow);
  e.addRow("Table 1", vRow2);
  e.addRow("Table 1", vRow3);

  e.selection("Table 1","Table 2", "==","Age","23");
  e.displayTable("Table 2");

  return 0;
}
