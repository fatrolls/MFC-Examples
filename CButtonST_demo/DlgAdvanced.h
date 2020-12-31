#ifndef _DLGADVANCED_H_
#define _DLGADVANCED_H_

#include "BtnST.h"
#include "WinXPButtonST.h"

#ifdef	BTNST_USE_BCMENU
#include "BCMenu.h"
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDlgAdvanced : public CDialog
{
public:
	CDlgAdvanced(CWnd* pParent = NULL);

	//{{AFX_DATA(CDlgAdvanced)
	enum { IDD = IDD_ADVANCED };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAdvanced)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAdvanced)
	virtual BOOL OnInitDialog();
	afx_msg void OnItem1();
	afx_msg void OnItem2();
	//}}AFX_MSG

private:
	LRESULT On_MenuCallback(WPARAM wParam, LPARAM lParam);

	void OnCancel();
	void OnOK();

	CWinXPButtonST	m_btnDerived;
	CButtonST		m_btnHyperLink;
	CButtonST		m_btnCursor;
	CButtonST		m_btnFocusRect;
	CButtonST		m_chkCheckbox;
	CButtonST		m_btnBitmap;

	BOOL			m_bTestCheck;	// A variable used to show DDX_Check feature

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
