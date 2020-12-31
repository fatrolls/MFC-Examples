#if !defined(AFX_BUTTONSTEXTLIST_H__DA15C743_C687_11D1_B110_B5F0ACB7A449__INCLUDED_)
#define AFX_BUTTONSTEXTLIST_H__DA15C743_C687_11D1_B110_B5F0ACB7A449__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ButtonsTextList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButtonsTextList window

class CButtonsTextList : public CListBox
{
// Construction
public:
	CButtonsTextList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonsTextList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CButtonsTextList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonsTextList)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONSTEXTLIST_H__DA15C743_C687_11D1_B110_B5F0ACB7A449__INCLUDED_)
