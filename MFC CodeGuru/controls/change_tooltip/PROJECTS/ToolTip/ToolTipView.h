// ToolTipView.h : interface of the CToolTipView class
//
/////////////////////////////////////////////////////////////////////////////

// determine number of elements in an array (not bytes)
#define _countof(array) (sizeof(array)/sizeof(array[0]))

class CToolTipView : public CView
{
protected: // create from serialization only
	CString m_strNewToolTipText;
	CToolTipView();
	DECLARE_DYNCREATE(CToolTipView)

// Attributes
public:
	CString GetTTT(void);
	void SetNewTTT(CString strNew);
    static CToolTipView* GetVP();

	CToolTipDoc* GetDocument();

// Operations
public:
 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipView)
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
	virtual ~CToolTipView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL GetToolText( UINT nID, CString& strTipText, CString& /*strMessage*/);

// Generated message map functions
protected:
	//{{AFX_MSG(CToolTipView)
	afx_msg void OnChangeToolTip();
	virtual afx_msg BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ToolTipView.cpp
inline CToolTipDoc* CToolTipView::GetDocument()
   { return (CToolTipDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
