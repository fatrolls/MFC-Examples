#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CBtnApp : public CWinApp
{
public:
	CBtnApp();
	//{{AFX_VIRTUAL(CBtnApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CBtnApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
