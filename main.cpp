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
#include "App.h"
using namespace std;

bool validatePhone(string &sPhoneIn);
bool validateDate(string &sDateIn);

int main() 
{
  //Declaring and initializing variables
  App a;
  char cMainChoice;
  int iAppointmentID, iCustomerID, iHairdresserID;
  string sName, sPhoneNumber, sAddress, sStartDate, sEndDate, sTime;

  do
  {
    //To display a menu of choices for the user to choose from
    printf("\n");
    a.displayMenu();
    cin >> cMainChoice;
    
    //Process the user's selection
    switch(cMainChoice) 
    {
      case 'a': 
      case 'A': a.showHairDressers();
        break;
      case 'b': 
      case 'B': 
        //Gather hair dresser's information
        printf("| Enter the Hair Dresser's name: ");
        cin >> sName;
        printf("| Enter the Hair Dresser's phone number: ");
        cin >> sPhoneNumber;

        while(!validatePhone(sPhoneNumber))
        {
          printf("| Phone number format incorrect, try again: ");
          cin >> sPhoneNumber;
        }

        printf("| Enter the Hair Dresser's address: ");
        cin >> sAddress;
        a.addHairDresser(sName, sPhoneNumber, sAddress);
        break;
      case 'c':
      case 'C':
        //Gather info to delete hair dresser
        printf("| Enter the Hair Dresser's id: ");
        cin >> iHairdresserID;
        printf("| Enter the Hair Dresser's name: ");
        cin >> sName;
        printf("| Enter the Hair Dresser's phone number: ");
        cin >> sPhoneNumber;

        while(validatePhone(sPhoneNumber))
        {
          printf("| Phone number format incorrect, try again: ");
          cin >> sPhoneNumber;
        }

        printf("| Enter the Hair Dresser's address: ");
        cin >> sAddress;
        a.removeHairDresser(iHairdresserID, sName, sPhoneNumber, sAddress);
        break;
      case 'd':
      case 'D': a.showCustomers();
        break;
      case 'e':
      case 'E':
        //Gather customer's information
        printf("| Enter the Customer's name: ");
        cin >> sName;
        printf("| Enter the Customer's phone number: ");
        cin >> sPhoneNumber;

        while(validatePhone(sPhoneNumber))
        {
          printf("| Phone number format incorrect, try again: ");
          cin >> sPhoneNumber;
        }

        printf("| Enter the Customer's address: ");
        cin >> sAddress;
        a.addCustomer(sName, sPhoneNumber, sAddress);
        break;
      case 'f':
      case 'F':
        //Gather info to delete customer
        printf("| Enter the Customer's id: ");
        cin >> iCustomerID;
        printf("| Enter the Customer's name: ");
        cin >> sName;
        printf("| Enter the Customer's phone number: ");
        cin >> sPhoneNumber;

        while(validatePhone(sPhoneNumber))
        {
          printf("| Phone number format incorrect, try again: ");
          cin >> sPhoneNumber;
        }

        printf("| Enter the Customer's address: ");
        cin >> sAddress;
        a.removeCustomer(iCustomerID, sName, sPhoneNumber, sAddress);
        break;
      case 'g':
      case 'G':
        //Gather info to add appointment
        printf("| Enter the Customer's id: ");
        cin >> iCustomerID;
        printf("| Enter the Hairdresser's id: ");
        cin >> iHairdresserID;
        printf("| Enter the time: ");
        cin >> sTime;
        a.addAppt(iCustomerID, iHairdresserID, sTime);
        break;
      case 'h':
      case 'H':
        //Gather info to remove appointment
        printf("| Enter the Appointment's id: ");
        cin >> iAppointmentID;
        printf("| Enter the Customer's id: ");
        cin >> iCustomerID;
        printf("| Enter the Hairdresser's id: ");
        cin >> iHairdresserID;
        printf("| Enter the time: ");
        cin >> sTime;
        a.removeAppt(iAppointmentID, iCustomerID, iHairdresserID, sTime);
        break;
      case 'i':
      case 'I':
        //Gather info to show customer's appointments
        printf("| Enter the Customer's id: ");
        cin >> iCustomerID;
        printf("| Enter a Start date: ");
        cin >> sStartDate;

        while(validateDate(sStartDate))
        {
          printf("| Date format incorrect, try again: ");
          cin >> sStartDate;
        }

        printf("| Enter an End dat: ");
        cin >> sEndDate;

        while(validateDate(sEndDate))
        {
          printf("| Date format incorrect, try again: ");
          cin >> sEndDate;
        }

        a.showApptsByCustomer(iCustomerID, sStartDate, sEndDate);
        break;
      case 'j':
      case 'J':
        //Gather info to show hairdresser's appointments
        printf("| Enter the Hairdresser's id: ");
        cin >> iHairdresserID;
        printf("| Enter a Start date: ");
        cin >> sStartDate;

        while(validateDate(sStartDate))
        {
          printf("| Date format incorrect, try again: ");
          cin >> sStartDate;
        }

        printf("| Enter an End dat: ");
        cin >> sEndDate;

        while(validateDate(sEndDate))
        {
          printf("| Date format incorrect, try again: ");
          cin >> sEndDate;
        }

        a.showApptsByCustomer(iHairdresserID, sStartDate, sEndDate);
        break;
      case 'k':
      case 'K':
        //Gather a range for showing appts
        printf("| Enter a Start date: ");
        cin >> sStartDate;

        while(validateDate(sStartDate))
        {
          printf("| Date format incorrect, try again: ");
          cin >> sStartDate;
        }

        printf("| Enter an End dat: ");
        cin >> sEndDate;

        while(validateDate(sEndDate))
        {
          printf("| Date format incorrect, try again: ");
          cin >> sEndDate;
        }

        a.showAppts(sStartDate, sEndDate);
        break;
      case 'l':
      case 'L': printf("| Goodbye :)\n");
        break;
      default:
        printf("| Invalid selection, please try again.\n");
    }
  } while (toupper(cMainChoice) != 'L'); //When 'E' is inputted the program ends
  
  /*
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
  if (pFileTest.readFromFile("testInput.txt"))
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
  */
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

bool validateDate(string &sDateIn)
{
  //Initializing and declaring variables
  int iCount = 0, iDay, iMonth, iYear;
  string sDay, sMonth, sYear;

  //Month-Day-Year format for date

  //Check to see if date is valid in multiple sizes and insert the missing parts
  if (sDateIn.length() == 6)
  {
    //(9/9/99)
    if ((ispunct(sDateIn[1]) && ispunct(sDateIn[3])) && (sDateIn[1] == sDateIn[3]))
    {
      sDateIn.insert(0, "0");
      sDateIn.insert(3, "0");
      string sDateInEnd = sDateIn.substr(6, 2);
      int iTemp = atoi(sDateInEnd.c_str());
      if (iTemp > 13)
      {
        sDateIn.insert(6, "1");
        sDateIn.insert(7, "9");
      }
      else
      {
        sDateIn.insert(6, "2");
        sDateIn.insert(7, "0");
      }
      
    }
    else
      return true;
  }
  if (sDateIn.length() == 7)
  {
    //(9/99/99)
    if ((ispunct(sDateIn[1]) && ispunct(sDateIn[4])) && (sDateIn[1] == sDateIn[4]))
    {

      sDateIn.insert(0, "0");
      string sDateInEnd = sDateIn.substr(6, 2);
      int iTemp = atoi(sDateInEnd.c_str());
      if (iTemp > 13)
      {
        sDateIn.insert(6, "1");
        sDateIn.insert(7, "9");
      }
      else
      {
        sDateIn.insert(6, "2");
        sDateIn.insert(7, "0");
      }
    }
    //(99/9/99)
    else if ((ispunct(sDateIn[2]) && ispunct(sDateIn[4])) && (sDateIn[2] == sDateIn[4]))
    {
      sDateIn.insert(4, "0");
      string sDateInEnd = sDateIn.substr(6, 2);
      int iTemp = atoi(sDateInEnd.c_str());
      if (iTemp > 13)
      {
        sDateIn.insert(6, "1");
        sDateIn.insert(7, "9");
      }
      else
      {
        sDateIn.insert(6, "2");
        sDateIn.insert(7, "0");
      }
    }
    else
      return true;
  }
  if (sDateIn.length() == 8)
  {
    //(99/99/99)
    if ((ispunct(sDateIn[2]) && ispunct(sDateIn[5])) && (sDateIn[2] == sDateIn[5]))
    {
      string sDateInEnd = sDateIn.substr(6, 2);
      int iTemp = atoi(sDateInEnd.c_str());
      if (iTemp > 13)
      {
        sDateIn.insert(6, "1");
        sDateIn.insert(7, "9");
      }
      else
      {
        sDateIn.insert(6, "2");
        sDateIn.insert(7, "0");
      }
    }
    //(9/9/9999)
    else if ((ispunct(sDateIn[1]) && ispunct(sDateIn[3])) && (sDateIn[1] == sDateIn[3]))
    {
      sDateIn.insert(0, "0");
      sDateIn.insert(3, "0");
    }
    else
      return true;
  }
  //Add a zero to the front of day or month if user didnt input it
  if (sDateIn.length() == 9)
  {
    //(9/99/9999)
    if ((ispunct(sDateIn[1]) && ispunct(sDateIn[4])) && (sDateIn[1] == sDateIn[4]))
    {
      sDateIn.insert(0, "0");
    }
    //(99/9/9999)
    else if ((ispunct(sDateIn[2]) && ispunct(sDateIn[4])) && (sDateIn[2] == sDateIn[4]))
    {
      sDateIn.insert(3, "0");
    }
    else
      return true;
  }
  if (sDateIn.length() == 10)
  {
    //(99/99/9999) now that it is formatted we can validate numbers
    if ((ispunct(sDateIn[2]) && ispunct(sDateIn[5])) && (sDateIn[2] == sDateIn[5]))
    {
      //Declare the variables
      sMonth = sDateIn.substr(0, 2);
      sDay = sDateIn.substr(3, 2);
      sYear = sDateIn.substr(6, 4);
    }
    else
      return true;

    iDay = atoi(sDay.c_str());
    iMonth = atoi(sMonth.c_str());
    iYear = atoi(sYear.c_str());

    if (iDay < 1 || iDay > 31 || iMonth < 1 || iMonth > 12 || iYear < 1900 
      || iYear > 2013)
      return true;
    else
    {
      if ((iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11) && iDay > 30)
        return true;
      else
      {
        if (iMonth == 2)
        {
          //Determine if its a leap year
          if ((iYear % 4 == 0) && !(iYear % 100 == 0)|| (iYear % 400 == 0))
          {
            if (iDay > 29)
              return true;
          }
          else
            if (iDay > 28)
              return true;
        }
      }
    }

    return false;
  }

  //Send back the outcome
  return true;
}

bool validatePhone(string &sPhoneIn)
{
  //boolean value set true, will change to false if matching word found
  bool bOutcome = true;
  int iCount = 0;

  //If first element in the phone number is not a paran and not a num, return
  if (sPhoneIn[0] != '(' && !isdigit(sPhoneIn[0]))
    return bOutcome;

  //If the phone number is too short or too long return
  if (sPhoneIn.length() < 10 || sPhoneIn.length() > 13)
    return bOutcome;

  bOutcome = false;

  //Loop while the number being tested is not null
  while (sPhoneIn[iCount] != '\0')
  {
    //Make bOutcome true if any of the elements are nonnum
    if (!isdigit(sPhoneIn[iCount]))
      bOutcome = true;
    
    //Increment counter
    iCount++;
  }


  //If its all numbers and no formatting, we will format for the lazy user
  if (bOutcome == false && sPhoneIn.length() == 10)
  {
    int iCount2 = 0;

      sPhoneIn.insert(0, "(");
      sPhoneIn.insert(4, ")");
      sPhoneIn.insert(8, "-");

      while (sPhoneIn[iCount2] != '\0')
      {
        sPhoneIn[iCount2] = sPhoneIn[iCount2];
        iCount2++;
      }

      sPhoneIn[iCount2] = '\0';
  }
  else if (bOutcome == false && sPhoneIn.length() != 10)
  {
    bOutcome = true;
  }
  else if (bOutcome == true)
  {
    //Test to see if the number is formatted or just garbage
    if (sPhoneIn[0] == '(' && sPhoneIn[4] == ')' && sPhoneIn[8] == '-')
      bOutcome = false;
    else
      bOutcome = true;
  }
      
  //Send back the outcome
    return bOutcome;
}
