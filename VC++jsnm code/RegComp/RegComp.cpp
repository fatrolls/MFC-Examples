// RegComp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "regcomp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CSpecialFileDialog : public CFileDialog
// exists only to display the icon
{
public:
	CSpecialFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
				DWORD dwFlags,LPCTSTR lpszFilter) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter) {}
	virtual BOOL OnInitDialog();
};

BOOL CSpecialFileDialog::OnInitDialog()
{
	if(CFileDialog::OnInitDialog() == TRUE) {
		HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		CWnd* pParent = GetParent();
		if(pParent != NULL) {  // null in NT 3.51
		// there's a phantom parent dialog -- gotta use it
			pParent->SetIcon(hIcon, TRUE);			// Set big icon
			pParent->SetIcon(hIcon, FALSE);		// Set small icon
			pParent->GetDlgItem(IDOK)->SetWindowText("Register");
		}
		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CRegCompApp

BEGIN_MESSAGE_MAP(CRegCompApp, CWinApp)
	//{{AFX_MSG_MAP(CRegCompApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegCompApp construction

CRegCompApp::CRegCompApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRegCompApp object

CRegCompApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRegCompApp initialization

BOOL CRegCompApp::InitInstance()
{
	TRACE("Entering CRegCompApp::InitInstance\n");
	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	// make sure to set Explorer options to allow DLLs to be visible
	CSpecialFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"OCX files (*.ocx)|*.ocx|DLL files (*.dll)|*.dll||");
	dlgFile.m_ofn.lpstrTitle = "Register OCX/DLL File";
	if(dlgFile.DoModal() != IDOK)  return FALSE;
	CString strDllPath = dlgFile.GetPathName();

	// this wouldn't work for a dynamically linked Regular DLL
	HINSTANCE h = ::LoadLibrary(strDllPath);
	if(h == NULL) {
		CString msg;
		msg.Format("Failed to find server %s", strDllPath);
		AfxMessageBox(msg);
		return FALSE;
	}
	FARPROC pFunc = ::GetProcAddress((HMODULE) h, "DllRegisterServer");
	if(pFunc == NULL) {
		AfxMessageBox("Failed to find DllRegisterServer function");
		return FALSE;
	}
	(*pFunc)();	// call the function to register the server
	AfxMessageBox("Server registered OK");
	return FALSE;
}
