#if !defined(AFX_VIEW4_H__A695B2D9_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_)
#define AFX_VIEW4_H__A695B2D9_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// View4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CView4 view

class CView4 : public CView
{
protected:
	CView4();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CView4)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CView4)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CView4();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CView4)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW4_H__A695B2D9_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_)
