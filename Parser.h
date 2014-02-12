/*******************************************************************************
    File: Parser.h

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

    This file contains the header for the parser
*******************************************************************************/

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

class Parser 
{
private:
  //Declare private variables
  vector <string> vValuesRead;

public:
  //Declare class methods
  Parser(){};

  bool readFromFile();
  void parse(string sLineIn);
  void validate();

  //Grammar functions


};

#endif
