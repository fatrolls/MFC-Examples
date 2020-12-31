// MfcSaver.h : main header file for the MFCSAVER application
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

#ifndef __MFCSAVER_H__
#define __MFCSAVER_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////

#include "ScreenSaverWnd.h"

class CMfcSaver : public CScreenSaverWnd
{
// Construction
public:
	CMfcSaver();

// Attributes
protected:

	struct _icon { int iImage; CPoint ptP; CSize szV; int nStuck; };

	CImageList m_ilIcons;
	CArray<_icon,_icon&> m_aIcon;
	int m_nIcons;
	int m_nSpeed;
public:
	int GetIconCount() const;
	void SetIconCount(int nIcons);
	//
	int GetIconSpeed() const;
	void SetIconSpeed(int nSpeed);

// Operations
public:
	void EraseMfcSaverIcon(int i, CDC* pDC);
	BOOL IsMfcSaverIconColliding(int i, CPoint ptP);
	BOOL IsMfcSaverIconOffscreen(int i);
	void UpdateMfcSaverIconPosition(int i);
	void DrawMfcSaverIcon(int i, CDC* pDC);
	void BounceMfcSaverIcon(int i);
	void SetupMfcSaverIcon(int i);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);
	virtual void OnInitialUpdate();
	virtual void SaveOptions();
	virtual void RestoreOptions();
	//{{AFX_VIRTUAL(CMfcSaver)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcSaver();

protected:
	//{{AFX_MSG(CMfcSaver)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif // __MFCSAVER_H__
