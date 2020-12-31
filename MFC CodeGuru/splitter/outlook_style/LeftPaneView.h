#if !defined(AFX_LEFTPANEVIEW_H__C50FD507_CEFA_11D1_9B01_0060970863EE__INCLUDED_)
#define AFX_LEFTPANEVIEW_H__C50FD507_CEFA_11D1_9B01_0060970863EE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LeftPaneView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLeftPaneView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CRightPaneFrame;

class CLeftPaneView : public CFormView
{
protected:
	CLeftPaneView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLeftPaneView)

// Form Data
public:
	//{{AFX_DATA(CLeftPaneView)
	enum { IDD = IDD_TREEVIEW };
	CTreeCtrl	m_treeCtrl;
	//}}AFX_DATA

// Attributes
public:
	CImageList m_ImageList;
	HTREEITEM  m_hSplitterView;
	HTREEITEM  m_hListCtrlView;
	HTREEITEM  m_hEditView;

	CRightPaneFrame* m_pRightPaneFrame;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftPaneView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLeftPaneView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CLeftPaneView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTPANEVIEW_H__C50FD507_CEFA_11D1_9B01_0060970863EE__INCLUDED_)
