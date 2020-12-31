#if !defined(AFX_MYFORMVIEW_H__82E1866F_87F1_4DE5_8D4A_81246B2F90B9__INCLUDED_)
#define AFX_MYFORMVIEW_H__82E1866F_87F1_4DE5_8D4A_81246B2F90B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "OXTabView.h"

class CMyFormView : public COXTabViewPage<CFormView>
{
protected:
	CMyFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyFormView)

// Form Data
public:
	//{{AFX_DATA(CMyFormView)
	enum { IDD = IDD_FORMVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFormView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMyFormView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYFORMVIEW_H__82E1866F_87F1_4DE5_8D4A_81246B2F90B9__INCLUDED_)
