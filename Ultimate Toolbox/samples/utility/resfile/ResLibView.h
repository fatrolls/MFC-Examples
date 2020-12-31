// ResLibView.h : interface of the CResLibView class
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

/////////////////////////////////////////////////////////////////////////////

class CResLibView : public CTreeView
{
protected: // create from serialization only
	CResLibView();
	DECLARE_DYNCREATE(CResLibView)

	// format output
	static void GetTypeOutput(CString& sType, int& iImage);
	static void GetNameOutput(CString& sName, WORD nLang);

	// tree item
	int GetSelectedResIndex();
	HTREEITEM FindTypeHItem(UINT nIndex);

	CImageList m_ilFolder;
	HTREEITEM  m_hRootItem;

	// values copied from document or app
	CResLibDoc*			m_pDoc;
	COXResourceLibrary* m_pResLib;
	CLIPFORMAT			m_nClipFormat;

	BOOL				m_bModifiable;

// Attributes
public:
	CResLibDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResLibView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResLibView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CResLibView)
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditClear();
	afx_msg void OnUpdateEditClear(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ResLibView.cpp
inline CResLibDoc* CResLibView::GetDocument()
   { return (CResLibDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
