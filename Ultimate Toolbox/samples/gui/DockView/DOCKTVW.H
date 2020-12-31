// docktvw.h : interface of the CDocktestView class
//
// Docktest demo of Dockable Views functionality
/////////////////////////////////////////////////////////////////////////////

class CDocktestView : public CView
{
protected: // create from serialization only
	CDocktestView();
	DECLARE_DYNCREATE(CDocktestView)

// Attributes
public:
	CDocktestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocktestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDocktestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDocktestView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in docktvw.cpp
inline CDocktestDoc* CDocktestView::GetDocument()
   { return (CDocktestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
