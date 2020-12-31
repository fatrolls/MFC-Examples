#if !defined(AFX_MYSLIDERCONTROL_H__C76FA857_51CC_4EB6_A8E2_8323BBEF10BD__INCLUDED_)
#define AFX_MYSLIDERCONTROL_H__C76FA857_51CC_4EB6_A8E2_8323BBEF10BD__INCLUDED_
#pragma once   // speed up compiling with MSVC++, file will only be read once
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySliderControl.h : header file
//
//
// MySliderControl.cpp : implementation file
//
//
// Copyright (C) 2002 by Nic Wilson
// All rights reserved
//
// This is free software.
// This code may be used in compiled form in any way you desire. This  
// file may be redistributed unmodified by any means PROVIDING it is   
// not sold for profit without the authors written consent, and   
// providing that this notice and the authors name and all copyright   
// notices remains intact. If the source code in this file is used in   
// any  commercial application then a statement along the lines of   
// "Portions Copyright © 2001-2002 Nic Wilson" must be included in   
// the startup banner, "About" box and printed documentation. An email   
// letting me know that you are using it would be nice.
//
// No warrantee of any kind, expressed or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Version: 1.0 //initial release 2001.
// Release: 1.0 // Release: 2.0 November 2002  Custom channels, and custom thumbs.
//       
// See Class Members.txt for an explanation of each member function. 
//
// FEATURES:
//
// Transparent background.
// Custom Transparent Channel
// Custom thumb with optional colours..
// CStatic objects can be auto sized.
// Derived from CSlider

// USAGE:

// Add the MySliderControl.cpp and MySliderControl.h files to your project using 
// "Insert Files into Project" function of Visual C++ or Studio.
// This can be accessed from the workspace by right clicking on the "Source 
// Files" and "Header Files" folders.
//
//
// Add one or more CSlider objects to your application.
//
// Add an  #include "MySliderControl.h" to your applications .h file.
// Add a variable of "Category:  Control",  "Variable Type: CMatrixStatic".
// If CMatrixStatic is does not appear then find your projects .CLW file and
// delete it.  Choose ClassWizard view and when prompted rebuild the CLW file 
// and include the MySliderControl files.  You will also need to select the correct
// dialog class for your dialog.  
// The other option is select the variable as a CSlider control variable then find
// alter its definition from CSliderControl to CMySliderControl.
//
// -----------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CMySliderControl window

class CMySliderControl : public CSliderCtrl
{
	HDC			m_dcBk;
	HBITMAP		m_bmpBk;
	HBITMAP     m_bmpBkOld;
	COLORREF	m_crThumbColor;
	COLORREF	m_crThumbColorSelected;

// Construction
public:
	CMySliderControl();
	bool m_bRedraw;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySliderControl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMySliderControl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMySliderControl)
		afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	void SetThumbColors(COLORREF face, COLORREF highlight);
	void SetllPos(LONGLONG nPos);
	void DrawTransparent(BOOL bRepaint);
private:
	void DrawChannel(CDC *pDC, LPNMCUSTOMDRAW lpcd);
	void DrawThumb(CDC *pDC, LPNMCUSTOMDRAW lpcd);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSLIDERCONTROL_H__C76FA857_51CC_4EB6_A8E2_8323BBEF10BD__INCLUDED_)
