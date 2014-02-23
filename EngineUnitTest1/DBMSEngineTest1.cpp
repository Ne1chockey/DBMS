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
    vector< tuple<int, string> > vRow;
    vector< tuple<int, string> > vRow2;
    vector< tuple<int, string> > vRow3;
    vector< tuple<int, string> > vRow4;
    vector< tuple<int, string> > vRow5;
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

      Assert::IsTrue(pass);
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
      Assert::IsFalse(found);
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
      
      Assert::IsTrue(good);
    }

    // Let's see if we can update rows
    TEST_METHOD(EngineTestUpdateRows)
    {
      // We created a table above. 
      // Let's add one row and update it

      // Create one row to insert
      vRow3.push_back(make_tuple(0,"Snoopy"));
      vRow3.push_back(make_tuple(1,"dog"));
      vRow3.push_back(make_tuple(2,"3"));
      e.addRow(sTableName, vRow3);

      ////////////////////////////////////////////////////
      /// NEED OUR CONDITIONS TO WORK FOR THIS TEST!!! ///
      ////////////////////////////////////////////////////

      Assert::IsTrue(false);

    }

    // Let's see if we can delete rows
    TEST_METHOD(EngineTestDeleteRows)
    {
      ////////////////////////////////////////////////////
      /// NEED OUR CONDITIONS TO WORK FOR THIS TEST!!! ///
      ////////////////////////////////////////////////////

      Assert::IsTrue(false);
    }

    // Test the relational algebra function Selection
    TEST_METHOD(EngineTestSelection)
    {
      ////////////////////////////////////////////////////
      /// NEED OUR CONDITIONS TO WORK FOR THIS TEST!!! ///
      ////////////////////////////////////////////////////

      Assert::IsTrue(false);
    }

    // Test the relational algebra function Projection
    TEST_METHOD(EngineTestProjection)
    {
      ////////////////////////////////////////////////////
      /// NEED OUR CONDITIONS TO WORK FOR THIS TEST!!! ///
      ////////////////////////////////////////////////////

      Assert::IsTrue(false);
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

      Assert::IsTrue(good);
    }

    // Test the relational algebra function Set Union
    TEST_METHOD(EngineTestSetUnion)
    {
      
    }
  };
}