// PreviewView.h : interface of the CMyPreviewView class
//
/////////////////////////////////////////////////////////////////////////////

class CMyPreviewView : public CView
{
protected: // create from serialization only
	CMyPreviewView();
	DECLARE_DYNCREATE(CMyPreviewView)

// Attributes
public:
	CPreviewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPreviewView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyPreviewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyPreviewView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PreviewView.cpp
inline CPreviewDoc* CMyPreviewView::GetDocument()
   { return (CPreviewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
