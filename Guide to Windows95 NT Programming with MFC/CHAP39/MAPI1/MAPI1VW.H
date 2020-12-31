// Mapi1Vw.h : interface of the CMapi1View class
//
/////////////////////////////////////////////////////////////////////////////

class CMapi1View : public CEditView
{
protected: // create from serialization only
	CMapi1View();
	DECLARE_DYNCREATE(CMapi1View)

// Attributes
public:
	CMapi1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapi1View)
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
	virtual ~CMapi1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMapi1View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Mapi1Vw.cpp
inline CMapi1Doc* CMapi1View::GetDocument()
   { return (CMapi1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
