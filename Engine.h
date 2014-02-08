/*******************************************************************************
    File: Engine.h

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
    Engine(){};
    void addTable(Table t) { vTableList.push_back(t); }
    void createTable(string sTableNameIn, vector<string> vColumnNamesIn); 
    void dropTable(string sTableNameIn);
    void displayTable(int iIndex);
    Table * getTable(int iIndex) { return &vTableList[iIndex]; }

    void insertInto(string sTableNameIn);
    void update();
    void deleteFrom();

    Table selection(string sTableNameIn, string sTableNameOut, string sOperator,
     string sColumn, string sAttribute); 
    void projection(); //select of a subset of the attributes of a relation
    void reNaming(); //rename the attributes in a relation
    void setUnion(); //compute the union of two relations, the relations must be union compatible
    void setDifference(); //compute the set diff of two relations and the relations must be union compatible
    void crossProduct(); //compute the cartesian product of two relations

    
};

#endif
