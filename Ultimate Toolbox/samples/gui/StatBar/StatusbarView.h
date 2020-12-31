// StatusbarView.h : interface of the CStatusbarView class
//
/////////////////////////////////////////////////////////////////////////////

class CStatusbarView : public CFormView
{
protected: // create from serialization only
	CStatusbarView();
	DECLARE_DYNCREATE(CStatusbarView)

public:
	//{{AFX_DATA(CStatusbarView)
	enum { IDD = IDD_STATUSBAR_FORM };
	BOOL	m_bFont;
	BOOL	m_bCursor;
	BOOL	m_bProcent;
	BOOL	m_bGlasses;
	BOOL	m_bTooltips;
	int		m_nLayout;
	//}}AFX_DATA

// Attributes
public:
	CStatusbarDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusbarView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStatusbarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStatusbarView)
	afx_msg void OnApplybutton();
	afx_msg void OnCheck1();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCursorcheck();
	afx_msg void OnFontcheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in StatusbarView.cpp
inline CStatusbarDoc* CStatusbarView::GetDocument()
   { return (CStatusbarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
