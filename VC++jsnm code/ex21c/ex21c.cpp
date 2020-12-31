// ex21c.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ex21c.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CEx21cApp

BEGIN_MESSAGE_MAP(CEx21cApp, CWinApp)
	//{{AFX_MSG_MAP(CEx21cApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx21cApp construction

CEx21cApp::CEx21cApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEx21cApp object

CEx21cApp theApp;


extern "C" __declspec(dllexport) double Ex21cSquareRoot(double d)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	TRACE("Entering Ex21cSquareRoot\n");
	if (d >= 0.0) {
		return sqrt(d);
	}
	AfxMessageBox("Can't take square root of a negative number.");
	return 0.0;
}
