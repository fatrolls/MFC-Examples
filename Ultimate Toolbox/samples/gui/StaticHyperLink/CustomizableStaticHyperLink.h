#if !defined(AFX_CUSTOMIZABLESTATICHYPERLINK_H__0F70C422_AD5C_11D1_B475_444553540000__INCLUDED_)
#define AFX_CUSTOMIZABLESTATICHYPERLINK_H__0F70C422_AD5C_11D1_B475_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CustomizableStaticHyperLink.h : header file
//

#include "OXStaticHyperLink.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomizableStaticHyperLink window

class CCustomizableStaticHyperLink : public COXStaticHyperLink
{
// Construction
public:
	CCustomizableStaticHyperLink();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizableStaticHyperLink)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomizableStaticHyperLink();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomizableStaticHyperLink)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZABLESTATICHYPERLINK_H__0F70C422_AD5C_11D1_B475_444553540000__INCLUDED_)
