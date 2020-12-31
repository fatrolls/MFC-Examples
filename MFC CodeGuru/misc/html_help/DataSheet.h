/////////////////////////////////////////////////////////////////////////////
// DataSheet.h : header file
//
#ifndef __DATASHEET_H__
#define __DATASHEET_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
//
// #includes
//
#include "DataPage.h"
/////////////////////////////////////////////////////////////////////////////
// CDataSheet

class CDataSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CDataSheet)

// Construction
public:
	CDataSheet(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CDataPage	m_Page1;
	CPageHelp	m_Page2;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDataSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDataSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(__DATASHEET_H__)
