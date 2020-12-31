// AgTest.h : main header file for the AGTEST application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

// Agent support
#include "AgentLib.h"

#define MT_SYSTEM   200
#define MT_PROCESS  210
#define MT_INIT     250
#define MT_EDIT     251
#define MT_CHECKBOX 252
#define MT_RADIO    253
#define MT_THREAD   254

#define AGENT(x,y,z)    \
      ::AgentSendText2A(x,MT_PROCESS,MT_SYSTEM,__FILE__,__LINE__,y,z)

/////////////////////////////////////////////////////////////////////////////
// CAgTestApp:
// See AgTest.cpp for the implementation of this class
//

class CAgTestApp : public CWinApp
{
public:
	CAgTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAgTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAgTestApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
