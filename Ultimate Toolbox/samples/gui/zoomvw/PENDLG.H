// pendlg.h : header file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


class CPenWidthsDlg : public CDialog
{
// Construction
public:
	CPenWidthsDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
	//{{AFX_DATA(CPenWidthsDlg)
	enum { IDD = IDD_PEN_WIDTHS };
	int     m_nThickWidth;
	int     m_nThinWidth;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CPenWidthsDlg)
	afx_msg void OnDefaultPenWidths();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
