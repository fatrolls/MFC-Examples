// stdafx.cpp : source file that includes just the standard includes
//	Adp_Test.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "StdCGI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
//////////////////////////////////////////////////////////////////////////////
// AssertFailedLine
// 07/11/96		Chnaged to use cout as this should be Multithread aware
// 15/05/96		Function Idea stolen ffom an idea in MFC
// Function is only relevant while in debug.
// If the user of this function needs the output to be placed in the HTML 
// document then remove the comment printf structure at the beginning and end.
// 
void AssertFailedLine( PCSTR cpszFileName, CINT ciLine )
{
	cout << "<!--ASSERT FAILURE\nProblem in File :-";
	cout << cpszFileName << "\n@ Line :- " << ciLine << "-->" << endl;
}		// End AssertFailedLine

//////////////////////////////////////////////////////////////////////////////
// OutPutInfoLine
// 07/11/96		Chnaged to use cout as this should be Multithread aware
// 23/05/96		Function Created
// Function is only relevant while in debug.
// If the user of this function needs the output to be placed in the HTML 
// document then remove the comment printf structure at the beginning and end.
// 
void OutPutInfoLine( PCSTR cpszFileName, CINT ciLine, PCSTR cpszOutput )
{
	cout << "<!--OutPut Info Line\nIn File :-" << cpszFileName;
	cout << " @ Line :- " << ciLine << "\nInfo :- " << cpszOutput << "-->" << endl;
}		// End OutPutInfoLine
#else
//////////////////////////////////////////////////////////////////////////////
// OutPutInfoLine
// 07/11/96		Chnaged to use cout as this should be Multithread aware
// 01/08/96		Added a ticker to make the Browser / User feel happy etc
void OutPutInfoLine( PCSTR cpszFileName, CINT ciLine, PCSTR cpszOutput )
{
	cout << "<!--App Load Timer-->" << endl;
}		// End OutPutInfoLine

#endif

