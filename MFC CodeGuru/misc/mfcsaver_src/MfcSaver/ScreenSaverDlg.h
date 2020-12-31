// ScreenSaverDlg.h : header file
//
//////////
//
// Copyright (C) 1991-98 Ed Halley.
//   http://www.explorati.com/people/ed/
//   ed@explorati.com
//
// This published source code represents original intellectual
// property, owned and copyrighted by Ed Halley.
//
// The owner has authorized this source code for general public
// use without royalty, under two conditions:
//    * The source code maintains this copyright notice in full.
//    * The source code is only distributed for free or
//      reasonable duplication cost, not for distribution profit.
//
// Unauthorized use, copying or distribution is a violation of
// U.S. and international laws and is strictly prohibited.
//
//////////
//

#ifndef __SCREENSAVERDLG_H__
#define __SCREENSAVERDLG_H__

/////////////////////////////////////////////////////////////////////////////

// CScreenSaverDlg:
// A configuration dialog for Win95+, WinNT3+ compliant screen savers.
// For use with CScreenSaverWnd, usually found in ScreenSaverWnd.cpp and .h.
// See documentation in those files for more information on screen savers.

/////////////////////////////////////////////////////////////////////////////

#include <scrnsave.h>

// Note: the dialog resource should be DLG_SCRNSAVECONFIGURE.
// Note: the icon resource should be ID_APP.

class CScreenSaverDlg : public CDialog
{
	DECLARE_DYNAMIC(CScreenSaverDlg)
public:
	CScreenSaverDlg();

// Attributes
protected:
public:

// Operations
public:

// Overridables
public:

// Overrides
public:
	//{{AFX_VIRTUAL(CScreenSaverDlg)
	//}}AFX_VIRTUAL
	virtual BOOL OnInitDialog();

// Implementation
public:
	virtual ~CScreenSaverDlg();
	static CScreenSaverDlg* sm_pTheConfigureDialog;

protected:
	virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CScreenSaverDlg)
	afx_msg void OnNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//friend BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT uMsg,
//                                              WPARAM wParam,
//                                              LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

inline CScreenSaverDlg* AfxGetScreenSaverDialog()
	{
		return CScreenSaverDlg::sm_pTheConfigureDialog;
	}

/////////////////////////////////////////////////////////////////////////////

BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT uMsg,
                                       WPARAM wParam, LPARAM lParam);
BOOL WINAPI RegisterDialogClasses(HANDLE hInstance);

/////////////////////////////////////////////////////////////////////////////

#endif // __SCREENSAVERDLG_H__
