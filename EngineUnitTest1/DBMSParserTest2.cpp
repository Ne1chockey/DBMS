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

  // This initialization will create a table "animals" with some columns.
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

  // This method will test of initialization above created our table properly.
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

  // This method will test if we can read from a file. 
  TEST_METHOD(ParserTestReadFile)
  {
    // Our reference table is already created. We just need to insert data.
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

    // Now let's read from our file with the parser.
    p.readFromFile("testAnimals.txt");

    // Now let's see if they are the same...
    // Begin comparison of tables
    bool same = false;

    // Compare the Column content
    std::vector<std::tuple<int, std::string, bool, std::string> > vRefColNames;
    std::vector<std::tuple<int, std::string, bool, std::string> > vParseColNames;

    vRefColNames = e.getTable("animals_ref").getColumnNames();
    vParseColNames = p.getEngine().getTable("animals").getColumnNames();

    // Compare the row content
    // The row vectors should be identical so no reason to iterate through
    std::vector<std::vector<std::tuple<int, std::string> > > vRefRows;
    std::vector<std::vector<std::tuple<int, std::string> > > vParseRows;

    vRefRows = e.getTable("animals_ref").getRows();
    vParseRows = p.getEngine().getTable("animals").getRows();

    if (vRefColNames == vParseColNames)
    {
      if (vRefRows == vParseRows)
      {
        same = true;
      }
    }

    // Make the assertion that my test succeeded and the tables are the same
    Assert::IsTrue (same);
  }

  // This method will test if we can insert rows using the parser commands. 
  TEST_METHOD(ParserTestInsertInto)
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

  //TEST_METHOD(ParserTestUpdateRows) 
  //{
  //  ////////////////////////////////////////////////////
  //  /// NEED OUR CONDITIONS TO WORK FOR THIS TEST!!! ///
  //  ////////////////////////////////////////////////////

  //  Assert::IsTrue(false);

  //}

  //TEST_METHOD(ParserTestDeleteRows) 
  //{
  //  ////////////////////////////////////////////////////
  //  /// NEED OUR CONDITIONS TO WORK FOR THIS TEST!!! ///
  //  ////////////////////////////////////////////////////

  //  Assert::IsTrue(false);

  //}

  //TEST_METHOD(ParserTestSelection) 
  //{
  //  ////////////////////////////////////////////////////
  //  /// NEED OUR CONDITIONS TO WORK FOR THIS TEST!!! ///
  //  ////////////////////////////////////////////////////

  //  Assert::IsTrue(false);

  //}

  // This will test the projection feature
  TEST_METHOD(ParserTestProjection)
  {
    // We want to test our projection feature of the parser.
    // Let's create a table first using our parser.
    p.parse("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);");
    p.parse("INSERT INTO animals VALUES FROM (\"Spot\", \"dog\", 10);");
    p.parse("INSERT INTO animals VALUES FROM (\"Snoopy\", \"dog\", 3);");
    p.parse("INSERT INTO animals VALUES FROM (\"Tweety\", \"bird\", 1);");
    p.parse("INSERT INTO animals VALUES FROM (\"Joe\", \"bird\", 2);");

    // I want to project only the names into a table called projected
    p.parse("projected <- project (name) animals");

    // Gonna create a vector of just the names.
    std::vector<std::string> animalNames;
    animalNames.push_back("Joe");
    animalNames.push_back("Spot");
    animalNames.push_back("Snoopy");
    animalNames.push_back("Tweety");
    animalNames.push_back("Joe");

    // Now we can grab our table from the parser and compare. We should get only names.
    bool good = false;

    Table projectTest = p.getEngine().getTable("projected");
    std::vector<std::tuple<int, std::string, bool, std::string> > vColValues;
    vColValues = projectTest.getColumnNames();

    std::vector<std::vector<std::tuple<int, std::string> > > vRowValues;
    vRowValues = projectTest.getRows();

    if (get<1>(vColValues[0]) == "name")
    {
      if (vRowValues.size() == animalNames.size())
      {
        good = true;
        for (int i = 0; i < animalNames.size(); i++)
        {
          string sRowNameEntry = get<1>((vRowValues[i])[0]);
          if (sRowNameEntry != animalNames[i])
          {
            good = false;
          }
        }
      }
    }

    Assert::IsTrue (good);
  }

  TEST_METHOD(ParserTestRenaming)
  {
    // Let's rename the columns of the table we created earlier...

    // New Names
    string sCol1NameNew = "animal_name";
    string sCol2NameNew = "animal_kind";
    string sCol3NameNew = "animal_years";
    string sTableNameNew = "animal_table";
    vector<string> vNewNames;
    vNewNames.push_back(sCol1NameNew);
    vNewNames.push_back(sCol2NameNew);
    vNewNames.push_back(sCol3NameNew);

    p.parse("animal_table <- rename (animal_name, animal_kind, animal_years) animals;");

    bool good = true;

    // Let's see if we can get our new table...
    Table check = p.getEngine().getTable(sTableNameNew);

    // And now we can check to see if our names are renamed.
    std::vector<std::tuple<int, std::string, bool, std::string> > vColNames;
    vColNames = check.getColumnNames();

    for (int i = 0; i < vNewNames.size(); i++)
    {
      if (vNewNames[i] != get<1>(vColNames[i]))
      {
        good = false;
      }
    }

    Assert::IsTrue (good);
  }

  // This method will test union with the parser. 
  TEST_METHOD(ParserTestSetUnion)
  {
    // Let's insert some rows into our current table first.
    p.parse("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
    p.parse("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);");
    p.parse("INSERT INTO animals VALUES FROM (\"Spot\", \"dog\", 10);");

    // Now let's create another table to union with this one. 
    p.parse("CREATE TABLE moreAnimals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
    p.parse("INSERT INTO moreAnimals VALUES FROM (\"Mikey\", \"lion\", 5);");
    p.parse("INSERT INTO moreAnimals VALUES FROM (\"Nemo\", \"clownfish\", 1);");
    // Add a row from the first table to see if it handles duplicates
    p.parse("INSERT INTO moreAnimals VALUES FROM (\"Joe\", \"cat\", 4);");

    // Make a reference table... We will compare our result to this.
    vRow.push_back(make_tuple(0,"Joe"));
    vRow.push_back(make_tuple(1,"cat"));
    vRow.push_back(make_tuple(2,"4"));

    vRow2.push_back(make_tuple(0,"Spot"));
    vRow2.push_back(make_tuple(1,"dog"));
    vRow2.push_back(make_tuple(2,"10"));

    vRow4.push_back(make_tuple(0, "Mikey"));
    vRow4.push_back(make_tuple(1, "lion"));
    vRow4.push_back(make_tuple(2, "5"));

    vRow5.push_back(make_tuple(0, "Nemo"));
    vRow5.push_back(make_tuple(1, "clownfish"));
    vRow5.push_back(make_tuple(2, "1"));

    string sTableName3 = "animalsUnioned";
    e.createTable(sTableName3, vColumnNames, vKeys);
    e.addRow(sTableName3, vRow);
    e.addRow(sTableName3, vRow2);
    e.addRow(sTableName3, vRow4);
    e.addRow(sTableName3, vRow5);

    // Set the union.
    p.parse("unionTest <- animals + moreAnimals;");

    // Compare our results.
    Table t1 = p.getEngine().getTable("unionTest");
    Table tRef = e.getTable(sTableName3);
    std::vector<std::vector<std::tuple<int, std::string> > > t1Rows;
    std::vector<std::vector<std::tuple<int, std::string> > > tRefRows;
    t1Rows = t1.getRows();
    tRefRows = tRef.getRows();

    if (t1.getColumnNames() == tRef.getColumnNames())
    {
      bool found = false;
      for (int i = 0; i < tRefRows.size(); i++)
      {
        for (int j = 0; j < t1Rows.size(); j++)
        {
          if (tRefRows[i][0] == t1Rows[j][0])
          {
            found = true;
            break;
          }
        }
        if (found == false)
        {
          Assert::IsTrue(found);
        }
      }
    }
  }

  // Test the difference feature in parser.
  TEST_METHOD(ParserTestSetDifference)
  {
    // Let's insert some rows into our current table first.
    p.parse("CREATE TABLE animal (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
    p.parse("INSERT INTO animal VALUES FROM (\"Joe\", \"cat\", 4);");
    p.parse("INSERT INTO animal VALUES FROM (\"Spot\", \"dog\", 10);");

    // Now let's create another table to difference with this one. 
    p.parse("CREATE TABLE moreAnimals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
    p.parse("INSERT INTO moreAnimals VALUES FROM (\"Mikey\", \"lion\", 5);");
    p.parse("INSERT INTO moreAnimals VALUES FROM (\"Nemo\", \"clownfish\", 1);");
    // Add a row from the first table to see if it handles duplicates
    p.parse("INSERT INTO moreAnimals VALUES FROM (\"Joe\", \"cat\", 4);");

    // Set the difference
    p.parse("animalsDifferenced <- animal - moreAnimals");

    // Make a reference table with the parser.
    p.parse("CREATE TABLE differenceTest (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
    p.parse("INSERT INTO differenceTest VALUES FROM (\"Spot\", \"dog\", 10);");

    // Compare our results.
    Table t1 = p.getEngine().getTable("animalsDifferenced");
    Table tRef = p.getEngine().getTable("differenceTest");

    bool good = false;

    Assert::AreEqual(t1.getRows().size(), tRef.getRows().size());
    if (t1.getColumnNames() == tRef.getColumnNames())
    {
      if (t1.getRows() == tRef.getRows())
      {
        good = true;
      }
    }
    Assert::IsTrue (good);
  }

  // 
  TEST_METHOD(ParserTestCrossProduct)
  {
    // Create two simple tables to cross product
    p.parse("CREATE TABLE cp_names (student VARCHAR(20)");
    p.parse("INSERT INTO cp_names VALUES FROM (\"Terry\");");
    p.parse("INSERT INTO cp_names VALUES FROM (\"Gus\");");

    p.parse("CREATE TABLE cp_class (class VARCHAR(20)");
    p.parse("INSERT INTO cp_class VALUES FROM (\"CSCE313\");");
    p.parse("INSERT INTO cp_class VALUES FROM (\"CSCE315\");");

    // Make a reference table
    p.parse("CREATE TABLE cp_ref (student VARCHAR(20), class VARCHAR(20))");
    p.parse("INSERT INTO cp_ref VALUES FROM (\"Terry\", \"CSCE313\");");
    p.parse("INSERT INTO cp_ref VALUES FROM (\"Terry\", \"CSCE315\");");
    p.parse("INSERT INTO cp_ref VALUES FROM (\"Gus\", \"CSCE313\");");
    p.parse("INSERT INTO cp_ref VALUES FROM (\"Gus\", \"CSCE315\");");

    // run the cross product
    p.parse("cp_result <- cp_names * cp_class;");

    // Compare the two tables.
    Table t1 = p.getEngine().getTable("cp_result");
    Table tRef = p.getEngine().getTable("cp_ref");

    bool good = false;

    if (t1.getColumnNames() == tRef.getColumnNames())
    {
      if (t1.getRows() == tRef.getRows())
      {
        good = true;
      }
    }
    Assert::IsTrue (good);
  }

};
}
