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
 This function will take in a vector of column names and trailing primary keys,
 and an integer specifying how many columns are in the vector.
*******************************************************************************/
void Engine::createTable(string sTableNameIn, vector<string> vColumnNamesIn)
{
    Table t(sTableNameIn);

    for (int i = 0; i < vColumnNamesIn.size(); ++i)
    {
        t.addColumn(make_tuple(i,vColumnNamesIn[i]));
    }
/*
    for (int i = sizeof(vColumnNamesIn)-iAmountOfColumns; 
        i < iAmountOfColumns; ++i)
    {
        t.addPrimaryKey((int)(vColumnNamesIn[i]));
    }
*/

}

/*******************************************************************************
 Remove a table from the list
*******************************************************************************/
void Engine::dropTable(string sTableNameIn)
{
    for (int i = 0; i < vTableList.size(); ++i)
    {
        if (vTableList[i].getTableName() == sTableNameIn)
        {
            vTableList.erase(vTableList.begin() + 1);
        }
    }
}

/*******************************************************************************
 Selects the tuples in a relation that satisfy a particular condition.
 sTableNameIn is going to be the existing table we are working with.
 sTableNameOut is the name we will give the newly created table.
 sOperator will be the operator to be used on sColumn and sAttribute
*******************************************************************************/
 Table Engine::selection(string sTableNameIn, string sTableNameOut, string sOperator, 
    string sColumn, string sAttribute)
{
    //Create a new table to send back
    Table tNewTable(sTableNameOut);
    int iTemp;
    tuple<int,string> tReturn;
    vector<string> vColumnValues;

    for (int i = 0; i < vTableList.size(); ++i)
    {
        //Execute if the table is found in the list
        if (vTableList[i].getTableName() == sTableNameIn)
        {
            //See if the column exists in the table
            tReturn = vTableList[i].getColumnIndex(sColumn);

            if (get<0>(tReturn) == -1)
            {
                printf("| The column does not exist.\n");
            }
            else
            {
                vColumnValues = vTableList[i].getColumnValues(get<0>(tReturn));

                //Execute if we are working with strings
                if (sOperator == "==")
                {
                    for (int x = 0; x < vColumnValues.size(); ++x)
                    {
                        //Execute if the attribute satisfies the condition
                        if (vColumnValues[x] == sAttribute)
                        {
                            //push back the row into the new table
                            tNewTable.addRow(vTableList[i].getRow(x));
                        }
                    }
                }

                //Execute if we are working with integers
                if (sOperator == ">=")
                {
                    /* code */
                }
                else if (sOperator == "<=")
                {
                    /* code */
                }
                else if (sOperator == ">")
                {
                    /* code */
                }
                else if (sOperator == "<")
                {
                    /* code */
                }
                else
                {
                    printf("| ERROR, invalid operator.\n");
                }
            }
        }
    }

    return tNewTable;
} 

/*******************************************************************************
 Display a table from the list
*******************************************************************************/
void Engine::displayTable(int iIndex)
{
    
    cout << "\n ";
    vector<tuple<int,string> > vColumnName = vTableList[iIndex].getColumnNames();
    vector<vector<tuple<int,string>> > vRows = vTableList[iIndex].getRows();
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




































