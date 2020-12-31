// winpeView.h : interface of the CDebugDirView class
//
/////////////////////////////////////////////////////////////////////////////

class CDebugDirView : public CScrollView
{
protected: // create from serialization only
	CDebugDirView();
	DECLARE_DYNCREATE(CDebugDirView)

// Attributes
public:
	CWinpeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDebugDirView)
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
	virtual ~CDebugDirView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDebugDirView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void PrintPage(CDC* pDC, UINT nPageNumber);
	void PrintPageHeader (CDC* pDC, UINT nPageNumber);
	PIMAGE_SECTION_HEADER GetSectionHeader(LPTSTR name,PIMAGE_NT_HEADERS pNTHeader);
	void DumpAuxSymbols(PIMAGE_SYMBOL pSymbolTable);
	LPTSTR GetSZStorageClass(BYTE storageClass);
	void GetSectionName(WORD section,LPTSTR buffer,UINT cbBuffer);
	void DumpSymbolTable(PIMAGE_SYMBOL pSymbolTable,UINT cSymbols);
	BOOL LookupSymbolName(DWORD index,LPTSTR buffer,UINT length);
	void DumpLineNumbers(PIMAGE_LINENUMBER pln,DWORD count);
	void DumpCOFFHeader();
	PIMAGE_COFF_SYMBOLS_HEADER PCOFFDebugInfo;
	PIMAGE_SYMBOL PCOFFSymbolTable;
    DWORD COFFSymbolCount;
	CStringArray m_DisplayData;
	INT GetDebugDir();
	INT GetSymbols();
	INT  m_cxOffset;
	INT  m_cyPrinter;
	INT  m_cxWidth;
	INT  m_cyScreen;
	INT m_nLinesTotal;
	INT m_nLinesPerPage;
	//
	//
	
	//
	//
	
};

#ifndef _DEBUG  // debug version in winpeView.cpp
inline CWinpeDoc* CDebugDirView::GetDocument()
   { return (CWinpeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
