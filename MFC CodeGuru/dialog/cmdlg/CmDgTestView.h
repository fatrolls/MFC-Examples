// CmDgTestView.h : interface of the CCmDgTestView class
//
/////////////////////////////////////////////////////////////////////////////

class CCmDgTestView : public CView
{
protected: // create from serialization only
	CCmDgTestView();
	DECLARE_DYNCREATE(CCmDgTestView)

// Attributes
public:
	CCmDgTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmDgTestView)
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
	virtual ~CCmDgTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCmDgTestView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CmDgTestView.cpp
inline CCmDgTestDoc* CCmDgTestView::GetDocument()
   { return (CCmDgTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
