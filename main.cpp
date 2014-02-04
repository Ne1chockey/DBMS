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
#include "Parser.h"
#include "Engine.h"
#include "App.h"
#include "Table.h"
using namespace std;

int main() 
{
    vector<string> vTemp;
    vector<string> vTemp2;
    Table t1;

    vTemp.push_back("John Doe");
    vTemp.push_back("23");
    vTemp.push_back("8175555555");
    vTemp.push_back("123 Something St. Ft Worth TX 76137");

    vTemp2.push_back("Jane Smith");
    vTemp2.push_back("18");

    t1.addColumn("Name");
    t1.addColumn("Age");
    t1.addColumn("Phone Number");
    t1.addColumn("Street");

    t1.addRow(vTemp);
    t1.addRow(vTemp2);
    cout << "sadfasdfas" << endl;
    t1.displayTable();
	
	return 0;
}
