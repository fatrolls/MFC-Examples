// Roll3vw.h : interface of the CRoll32View class
//
/////////////////////////////////////////////////////////////////////////////

class CRoll32View : public CView
{
protected: // create from serialization only
	CRoll32View();
	DECLARE_DYNCREATE(CRoll32View)

// Attributes
public:
	CRoll32Doc* GetDocument();
	// member variable for Example dialog
	DWORD	m_hExampleDlg;
	DWORD	m_hExampleDlg2;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoll32View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRoll32View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRoll32View)
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg BOOL OnRollupMessage(CWnd* pWndRollup,UINT message,UINT rollupID);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Roll3vw.cpp
inline CRoll32Doc* CRoll32View::GetDocument()
   { return (CRoll32Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
