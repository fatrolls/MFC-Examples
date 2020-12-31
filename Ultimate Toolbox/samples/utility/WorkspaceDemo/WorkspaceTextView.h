// WorkspaceDemoView.h : interface of the CWorkspaceTextView class
//
/////////////////////////////////////////////////////////////////////////////

class CWorkspaceTextView : public CEditView
{
protected: // create from serialization only
	CWorkspaceTextView();
	DECLARE_DYNCREATE(CWorkspaceTextView)

// Attributes
public:
	CWorkspaceTextDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceTextView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWorkspaceTextView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceTextView)
	afx_msg void OnSquare();
	afx_msg void OnCircle();
	afx_msg void OnChange();
	afx_msg void OnWindowNewlengthwindow();
	afx_msg void OnWindowNewtextwindow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WorkspaceDemoView.cpp
inline CWorkspaceTextDoc* CWorkspaceTextView::GetDocument()
   { return (CWorkspaceTextDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
