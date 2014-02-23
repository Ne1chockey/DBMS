#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Engine.h"
#include "..\Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineUnitTest1
{
TEST_CLASS(DBMSParserTest2)
{
public:
  vector< tuple<string,string,bool> > vColumnNames;
  vector<tuple<int, string> > vRow;
  vector<tuple<int, string> > vRow2;
  vector<tuple<int, string> > vRow3;
  vector<tuple<int, string> > vRow4;
  vector<tuple<int, string> > vRow5;
  vector<string> vKeys;
  Parser p;
  Engine e;

  TEST_METHOD_INITIALIZE(CreateTables)
  {
    // Create the table using the parser
    p.parse("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");

    // Create a hardcoded table to compare against
    vColumnNames.push_back(make_tuple("name","string",true));
    vColumnNames.push_back(make_tuple("kind","string",true));
    vColumnNames.push_back(make_tuple("years","int",false));
    vKeys.push_back("name");
    vKeys.push_back("kind");
    e.createTable("animals_ref", vColumnNames, vKeys);

  }

  TEST_METHOD(ParserTestCreateTable)
  {
    // We created our table above...
    // Let's see if they are the same as our reference.

    // Begin comparison of tables
    bool same = true;

    // Compare the Column content
    std::vector<std::tuple<int, std::string, bool, std::string> > vRefColNames;
    std::vector<std::tuple<int, std::string, bool, std::string> > vParseColNames;

    vRefColNames = e.getTable("animals_ref").getColumnNames();
    vParseColNames = p.getEngine().getTable("animals").getColumnNames();

    if (vRefColNames != vParseColNames)
    {
      same = false;
    }

    // Compare the row content (I should expect nothing in the rows)
    std::vector<std::vector<std::tuple<int, std::string> > > vRefRows;
    std::vector<std::vector<std::tuple<int, std::string> > > vParseRows;

    vRefRows = e.getTable("animals_ref").getRows();
    vParseRows = p.getEngine().getTable("animals").getRows();

    if (vRefRows != vParseRows)
    {
      same = false;
    }

    // Make the assertion that my test succeeded and the tables are the same
    Assert::IsTrue (same);
  }

  TEST_METHOD(ParserTestInsertRows)
  {
    // Let's insert some rows into our table and see if they come out the same

    // Create the rows for our hardcoded table...
    vRow.push_back(make_tuple(0,"Joe"));
    vRow.push_back(make_tuple(1,"cat"));
    vRow.push_back(make_tuple(2,"4"));

    vRow2.push_back(make_tuple(0,"Spot"));
    vRow2.push_back(make_tuple(1,"dog"));
    vRow2.push_back(make_tuple(2,"10"));

    vRow3.push_back(make_tuple(0,"Snoopy"));
    vRow3.push_back(make_tuple(1,"dog"));
    vRow3.push_back(make_tuple(2,"3"));

    vRow4.push_back(make_tuple(0,"Tweety"));
    vRow4.push_back(make_tuple(1,"bird"));
    vRow4.push_back(make_tuple(2,"1"));

    vRow5.push_back(make_tuple(0,"Joe"));
    vRow5.push_back(make_tuple(1,"bird"));
    vRow5.push_back(make_tuple(2,"2"));

    e.addRow("animal_ref", vRow);
    e.addRow("animal_ref", vRow2);
    e.addRow("animal_ref", vRow3);
    e.addRow("animal_ref", vRow4);
    e.addRow("animal_ref", vRow5);

    // Create the rows using our parser for the parser table...
    p.parse("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
    p.parse("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);");
    p.parse("INSERT INTO animals VALUES FROM (\"Spot\", \"dog\", 10);");
    p.parse("INSERT INTO animals VALUES FROM (\"Snoopy\", \"dog\", 3);");
    p.parse("INSERT INTO animals VALUES FROM (\"Tweety\", \"bird\", 1);");
    p.parse("INSERT INTO animals VALUES FROM (\"Joe\", \"bird\", 2);");

    // Now let's see if they are the same...
    // Begin comparison of tables
    bool same = true;

    // Compare the Column content
    std::vector<std::tuple<int, std::string, bool, std::string> > vRefColNames;
    std::vector<std::tuple<int, std::string, bool, std::string> > vParseColNames;

    vRefColNames = e.getTable("animals_ref").getColumnNames();
    vParseColNames = p.getEngine().getTable("animals").getColumnNames();

    if (vRefColNames != vParseColNames)
    {
      same = false;
    }

    // Compare the row content
    // The row vectors should be identical so no reason to iterate through
    std::vector<std::vector<std::tuple<int, std::string> > > vRefRows;
    std::vector<std::vector<std::tuple<int, std::string> > > vParseRows;

    vRefRows = e.getTable("animals_ref").getRows();
    vParseRows = p.getEngine().getTable("animals").getRows();

    if (vRefRows != vParseRows)
    {
      same = false;
    }

    // Make the assertion that my test succeeded and the tables are the same
    Assert::IsTrue (same);
  }
};
}
