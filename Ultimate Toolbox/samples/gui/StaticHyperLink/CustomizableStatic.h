#if !defined(AFX_CUSTOMIZABLESTATIC_H__0F70C422_AD5C_11D1_B475_444553540000__INCLUDED_)
#define AFX_CUSTOMIZABLESTATIC_H__0F70C422_AD5C_11D1_B475_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CustomizableStatic.h : header file
//

#include "OXStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomizableStatic window

class CCustomizableStatic : public COXStatic
{
// Construction
public:
	CCustomizableStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizableStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomizableStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomizableStatic)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZABLESTATIC_H__0F70C422_AD5C_11D1_B475_444553540000__INCLUDED_)
