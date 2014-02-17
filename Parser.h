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
#include "Engine.h"
using namespace std;

class Parser 
{
private:
  //Declare private variables
  vector <string> vValuesRead;
  Engine e;

public:
	//Tree data structure
	struct treeNode{
		char data;
		treeNode *leftChild;
		treeNode *rightChild;
	};
	
	//Tree functions
	void traversal(treeNode *start); //In Order Traversal
  //Declare class methods
  Parser(){};

  bool readFromFile();
  void parse(string sLineIn);
  void validate();

  //Grammar functions
  bool findCreateTable(string sLineIn);
  bool findInsertInto(string sLineIn);
  bool findShow(string sLineIn);
  bool findWrite(string sLineIn);
  bool findOpen(string sLineIn);
  bool findClose(string sLineIn);
  bool findExit(string sLineIn);
  bool findArrow(string sLineIn);
  /*
  string query(string sRelationName, string sExpr);
  string relationName(string iIdentifier);
  string identifier(char cAlpha, char cAlphaOrDigit);
  string alpha(char cAlpha);
  string digit(char cDigit);
  string expr(string sExpr);
  string atomicExpr(string sRelationNameOrExpr);
  string selection(string sCondition, string sAtomicExpr);
  */

  //helper functions 
  vector<tuple<string,string,bool> > createColVector (string sLineIn);
  vector<string> createVector (string sLineIn);
  vector< tuple<int, string> > createRowVector (string sLineIn);
  string cleanSpaces(string sLineIn);
  bool checkParenthesis(string sLineIn);
};

#endif
