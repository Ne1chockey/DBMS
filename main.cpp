/*******************************************************************************
    File: main.cpp

    Authors: Gustavo Pedroso UIN: 423002834
             Levi Clark      UIN: 520007880
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
#include "Parser.h"
using namespace std;



int main() 
{
  //Declare variables
  vector< tuple<string,string,bool> > vColumnNames;
  vector< tuple<int, string> > vRow;
  vector< tuple<int, string> > vRow2;
  vector< tuple<int, string> > vRow3;
  vector< tuple<int, string> > vRow4;
  vector< tuple<int, string> > vRow5;
  vector<string> vKeys;
  Engine e;
  Parser pFileTest;
  Parser pCommandLineTest;
  string sLineIn;
  int iParse = 1;
  
  //Test the parser reading from a file
  if (pFileTest.readFromFile())
  {
    //the file was read properly and values were parsed 
    printf("The file was found.\n");
  }
  
  //Test the parser reading from command line input
  while (iParse)
  {
    printf("Enter line for parser: ");
    cin >> sLineIn;

    pCommandLineTest.parse(sLineIn);
    cin.clear();
    cin.ignore();
    printf("Enter another line? 1 or 0: ");
    cin >> iParse;
  }


  /***********************************************************************
    ENGINE TESTING BELOW, UNCOMMENT TO SEE
  ************************************************************************/
  /*
  //Create columns for the main table
  vColumnNames.push_back(make_tuple("Name","string",false));
  vColumnNames.push_back(make_tuple("Age","int",false));
  vColumnNames.push_back(make_tuple("Phone Number","string",false));
  vColumnNames.push_back(make_tuple("Address","string",false));
  vKeys.push_back("Name");
  //create a main table to work with
  e.createTable("Main Table", vColumnNames, vKeys);

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
  e.displayTable("Main Table");
  e.displayTable("Equality Table");
  cout << "The equality test is age == 23" << endl;
  cout << "Press Enter to continue..." << endl;
  cin.get();

   
  //Projection testing
  vector<string> vColNames;
  vColNames.push_back("Name");
  vColNames.push_back("Age");

  e.projection("Main Table", vColNames);

  e.displayTable("Main Table projection");
  cout << "Name and Age values are projected. " << endl;
  cout << "Press Enter to continue..." << endl;
  cin.get();

  // Rename Testing
  string testValue1 = "Full Name";
  string testValue2 = "Oldness";
  string testValue3 = "Digits";
  string testValue4 = "Ma house";
  vector<string> renames;
  renames.push_back(testValue1);
  renames.push_back(testValue2);
  renames.push_back(testValue3);
  renames.push_back(testValue4);
  e.reNaming(renames, "Equality Table");
  
  e.displayTable("Equality Table renamed");
  cout << "Press Enter to continue..." << endl;
  cin.get();
  
  // Union Testing
  e.createTable("Other Table", vColumnNames, vKeys);
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
  e.displayTable("Main Table");
  e.displayTable("Other Table");
  e.setUnion("Main Table", "Other Table");
  e.displayTable("Main Table and Other Table union");
  cout << "Press Enter to continue..." << endl;
  cin.get();
  
  // Difference Testing (relies on content fron union testing)
  cout << endl << endl;
  
  e.displayTable("Main Table");
  e.displayTable("Other Table");
 
  e.setDifference("Main Table", "Other Table");
  e.displayTable("Main Table and Other Table difference");
  cout << "Press Enter to continue..." << endl;
  cin.get();
  
  e.setDifference("Other Table", "Main Table");
  e.displayTable("Main Table");
  e.displayTable("Other Table");
  e.displayTable("Other Table and Main Table difference");
  cout << "Press Enter to continue..." << endl;
  cin.get();
  
  //Crossproduct testing
  e.crossProduct("Main Table", "Other Table");
  e.displayTable("Main Table");
  e.displayTable("Other Table");
  e.displayTable("Main Table and Other Table cross product");
  cout << "Press Enter to continue..." << endl;
  cin.get();

  //Natural Join testing
  e.addColumn("Other Table", "Extra Column", "string",false);
  e.addColumn("Other Table", "Another Column", "string",false);
  e.addColumn("Other Table", "And Another", "string",false);
  e.displayTable("Main Table");
  e.displayTable("Other Table");
  e.naturalJoin("Main Table", "Other Table");
  e.displayTable("Main Table and Other Table natural join");
  cout << "Press Enter to continue..." << endl;
  cin.get();

  //testing update
  e.displayTable("Other Table");
  vector <string> vCN;
  vCN.push_back("Nameddd");
  vector <string> vNVal;
  vNVal.push_back("lllllevi");
  vector<tuple<string, string, string> > comparison;
  comparison.push_back(make_tuple("Name", "==", "Levi Clark"));

  e.update(vCN, vNVal, "Other Table", comparison);
  e.displayTable("Other Table");
  cout << "Press Enter to continue..." << endl;
  cin.get();
  e.displayTable("Main Table");
  e.displayTable("Other Table");
  e.dropTable("Other Table");
  e.displayTable("Main Table");
  e.displayTable("Other Table");
  cout << "Press Enter to continue..." << endl;
  cin.get();
  */
  return 0;
}
