#if !defined(_STANDARDTOOLBAR_H__)
#define _STANDARDTOOLBAR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StandardToolBar.h : header file
//

#include "OXCoolToolBar.h"
#include "OXCoolComboBox.h"
/////////////////////////////////////////////////////////////////////////////
// CStandardToolBar window

class CStandardToolBar : public COXCoolToolBar
{
// Construction
public:
	CStandardToolBar();

// Attributes
public:

protected:
	COXCoolComboBox m_combo;
	int m_nSavedCurSel;
	int m_nComboItemIndex;
	UINT m_nID;
	UINT m_nStyle;
	int m_nImage;

// Operations
public:
	BOOL CreateCombo(int nItemIndex);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStandardToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStandardToolBar();

protected:
	// function called everytime when toolbar changes its docking side
	virtual void OnChangeDockSide(DWORD dwDockSide);
	// function called everytime when toolbar changes its state from
	// docking to floating and vise versa
	virtual void OnFloatingDocking(BOOL bFloating);


	// Generated message map functions
protected:
	//{{AFX_MSG(CStandardToolBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_STANDARDTOOLBAR_H__)
