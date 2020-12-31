// TabTestView.h : interface of the CTabTestView class
//
/////////////////////////////////////////////////////////////////////////////
#include "TabCtrlAdvanced.h"

class CTabTestView : public CView
{
	CTabCtrlAdvanced* m_pTab;
protected: // create from serialization only
	CTabTestView();
	DECLARE_DYNCREATE(CTabTestView)

// Attributes
public:
	CTabTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabTestView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TabTestView.cpp
inline CTabTestDoc* CTabTestView::GetDocument()
   { return (CTabTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
