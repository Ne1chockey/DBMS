/*******************************************************************************
    File: main.cpp

    Authors: Gustavo Pedroso UIN: 423002834
             Levi Clark UIN:
             Terry Chen UIN:
             Daniel He UIN:

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
#include "Parser.h"
#include "Engine.h"
#include "App.h"
#include "Table.h"
using namespace std;

int main() 
{
    vector<tuple<int, string>> vTemp;
    vector<tuple<int, string>> vTemp2;
    Table t1;

    vTemp.push_back(make_tuple(0,"John Doe"));
    vTemp.push_back(make_tuple(1,"23"));
    vTemp.push_back(make_tuple(2,"8175555555"));
    vTemp.push_back(make_tuple(3,"123 Something St. Ft Worth TX 76137"));

    vTemp2.push_back(make_tuple(0,"Jane Smith"));
    vTemp2.push_back(make_tuple(2,"8171231234"));

    t1.addColumn(make_tuple(0,"Name"));
    t1.addColumn(make_tuple(1,"Age"));
    t1.addColumn(make_tuple(2,"Phone Number"));
    t1.addColumn(make_tuple(3,"Street"));

    t1.addRow(vTemp);
    t1.addRow(vTemp2);

    t1.displayTable();
	
	return 0;
}
