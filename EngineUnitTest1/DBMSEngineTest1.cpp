#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Engine.h"
#include <tuple>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineUnitTest1
{
TEST_CLASS(DBMSEngineTest1)
{
public:
  vector< tuple<string,string,bool> > vColumnNames;
  vector<tuple<int, string> > vRow;
  vector<tuple<int, string> > vRow2;
  vector<tuple<int, string> > vRow3;
  vector<tuple<int, string> > vRow4;
  vector<tuple<int, string> > vRow5;
  vector<string> vKeys;
  Engine e;
  string sTableName;
  string sCol1Name;
  string sCol2Name;
  string sCol3Name;
  string sCol1Type;
  string sCol2Type;
  string sCol3Type;

  // This initialization will create a table "animals" with some columns.
  TEST_METHOD_INITIALIZE(CreateTable)
  {
    // Let's create a table
    // We are doing this in initialize so that it's easier to test err'thang

    // Create some variables so it's easier to see what we've put in
    sTableName = "animals";
    sCol1Name = "name";
    sCol2Name = "kind";
    sCol3Name = "years";
    sCol1Type = "string";
    sCol2Type = "string";
    sCol3Type = "int";

    vColumnNames.push_back(make_tuple(sCol1Name,sCol1Type,true));
    vColumnNames.push_back(make_tuple(sCol2Name,sCol2Type,true));
    vColumnNames.push_back(make_tuple(sCol3Name,sCol3Type,false));
    vKeys.push_back(sCol1Name);
    vKeys.push_back(sCol2Name);
    e.createTable(sTableName, vColumnNames, vKeys);
  }

  // This will test if our initialization above created the table properly
  TEST_METHOD(EngineTestCreateTables)
  {
    // We already created the table above.
    // Now we will do the comparisons.
    bool pass = false;

    // Get our table's column names
    Table check = e.getTable("animals");
    std::vector<std::tuple<int, std::string, bool, std::string> > vCols;
    vCols = check.getColumnNames();

    // Make our vector of reference columns so it's easier to compare
    std::vector<std::tuple<int, std::string, bool, std::string> > vColsRef;
    vColsRef.push_back(make_tuple(0, sCol1Name, true, sCol1Type));
    vColsRef.push_back(make_tuple(1, sCol2Name, true, sCol2Type));
    vColsRef.push_back(make_tuple(2, sCol3Name, false, sCol3Type));

    if (vCols == vColsRef)
    {
      pass = true;
    }

    Assert::IsTrue (pass);
  }

  // This will test if we can drop the table we just created above.
  TEST_METHOD(EngineTestDropTable)
  {
    // We created a table above.
    // Now if we drop we shouldn't be able to find it.

    bool found = false;
    e.dropTable(sTableName);

    // Get the table list so we can search through it
    vector<Table> vTableList = e.getTableList();

    for (int i = 0; i < vTableList.size(); i++)
    {
      if (vTableList[i].getTableName() == sTableName)
      {
        found = true;
      }
    }

    // If we didn't find it then this should stay false...
    Assert::IsFalse (found);
  }

  // Let's see if we can insert rows, and if they match up.
  TEST_METHOD(EngineTestInsertRows)
  {
    // We created a table above...
    // Let's insert some rows and see if they show up

    // Create our rows for insertion
    vRow.push_back(make_tuple(0,"Joe"));
    vRow.push_back(make_tuple(1,"cat"));
    vRow.push_back(make_tuple(2,"4"));

    vRow2.push_back(make_tuple(0,"Spot"));
    vRow2.push_back(make_tuple(1,"dog"));
    vRow2.push_back(make_tuple(2,"10"));

    // Add the rows to our table
    e.addRow(sTableName, vRow);
    e.addRow(sTableName, vRow2);

    // Now we shall check if our rows got added.
    bool good = false;

    Table check = e.getTable(sTableName);

    std::vector<std::vector<std::tuple<int, std::string> > > vRows;
    vRows = check.getRows();

    // We only added two rows, so check them both
    if (vRows[0] == vRow)
    {
      if (vRows[1] == vRow2)
      {
        good = true;
      }
    }

    Assert::IsTrue (good);
  }

  //// Let's see if we can update rows
  //TEST_METHOD(EngineTestUpdateRows)
  //{
  //  // We created a table above.
  //  // Let's add one row and update it

  //  // Create one row to insert
  //  vRow3.push_back(make_tuple(0,"Snoopy"));
  //  vRow3.push_back(make_tuple(1,"dog"));
  //  vRow3.push_back(make_tuple(2,"3"));
  //  e.addRow(sTableName, vRow3);

  //  ////////////////////////////////////////////////////
  //  /// NEED OUR CONDITIONS TO WORK FOR THIS TEST!!! ///
  //  ////////////////////////////////////////////////////

  //  Assert::IsTrue(false);

  //}

  // Let's see if we can delete rows
  TEST_METHOD(EngineTestDeleteRows)
  {
    ////////////////////////////////////////////////////
    /// NEED OUR CONDITIONS TO WORK FOR THIS TEST!!! ///
    ////////////////////////////////////////////////////

    // Insert a row into our table.
    vRow.push_back(make_tuple(0,"Joe"));
    e.addRow(sTableName, vRow);

    // Delete that row!
    e.deleteRow(sTableName, vRow);

    // Check to see that there are no rows
    Assert::AreEqual((int)e.getTable(sTableName).getRows().size(), 0);
  }

  //// Test the relational algebra function Selection
  //TEST_METHOD(EngineTestSelection)
  //{
  //  ////////////////////////////////////////////////////
  //  /// NEED OUR CONDITIONS TO WORK FOR THIS TEST!!! ///
  //  ////1////////////////////////////////////////////////

  //  Assert::IsTrue(false);
  //}

  // Test the relational algebra function Projection
  TEST_METHOD(EngineTestProjection)
  {
    // Let's insert several rows first.
    // Create our rows for insertion
    vRow.push_back(make_tuple(0,"Joe"));
    vRow.push_back(make_tuple(1,"cat"));
    vRow.push_back(make_tuple(2,"4"));

    vRow2.push_back(make_tuple(0,"Spot"));
    vRow2.push_back(make_tuple(1,"dog"));
    vRow2.push_back(make_tuple(2,"10"));

    vRow3.push_back(make_tuple(0,"Snoopy"));
    vRow3.push_back(make_tuple(1,"dog"));
    vRow3.push_back(make_tuple(2,"3"));

    // Add the rows to our table
    e.addRow(sTableName, vRow);
    e.addRow(sTableName, vRow2);
    e.addRow(sTableName, vRow3);

    // I want to project the column name only.
    std::vector<std::string> vColName;
    vColName.push_back("name");
    // I want to call the new table "projected"
    e.projection(sTableName, "projected", vColName);

    // Gonna create a vector of just the names.
    std::vector<std::string> animalNames;
    animalNames.push_back("Joe");
    animalNames.push_back("Spot");
    animalNames.push_back("Snoopy");

    // Now let's compare our tables.
    bool good = false;

    Table projectTest = e.getTable("projected");
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

  // Test the relational algebra function Renaming
  TEST_METHOD(EngineTestRenaming)
  {
    // Let's rename the columns of the table we created earlier...

    // New Names
    string sCol1NameNew = "animal name";
    string sCol2NameNew = "animal kind";
    string sCol3NameNew = "animal type";
    string sTableNameNew = "animal table";
    vector<string> vNewNames;
    vNewNames.push_back(sCol1NameNew);
    vNewNames.push_back(sCol2NameNew);
    vNewNames.push_back(sCol3NameNew);

    e.reNaming(sTableName, sTableNameNew, vNewNames);

    bool good = true;

    // Let's see if we can get our new table...
    Table check = e.getTable(sTableNameNew);

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

  // Test the relational algebra function Set Union
  TEST_METHOD(EngineTestSetUnion)
  {
    // Let's insert some things into our current table first.
    // Create our rows for insertion
    vRow.push_back(make_tuple(0,"Joe"));
    vRow.push_back(make_tuple(1,"cat"));
    vRow.push_back(make_tuple(2,"4"));

    vRow2.push_back(make_tuple(0,"Spot"));
    vRow2.push_back(make_tuple(1,"dog"));
    vRow2.push_back(make_tuple(2,"10"));

    // Add the rows to our table
    e.addRow(sTableName, vRow);
    e.addRow(sTableName, vRow2);

    // Now let's create another table to union with this one.
    string sTableName2 = "moreAnimals";
    vRow4.push_back(make_tuple(0, "Mikey"));
    vRow4.push_back(make_tuple(1, "lion"));
    vRow4.push_back(make_tuple(2, "5"));

    vRow5.push_back(make_tuple(0, "Nemo"));
    vRow5.push_back(make_tuple(1, "clownfish"));
    vRow5.push_back(make_tuple(2, "1"));

    // Make the table and add the rows.
    e.createTable(sTableName2, vColumnNames, vKeys);
    e.addRow(sTableName2, vRow4);
    e.addRow(sTableName2, vRow5);
    // Add a row from the first table to see if it handles duplicates
    e.addRow(sTableName2, vRow);

    // Make a reference table... we will compare our result to this.
    string sTableName3 = "animalsUnioned";
    e.createTable(sTableName3, vColumnNames, vKeys);
    e.addRow(sTableName3, vRow);
    e.addRow(sTableName3, vRow2);
    e.addRow(sTableName3, vRow4);
    e.addRow(sTableName3, vRow5);

    // Set the union...
    string sTableNameUnion = "unionTest";
    e.setUnion(sTableName, sTableName2, sTableNameUnion);

    // Compare our results.
    Table t1 = e.getTable(sTableNameUnion);
    Table tRef = e.getTable(sTableName3);

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

  // Test the relational algebra function Set Difference
  TEST_METHOD(EngineTestSetDifference)
  {
    // Let's insert some things into our current table first.
    // Create our rows for insertion
    vRow.push_back(make_tuple(0,"Joe"));
    vRow.push_back(make_tuple(1,"cat"));
    vRow.push_back(make_tuple(2,"4"));

    vRow2.push_back(make_tuple(0,"Spot"));
    vRow2.push_back(make_tuple(1,"dog"));
    vRow2.push_back(make_tuple(2,"10"));

    // Add the rows to our table
    e.addRow(sTableName, vRow);
    e.addRow(sTableName, vRow2);

    // Now let's create another table to difference with this one.
    string sTableName2 = "moreAnimals";
    vRow4.push_back(make_tuple(0, "Mikey"));
    vRow4.push_back(make_tuple(1, "lion"));
    vRow4.push_back(make_tuple(2, "5"));

    vRow5.push_back(make_tuple(0, "Nemo"));
    vRow5.push_back(make_tuple(1, "clownfish"));
    vRow5.push_back(make_tuple(2, "1"));

    // Make the table and add the rows.
    e.createTable(sTableName2, vColumnNames, vKeys);
    e.addRow(sTableName2, vRow4);
    e.addRow(sTableName2, vRow5);
    // Add a row from the first table to test our difference
    e.addRow(sTableName2, vRow);

    // Make a reference table... we will compare our result to this.
    string sTableName3 = "animalsDifferenced";
    e.createTable(sTableName3, vColumnNames, vKeys);
    e.addRow(sTableName3, vRow2);

    // Set the difference...
    string sTableNameDifference = "differenceTest";
    e.setDifference(sTableName, sTableName2, sTableNameDifference);

    // Compare our results.
    Table t1 = e.getTable(sTableNameDifference);
    Table tRef = e.getTable(sTableName3);

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

  // Test the relational algebra function Cross Product
  TEST_METHOD(EngineTestCrossProduct)
  {
    // Create two simple tables to cross product.

    // Make two separate tables--students and class
    vector< tuple<string,string,bool> > vColNameCP1;
    vector< tuple<string,string,bool> > vColNameCP2;
    vector< tuple<string,string,bool> > vColNameCP3;
    vector<tuple<int, string> > vRow1CP1;
    vector<tuple<int, string> > vRow2CP1;
    vector<tuple<int, string> > vRow1CP2;
    vector<tuple<int, string> > vRow2CP2;
    vector<tuple<int, string> > vRow1CP3;
    vector<tuple<int, string> > vRow2CP3;
    vector<tuple<int, string> > vRow3CP3;
    vector<tuple<int, string> > vRow4CP3;
    vColNameCP1.push_back(make_tuple("Student", "string", true));
    vColNameCP2.push_back(make_tuple("Class", "string", false));
    vColNameCP3.push_back(make_tuple("Student", "string", true));
    vColNameCP3.push_back(make_tuple("Class", "string", false));
    
    // Add the students to the student table
    vRow1CP1.push_back(make_tuple(0, "Terry"));
    vRow2CP1.push_back(make_tuple(0, "Gus"));
    
    // Add the classes to the class table
    vRow1CP2.push_back(make_tuple(0, "CSCE313"));
    vRow1CP2.push_back(make_tuple(0, "CSCE315"));

    e.addRow("cp_names", vRow1CP1);
    e.addRow("cp_names", vRow2CP1);

    e.addRow("cp_class", vRow1CP2);
    e.addRow("cp_class", vRow2CP2);

    // Perform the cross product operation here:
    e.crossProduct("cp_names", "cp_class", "cp_result");

    // Make our reference table.
    vRow1CP3.push_back(make_tuple(0, "Terry"));
    vRow1CP3.push_back(make_tuple(1, "CSCE313"));

    vRow2CP3.push_back(make_tuple(0, "Terry"));
    vRow2CP3.push_back(make_tuple(1, "CSCE315"));

    vRow3CP3.push_back(make_tuple(0, "Gus"));
    vRow3CP3.push_back(make_tuple(1, "CSCE313"));

    vRow4CP3.push_back(make_tuple(0, "Gus"));
    vRow4CP3.push_back(make_tuple(1, "CSCE315"));
    
    e.addRow("cp_ref", vRow1CP3);
    e.addRow("cp_ref", vRow2CP3);
    e.addRow("cp_ref", vRow3CP3);
    e.addRow("cp_ref", vRow4CP3);

    // Compare the tables. 

    Table t1 = e.getTable("cp_result");
    Table tRef = e.getTable("cp_ref");

    bool good = false; 

    if (t1.getColumnNames() == tRef.getColumnNames()) 
    {
      if (t1.getRows() == tRef.getRows())
      {
        good = true;
      }
    }
    Assert::IsTrue(good);
  }

  //// Test natural join.
  //TEST_METHOD(EngineTestNaturalJoin)
  //{
  //  // Make super simple table to test this

  //  // Make two separate tables--students and class
  //  vector< tuple<string,string,bool> > vColNameNJ1;
  //  vector< tuple<string,string,bool> > vColNameNJ2;

  //  vector<tuple<int, string> > vRow1NJ1;
  //  vector<tuple<int, string> > vRow2NJ1;
  //  vector<tuple<int, string> > vRow1NJ2;
  //  vector<tuple<int, string> > vRow2NJ2;

  //  vector<string> vKeys;
  //  vKeys.push_back("classID");

  //  vColNameNJ1.push_back(make_tuple("Student", "string", false));
  //  vColNameNJ1.push_back(make_tuple("classID", "int", true));

  //  vColNameNJ2.push_back(make_tuple("Class", "string", false));
  //  vColNameNJ2.push_back(make_tuple("classID", "int", true));
  //  
  //  e.createTable("nj_names", vColNameNJ1, vKeys);
  //  e.createTable("nj_class", vColNameNJ2, vKeys);

  //  // Add the students to the student table
  //  vRow1NJ1.push_back(make_tuple(0, "Terry"));
  //  vRow1NJ1.push_back(make_tuple(1, "1"));
  //  vRow2NJ1.push_back(make_tuple(0, "Gus"));
  //  vRow2NJ1.push_back(make_tuple(1, "2"));
  //  
  //  // Add the classes to the class table
  //  vRow1NJ2.push_back(make_tuple(0, "CSCE313"));
  //  vRow1NJ2.push_back(make_tuple(1, "1"));
  //  vRow2NJ2.push_back(make_tuple(0, "CSCE315"));
  //  vRow2NJ2.push_back(make_tuple(1, "2"));

  //  e.addRow("nj_names", vRow1NJ1);
  //  e.addRow("nj_names", vRow2NJ1);

  //  e.addRow("nj_class", vRow1NJ2);
  //  e.addRow("nj_class", vRow2NJ2);

  //  // Perform the natural join
  //  e.naturalJoin("nj_names", "nj_class");

  //  Table t1 = e.getTable("nj_names and nj_class natural join");
  //  std::vector<std::vector<std::tuple<int, std::string> > > vNJRows;
  //  vNJRows = t1.getRows();
  //  bool caseA = false;
  //  bool caseB = false;
  //  
  //  Assert::AreEqual((int)t1.getRow(0).size(), 0);

  //  for (int i = 0; i < vNJRows.size(); i++) 
  //  {
  //    if (get<1>(t1.getRow(i)[0]) == "Terry") 
  //    {
  //      if (get<1>(t1.getRow(i)[1]) == "CSCE313")
  //      {
  //        caseA = true;
  //      }
  //    }
  //    if (get<1>(t1.getRow(i)[0]) == "Gus") 
  //    {
  //      if (get<1>(t1.getRow(i)[1]) == "CSCE315")
  //      {
  //        caseA = true;
  //      }
  //    }
  //  }


  //}

};
}
