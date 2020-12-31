// XColourPicker.h : header file
//
// Written by Chris Maunder (chrismaunder@codeguru.com)
// Extended by Alexander Bischofberger (bischofb@informatik.tu-muenchen.de)
// Copyright (c) 1998.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is
// not sold for profit without the authors written consent, and
// providing that this notice and the authors name is included. If
// the source code in  this file is used in any commercial application
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage whatsoever.
// It's free - so you get what you pay for.

#ifndef XCOLOURPICKER_H
#define XCOLOURPICKER_H

#include "XColourPopup.h"

/////////////////////////////////////////////////////////////////////////////
// CXColourPicker window

void AFXAPI DDX_ColorPicker(CDataExchange * pDX, int nIDC, COLORREF & crColor);
void AFXAPI DDX_ColorPickerCustom(CDataExchange * pDX, int nIDC, CString & strCustomColors);

/////////////////////////////////////////////////////////////////////////////
// CXColourPicker window

class CXColourPicker : public CButton
{
	DECLARE_DYNCREATE(CXColourPicker);

// Construction
public:
	CXColourPicker();
	virtual ~CXColourPicker();

// Attributes
public:
	int m_nSelectedRow, m_nSelectedCol;
	void SetColor(COLORREF crColor);
	COLORREF GetColor();
	void SetCustomColors(COLORREF * pCustomColors);
	void GetCustomColors(COLORREF * pCustomColors);
	void SetCustomColors(LPCTSTR lpszCustomColors);
	CString GetCustomColors();

// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXColourPicker)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSize GetArrowSize();

	// protected attributes
protected:
	BOOL	 m_bTrackSelection;
	COLORREF m_crColor;
	COLORREF m_crEnabledColor;
	COLORREF m_CustomColors[16];
	CRect    m_ArrowRect;

	COLORREF m_DefaultColor;
	BOOL	m_bPopupActive;

	// Generated message map functions
protected:
	//{{AFX_MSG(CXColourPicker)
	afx_msg BOOL OnClicked();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnable(BOOL bEnable);
	//}}AFX_MSG
	afx_msg LONG OnSelEndOK(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnSelEndCancel(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnSelChange(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif //XCOLOURPICKER_H
