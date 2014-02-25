/*******************************************************************************
 File: App.h

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

 This file contains the header for the app
 *******************************************************************************/

#ifndef APP_H
#define APP_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Parser.h"
using namespace std;

/*******************************************************************************
 Database Schema:

 Hair Dresser: ID, name, Phone number, address
 Customers: ID, name, phone number, address
 Appointments: ID, customer_id, hairdresser_id, time, date
 *******************************************************************************/

class App
{
private:
  //Declare private variables
  Parser p;
  int iCountTableVersions;// = 0;

public:
  //Declare class methods
  App();

  void displayMenu();
  void showHairDressers()
  {
    p.parse("SHOW Hairdressers");
  }

  void addHairDresser(string sName, string sPhonenumber, string sAddress);
  void removeHairDresser(string sName);

  void showCustomers()
  {
    p.parse("SHOW Customers");
  }
  void addCustomer(string sName, string sPhonenumber, string sAddress);
  void removeCustomer(string sName);

  void addAppt(string sCustomer_id, string sHairdresser_id, string sTime,
      string sDate);
  void removeAppt(string sTime);
  void showAppts(string sStartDate, string sEndDate);
  void showApptsByCustomer(string sCustomer_id, string sStartDate,
      string sEndDate);
  void showApptsByHairdresser(string sHairdresser_id, string sStartDate,
      string sEndDate);

  void showAppointments()
  {
    p.parse("SHOW Appointments");
  }
};

#endif
