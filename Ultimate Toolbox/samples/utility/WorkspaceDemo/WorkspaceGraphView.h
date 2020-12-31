// WorkspaceGraphView.h : header file
//
//====================================================================
//===============  Dundas Software ==================================
//===================================================================

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceGraphView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CWorkspaceGraphDoc;

class CWorkspaceGraphView : public CFormView
{
protected:
	CWorkspaceGraphView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CWorkspaceGraphView)

// Form Data
public:
	CWorkspaceGraphDoc* GetDocument();

	//{{AFX_DATA(CWorkspaceGraphView)
	enum { IDD = IDD_GRAPH_FORM };
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
	//{{AFX_VIRTUAL(CWorkspaceGraphView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT m_nPolyRadius;
	UINT m_nPolyOffsetX;
	UINT m_nPolyOffsetY;
	UINT m_nSides;
	UINT m_color;

	virtual ~CWorkspaceGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CWorkspaceGraphView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WorkspaceDemoView.cpp
inline CWorkspaceGraphDoc* CWorkspaceGraphView::GetDocument()
   { return (CWorkspaceGraphDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
