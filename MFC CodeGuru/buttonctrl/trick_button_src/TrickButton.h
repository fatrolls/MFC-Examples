#if !defined(AFX_TRICKBUTTON_H__B6A0FBAD_FDF4_11D1_AB40_8C80B0000000__INCLUDED_)
#define AFX_TRICKBUTTON_H__B6A0FBAD_FDF4_11D1_AB40_8C80B0000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// TrickButton.h : header file
//
// TrickButton is a drop-in pushbutton control that cannot
// be pressed. As soon as the user moves the mouse over the 
// the button will scurry away out of reach. Check out the 
// header file or the accompanying HTML doc file for details.
//
// Written by Chris Maunder (Chris.Maunder@cbr.clw.csiro.au)
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
// The author accepts no liability if it causes any damage to your
// computer, causes your pet cat to fall ill, increases baldness or
// makes you car start emitting strange noises when you start it up.
//
// Expect bugs.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 

/////////////////////////////////////////////////////////////////////////////
// CTrickButton window

class CTrickButton : public CButton
{
// Construction
public:
	CTrickButton();

// Attributes
public:
    int m_nJumpDistance;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrickButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTrickButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTrickButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRICKBUTTON_H__B6A0FBAD_FDF4_11D1_AB40_8C80B0000000__INCLUDED_)
