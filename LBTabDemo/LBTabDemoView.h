// LBTabDemoView.h : interface of the CLBTabDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LBTABDEMOVIEW_H__D7B746AD_C6B1_11D3_BB51_CD4AD9600417__INCLUDED_)
#define AFX_LBTABDEMOVIEW_H__D7B746AD_C6B1_11D3_BB51_CD4AD9600417__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLBTabDemoView : public CView
{
protected: // create from serialization only
	CLBTabDemoView();
	DECLARE_DYNCREATE(CLBTabDemoView)
	
// Attributes
public:
	CLBTabDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLBTabDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLBTabDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CLBTabDemoView)
	afx_msg void OnDemoStack();
	afx_msg void OnDemoUnstack();
	afx_msg void OnCommonTab();
	afx_msg void OnCommonTabStack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LBTabDemoView.cpp
inline CLBTabDemoDoc* CLBTabDemoView::GetDocument()
   { return (CLBTabDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LBTABDEMOVIEW_H__D7B746AD_C6B1_11D3_BB51_CD4AD9600417__INCLUDED_)
