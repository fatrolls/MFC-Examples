// SystemStateInfo.h : main header file for the SYSTEMSTATEINFO application
//

#if !defined(AFX_SYSTEMSTATEINFO_H__367620A8_4CA7_11D2_A72F_525400DAF3CE__INCLUDED_)
#define AFX_SYSTEMSTATEINFO_H__367620A8_4CA7_11D2_A72F_525400DAF3CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSystemStateInfoApp:
// See SystemStateInfo.cpp for the implementation of this class
//

class CSystemStateInfoApp : public CWinApp
{
public:
	CSystemStateInfoApp();

protected:

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemStateInfoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSystemStateInfoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMSTATEINFO_H__367620A8_4CA7_11D2_A72F_525400DAF3CE__INCLUDED_)
