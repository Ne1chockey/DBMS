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
#include "Engine.h"
using namespace std;

/*******************************************************************************
Database Schema:

Hair Dresser: ID, name, Phone number, address
Customers: ID, anme, phone number, address
Appointments: ID, customer_id, hairdresser_id, time
*******************************************************************************/

class App 
{
private:
  //Declare private variables

public:
  //Declare class methods
  App(){};

  void displayMenu();
  void showHairDressers();
  void addHairDresser(string sName, string sPhonenumber, string sAddress);
  void removeHairDresser(int id, string sName, string sPhonenumber, string sAddress);

  void showCustomers();
  void addCustomer(string sName, string sPhonenumber, string sAddress);
  void removeCustomer(int id, string sName, string sPhonenumber, string sAddress);


  void addAppt(int iCustomer_id, int iHairdresser_id, string sTime);
  void removeAppt(int id, int iCustomer_id, int iHairdresser_id, string sTime);
  void showAppts(string sStartDate, string sEndDate);
  void showApptsByCustomer(int iCustomer_id, string sStartDate, string sEndDate);
  void showApptsByHairdresser(int iHairdresser_id, string sStartDate, string sEndDate);
};

#endif
