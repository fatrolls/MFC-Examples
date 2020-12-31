#if !defined(AFX_MYANIMATECTRL_H__A3CC4434_1C26_11D2_8890_0080C83F712F__INCLUDED_)
#define AFX_MYANIMATECTRL_H__A3CC4434_1C26_11D2_8890_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyAnimateCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyAnimateCtrl window

class CMyAnimateCtrl : public CAnimateCtrl
{
// Construction
public:
	CMyAnimateCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAnimateCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyAnimateCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyAnimateCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	afx_msg LONG OnMouseEnter(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYANIMATECTRL_H__A3CC4434_1C26_11D2_8890_0080C83F712F__INCLUDED_)
