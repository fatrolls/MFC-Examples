// COptionsSheet.h : header file
//
// This class defines custom modal property sheet 
// COptionsSheet.
 
#ifndef __COPTIONSSHEET_H__
#define __COPTIONSSHEET_H__

#include "CDisplayOptionsPage.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsSheet

class COptionsSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(COptionsSheet)

// Construction
public:
	COptionsSheet(CWnd* pWndParent = NULL);

// Attributes
public:
	CDisplayOptionsPage m_displayOptionsPage;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COptionsSheet();

// Generated message map functions
protected:
	//{{AFX_MSG(COptionsSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __COPTIONSSHEET_H__
