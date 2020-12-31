#if !defined(AFX_CHILDFRAME2_H__A695B2DB_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_)
#define AFX_CHILDFRAME2_H__A695B2DB_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChildFrame2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChildFrame2 frame

class CChildFrame2 : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame2)
protected:
	CChildFrame2();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame2)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CChildFrame2();

	// Generated message map functions
	//{{AFX_MSG(CChildFrame2)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRAME2_H__A695B2DB_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_)
