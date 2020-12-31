#ifndef EXMENU_H
#define EXMENU_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EXMenu.h : header file
//
#include <vector>


/////////////////////////////////////////////////////////////////////////////
// EXMenu command target

class EXMenu : public CMenu
{
	DECLARE_DYNCREATE(EXMenu)

	EXMenu();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	virtual ~EXMenu();
//	void AddMenuItem(int nStringId, int nMenuId);
//	void AddPopupMenuItem(UINT nID);
	void AddCommand( int nStringId , int nID , bool bChecked );
	void AddCommand( const char* pText , int nID , bool bChecked );

	void AddSeparator();
	EXMenu* AddMenu( UINT nStringID );

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EXMenu)
	//}}AFX_VIRTUAL

public:
	void AttachPopupMenu(UINT nStringID, EXMenu *pMenu);
	std::vector<EXMenu *> m_vMenues;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMENU_H__E74F2468_7123_4052_9AFB_D5E2BDAFF2CA__INCLUDED_)
