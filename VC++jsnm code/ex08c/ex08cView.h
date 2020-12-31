#if !defined(EX08CVIEW_H__6084D1FD_488C_11D0_8488_00400526305B__INCLUDED_)
#define EX08CVIEW_H__6084D1FD_488C_11D0_8488_00400526305B__INCLUDED_

// ex08cView.h : interface of the CEx08cView class
//
/////////////////////////////////////////////////////////////////////////////

class CEx08cView : public CView
{
protected: // create from serialization only
	CEx08cView();
	DECLARE_DYNCREATE(CEx08cView)

// Attributes
public:
	CEx08cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx08cView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx08cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx08cView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEngine(UINT nCommand);
	afx_msg void OnViewRefreshbrowse();
	afx_msg void OnViewUpdatebrowse();
	afx_msg void OnViewRefreshsearch();
	afx_msg void OnViewBacksearch();
	afx_msg void OnViewForwardsearch();
	afx_msg void OnViewBackbrowse();
	afx_msg void OnViewForwardbrowse();
	afx_msg void OnFilePrintbrowse();
	afx_msg void OnFilePrintsearch();
	afx_msg void OnUpdateIndicatorBusy(CCmdUI* pCmdUI);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnBeforeNavigateExplorer1(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT FAR* PostData, LPCTSTR Headers, BOOL FAR* Cancel);
	afx_msg void OnStatusTextChangeExplorer1(LPCTSTR Text);
	afx_msg void OnBeforeNavigateExplorer2(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT FAR* PostData, LPCTSTR Headers, BOOL FAR* Cancel);
	afx_msg void OnTitleChangeExplorer2(LPCTSTR Text);
	afx_msg void OnStatusTextChangeExplorer2(LPCTSTR Text);
	afx_msg void OnNewWindowExplorer2(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT FAR* PostData, LPCTSTR Headers, BOOL FAR* Processed);
	DECLARE_MESSAGE_MAP()
private:
	void UpdateStatusBar();
	BOOL KeepSearching(LPCTSTR URL);
};

#ifndef _DEBUG  // debug version in ex08cView.cpp
inline CEx08cDoc* CEx08cView::GetDocument()
   { return (CEx08cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(EX08CVIEW_H__6084D1FD_488C_11D0_8488_00400526305B__INCLUDED)
