// CustomizeView.h : interface of the CCustomizeView class
//
/////////////////////////////////////////////////////////////////////////////

class CCustomizeView : public CView
{
protected: // create from serialization only
	CCustomizeView();
	DECLARE_DYNCREATE(CCustomizeView)
	PROCESS_INFORMATION	 process;
// Attributes
public:
	CCustomizeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomizeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustomizeView)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CustomizeView.cpp
inline CCustomizeDoc* CCustomizeView::GetDocument()
   { return (CCustomizeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
