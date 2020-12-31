#if !defined(AFX_COLORCOMBOEX_H__82ACEB03_8F6E_11D1_B7B1_00A024DE65ED__INCLUDED_)
#define AFX_COLORCOMBOEX_H__82ACEB03_8F6E_11D1_B7B1_00A024DE65ED__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ColorComboEx.h : header file
//
// Eric Zimmerman coolez@one.net

#include <afxtempl.h>	// Used for CArray

/////////////////////////////////////////////////////////////////////////////
// CColorComboEx window

class CColorComboEx : public CComboBox
{
// Construction
public:
	CColorComboEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorComboEx)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	CArray<COLORREF, COLORREF> colors;
	virtual ~CColorComboEx();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CColorComboEx)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORCOMBOEX_H__82ACEB03_8F6E_11D1_B7B1_00A024DE65ED__INCLUDED_)
