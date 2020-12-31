#if !defined(AFX_PROPPAGE3_H__91A4B005_0AB6_11D2_8412_0000B43382FE__INCLUDED_)
#define AFX_PROPPAGE3_H__91A4B005_0AB6_11D2_8412_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPage3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPage3 dialog
#include "ColourPicker.h"
class Doc;
class View;

class CPropPage3 : public CDialog
{
// Construction
public:
	CPropPage3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropPage3)
	enum { IDD = IDD_PROP_PAGE3 };
	CColourPicker	wndTextCol;
	CColourPicker	wndBdrCol;
	CColourPicker	wndBkCol;
	CComboBox	wndLineType;
	CComboBox	wndBorderSize;
	CComboBox	wndBorder;
	CComboBox	wndBckType;
	int		iLineWidth;
	//}}AFX_DATA
	COLORREF	crBack, crText, crBdr;

	Doc * pDoc;
	View * pView;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropPage3)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelendokCbBckType();
	afx_msg void OnSelendokCbBorder();
	afx_msg void OnSelendokCbBordersize();
	afx_msg void OnSelendokCbLinetype();
	afx_msg void OnKillfocusEdLw();
	afx_msg LONG OnColSelendOk(UINT lParam, LONG wParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGE3_H__91A4B005_0AB6_11D2_8412_0000B43382FE__INCLUDED_)
