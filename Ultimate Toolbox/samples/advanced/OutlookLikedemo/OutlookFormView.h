#if !defined(AFX_OUTLOOKFORMVIEW_H__D6095444_2C7B_11D2_88E3_0080C859A484__INCLUDED_)
#define AFX_OUTLOOKFORMVIEW_H__D6095444_2C7B_11D2_88E3_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OutlookFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutlookFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class COutlookFormView : public CFormView
{
protected:
	COutlookFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COutlookFormView)

// Form Data
public:
	//{{AFX_DATA(COutlookFormView)
	enum { IDD = IDD_FORMVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookFormView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COutlookFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(COutlookFormView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLOOKFORMVIEW_H__D6095444_2C7B_11D2_88E3_0080C859A484__INCLUDED_)
