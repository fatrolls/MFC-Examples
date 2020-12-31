// CustVw.h : interface of the CCustomersTable class
//
/////////////////////////////////////////////////////////////////////////////

class CCustomersTable: public CDaoTableView
{
protected: // create from serialization only
	CCustomersTable();
	DECLARE_DYNCREATE(CCustomersTable)

// Attributes
public:
	CMSDIDaoDoc* GetDocument();
	CCustomersSet *m_pCustomersSet;

// Operations
public:
	virtual CDaoRecordset* OnGetRecordset();
	virtual long GetRecordCount();
	virtual void GetPrintTitle(CString& strTitle);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomersTable)
	public:
	virtual void OnDraw(CDC* pDC);	// overridden to draw this view
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
	virtual ~CCustomersTable();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCustomersTable)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in DaoView.cpp
inline CMSDIDaoDoc* CCustomersTable::GetDocument()
   { return (CMSDIDaoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
