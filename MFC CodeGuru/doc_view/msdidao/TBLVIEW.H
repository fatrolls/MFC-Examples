// DaoView.h : interface of the CDaoTableView class
//
/////////////////////////////////////////////////////////////////////////////

typedef struct { CRect rectItem, rectLabel; UINT nJustify; } PRNCOLINFO;

class CDaoTableView : public CListView
{
protected: // create from serialization only
	CDaoTableView();
	DECLARE_DYNCREATE(CDaoTableView)

// Attributes
public:
	CMSDIDaoDoc* GetDocument();

// list view colors
	COLORREF m_colorText;
	COLORREF m_colorTextBk;
	COLORREF m_colorBkgnd;

// list font
	CFont m_Font;
	int m_tmAveCharWidth;

// list size and position
	int m_cxClient, m_cyClient;

// list operation
	int m_nJustifyFirstCol;
	CArray<COleVariant, COleVariant&> m_Record;
	UINT JustifyText(int fmt, int c);
	void RepaintSelectedItems();
	void UpdateViews();
	BOOL AddColumn(LPCTSTR strItem, int nItem, int nSubItem, int nMask, int nFmt);
	BOOL AddItem(int nItem, LPARAM lParam = 0);
	LPCTSTR MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset);
	void DrawRaster(CDC* pDC);

// printing
	BOOL m_bFitToPage;
	BOOL m_bPrintMarge;
	CPrinterFont m_PrintFont;
	int m_PageHeight;
	int m_nColPage;
	int m_RowsPerPrintedPage;
	int PrintCharPerLine();

// Operations
public:
	virtual CDaoRecordset* OnGetRecordset();
	virtual long GetRecordCount();
	virtual void GetPrintTitle(CString& strTitle);
	virtual void SetPrintRectangle(CDC* pDC, CPrintInfo* pInfo);
	virtual int  GetListLine(int Line, CString& strLine);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoTableView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

// Implementation
public:
	virtual ~CDaoTableView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDaoTableView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReturn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnHeaderBeginTrack(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHeaderEndTrack(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DaoView.cpp
inline CMSDIDaoDoc* CDaoTableView::GetDocument()
   { return (CMSDIDaoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
