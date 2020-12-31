// DockPropView.h : interface of the CDockPropView class
//
/////////////////////////////////////////////////////////////////////////////

class CDockPropView : public CFormView
{
protected: // create from serialization only
	CDockPropView();
	DECLARE_DYNCREATE(CDockPropView)

public:
	//{{AFX_DATA(CDockPropView)
	enum { IDD = IDD_DOCKPROP_FORM };
	int		m_nSetActive;
	int		m_nDelPage;
	//}}AFX_DATA

// Attributes
public:
	CDockPropDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockPropView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDockPropView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDockPropView)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DockPropView.cpp
inline CDockPropDoc* CDockPropView::GetDocument()
   { return (CDockPropDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
