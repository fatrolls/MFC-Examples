////////////////////////////////////////////////////////////////////////////////
// CppSQLite3 - A C++ wrapper around the SQLite3 embedded database library.
//
// Copyright (c) 2004..2007 Rob Groves. All Rights Reserved. rob.groves@btinternet.com
// 
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without a written
// agreement, is hereby granted, provided that the above copyright notice, 
// this paragraph and the following two paragraphs appear in all copies, 
// modifications, and distributions.
//
// IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT,
// INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
// PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
// EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF
// ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS". THE AUTHOR HAS NO OBLIGATION
// TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
//
// V3.0		03/08/2004	-Initial Version for sqlite3
//
// V3.2		12/07/2007	-Added tests for new functionality
////////////////////////////////////////////////////////////////////////////////
#include "CppSQLite3.h"
#include <ctime>
#include <iostream>

using namespace std;

const char* gszFile = "C:\\test.db";

int main(int argc, char** argv)
{
    try
    {
		int row;
        CppSQLite3DB db;

        cout << "SQLite Header Version: " << CppSQLite3DB::SQLiteHeaderVersion() << endl;
        cout << "SQLite Library Version: " << CppSQLite3DB::SQLiteLibraryVersion() << endl;
        cout << "SQLite Library Version Number: " << CppSQLite3DB::SQLiteLibraryVersionNumber() << endl;

        remove(gszFile);
        db.open(gszFile);

        ////////////////////////////////////////////////////////////////////////////////
        // Demonstrate getStringField(), getIntField(), getFloatField()
        ////////////////////////////////////////////////////////////////////////////////
        db.execDML("create table parts(no int, name char(20), qty int, cost number);");
        db.execDML("insert into parts values(1, 'part1', 100, 1.11);");
        db.execDML("insert into parts values(2, null, 200, 2.22);");
        db.execDML("insert into parts values(3, 'part3', null, 3.33);");
        db.execDML("insert into parts values(4, 'part4', 400, null);");

        cout << endl << "CppSQLite3Query getStringField(), getIntField(), getFloatField() tests" << endl;
        CppSQLite3Query q = db.execQuery("select * from parts;");
        while (!q.eof())
        {
            cout << q.getIntField(0) << "|";
            cout << q.getStringField(1) << "|";
            cout << q.getInt64Field(2) << "|";
            cout << q.getFloatField(3) << "|" << endl;
            q.nextRow();
        }

        cout << endl << "specify NULL values tests" << endl;
        q = db.execQuery("select * from parts;");
        while (!q.eof())
        {
            cout << q.getIntField(0) << "|";
            cout << q.getStringField(1, "NULL") << "|";
            cout << q.getIntField(2, -1) << "|";
            cout << q.getFloatField(3, -3.33) << "|" << endl;
            q.nextRow();
        }

        cout << endl << "Specify fields by name" << endl;
        q = db.execQuery("select * from parts;");
        while (!q.eof())
        {
            cout << q.getIntField("no") << "|";
            cout << q.getStringField("name") << "|";
            cout << q.getInt64Field("qty") << "|";
            cout << q.getFloatField("cost") << "|" << endl;
            q.nextRow();
        }

        cout << endl << "specify NULL values tests" << endl;
        q = db.execQuery("select * from parts;");
        while (!q.eof())
        {
            cout << q.getIntField("no") << "|";
            cout << q.getStringField("name", "NULL") << "|";
            cout << q.getIntField("qty", -1) << "|";
            cout << q.getFloatField("cost", -3.33) << "|" << endl;
            q.nextRow();
        }
		q.finalize();

		////////////////////////////////////////////////////////////////////////////////
        // Demonstrate getStringField(), getIntField(), getFloatField()
		// But this time on CppSQLite3Table
        ////////////////////////////////////////////////////////////////////////////////
        cout << endl << "CppSQLite3Table getStringField(), getIntField(), getFloatField() tests" << endl;
        CppSQLite3Table t = db.getTable("select * from parts;");
        for (row = 0; row < t.numRows(); row++)
        {
            t.setRow(row);
            cout << t.getIntField(0) << "|";
            cout << t.getStringField(1) << "|";
            cout << t.getIntField(2) << "|";
            cout << t.getFloatField(3) << "|" << endl;
        }

        cout << endl << "specify NULL values tests" << endl;
        for (row = 0; row < t.numRows(); row++)
        {
            t.setRow(row);
            cout << t.getIntField(0, -1) << "|";
            cout << t.getStringField(1, "NULL") << "|";
            cout << t.getIntField(2, -1) << "|";
            cout << t.getFloatField(3, -3.33) << "|" << endl;
        }

        cout << endl << "Specify fields by name" << endl;
        for (row = 0; row < t.numRows(); row++)
        {
            t.setRow(row);
            cout << t.getIntField("no") << "|";
            cout << t.getStringField("name") << "|";
            cout << t.getIntField("qty") << "|";
            cout << t.getFloatField("cost") << "|" << endl;
        }

        cout << endl << "specify NULL values tests" << endl;
        for (row = 0; row < t.numRows(); row++)
        {
            t.setRow(row);
            cout << t.getIntField("no") << "|";
            cout << t.getStringField("name", "NULL") << "|";
            cout << t.getIntField("qty", -1) << "|";
            cout << t.getFloatField("cost", -3.33) << "|" << endl;
        }


		////////////////////////////////////////////////////////////////////////////////
		// Demonstrate multi-statement DML
		// Note that number of rows affected is only from the last statement
		// when multiple statements are used
		////////////////////////////////////////////////////////////////////////////////
        cout << endl << "Multi-Statement execDML()" << endl;
		const char* szDML = "insert into parts values(5, 'part5', 500, 5.55);"
							"insert into parts values(6, 'part6', 600, 6.66);"
							"insert into parts values(7, 'part7', 700, 7.77);";
		int nRows = db.execDML(szDML);
		cout << endl << nRows << " rows affected" << endl;
        cout << db.execScalar("select count(*) from parts;") << " rows in parts table" << endl;
		            szDML = "delete from parts where no = 2;"
							"delete from parts where no = 3;";
		nRows = db.execDML(szDML);
        cout << endl << nRows << " rows affected" << endl;
        cout << db.execScalar("select count(*) from parts;") << " rows in parts table" << endl;


		////////////////////////////////////////////////////////////////////////////////
		// Demonstrate new typing system & BLOBS
		// ANy data can be stored in any column
		////////////////////////////////////////////////////////////////////////////////
        cout << endl << "Data types and BLOBs()" << endl;
        db.execDML("create table types(no int, "
				"name char(20), qty float, dat blob);");
        db.execDML("insert into types values(null, null, null, null);");
        db.execDML("insert into types values(1, 2, 3, 4);");
        db.execDML("insert into types values(1.1, 2.2, 3.3, 4.4);");
        db.execDML("insert into types values('a', 'b', 'c', 'd');");

        CppSQLite3Statement stmt = db.compileStatement("insert into types values(?,?,?,?);");
        unsigned char buf[256];
		memset(buf, 1, 1); stmt.bind(1, buf, 1);
		memset(buf, 2, 2); stmt.bind(2, buf, 2);
		memset(buf, 3, 3); stmt.bind(3, buf, 3);
		memset(buf, 4, 4); stmt.bind(4, buf, 4);
		stmt.execDML();
        cout << db.execScalar("select count(*) from types;") << " rows in types table" << endl;

        q = db.execQuery("select * from types;");
        while (!q.eof())
        {
			for (int i = 0; i < q.numFields(); i++)
			{
				switch (q.fieldDataType(i))
				{
				case SQLITE_INTEGER  : cout << "SQLITE_INTEGER|"; break;
				case SQLITE_FLOAT    : cout << "SQLITE_FLOAT  |"; break;
				case SQLITE_TEXT     : cout << "SQLITE_TEXT   |"; break;
				case SQLITE_BLOB     : cout << "SQLITE_BLOB   |"; break;
				case SQLITE_NULL     : cout << "SQLITE_NULL   |"; break;
				default: cout << "***UNKNOWN TYPE***"; break;
				}
			}
            q.nextRow();
			cout << endl;
        }

        nRows = db.execDML("delete from types where no = 1 or no = 1.1 or no = 'a' or no is null;");
		cout << endl << nRows << " rows deleted, leaving binary row only" << endl;

        q = db.execQuery("select * from types;");
		const unsigned char* pBlob;
		int nLen;
		pBlob = q.getBlobField(0, nLen);
		cout << "Field 1 BLOB length: " << nLen << endl;
		pBlob = q.getBlobField(1, nLen);
		cout << "Field 2 BLOB length: " << nLen << endl;
		pBlob = q.getBlobField(2, nLen);
		cout << "Field 3 BLOB length: " << nLen << endl;
		pBlob = q.getBlobField(3, nLen);
		cout << "Field 4 BLOB length: " << nLen << endl;

		q.finalize();

        nRows = db.execDML("delete from types;");
		cout << endl << nRows << " rows deleted, leaving empty table" << endl;
        unsigned char bin[256];

        for (int i = 0; i < sizeof bin; i++)
        {
            bin[i] = i;
        }

        stmt = db.compileStatement("insert into types values(?,0,0,0);");
		stmt.bind(1, bin, sizeof bin);
		stmt.execDML();

        cout << "Stored binary Length: " << sizeof bin << endl;

        q = db.execQuery("select * from types;");

		pBlob = q.getBlobField(0, nLen);
		cout << "Field 1 BLOB length: " << nLen << endl;

        for (i = 0; i < sizeof bin; i++)
        {
            if (pBlob[i] != i)
            {
				cout << "Problem: i: ," << i << " BLOB[i]: " << pBlob[i] << endl;
            }
        }
	}
    catch (CppSQLite3Exception& e)
    {
        cerr << e.errorCode() << ":" << e.errorMessage() << endl;
    }

	////////////////////////////////////////////////////////////////////////////////
    // Loop until user enters q or Q
    ////////////////////////////////////////////////////////////////////////////////
    char c(' ');

    while (c != 'q' && c != 'Q')
    {
        cout << "Press q then enter to quit: ";
        cin >> c;
    }
    return 0;
}

