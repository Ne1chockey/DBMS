/*******************************************************************************
    File: Table.h

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

    This file contains the header for the table attributes
*******************************************************************************/

#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

class Table
{
private:
    vector<string> vColumnName;
    vector<vector<void *> > vRows;

public:
    void makeTuple(){};
    Table(){};
    void addColumn(string s){vColumnName.push_back(s);}
    //void addRow(vector<void*> v){vRows.push_back(v);}

};

#endif