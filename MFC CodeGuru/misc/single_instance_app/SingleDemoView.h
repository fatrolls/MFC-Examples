// SingleDemoView.h : interface of the CSingleDemoView class
//
/////////////////////////////////////////////////////////////////////////////

class CSingleDemoView : public CView
{
protected: // create from serialization only
	CSingleDemoView();
	DECLARE_DYNCREATE(CSingleDemoView)

// Attributes
public:
	CSingleDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSingleDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSingleDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSingleDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SingleDemoView.cpp
inline CSingleDemoDoc* CSingleDemoView::GetDocument()
   { return (CSingleDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
