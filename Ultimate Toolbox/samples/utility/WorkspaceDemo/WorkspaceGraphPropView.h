// WorkspaceGraphPropView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphPropView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CWorkspaceGraphDoc;

class CWorkspaceGraphPropView : public CFormView
{
protected:
	CWorkspaceGraphPropView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CWorkspaceGraphPropView)

// Form Data
public:
	CWorkspaceGraphDoc* GetDocument();

	//{{AFX_DATA(CWorkspaceGraphPropView)
	enum { IDD = IDD_GRAPHPROP_FORM };
	CSpinButtonCtrl	m_wndSidesSpin;
	CString	m_sSides;
	CString	m_sColor;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceGraphPropView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CWorkspaceGraphPropView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CWorkspaceGraphPropView)
	afx_msg void OnColorBrowse();
	afx_msg void OnChangeSides();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WorkspaceDemoView.cpp
inline CWorkspaceGraphDoc* CWorkspaceGraphPropView::GetDocument()
   { return (CWorkspaceGraphDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
