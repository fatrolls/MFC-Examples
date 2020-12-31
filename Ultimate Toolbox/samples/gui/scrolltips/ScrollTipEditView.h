// ScrollTipEditView.h : interface of the CScrollTipEditView class
//
/////////////////////////////////////////////////////////////////////////////
#include "OXScrollTipOwner.h"

class CScrollTipDemoCntrItem;

class CScrollTipEditView : public CRichEditView
{
protected: // create from serialization only
	CScrollTipEditView();
	DECLARE_DYNCREATE(CScrollTipEditView)

// Attributes
public:
	CScrollTipDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollTipEditView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScrollTipEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	COXScrollTipOwner m_wndHScrollTipOwner;
	COXScrollTipOwner m_wndVScrollTipOwner;

// Generated message map functions
protected:
	void AdjustSettings();
	//{{AFX_MSG(CScrollTipEditView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ScrollTipEditView.cpp
inline CScrollTipDoc* CScrollTipEditView::GetDocument()
   { return (CScrollTipDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
