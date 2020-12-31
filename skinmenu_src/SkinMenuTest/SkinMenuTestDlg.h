// SkinMenuTestDlg.h : header file
//
//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(AFX_SKINMENUTESTDLG_H__4555C167_5806_46CE_AC5F_5BF9ACBDD4A9__INCLUDED_)
#define AFX_SKINMENUTESTDLG_H__4555C167_5806_46CE_AC5F_5BF9ACBDD4A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\skinwindows\skinmenu.h"

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuTestDlg dialog

class CSkinMenuTestDlg : public CDialog, protected ISkinMenuRender
{
// Construction
public:
	CSkinMenuTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSkinMenuTestDlg)
	enum { IDD = IDD_SKINMENUTEST_DIALOG };
	CWebBrowser2	m_browser;
	CString	m_sSkinPath;
	int		m_nColorScheme;
	BOOL	m_bGradient;
	BOOL	m_bSidebar;
	CString	m_sEdit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinMenuTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSkinMenuTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnSelchangeColorscheme();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGradientChange();
	afx_msg void OnSidebarChange();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void ResetMenuMgr();

	// ISkinMenuRender overrides
	BOOL DrawMenuNonClientBkgnd(CDC* pDC, LPRECT pRect);
	BOOL DrawMenuClientBkgnd(CDC* pDC, LPRECT pRect, LPRECT pClip);
	BOOL DrawMenuSidebar(CDC* pDC, LPRECT pRect, LPCTSTR szTitle);
	BOOL DrawMenuBorder(CDC* pDC, LPRECT pRect);

	void DrawGradientBkgnd(CDC* pDC, LPRECT pRect, LPRECT pClip);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINMENUTESTDLG_H__4555C167_5806_46CE_AC5F_5BF9ACBDD4A9__INCLUDED_)
