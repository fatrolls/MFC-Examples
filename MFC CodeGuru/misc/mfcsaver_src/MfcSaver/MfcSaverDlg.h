// MfcSaverDlg.h : header file
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

#ifndef __MFCSAVERDLG_H__
#define __MFCSAVERDLG_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////

#include "ScreenSaverDlg.h"

class CMfcSaverDlg : public CScreenSaverDlg
{
// Construction
public:
	CMfcSaverDlg();

// Dialog Data
public:
	//{{AFX_DATA(CMfcSaverDlg)
	enum { IDD = DLG_SCRNSAVECONFIGURE };
	//}}AFX_DATA

// Overrides
public:
	//{{AFX_VIRTUAL(CMfcSaverDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	//{{AFX_MSG(CMfcSaverDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnURL();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // __MFCSAVERDLG_H__
