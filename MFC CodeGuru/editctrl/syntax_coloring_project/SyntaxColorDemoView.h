// SyntaxColorDemoView.h : interface of the CSyntaxColorDemoView class
//
/////////////////////////////////////////////////////////////////////////////

class ColorEditWnd;
class CSyntaxColorDemoView : public CFormView
{

public:
	ColorEditWnd * cColorWnd;


protected: // create from serialization only
	CSyntaxColorDemoView();
	DECLARE_DYNCREATE(CSyntaxColorDemoView)

public:
	//{{AFX_DATA(CSyntaxColorDemoView)
	enum{ IDD = IDD_SYNTAXCOLORDEMO_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CSyntaxColorDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSyntaxColorDemoView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSyntaxColorDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSyntaxColorDemoView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnRetab();
	afx_msg void OnShow();
	afx_msg void OnUpdateShow(CCmdUI* pCmdUI);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SyntaxColorDemoView.cpp
inline CSyntaxColorDemoDoc* CSyntaxColorDemoView::GetDocument()
   { return (CSyntaxColorDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
