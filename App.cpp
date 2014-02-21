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
#include "App.h"
using namespace std;

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
  printf("| I) Show Appointments By Customer\n");
  printf("| J) Show Appointments By Hairdresser\n");
  printf("| K) Show Appointments\n");
  printf("| L) Exit\n");
  printf("|-------------------------------------");
  printf("-----------------------------------------|\n");
  printf("| Enter a selection: ");
}

/*******************************************************************************
Function to show the hair dressers
*******************************************************************************/
void App::showHairDressers()
{

}

/*******************************************************************************
Function to add a hair dresser to the hair dresser relation
*******************************************************************************/
void App::addHairDresser(string sName, string sPhonenumber, string sAddress)
{

}

/*******************************************************************************
Function to remove a hair dresser from the hair dresser relation
*******************************************************************************/
void App::removeHairDresser(int id, string sName, string sPhonenumber, 
  string sAddress)
{

}

/*******************************************************************************
Function to show customers
*******************************************************************************/
void App::showCustomers()
{

}

/*******************************************************************************
Function to add a customer to the hair dresser relation
*******************************************************************************/
void App::addCustomer(string sName, string sPhonenumber, string sAddress)
{

}

/*******************************************************************************
Function to remove a customer to the hair dresser relation
*******************************************************************************/
void App::removeCustomer(int id, string sName, string sPhonenumber, string sAddress)
{

}

/*******************************************************************************
Function to add a appointment to the appointment relation
*******************************************************************************/
void App::addAppt(int iCustomer_id, int iHairdresser_id, string sTime)
{

}

/*******************************************************************************
Function to remove a appointment to the appointment relation
*******************************************************************************/
void App::removeAppt(int id, int iCustomer_id, int iHairdresser_id, string sTime)
{

}

/*******************************************************************************
Function to show appointments
*******************************************************************************/
void App::showAppts(string sStartDate, string sEndDate)
{

}

/*******************************************************************************
Function to project appointments from appointment relation by range
*******************************************************************************/
void App::showApptsByCustomer(int iCustomer_id, string sStartDate, string sEndDate)
{

}

/*******************************************************************************
Function to project appointments from appointment relation by range
*******************************************************************************/
void App::showApptsByHairdresser(int iHairdresser_id, string sStartDate, 
  string sEndDate)
{

}
