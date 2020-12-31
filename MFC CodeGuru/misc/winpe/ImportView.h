// winpeView.h : interface of the CImportView class
//
/////////////////////////////////////////////////////////////////////////////

class CImportView : public CScrollView
{
protected: // create from serialization only
	CImportView();
	DECLARE_DYNCREATE(CImportView)

// Attributes
public:
	CWinpeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportView)
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
	virtual ~CImportView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImportView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AttaLine(CHAR* pLine);
	void PrintPage(CDC* pDC, UINT nPageNumber);
	void PrintPageHeader (CDC* pDC, UINT nPageNumber);
	CStringArray m_DisplayData;
	INT GetImportsSection();
	INT m_nLinesTotal;
	INT m_nLinesPerPage;
	INT  m_cxOffset;
	INT  m_cyPrinter;
	INT  m_cxWidth;
	INT  m_cyScreen;
	BOOL m_keepprinting;
	//
	//
	
	//
	//
	
};

#ifndef _DEBUG  // debug version in winpeView.cpp
inline CWinpeDoc* CImportView::GetDocument()
   { return (CWinpeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
