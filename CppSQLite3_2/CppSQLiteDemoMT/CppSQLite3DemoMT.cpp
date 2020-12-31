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
#include <process.h>
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

const char* gszFile = "C:\\test.db";
int nThreads;

using namespace std;

void LongQueryThreadProc(void* p)
{
	CppSQLite3DB* pdb = (CppSQLite3DB*)p;

	try
	{
		// Meaningless query, with sub-query to slow things down
		const char* szSQL = "select d.dayno, sum(numcalls) "
							"from details d "
							"where dayno+numcalls in "
							"(select d2.dayno+d2.numcalls from details d2) "
							"group by dayno order by 1;";

		cout << "LongQueryThreadProc: starting query" << endl;
		CppSQLite3Query q = pdb->execQuery(szSQL);

		cout << "LongQueryThreadProc: ";
		for (int fld = 0; fld < q.numFields(); fld++)
		{
			cout << q.fieldName(fld) << "|";
		}
		cout << endl;

		while (!q.eof())
		{
			cout << "LongQueryThreadProc: ";
			cout << q.fieldValue(0) << "|";
			cout << q.fieldValue(1) << "|" << endl;
			q.nextRow();
		}
	}
	catch (CppSQLite3Exception& e)
	{
		cout << "LongQueryThreadProc: " << e.errorCode() << ":" << e.errorMessage() << endl;
	}

	nThreads--;
}


void ReadLockThreadProc(void* p)
{
	CppSQLite3DB db;

	try
	{
		db.open(gszFile);

		// access rows to lock table
		cout << "ReadLockThreadProc: creating read lock" << endl;

		CppSQLite3Query q = db.execQuery("select * from details where dayno = 1;");

		int nLockSeconds(5);

		for (int i = 0; i < nLockSeconds; i++)
		{
			Sleep(1000);
		}

		q.finalize();
		cout << "ReadLockThreadProc: released read lock" << endl;
	}
	catch (CppSQLite3Exception& e)
	{
		cout << "ReadLockThreadProc: " << e.errorCode() << ":" << e.errorMessage() << endl;
	}

	nThreads--;
}


void WriteLockThreadProc(void* p)
{
	CppSQLite3DB db;

	try
	{
		db.open(gszFile);
		db.setBusyTimeout(20000);

		// access rows to lock table
		cout << "WriteLockThreadProc: creating write lock" << endl;
		db.execDML("begin transaction;");
		db.execDML("update details set numcalls = 10 where dayno = 1;");

		int nLockSeconds(20);

		for (int i = 0; i < nLockSeconds; i++)
		{
			Sleep(1000);
		}

		db.execDML("commit transaction;");
		cout << "WriteLockThreadProc: released write lock" << endl;
	}
	catch (CppSQLite3Exception& e)
	{
		cout << "WriteLockThreadProc: " << e.errorCode() << ":" << e.errorMessage() << endl;
	}

	nThreads--;
}


