// winpeView.h : interface of the CResourceSView class
//
/////////////////////////////////////////////////////////////////////////////

class CResourceSView : public CScrollView
{
protected: // create from serialization only
	CResourceSView();
	DECLARE_DYNCREATE(CResourceSView)

// Attributes
public:
	CWinpeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceSView)
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
	virtual ~CResourceSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CResourceSView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void PrintPage(CDC* pDC, UINT nPageNumber);
	void PrintPageHeader(CDC* pDC, UINT nPageNumber);
	LPVOID GetSectionPtr(LPTSTR name,PIMAGE_NT_HEADERS pNTHeader,DWORD imageBase);
	void DumpResourceEntry(PIMAGE_RESOURCE_DIRECTORY_ENTRY resDirEntry, DWORD resourceBase,DWORD level);
	void GetResourceNameFromId(DWORD id,DWORD resourceBase,LPTSTR buffer,UINT cBytes);
	void GetResourceTypeName(DWORD type,LPTSTR buffer,UINT cBytes);
	void DumpResourceDirectory(PIMAGE_RESOURCE_DIRECTORY resDir,
										   DWORD resourceBase,
										   DWORD level,
										   DWORD resourceType);
	CStringArray m_DisplayData;
	INT GetResourceSection();
	
	
	INT m_nLinesTotal;
	INT m_nLinesPerPage;
	INT  m_cxOffset;
	INT  m_cyPrinter;
	INT  m_cxWidth;
	//
	//
	
	//
	//
	
};

#ifndef _DEBUG  // debug version in winpeView.cpp
inline CWinpeDoc* CResourceSView::GetDocument()
   { return (CWinpeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
