// RegTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RegTest.h"
#include "RegTestDlg.h"

#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// derive a class from CRegistry to demonstrate the RegistryTreeWalk()
// method.
class CMyReg : public CRegistry {
	public:
		virtual BOOL	OnValueHit(
							LPCTSTR Key,
							LPCTSTR ValueName,
							const CRegVal & Value,
							USHORT Depth
						) {
							CString mes;
							mes.Format(TEXT("Hit value on path \"%s\": \"%s\" (depth: %hu)"),
								Key, ValueName, Depth);
							::MessageBox(0,mes,TEXT("OnValueHit"),MB_OK);
							return TRUE;	// continue walk
						}

		virtual BOOL	OnKeyHit( LPCTSTR Key, USHORT Depth ) {
							CString mes;
							mes.Format(TEXT("Hit key \"%s\" (depth: %hu)"),
								Key, Depth);
							::MessageBox(0,mes,TEXT("OnKeyHit"),MB_OK);
							return TRUE;	// continue walk
						}
};

/////////////////////////////////////////////////////////////////////////////
// CRegTestApp

BEGIN_MESSAGE_MAP(CRegTestApp, CWinApp)
	//{{AFX_MSG_MAP(CRegTestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegTestApp construction

CRegTestApp::CRegTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRegTestApp object

CRegTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRegTestApp initialization

BOOL CRegTestApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// replace the pathes in the following example with your favourits
	CMyReg reg;
	CRegVal regval;
	
	// Set the path to something you like.
	// Note that the example path is a bad one, because it has a trailing
	// backslash. Watch your debugger's output window to see a comment from
	// the registry class about such paths.
	reg.RegistryTreeWalk(TEXT("Software\\Lemmy\\"));


	CRegTestDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
