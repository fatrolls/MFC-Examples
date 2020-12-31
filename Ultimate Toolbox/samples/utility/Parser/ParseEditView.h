#if !defined(AFX_PARSEEDITVIEW_H__D58F87C4_2833_11D3_AA1A_D8EC0A000000__INCLUDED_)
#define AFX_PARSEEDITVIEW_H__D58F87C4_2833_11D3_AA1A_D8EC0A000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParseEditView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParseEditView view

class CParseEditView : public CEditView
{
protected:
	CParseEditView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CParseEditView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParseEditView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CParseEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CParseEditView)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARSEEDITVIEW_H__D58F87C4_2833_11D3_AA1A_D8EC0A000000__INCLUDED_)
