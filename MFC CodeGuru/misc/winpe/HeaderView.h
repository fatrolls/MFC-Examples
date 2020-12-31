// winpeView.h : interface of the CHeaderView class
//
/////////////////////////////////////////////////////////////////////////////

class CHeaderView : public CScrollView
{
protected: // create from serialization only
	CHeaderView();
	DECLARE_DYNCREATE(CHeaderView)

// Attributes
public:
	CWinpeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHeaderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHeaderView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CStringArray m_DisplayData;
	void PrintPage(CDC* pDC, UINT nPageNumber);
	void PrintPageHeader (CDC* pDC, UINT nPageNumber);
	INT GetFileHdrOptions();
	INT GetOptnlHdrOptions();
	INT m_nLinesTotal;
	INT m_cyScreen;
	INT  m_cxOffset;
	INT  m_cyPrinter;
	INT  m_cxWidth;
	INT m_nLinesPerPage;
	//
	//
	
	//
	//
	
};

#ifndef _DEBUG  // debug version in winpeView.cpp
inline CWinpeDoc* CHeaderView::GetDocument()
   { return (CWinpeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
