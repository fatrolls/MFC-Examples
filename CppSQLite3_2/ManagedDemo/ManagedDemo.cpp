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
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#using <mscorlib.dll>
#include <tchar.h>
#include <ctime>
#include "CppSQLite3.h"

using namespace System;
const char* gszFile = "C:\\test.db";

// This is the entry point for this application
int _tmain(void)
{
    try
    {
        int i, fld;
        time_t tmStart, tmEnd;
		CppSQLite3DB db;

		Console::WriteLine(db.SQLiteVersion());

		remove(gszFile);
		db.open(gszFile);

		Console::WriteLine("");
		Console::WriteLine("Creating emp table");
		db.execDML("create table emp(empno int, empname char(20));");

        ////////////////////////////////////////////////////////////////////////////////
        // Execute some DML, and print number of rows affected by each one
        ////////////////////////////////////////////////////////////////////////////////
		Console::WriteLine("");
		Console::WriteLine("DML tests");
        int nRows = db.execDML("insert into emp values (7, 'David Beckham');");
        Console::Write(nRows);
		Console::WriteLine(" rows inserted");

        nRows = db.execDML("update emp set empname = 'Christiano Ronaldo' where empno = 7;");
        Console::Write(nRows);
		Console::WriteLine(" rows updated");

        nRows = db.execDML("delete from emp where empno = 7;");
        Console::Write(nRows);
		Console::WriteLine(" rows deleted");

		
		////////////////////////////////////////////////////////////////////////////////
        // Transaction Demo
        // The transaction could just as easily have been rolled back
        ////////////////////////////////////////////////////////////////////////////////
        int nRowsToCreate(50000);
		Console::WriteLine("");
        Console::Write("Transaction test, creating ");
		Console::Write(nRowsToCreate);
        Console::WriteLine(" rows please wait...");
        tmStart = time(0);
        db.execDML("begin transaction;");

        for (i = 0; i < nRowsToCreate; i++)
        {
            char buf[128];
            sprintf(buf, "insert into emp values (%d, 'Empname%06d');", i, i);
            db.execDML(buf);
        }

        db.execDML("commit transaction;");
        tmEnd = time(0);

		////////////////////////////////////////////////////////////////////////////////
        // Demonstrate CppSQLite3DB::execScalar()
        ////////////////////////////////////////////////////////////////////////////////
		Console::WriteLine("");
        Console::Write(db.execScalar("select count(*) from emp;"));
		Console::Write(" rows in emp table in ");
        Console::Write(tmEnd-tmStart);
		Console::WriteLine(" seconds (that was fast!)");

        ////////////////////////////////////////////////////////////////////////////////
        // Re-create emp table with auto-increment field
        ////////////////////////////////////////////////////////////////////////////////
		Console::WriteLine("");
        Console::WriteLine("Auto increment test");
        db.execDML("drop table emp;");
        db.execDML("create table emp(empno integer primary key, empname char(20));");
        Console::Write(nRows);
		Console::WriteLine(" rows deleted");

        for (i = 0; i < 5; i++)
        {
            char buf[128];
            sprintf(buf, "insert into emp (empname) values ('Empname%06d');", i+1);
            db.execDML(buf);
			Console::Write("primary key: ");
		    Console::WriteLine(db.lastRowId());
        }

        ////////////////////////////////////////////////////////////////////////////////
        // Query data and also show results of inserts into auto-increment field
        ////////////////////////////////////////////////////////////////////////////////
		Console::WriteLine("");
        Console::WriteLine("Select statement test");
        CppSQLite3Query q = db.execQuery("select * from emp order by 1;");

        for (fld = 0; fld < q.numFields(); fld++)
        {
			Console::Write(q.fieldName(fld));
			Console::Write("(");
			Console::Write(q.fieldDeclType(fld));
			Console::Write(")|");
        }
        Console::WriteLine();

        while (!q.eof())
        {
			Console::Write(q.fieldValue(0));
			Console::Write("|");
			Console::Write(q.fieldValue(1));
			Console::WriteLine("|");
            q.nextRow();
        }

		////////////////////////////////////////////////////////////////////////////////
        // SQLite's printf() functionality. Handles embedded quotes and NULLs
        ////////////////////////////////////////////////////////////////////////////////
		Console::WriteLine("");
        Console::WriteLine("SQLite sprintf test");
        CppSQLite3Buffer bufSQL;
        bufSQL.format("insert into emp (empname) values (%Q);", "He's bad");
        Console::WriteLine(bufSQL);
        db.execDML(bufSQL);

        bufSQL.format("insert into emp (empname) values (%Q);", NULL);
        Console::WriteLine(bufSQL);
        db.execDML(bufSQL);

        ////////////////////////////////////////////////////////////////////////////////
        // Fetch table at once, and also show how to use CppSQLite3Table::setRow() method
        ////////////////////////////////////////////////////////////////////////////////
		Console::WriteLine("");
        Console::WriteLine("getTable() test");
        CppSQLite3Table t = db.getTable("select * from emp order by 1;");

        for (fld = 0; fld < t.numFields(); fld++)
        {
            Console::Write(t.fieldName(fld));
			Console::Write("|");
        }
        Console::WriteLine("");

		for (int row = 0; row < t.numRows(); row++)
        {
            t.setRow(row);
            for (int fld = 0; fld < t.numFields(); fld++)
            {
                if (!t.fieldIsNull(fld))
				{
		            Console::Write(t.fieldValue(fld));
					Console::Write("|");
				}
                else
                    Console::Write("NULL|");
            }
	        Console::WriteLine("");
        }

        ////////////////////////////////////////////////////////////////////////////////
        // Test CppSQLite3Binary by storing/retrieving some binary data, checking
        // it afterwards to make sure it is the same
        ////////////////////////////////////////////////////////////////////////////////
		Console::WriteLine("");
		Console::WriteLine("Binary data test");
        db.execDML("create table bindata(desc char(10), data blob);");
        
        unsigned char bin[256];
        CppSQLite3Binary blob;

        for (i = 0; i < sizeof bin; i++)
        {
            bin[i] = i;
        }

        blob.setBinary(bin, sizeof bin);

        bufSQL.format("insert into bindata values ('testing', %Q);", blob.getEncoded());
        db.execDML(bufSQL);
		Console::Write("Stored binary Length: ");
	    Console::WriteLine(sizeof bin);

        q = db.execQuery("select data from bindata where desc = 'testing';");

        if (!q.eof())
        {
            blob.setEncoded((unsigned char*)q.fieldValue("data"));
			Console::Write("Retrieved binary Length: ");
			Console::WriteLine(blob.getBinaryLength());
        }

        const unsigned char* pbin = blob.getBinary();
        for (i = 0; i < sizeof bin; i++)
        {
            if (pbin[i] != i)
            {
				Console::Write("Problem: i=");
				Console::Write(i);
				Console::Write(", bin[i]=");
				Console::WriteLine(pbin[i]);
            }
        }

		q.finalize();

        ////////////////////////////////////////////////////////////////////////////////
        // Pre-compiled Statements Demo
        ////////////////////////////////////////////////////////////////////////////////
		Console::WriteLine("");
		Console::Write("Transaction test, creating ");
		Console::Write(nRowsToCreate);
		Console::WriteLine(" rows please wait...");

		db.execDML("drop table emp;");
        db.execDML("create table emp(empno int, empname char(20));");
        tmStart = time(0);
        db.execDML("begin transaction;");

        CppSQLite3Statement stmt = db.compileStatement("insert into emp values (?, ?);");
        for (i = 0; i < nRowsToCreate; i++)
        {
            char buf[16];
            sprintf(buf, "EmpName%06d", i);
            stmt.bind(1, i);
            stmt.bind(2, buf);
            stmt.execDML();
            stmt.reset();
        }

        db.execDML("commit transaction;");
        tmEnd = time(0);

		Console::Write(db.execScalar("select count(*) from emp;"));
		Console::Write(" rows in emp table in ");
		Console::Write(tmEnd-tmStart);
		Console::WriteLine(" seconds (that was even faster!)");
		Console::WriteLine("");
		Console::WriteLine("End of tests");
	}
    catch (CppSQLite3Exception& e)
    {
        Console::WriteLine(e.errorMessage());
    }

	Console::Write("Press enter to quit: ");
	Console::ReadLine();
    return 0;
}