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
#include "Parser.h"
using namespace std;

App::App()
{
  //set table versions to zero, needed for relation selections later
  iCountTableVersions = 0;

  p.parse(
      "CREATE TABLE Hairdressers (Name VARCHAR(20), Phone Number VARCHAR(8), Address VARCHAR(20)) PRIMARY KEY (Name, Phone Number)");

  p.parse(
      "CREATE TABLE Customers (Name VARCHAR(20), Phone Number VARCHAR(8), Address VARCHAR(20)) PRIMARY KEY (Name, Phone Number)");

  p.parse(
      "CREATE TABLE Appointments (Customer ID INTEGER, Hairdresser ID INTEGER, Time VARCHAR(10), Date VARCHAR(10)) PRIMARY KEY (Time)");
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
  p.parse(
      "INSERT INTO Hairdressers VALUES FROM (" + sName + ", " + sPhonenumber
          + ", " + sAddress + ")");
}

/*******************************************************************************
 Function to remove a hair dresser from the hair dresser relation
 *******************************************************************************/
void App::removeHairDresser(string sName)
{
  p.parse("DELETE FROM Hairdressers WHERE (Name == " + sName + ")");
}

/*******************************************************************************
 Function to add a customer to the hair dresser relation
 *******************************************************************************/
void App::addCustomer(string sName, string sPhonenumber, string sAddress)
{
  p.parse(
      "INSERT INTO Customers VALUES FROM (" + sName + ", " + sPhonenumber + ", "
          + sAddress + ")");
}

/*******************************************************************************
 Function to remove a customer to the hair dresser relation
 *******************************************************************************/
void App::removeCustomer(string sName)
{
  p.parse("DELETE FROM Customers WHERE (Name == " + sName + ")");
}

/*******************************************************************************
 Function to add a appointment to the appointment relation
 *******************************************************************************/
void App::addAppt(string sCustomer_id, string sHairdresser_id, string sTime,
    string sDate)
{
  p.parse(
      "INSERT INTO Appointments VALUES FROM (" + sCustomer_id + ", "
          + sHairdresser_id + ", " + sTime + ", " + sDate + ")");
}

/*******************************************************************************
 Function to remove a appointment to the appointment relation
 *******************************************************************************/
void App::removeAppt(string sTime)
{
  p.parse("DELETE FROM Appointments WHERE (Time == " + sTime + ")");
}

/*******************************************************************************
 Function to show appointments
 *******************************************************************************/
void App::showAppts(string sStartDate, string sEndDate)
{
  string sTempName = "temp";
  sTempName += static_cast<ostringstream*>(&(ostringstream()
      << iCountTableVersions))->str();
  string sNewName = sTempName + "1";

  //do selection of the appointments table and show it
  p.parse(sTempName + " <- select (Date >= " + sStartDate + ") Appointments");
  p.parse(sNewName + " <- select (Date <= " + sEndDate + ") " + sTempName);
  p.parse("SHOW " + sNewName);
  iCountTableVersions++;
}

/*******************************************************************************
 Function to project appointments from appointment relation by range
 *******************************************************************************/
void App::showApptsByCustomer(string sCustomer_id, string sStartDate,
    string sEndDate)
{
  //do selection of the appointment table for a customer and show it
  string sTempName = "temp";
  sTempName += static_cast<ostringstream*>(&(ostringstream()
      << iCountTableVersions))->str();
  string sNewName = sTempName + "1";
  string sFinalName = sNewName + "2";

  p.parse(sTempName + " <- select (Date >= " + sStartDate + ") Appointments");
  p.parse(sNewName + " <- select (Date <= " + sEndDate + ") " + sTempName);
  p.parse(sFinalName + " <- select (Date == " + sCustomer_id + ") " + sNewName);
  p.parse("SHOW " + sFinalName);
  iCountTableVersions++;
}

/*******************************************************************************
 Function to project appointments from appointment relation by range
 *******************************************************************************/
void App::showApptsByHairdresser(string sHairdresser_id, string sStartDate,
    string sEndDate)
{
  //do selection of the appointment table for a hair dresser and show it
  string sTempName = "temp";
  sTempName += static_cast<ostringstream*>(&(ostringstream()
      << iCountTableVersions))->str();
  string sNewName = sTempName + "1";
  string sFinalName = sNewName + "2";

  p.parse(sTempName + " <- select (Date >= " + sStartDate + ") Appointments");
  p.parse(sNewName + " <- select (Date <= " + sEndDate + ") " + sTempName);
  p.parse(
      sFinalName + " <- select (Date == " + sHairdresser_id + ") " + sNewName);
  p.parse("SHOW " + sFinalName);
  iCountTableVersions++;
}
