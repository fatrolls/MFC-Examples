#if !defined(AFX_LISTCTRLVIEW_H__C50FD509_CEFA_11D1_9B01_0060970863EE__INCLUDED_)
#define AFX_LISTCTRLVIEW_H__C50FD509_CEFA_11D1_9B01_0060970863EE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ListCtrlView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListCtrlView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CListCtrlView : public CFormView
{
public:	// changed from protected
	CListCtrlView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CListCtrlView)

// Form Data
public:
	//{{AFX_DATA(CListCtrlView)
	enum { IDD = IDD_LISTCTRLVIEW };
	CListCtrl	m_listCtrl;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CListCtrlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CListCtrlView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLVIEW_H__C50FD509_CEFA_11D1_9B01_0060970863EE__INCLUDED_)
