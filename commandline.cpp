/*******************************************************************************
 File: commandline.cpp

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

 This file contains the commandline file
 *******************************************************************************/

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include "Parser.h"
using namespace std;

   
int main()
{
   Parser pCommandLineTest;
   string sLineIn;
   string sAgain = "1";

   //Test the parser reading from command line input
   while (sAgain == "1")
   {
      printf("Enter line for parser: ");
      getline(cin,sLineIn);

      pCommandLineTest.parse(sLineIn);
      printf("Enter another line? 1 or 0: ");
      getline(cin, sAgain);
   }

   return 0;
}