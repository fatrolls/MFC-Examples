// winpeView.h : interface of the CSectionTblView class
//
/////////////////////////////////////////////////////////////////////////////

class CSectionTblView : public CScrollView
{
protected: // create from serialization only
	CSectionTblView();
	DECLARE_DYNCREATE(CSectionTblView)

// Attributes
public:
	CWinpeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSectionTblView)
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
	virtual ~CSectionTblView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSectionTblView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
	CStringArray m_DisplayData;
	INT GetSectionTable();
	void PrintPage(CDC* pDC, UINT nPageNumber);
	void PrintPageHeader(CDC* pDC, UINT nPageNumber);
	INT m_cyScreen;
	INT m_cyPrinter;
	INT m_cxOffset;
	INT m_cxWidth;
	INT m_nLinesTotal;
	INT m_nLinesPerPage;
	//
	//
	
	//
	//
	
};

#ifndef _DEBUG  // debug version in winpeView.cpp
inline CWinpeDoc* CSectionTblView::GetDocument()
   { return (CWinpeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
