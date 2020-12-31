// DIBView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDIBView view

#define WM_DOREALIZE (WM_USER + 0)
#define IS_WIN30_DIB(lpbi) ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))

class CDIBView : public CView
{
protected:
	CDIBView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDIBView)

// Attributes
public:
	HDIB m_hDIB;
	CPalette* m_palDIB;
	CSize m_sizeDoc;

// Operations
public:
	void ReplaceHDIB(HDIB hDIB);
	void InitDIBData();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIBView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDIBView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDIBView)
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg LRESULT OnDoRealize(WPARAM wParam, LPARAM lParam);  // user message
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
