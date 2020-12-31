// CategVw.h : interface of the CCategoriesTable class
//
/////////////////////////////////////////////////////////////////////////////

class CCategoriesTable: public CDaoTableView
{
protected: // create from serialization only
	CCategoriesTable();
	DECLARE_DYNCREATE(CCategoriesTable)

// Attributes
public:
	CMSDIDaoDoc* GetDocument();
	CCategoriesSet *m_pCategoriesSet;

// Operations
public:
	virtual CDaoRecordset* OnGetRecordset();
	virtual long GetRecordCount();
	virtual void GetPrintTitle(CString& strTitle);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCategoriesTable)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCategoriesTable();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCategoriesTable)
	afx_msg void OnDestroy();
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReturn(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DaoView.cpp
inline CMSDIDaoDoc* CCategoriesTable::GetDocument()
   { return (CMSDIDaoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
