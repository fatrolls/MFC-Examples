// ex32aView.h : interface of the CEx32aView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx32aCntrItem;

class CEx32aView : public CRichEditView
{
protected: // create from serialization only
	CEx32aView();
	DECLARE_DYNCREATE(CEx32aView)

// Attributes
public:
	CEx32aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx32aView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx32aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx32aView)
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnEditClearAll();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStart(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex32aView.cpp
inline CEx32aDoc* CEx32aView::GetDocument()
   { return (CEx32aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
