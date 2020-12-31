// grafview.h : interface of the CGrafView class
//
/////////////////////////////////////////////////////////////////////////////

class CGrafView : public CView
{
protected: // create from serialization only
	CGrafView();
	DECLARE_DYNCREATE(CGrafView)

// Attributes
public:
	CMsdiDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CGrafView();
	virtual void OnDraw(CDC* pDC);	// overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Printing support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Generated message map functions
protected:
	//{{AFX_MSG(CGrafView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in grafview.cpp
inline CMsdiDoc* CGrafView::GetDocument()
   { return (CMsdiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
