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
    vector<void *> vTemp;
    vector<void *> vTemp2;
    Table *t1 = new Table();

    vTemp.push_back((char *)'a');
    vTemp.push_back((int *) 234);
    vTemp.push_back((string *)"sdfas");
    vTemp2.push_back((string *)"sdf");

    for (int i = 0; i < vTemp.size(); ++i)
    {
        cout << vTemp[i] << endl;
    }
    //t1.addRow(vTemp);
    //t1.addRow(vTemp2);

	
	return 0;
}
