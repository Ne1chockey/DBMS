/*******************************************************************************
    File: main.cpp

    Authors: Gustavo Pedroso UIN: 423002834
             Levi Clark      UIN:
             Terry Chen      UIN: 121007055
             Daniel He       UIN: 620006827

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
#include "Engine.h"
using namespace std;

int main() 
{
  //Declare variables
  vector< tuple<string, string> > vColumnNames;
  vector< tuple<int, string> > vRow;
  vector< tuple<int, string> > vRow2;
  vector< tuple<int, string> > vRow3;
  vector< tuple<int, string> > vRow4;
  vector< tuple<int, string> > vRow5;
  Engine e;

  //NOTE TO SELF: change this to where the function takes in the two parameters
  //instead of making a tuple and sending, have the function make the tuple
  //dont make the user make a tuple and send it, lets do that on our end.

  //Create columns for the main table
  vColumnNames.push_back(make_tuple("Name","string"));
  vColumnNames.push_back(make_tuple("Age","int"));
  vColumnNames.push_back(make_tuple("Phone Number","string"));
  vColumnNames.push_back(make_tuple("Address","string"));

  //create a main table to work with
  e.createTable("Main Table", vColumnNames);

  //Push the row values into each row
  vRow.push_back(make_tuple(0,"John Doe"));
  vRow.push_back(make_tuple(1,"23"));
  vRow.push_back(make_tuple(2,"8175555555"));
  vRow.push_back(make_tuple(3,"123 Something St. Ft Worth TX 76137"));

  vRow2.push_back(make_tuple(0,"Jane Smith"));
  vRow2.push_back(make_tuple(1,"15"));
  vRow2.push_back(make_tuple(2,"8171231234"));
  vRow2.push_back(make_tuple(3,"456 That St. Ft Worth TX 76137"));

  vRow3.push_back(make_tuple(0,"Rick Raptor"));
  vRow3.push_back(make_tuple(1,"23"));
  vRow3.push_back(make_tuple(2,"8171231234"));
  vRow3.push_back(make_tuple(3,"999 Elm St. Ft Worth TX 76137"));

  vRow4.push_back(make_tuple(0,"Old Blue"));
  vRow4.push_back(make_tuple(1,"100"));
  vRow4.push_back(make_tuple(2,"8173335555"));
  vRow4.push_back(make_tuple(3,"1 Hello Dr. Keller TX 76244"));

  vRow5.push_back(make_tuple(0,"Will Johnson"));
  vRow5.push_back(make_tuple(1,"5"));
  vRow5.push_back(make_tuple(2,"3611238585"));
  vRow5.push_back(make_tuple(3,"687 Dude Ave. Corpus Christi TX 78412"));

  //Add each row to the main table
  e.addRow("Main Table", vRow);
  e.addRow("Main Table", vRow2);
  e.addRow("Main Table", vRow3);
  e.addRow("Main Table", vRow4);
  e.addRow("Main Table", vRow5);

  //Test the selection function with all possibilities
  e.selection("Main Table","Equality Table", "==","Age","23");
  e.selection("Main Table","Less Than Or Equal To Table", "<=","Age","15");
  e.selection("Main Table","Greater Than Or Equal To Table", ">=","Age","23");
  e.selection("Main Table","Less Than Table", "<","Age","100");
  e.selection("Main Table","Greater Than Table", ">","Age","23");

  //Change the table name to the table you want to view
  e.displayTable("Equality Table");
   
  //Projection testing
  vector<string> vColNames;
  vColNames.push_back("Name");
  vColNames.push_back("Age");

  e.projection("Main Table", vColNames);

  e.displayTable("Main Table projection");

  // Rename Testing
  vector<string> renames = {"Full Name", "Oldness", "Digits", "Ma house"};
  e.reNaming(renames, "Equality Table");
  
  e.displayTable("Equality Table renamed");
  
  // Union Testing
  e.createTable("Other Table", vColumnNames);
  e.addRow("Other Table", vRow);
  e.addRow("Other Table", vRow2);
  e.addRow("Other Table", vRow3);
  
  vector< tuple<int, string> > vURow1;
  vector< tuple<int, string> > vURow2;
  vector< tuple<int, string> > vURow3;
  vector< tuple<int, string> > vURow4;
  
  vURow1.push_back(make_tuple(0,"Gus Pedroso"));
  vURow1.push_back(make_tuple(1,"1"));
  vURow1.push_back(make_tuple(2,"1234567890"));
  vURow1.push_back(make_tuple(3,"Somewhere Off Campus 1"));

  vURow2.push_back(make_tuple(0,"Levi Clark"));
  vURow2.push_back(make_tuple(1,"2"));
  vURow2.push_back(make_tuple(2,"0987654321"));
  vURow2.push_back(make_tuple(3,"Somewhere Off Campus 2"));

  vURow3.push_back(make_tuple(0,"Terry Chen"));
  vURow3.push_back(make_tuple(1,"3"));
  vURow3.push_back(make_tuple(2,"2222222222"));
  vURow3.push_back(make_tuple(3,"Somewhere On Campus 1"));

  vURow4.push_back(make_tuple(0,"Daniel He"));
  vURow4.push_back(make_tuple(1,"4"));
  vURow4.push_back(make_tuple(2,"3333333333"));
  vURow4.push_back(make_tuple(3,"Somewhere Off Campus 4"));
  
  e.addRow("Other Table", vURow1);
  e.addRow("Other Table", vURow2);
  e.addRow("Other Table", vURow3);
  e.addRow("Other Table", vURow4);
  
  e.setUnion("Main Table", "Other Table");
  e.displayTable("Main Table and Other Table union");
  
  return 0;
}
