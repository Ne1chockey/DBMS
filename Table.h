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
#include <tuple>
using namespace std;

class Table
{
private:
    vector<tuple<int,string> > vColumnName;
    vector<vector<tuple<int,string>> > vRows;
    vector<string> vTypes; 
    vector<int> vPrimaryKeys;
    string sTableName;

public:
    Table(){};
    Table(string sTableNameIn) {sTableName = sTableNameIn; }

    void addColumn(tuple<int,string> s){vColumnName.push_back(s);}
    void addRow(vector<tuple<int,string> > v){vRows.push_back(v);}
    tuple<int,string> getColumnIndex(string sColumnNameIn);
    vector<tuple<int,string> > getRow(int iIndex);
    vector<vector<tuple<int,string>> > getRows(){ return vRows; }
    vector<string> getColumnValues(int iIndex);
    vector<tuple<int,string> > getColumnNames() { return vColumnName; }
    void addPrimaryKey(int iKeyIn) { vPrimaryKeys.push_back(iKeyIn); }
    void displayTable();


    string getTableName() { return sTableName; }

};

#endif