#if !defined(AFX_BUDDIEDSLIDERCTRL_H__9937B237_C5AB_417C_B568_D04C313BFE0B__INCLUDED_)
#define AFX_BUDDIEDSLIDERCTRL_H__9937B237_C5AB_417C_B568_D04C313BFE0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CustomDrawSliderCtrl.h"

// BuddiedSliderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuddiedSliderCtrl window

class CBuddiedSliderCtrl : public CCustomDrawSliderCtrl
{
// Construction
public:
	CBuddiedSliderCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuddiedSliderCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	CBrush m_brWhiteBrush;
	void SetPos( int nPos );
	CWnd* m_pBuddyWnd;
	void ReflectedScrollMessage();
	HWND SetBuddy( CWnd* pBuddyWnd );
	virtual ~CBuddiedSliderCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBuddiedSliderCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUDDIEDSLIDERCTRL_H__9937B237_C5AB_417C_B568_D04C313BFE0B__INCLUDED_)
