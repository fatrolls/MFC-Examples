// LayoutManagerView.h : interface of the CLayoutManagerView class
//
#include "DlgDemo.h"
#include "OXLayoutManager.h"

/////////////////////////////////////////////////////////////////////////////

class CLayoutManagerView : public CView
{
protected: // create from serialization only
	CLayoutManagerView();
	DECLARE_DYNCREATE(CLayoutManagerView)

// Attributes
public:
	CLayoutManagerDoc* GetDocument();
	CDlgDemo m_dlgDemo;
	COXLayoutManager m_LayoutManager;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayoutManagerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLayoutManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLayoutManagerView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LayoutManagerView.cpp
inline CLayoutManagerDoc* CLayoutManagerView::GetDocument()
   { return (CLayoutManagerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
