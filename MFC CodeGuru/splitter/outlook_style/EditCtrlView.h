#if !defined(AFX_EDITCTRLVIEW_H__C50FD50A_CEFA_11D1_9B01_0060970863EE__INCLUDED_)
#define AFX_EDITCTRLVIEW_H__C50FD50A_CEFA_11D1_9B01_0060970863EE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EditCtrlView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditCtrlView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CEditCtrlView : public CFormView
{
public:	// changed from protected
	CEditCtrlView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEditCtrlView)

// Form Data
public:
	//{{AFX_DATA(CEditCtrlView)
	enum { IDD = IDD_EDITVIEW };
	CEdit	m_editCtrl;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditCtrlView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEditCtrlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CEditCtrlView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCTRLVIEW_H__C50FD50A_CEFA_11D1_9B01_0060970863EE__INCLUDED_)
