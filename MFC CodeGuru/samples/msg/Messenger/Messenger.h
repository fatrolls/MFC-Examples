// Messenger.h : main header file for the MESSENGER application
//

#if !defined(AFX_MESSENGER_H__3987ADC8_E657_11D1_B802_0060084C3BF4__INCLUDED_)
#define AFX_MESSENGER_H__3987ADC8_E657_11D1_B802_0060084C3BF4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMessengerApp:
// See Messenger.cpp for the implementation of this class
//

class CMessengerApp : public CWinApp
{
public:
	CString m_DBPath;

	CMessengerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessengerApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMessengerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSENGER_H__3987ADC8_E657_11D1_B802_0060084C3BF4__INCLUDED_)
