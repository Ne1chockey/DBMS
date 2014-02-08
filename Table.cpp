/*******************************************************************************
    File: Table.cpp

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

	This file contains the table implementation file 
*******************************************************************************/

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include "Table.h"
using namespace std;

/*******************************************************************************
Display the table, need to put formatting for n/a
*******************************************************************************/
void Table::displayTable()
{
    
    cout << "\n ";

    for (int i = 0; i < vColumnName.size(); ++i)
    {
        cout << "-----------------------";
    }
    cout << "\n";

    for (int i = 0; i < vColumnName.size(); ++i)
    {
        cout << " | " << setw(20) << left << get<1>(vColumnName[i]);
    }
    cout << "\n";

    for (int i = 0; i < vColumnName.size(); ++i)
    {
        cout << "-----------------------";
    }
    cout << "\n";

    for (int i = 0; i < vRows.size(); ++i)
    {
        for (int a = 0; a < vColumnName.size(); ++a)
        {
            for (vector<tuple<int,string> >::iterator it = vRows[i].begin(); 
                it != vRows[i].end(); ++it)
            {
                if (get<0>(*it) == get<0>(vColumnName[a]))
                {
                    cout << " | " << setw(20) << left << get<1>(*it);
                    break;
                }
            }
        }

        cout << "\n";
        for (int y = 0; y < vColumnName.size(); ++y)
        {
            cout << "-----------------------";
        }
        cout << "\n";
    }
    cout << "\n";
}

/*******************************************************************************
 This function returns the index of the column or -1 if the column is not found
 and the type of the column
*******************************************************************************/
tuple<int,string> Table::getColumnIndex(string sColumnNameIn)
{
    for (int i = 0; i < vColumnName.size(); ++i)
    {
        //Execute if the column was found
        if (get<1>(vColumnName[i]) == sColumnNameIn)
        {
            return make_tuple(get<0>(vColumnName[i]), 
                vTypes[get<0>(vColumnName[i])]);
        }
    }

    //The column was not found
    return make_tuple(-1,"n/a");
}

/*******************************************************************************
 This function takes the index of a column and returns the values of the column
*******************************************************************************/
vector<string> Table::getColumnValues(int iIndex)
{
    //create a vector of strings to return column values
    vector<string> vReturn;

    for (int i = 0; i < vRows.size(); ++i)
    {
        for (vector<tuple<int,string> >::iterator it = vRows[i].begin(); 
            it != vRows[i].end(); ++it)
        {
            //Execute if the column is found
            if (get<0>(*it) == get<0>(vColumnName[iIndex]))
            {
                vReturn.push_back(get<1>(*it));
                break;
            }
        }
    }

    return vReturn;
}

/*******************************************************************************
 This function takes the index of a column and returns the values of the column
*******************************************************************************/
vector<tuple<int,string> > Table::getRow(int iIndex)
{
    vector<tuple<int,string> > vReturn;

    for (vector<tuple<int,string> >::iterator it = vRows[iIndex].begin(); 
        it != vRows[iIndex].end(); ++it)
    {
        vReturn.push_back(make_tuple(get<0>(*it),get<1>(*it)));
    }

    return vReturn;
}
















