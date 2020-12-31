// TcxMsgBoxDemo.h : main header file for the TCXMSGBOXDEMO application
//

#if !defined(AFX_TCXMSGBOXDEMO_H__58875259_90FF_11D3_A393_00104B4DFB35__INCLUDED_)
#define AFX_TCXMSGBOXDEMO_H__58875259_90FF_11D3_A393_00104B4DFB35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTcxMsgBoxDemoApp:
// See TcxMsgBoxDemo.cpp for the implementation of this class
//

class CTcxMsgBoxDemoApp : public CWinApp
{
public:
	CTcxMsgBoxDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTcxMsgBoxDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTcxMsgBoxDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCXMSGBOXDEMO_H__58875259_90FF_11D3_A393_00104B4DFB35__INCLUDED_)