int main(int argc, char** argv)
{
	try
	{
        cout << "SQLite Header Version: " << CppSQLite3DB::SQLiteHeaderVersion() << endl;
        cout << "SQLite Library Version: " << CppSQLite3DB::SQLiteLibraryVersion() << endl;
        cout << "SQLite Library Version Number: " << CppSQLite3DB::SQLiteLibraryVersionNumber() << endl;

		remove(gszFile);

		CppSQLite3DB db;

		cout << endl << "Main thread: Opening DB." << endl;
		db.open(gszFile);
		cout << "Main thread: Opened DB." << endl;

		////////////////////////////////////////////////////////////////////////////////
		// Create a largish table to use in later tests
		// For fast PCs increase nRows
		////////////////////////////////////////////////////////////////////////////////
		int nRows(100000);

		cout << endl << "Main thread: creating " << nRows << " rows" << endl;
		db.execDML("create table details (dayno int, numcalls int);");
		db.execDML("begin transaction;");

		srand((unsigned)time(0));

		for (int i = 0; i < nRows; i++)
		{
			char buf[128];
			sprintf(buf, "insert into details values (%d, %d);",
					rand()%7, rand());
			db.execDML(buf);
		}

		db.execDML("commit transaction;");
		cout << "Main thread: created " << nRows << " rows" << endl;


		////////////////////////////////////////////////////////////////////////////////
		// INTERRUPT TEST
		// Create thread to run a longish query that we will interrupt from main thread.
		// Note that we pass the DB as a parameter to the thread, as sqlite_interrupt()
		// must be used on the same CppSQLite instance that is running the operation
		// to be interrupted.
		////////////////////////////////////////////////////////////////////////////////
		cout << endl << "Interrupt test" << endl;
		nThreads = 1;
		_beginthread(LongQueryThreadProc, 0, &db);
		Sleep(1000);
		db.interrupt();

		cout << "Waiting for LongQueryThreadProc" << endl;
		while (nThreads) Sleep(100);
		cout << "Done waiting for LongQueryThreadProc" << endl;


		////////////////////////////////////////////////////////////////////////////////
		// BUSY TEST1 on execDML()
		// Create thread that creates a write lock. We will then try to work on
		// that table in the main thread, and demonstrate SQLite's retry mechanism.
		// Main thread will timeout as lock thread has longer 20 second timeout
		////////////////////////////////////////////////////////////////////////////////
		cout << endl << "SQLITE_BUSY test1 on CppSQLite3DB::execDML() - Main times out BUSY" << endl;
		nThreads = 1;
		_beginthread(WriteLockThreadProc, 0, 0);
		Sleep(2000);

		try
		{
			db.setBusyTimeout(10000);
			int nRows = db.execDML("update details set numcalls = 100 where dayno = 1;");
			cout << "Main thread: updated " << nRows << " rows" << endl;
		}
		catch (CppSQLite3Exception& e)
		{
			cout << "Main thread: " << e.errorCode() << ":" << e.errorMessage() << endl;
		}
		while (nThreads) Sleep(100);


		////////////////////////////////////////////////////////////////////////////////
		// BUSY TEST2 on execDML()
		// Create thread that creates a write lock. We will then try to work on
		// that table in the main thread, and demonstrate SQLite's retry mechanism.
		// This time the thread will timeout as main thread has longer timeout set
		// Only works if DLL compiled with SQLITE_BUSY_RESERVED_LOCK defined
		////////////////////////////////////////////////////////////////////////////////
		cout << endl << "SQLITE_BUSY test2 on CppSQLite3DB::execDML() - Thread times out BUSY" << endl;
		nThreads = 1;
		_beginthread(WriteLockThreadProc, 0, 0);
		Sleep(2000);

		try
		{
			db.setBusyTimeout(30000);
			int nRows = db.execDML("update details set numcalls = 100 where dayno = 1;");
			cout << "Main thread: updated " << nRows << " rows" << endl;
		}
		catch (CppSQLite3Exception& e)
		{
			cout << "Main thread: " << e.errorCode() << ":" << e.errorMessage() << endl;
		}
		while (nThreads) Sleep(100);


		////////////////////////////////////////////////////////////////////////////////
		// BUSY TEST3 on execDML()
		// Create thread that read locks a table for 5 secs. We will then try to work on
		// that table in the main thread, and demonstrate SQLite's retry mechanism.
		// Main thread will retry until read lock is released
		////////////////////////////////////////////////////////////////////////////////
		cout << endl << "SQLITE_BUSY test3 on CppSQLite3DB::execDML() - Main waits until thread complete" << endl;
		nThreads = 1;
		_beginthread(ReadLockThreadProc, 0, 0);
		Sleep(2000);

		try
		{
			db.setBusyTimeout(10000);
			int nRows = db.execDML("update details set numcalls = 100 where dayno = 1;");
			cout << "Main thread: updated " << nRows << " rows" << endl;
		}
		catch (CppSQLite3Exception& e)
		{
			cout << "Main thread: " << e.errorCode() << ":" << e.errorMessage() << endl;
		}
		while (nThreads) Sleep(100);


	    ////////////////////////////////////////////////////////////////////////////////
		// BUSY TEST1 on pre-compiled DML
		// Create thread that creates a write lock. We will then try to work on
		// that table in the main thread, and demonstrate SQLite's retry mechanism.
		// Main thread will timeout as lock thread has longer 20 second timeout
		////////////////////////////////////////////////////////////////////////////////
		cout << endl << "SQLITE_BUSY test1 on pre-compiled DML - Main times out BUSY" << endl;
		nThreads = 1;
		_beginthread(WriteLockThreadProc, 0, 0);
		Sleep(1000);

		try
		{
			db.setBusyTimeout(10000);
			CppSQLite3Statement stmt = db.compileStatement("update details set numcalls = 100 where dayno = 1;");
			stmt.execDML();
			cout << "Main thread: executed pre-compiled DML" << endl;
		}
		catch (CppSQLite3Exception& e)
		{
			cout << "Main thread: " << e.errorCode() << ":" << e.errorMessage() << endl;
		}
		while (nThreads) Sleep(100);


		////////////////////////////////////////////////////////////////////////////////
		// BUSY TEST2 on pre-compiled DML
		// Create thread that creates a write lock. We will then try to work on
		// that table in the main thread, and demonstrate SQLite's retry mechanism.
		// This time the thread will timeout as main thread has longer timeout set
		// Only works if DLL compiled with SQLITE_BUSY_RESERVED_LOCK defined
		////////////////////////////////////////////////////////////////////////////////
		cout << endl << "SQLITE_BUSY test2 on pre-compiled DML - Thread times out BUSY" << endl;
		nThreads = 1;
		_beginthread(WriteLockThreadProc, 0, 0);
		Sleep(1000);

		try
		{
			db.setBusyTimeout(30000);
			CppSQLite3Statement stmt = db.compileStatement("update details set numcalls = 100 where dayno = 1;");
			stmt.execDML();
			cout << "Main thread: executed pre-compiled DML" << endl;
		}
		catch (CppSQLite3Exception& e)
		{
			cout << "Main thread: " << e.errorCode() << ":" << e.errorMessage() << endl;
		}
		while (nThreads) Sleep(100);


		////////////////////////////////////////////////////////////////////////////////
		// BUSY TEST3 on pre-compiled DML
		// Create thread that read locks a table for 5 secs. We will then try to work on
		// that table in the main thread, and demonstrate SQLite's retry mechanism.
		// Main thread will retry until read lock is released
		////////////////////////////////////////////////////////////////////////////////
		cout << endl << "SQLITE_BUSY test3 on pre-compiled DML - Main waits until Thread complete" << endl;
		nThreads = 1;
		_beginthread(ReadLockThreadProc, 0, 0);
		Sleep(1000);

		try
		{
			db.setBusyTimeout(10000);
			CppSQLite3Statement stmt = db.compileStatement("update details set numcalls = 100 where dayno = 1;");
			stmt.execDML();
			cout << "Main thread: executed pre-compiled DML" << endl;
		}
		catch (CppSQLite3Exception& e)
		{
			cout << "Main thread: " << e.errorCode() << ":" << e.errorMessage() << endl;
		}
		while (nThreads) Sleep(100);
	}
	catch (CppSQLite3Exception& e)
	{
		cout << e.errorCode() << ":" << e.errorMessage() << endl;
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
