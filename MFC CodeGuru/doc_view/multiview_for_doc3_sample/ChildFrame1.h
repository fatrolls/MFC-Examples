#if !defined(AFX_CHILDFRAME1_H__A695B2DA_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_)
#define AFX_CHILDFRAME1_H__A695B2DA_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChildFrame1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChildFrame1 frame

class CChildFrame1 : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame1)
protected:
	CChildFrame1();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame1)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CChildFrame1();

	// Generated message map functions
	//{{AFX_MSG(CChildFrame1)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRAME1_H__A695B2DA_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_)
