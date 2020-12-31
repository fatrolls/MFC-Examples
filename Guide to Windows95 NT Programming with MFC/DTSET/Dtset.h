// dtset.h : main header file for the DATENTRY application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDTSetApp:
// See datentry.cpp for the implementation of this class
//

class CDTSetApp : public CWinApp
{
public:
	CDTSetApp();

protected:
	//{{AFX_VIRTUAL(CDTSetApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDTSetApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  CString m_sHelpFilePath;
};


/////////////////////////////////////////////////////////////////////////////
