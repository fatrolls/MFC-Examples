#ifndef __AFX_APBARDLG_H__
#define __AFX_APBARDLG_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ApBarDlg.h : header file
//

#include "AppBar.h"

/////////////////////////////////////////////////////////////////////////////
// CAppBarDlg dialog

class CAppBarDlg : public CDialog
{
public:
	CAppBarDlg(int, CWnd* pParent = NULL);   // standard constructor

protected:
	BOOL ShowMenu (const CRect& rect, int iResourceID, int iBoldID = -1);
    CAppBar* m_pAppBar;
	BOOL m_bHidden;
	BOOL m_bOnTop;
	// Generated message map functions
	//{{AFX_MSG(CAppBarDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    BOOL m_bMoving;
    RECT m_rcDrag;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APBARDLG_H__AB5CEE06_A955_11D1_B258_006097960BB7__INCLUDED_)
