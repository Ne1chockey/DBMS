/*******************************************************************************
    File: Engine.cpp

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

	This file contains the implementation for the engine
*******************************************************************************/

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Engine.h"
using namespace std;

/*******************************************************************************

*******************************************************************************/
Engine::Engine()
{

}

/*******************************************************************************
 This function will take in a vector of column names and trailing primary keys,
 and an integer specifying how many columns are in the vector.
*******************************************************************************/
Engine::createTable(string sTableNameIn, vector<string> vColumnNamesIn, int iAmountOfColumns)
{
    Table t(sTableNameIn);

    for (int i = 0; i < iAmountOfColumns; ++i)
    {
        t.addColumn(make_tuple(i,vColumnNamesIn[i]));
    }

    for (int i = 0; i < sizeof(vColumnNamesIn)-iAmountOfColumns; ++i)
    {
        t.vPrimaryKeys.push_back
    }
    

}