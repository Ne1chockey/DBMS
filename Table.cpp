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
            for (vector<tuple<int,string> >::iterator it = vRows[i].begin(); it != vRows[i].end(); ++it)
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