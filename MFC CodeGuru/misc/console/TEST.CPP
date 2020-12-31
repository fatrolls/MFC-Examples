#include <windows.h>

#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>

#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif

#include "console.h"



#include <crtdbg.h>


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR     lpCmdLine,
                     int       nCmdShow)
{
    CConsole con(TRUE);
    con.RedirectToConsole(0);      
    int iVar;
    printf ("NumLines:%d,Columns:%d,Attibutes:%d,MaxLines:%d\n",
        con.GetNumberOfLines(),con.GetNumberOfColumns (), con.GetAttributes(),
        con.GetMaxLinesInWindow());
            

    // test stdio
    con.SetNumberOfLines (200);
    con.SetNumberOfColumns (132);
    con.SetMaxLinesInWindow (25);

    printf ("NumLines:%d,Columns:%d,Attibutes:%d,MaxLines:%d\n",
        con.GetNumberOfLines(),con.GetNumberOfColumns (), con.GetAttributes(),
        con.GetMaxLinesInWindow());

    fprintf(stdout, "Test output to stdout\n");
    fprintf(stderr, "Test output to stderr\n");
    fprintf(stdout, "Enter an integer to test stdin: ");
    WORD x = con.SetAttributes (FOREGROUND_BLUE|BACKGROUND_GREEN,2);
    scanf("%d", &iVar);
    con.SetAttributes (x);
   printf("You entered %d\n", iVar);

    //test iostreams
    cout << "Test output to cout" << endl;
    cerr << "Test output to cerr" << endl;
    clog << "Test output to clog" << endl;
    cout << "Enter an integer to test cin: ";
    cin >> iVar;
    cout << "You entered " << iVar << endl;

#ifndef _USE_OLD_IOSTREAMS
    // test wide iostreams
    wcout << L"Test output to wcout" << endl;
    wcerr << L"Test output to wcerr" << endl;
    wclog << L"Test output to wclog" << endl;
    wcout << L"Enter an integer to test wcin: ";
    wcin >> iVar;
    wcout << L"You entered " << iVar << endl;
#endif


    // test CrtDbg output
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDERR );
    _CrtSetReportMode( _CRT_ERROR,  _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR,  _CRTDBG_FILE_STDERR);
    _CrtSetReportMode( _CRT_WARN,   _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_WARN,   _CRTDBG_FILE_STDERR);

    _RPT0(_CRT_WARN, "This is testing _CRT_WARN output\n");
    _RPT0(_CRT_ERROR, "This is testing _CRT_ERROR output\n");

    _ASSERT( 0 && "testing _ASSERT" );
    _ASSERTE( 0 && "testing _ASSERTE" );

    Sleep(2000);

    return 0;
}


