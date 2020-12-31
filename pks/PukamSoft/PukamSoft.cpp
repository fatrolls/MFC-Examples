// PukamSoft.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PukamSoft.h"
#include "PukamSoftDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPukamSoftApp

BEGIN_MESSAGE_MAP(CPukamSoftApp, CWinApp)
	//{{AFX_MSG_MAP(CPukamSoftApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPukamSoftApp construction

CPukamSoftApp::CPukamSoftApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPukamSoftApp object

CPukamSoftApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPukamSoftApp initialization

BOOL CPukamSoftApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
#if 0
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif
	if (m_dbWrapper.CreateConnection(LPCTSTR("Microsoft.Jet.OLEDB.4.0"),LPCTSTR("PukamSoft.mdb")) == FALSE)
	{
		AfxMessageBox(m_dbWrapper.GetErrorMessage());
		return FALSE;
	}

	m_hDLL = ::LoadLibrary(DLLFILENAME);

	if(!m_hDLL)
	{
		AfxMessageBox("Failed to load Resource DLL");
		return FALSE;
	}

	LoadData();

	CPukamSoftDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

CCustomDB* CPukamSoftApp::GetConnectionObject()
{
	return &m_dbWrapper;
}

int CPukamSoftApp::ExitInstance() 
{
	if(m_hDLL)
	{
		FreeLibrary(m_hDLL);
	}
	
	return CWinApp::ExitInstance();
}

HMODULE CPukamSoftApp::GetDLLHandle()
{
	return m_hDLL;
}

void CPukamSoftApp::LoadData()
{
	CString csField1 = "PK_vCategory";
	CString csField2 = "PK_vStorageLocation";

	m_dbWrapper.Select("Category",&m_csCategoriesArray,1,(char*)(LPCTSTR)csField1);
	m_dbWrapper.Select("Storage_Location",&m_csStorageLocationArray,1,(char*)(LPCTSTR)csField2);
}

CStringArray* CPukamSoftApp::GetCategories()
{
	return &m_csCategoriesArray;
}

CStringArray* CPukamSoftApp::GetStorageLocation()
{
	return &m_csStorageLocationArray;
}