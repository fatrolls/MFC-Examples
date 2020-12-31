#if !defined(AFX_GFXPROPERTY_H__10E221D2_0F42_11D2_842B_0000B43382FE__INCLUDED_)
#define AFX_GFXPROPERTY_H__10E221D2_0F42_11D2_842B_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GfxProperty.h : header file
//
#include "PinButton.h"

/////////////////////////////////////////////////////////////////////////////
// CGfxProperty dialog

class CGfxProperty : public CDialog
{
// Construction
public:
	void DoIt();
	void InvalidateTab(const int idx);
	void HideAllPages();
	void AddPage(CDialog * pPage, const char * pText);
	CGfxProperty(CWnd* pParent = NULL);   // standard constructor

	virtual ~CGfxProperty();

	void DrawTabRect(CDC * pdc, CRect rc, bool bSel);
	void SetCurSel(int iSel);
	void MaximizeDlgRect(CDialog * pDlg, int & cx, int & cy);
	void ClearTabArray();
	void SetDialogSize();

	CStringArray csTabArray;
	CPtrArray pPages;

	CRect * pTabRect;
	enum { CG_TAB_HEIGHT = 20 };

	int iActSel;
	void InstallHook(BOOL bInstall);

	CDocument * pDocument;
	CWnd * pWnd;

// Dialog Data
	//{{AFX_DATA(CGfxProperty)
	enum { IDD = IDD_GFX_PROPERTY };
	CPinButton	wndOk;
	CPinButton	wndPin;
	CPinButton	wndHelp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGfxProperty)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGfxProperty)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnBtHelp();
	afx_msg void OnBtPin();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GFXPROPERTY_H__10E221D2_0F42_11D2_842B_0000B43382FE__INCLUDED_)
