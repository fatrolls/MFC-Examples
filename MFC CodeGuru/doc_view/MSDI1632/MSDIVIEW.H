// msdiview.h : interface of the CMsdiView class
//
/////////////////////////////////////////////////////////////////////////////

class CMsdiView : public CFormView
{
protected: // create from serialization only
	CMsdiView();
	DECLARE_DYNCREATE(CMsdiView)

public:
	//{{AFX_DATA(CMsdiView)
	enum{ IDD = IDD_MSDI_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CMsdiDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CMsdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Printing support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);

// Generated message map functions
protected:
	//{{AFX_MSG(CMsdiView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in msdiview.cpp
inline CMsdiDoc* CMsdiView::GetDocument()
   { return (CMsdiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
