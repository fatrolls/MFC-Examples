// ResizingPropSheet.h : header file
//
// This class defines custom modal property sheet 
// CResizingPropSheet.
 
#ifndef __RESIZINGPROPSHEET_H__
#define __RESIZINGPROPSHEET_H__

#include "ResizingPropPage.h"

/////////////////////////////////////////////////////////////////////////////
// CResizingPropSheet

class COXLayoutManager;

class CResizingPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CResizingPropSheet)

// Construction
public:
	CResizingPropSheet(CWnd* pWndParent = NULL);

// Attributes
public:
	CResizingPropPage1 m_Page1;
	CResizingPropPage2 m_Page2;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResizingPropSheet)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResizingPropSheet();

protected:
	COXLayoutManager* m_pLayoutManager;
	CRect m_rectPage;

// Generated message map functions
protected:
	//{{AFX_MSG(CResizingPropSheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __RESIZINGPROPSHEET_H__
