#if !defined(AFX_CMFORMVIEW_H__D5D5E428_F1FA_11D1_9447_BC2A94000000__INCLUDED_)
#define AFX_CMFORMVIEW_H__D5D5E428_F1FA_11D1_9447_BC2A94000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CMFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMFormView : public CFormView
{
protected:
	CMFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMFormView)

// Form Data
public:
	//{{AFX_DATA(CMFormView)
	enum { IDD = IDD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFormView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMFormView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMFORMVIEW_H__D5D5E428_F1FA_11D1_9447_BC2A94000000__INCLUDED_)
