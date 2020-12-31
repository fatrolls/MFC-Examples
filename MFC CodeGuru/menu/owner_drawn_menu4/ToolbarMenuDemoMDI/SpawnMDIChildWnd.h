#if !defined(AFX_SPAWNMDICHILDWND_H__13CAB7C4_D316_11D1_8693_000000000000__INCLUDED_)
#define AFX_SPAWNMDICHILDWND_H__13CAB7C4_D316_11D1_8693_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SpawnMDIChildWnd.h : header file
//
#include "MenuSpawn.h"

/////////////////////////////////////////////////////////////////////////////
// CSpawnMDIChildWnd frame

class CSpawnMDIChildWnd : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CSpawnMDIChildWnd)
protected:
	CSpawnMDIChildWnd();           // protected constructor used by dynamic creation

// Attributes
public:
// COOLMENU SUPPORT
	CMenuSpawn	cSpawn;
// END COOLMENU SUPPORT

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpawnMDIChildWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSpawnMDIChildWnd();

	// Generated message map functions
	//{{AFX_MSG(CSpawnMDIChildWnd)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPAWNMDICHILDWND_H__13CAB7C4_D316_11D1_8693_000000000000__INCLUDED_)
