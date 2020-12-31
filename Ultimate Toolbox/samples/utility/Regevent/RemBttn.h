#if !defined(AFX_REMBTTN_H__401B21F9_ED61_11D0_A23A_0000929B340A__INCLUDED_)
#define AFX_REMBTTN_H__401B21F9_ED61_11D0_A23A_0000929B340A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RemBttn.h : header file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

/////////////////////////////////////////////////////////////////////////////
// CRemBttn window

class CRemBttn : public CButton
{
// Construction
public:
	CRemBttn();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemBttn)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bClick;
	virtual ~CRemBttn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRemBttn)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REMBTTN_H__401B21F9_ED61_11D0_A23A_0000929B340A__INCLUDED_)
