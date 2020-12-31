// WorkspaceLengthView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceLengthView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CWorkspaceLengthView : public CFormView
{
protected:
	CWorkspaceLengthView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CWorkspaceLengthView)

// Form Data
public:
	CWorkspaceTextDoc* GetDocument();

	//{{AFX_DATA(CWorkspaceLengthView)
	enum { IDD = IDD_LENGTH_FORM };
	CSpinButtonCtrl	m_wndLengthSpin;
	CString	m_sLength;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceLengthView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CWorkspaceLengthView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CWorkspaceLengthView)
	afx_msg void OnWindowNewtextwindow();
	afx_msg void OnWindowNewlengthwindow();
	afx_msg void OnChangeLength();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WorkspaceDemoView.cpp
inline CWorkspaceTextDoc* CWorkspaceLengthView::GetDocument()
   { return (CWorkspaceTextDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
