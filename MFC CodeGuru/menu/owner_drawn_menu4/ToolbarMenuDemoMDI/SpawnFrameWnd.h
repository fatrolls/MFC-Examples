#if !defined(AFX_SPAWNFRAMEWND_H__13CAB7C3_D316_11D1_8693_000000000000__INCLUDED_)
#define AFX_SPAWNFRAMEWND_H__13CAB7C3_D316_11D1_8693_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SpawnFrameWnd.h : header file
//
#include "MenuSpawn.h"

/////////////////////////////////////////////////////////////////////////////
// CSpawnFrameWnd frame

class CSpawnFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CSpawnFrameWnd)
protected:
	CSpawnFrameWnd();           // protected constructor used by dynamic creation

// Attributes
public:
// COOLMENU SUPPORT
	CMenuSpawn	cSpawn;
	CRect oldMenuBarRc;
	bool bMenuLooping;
	UINT uiTimerId;
// END COOLMENU SUPPORT

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpawnFrameWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSpawnFrameWnd();

	// Generated message map functions
	//{{AFX_MSG(CSpawnFrameWnd)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnEnterMenuLoop(BOOL bIsTrackPopupMenu);
	afx_msg void OnExitMenuLoop(BOOL bIsTrackPopupMenu);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPAWNFRAMEWND_H__13CAB7C3_D316_11D1_8693_000000000000__INCLUDED_)
