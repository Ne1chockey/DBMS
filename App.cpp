/*******************************************************************************
 File: App.cpp

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

 This file contains the implementation for the App
 *******************************************************************************/

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "App.h"
#include "Engine.h"
using namespace std;

App::App()
{
  //Declare variables for creating the necessary relations
  vector < tuple<string, string, bool> > vColumnNames;
  vector < string > vKeys;

  //Create columns for the hairdresser relation
  vColumnNames.push_back(make_tuple("Name", "string", false));
  vColumnNames.push_back(make_tuple("Phone Number", "string", false));
  vColumnNames.push_back(make_tuple("Address", "string", false));
  vKeys.push_back("Name");
  vKeys.push_back("Phone Number");

  //create the hairdresser relation
  e.createTable("Hairdressers", vColumnNames, vKeys);

  //clear the vector for the next relation info
  vColumnNames.clear();
  vKeys.clear();

  //Create columns for the hairdresser relation
  vColumnNames.push_back(make_tuple("Name", "string", false));
  vColumnNames.push_back(make_tuple("Phone Number", "string", false));
  vColumnNames.push_back(make_tuple("Address", "string", false));
  vKeys.push_back("Name");
  vKeys.push_back("Phone Number");

  //create the hairdresser relation
  e.createTable("Customers", vColumnNames, vKeys);

  //clear the vector for the next relation info
  vColumnNames.clear();
  vKeys.clear();

  //Create columns for the hairdresser relation
  vColumnNames.push_back(make_tuple("Customer ID", "integer", false));
  vColumnNames.push_back(make_tuple("Hairdresser ID", "integer", false));
  vColumnNames.push_back(make_tuple("Time", "string", false));
  vColumnNames.push_back(make_tuple("Date", "string", false));
  vKeys.push_back("Date");

  //create the hairdresser relation
  e.createTable("Appointments", vColumnNames, vKeys);
}

/*******************************************************************************
 Function to display the menu
 *******************************************************************************/
void App::displayMenu()
{
  printf("\n|-------------------------------------");
  printf("-----------------------------------------|\n");
  printf("|                             Salon Application");
  printf("                                |\n");
  printf("|-------------------------------------");
  printf("-----------------------------------------|\n");
  printf("| A) Display Hairdressers\n");
  printf("| B) Add Hairdressers\n");
  printf("| C) Remove Hairdresser\n");
  printf("| D) Display Customers\n");
  printf("| E) Add Customer\n");
  printf("| F) Remove Customer\n");
  printf("| G) Add Appointment\n");
  printf("| H) Remove Appointment\n");
  printf("| I) Display Appointments By Customer\n");
  printf("| J) Display Appointments By Hairdresser\n");
  printf("| K) Display Appointments in range\n");
  printf("| L) Display All Appointments\n");
  printf("| M) Exit\n");
  printf("|-------------------------------------");
  printf("-----------------------------------------|\n");
  printf("| Enter a selection: ");
}

/*******************************************************************************
 Function to add a hair dresser to the hair dresser relation
 *******************************************************************************/
void App::addHairDresser(string sName, string sPhonenumber, string sAddress)
{
  vector < tuple<int, string> > vRow;

  vRow.push_back(make_tuple(0, sName));
  vRow.push_back(make_tuple(1, sPhonenumber));
  vRow.push_back(make_tuple(2, sAddress));

  //Add row to the relation
  e.addRow("Hairdressers", vRow);
}

/*******************************************************************************
 Function to remove a hair dresser from the hair dresser relation
 *******************************************************************************/
void App::removeHairDresser(string id, string sName, string sPhonenumber,
    string sAddress)
{
  vector < tuple<int, string> > vRow;

  vRow.push_back(make_tuple(0, sName));
  vRow.push_back(make_tuple(1, sPhonenumber));
  vRow.push_back(make_tuple(2, sAddress));

  e.deleteRow("Hairdressers", vRow);
}

/*******************************************************************************
 Function to add a customer to the hair dresser relation
 *******************************************************************************/
void App::addCustomer(string sName, string sPhonenumber, string sAddress)
{
  vector < tuple<int, string> > vRow;

  vRow.push_back(make_tuple(0, sName));
  vRow.push_back(make_tuple(1, sPhonenumber));
  vRow.push_back(make_tuple(2, sAddress));

  //Add row to the relation
  e.addRow("Customers", vRow);
}

/*******************************************************************************
 Function to remove a customer to the hair dresser relation
 *******************************************************************************/
void App::removeCustomer(string id, string sName, string sPhonenumber,
    string sAddress)
{
  vector < tuple<int, string> > vRow;

  vRow.push_back(make_tuple(0, sName));
  vRow.push_back(make_tuple(1, sPhonenumber));
  vRow.push_back(make_tuple(2, sAddress));

  e.deleteRow("Customers", vRow);
}

/*******************************************************************************
 Function to add a appointment to the appointment relation
 *******************************************************************************/
void App::addAppt(string sCustomer_id, string sHairdresser_id, string sTime,
    string sDate)
{
  vector < tuple<int, string> > vRow;

  vRow.push_back(make_tuple(0, sCustomer_id));
  vRow.push_back(make_tuple(1, sHairdresser_id));
  vRow.push_back(make_tuple(2, sTime));
  vRow.push_back(make_tuple(3, sDate));

  e.addRow("Appointments", vRow);
}

/*******************************************************************************
 Function to remove a appointment to the appointment relation
 *******************************************************************************/
void App::removeAppt(string id, string sCustomer_id, string sHairdresser_id,
    string sTime, string sDate)
{
  vector < tuple<int, string> > vRow;

  vRow.push_back(make_tuple(0, sCustomer_id));
  vRow.push_back(make_tuple(1, sHairdresser_id));
  vRow.push_back(make_tuple(2, sTime));
  vRow.push_back(make_tuple(3, sDate));

  e.deleteRow("Appointments", vRow);
}

/*******************************************************************************
 Function to show appointments
 *******************************************************************************/
void App::showAppts(string sStartDate, string sEndDate)
{
  string sTempName = "temp ";
  sTempName += static_cast<ostringstream*>(&(ostringstream()
      << iCountTableVersions))->str();
  string sNewName = "Appt Range (" + sStartDate + " - " + sEndDate + ")";

  //do selection of the appointments table and show it
  e.selection("Appointments", sTempName, ">=", "Date", sStartDate);
  e.displayTable(sTempName);
  e.selection(sTempName, sNewName, "<=", "Date", sEndDate);
  e.displayTable(sNewName);
  iCountTableVersions++;
}

/*******************************************************************************
 Function to project appointments from appointment relation by range
 *******************************************************************************/
void App::showApptsByCustomer(string sCustomer_id, string sStartDate,
    string sEndDate)
{
  //do selection of the customer table and show it
  //e.selection();
  //e.displayTable();
}

/*******************************************************************************
 Function to project appointments from appointment relation by range
 *******************************************************************************/
void App::showApptsByHairdresser(string sHairdresser_id, string sStartDate,
    string sEndDate)
{
  //do selection of the customer table and show it
  //e.selection();
  //e.displayTable();
}
