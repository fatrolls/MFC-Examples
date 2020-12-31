#if !defined(AFX_BARDLG_H__D9E740F4_1585_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_BARDLG_H__D9E740F4_1585_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include "ToolBar.h"

class CBarDialog : public CDialog
{
public:
	CBarDialog(CWnd* pParent = NULL);
	//{{AFX_DATA(CBarDialog)
	enum { IDD = IDD_DIALOG };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CBarDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	CStatusBar m_wndStatusBar;
	CDlgToolBar m_wndToolBar;
	//{{AFX_MSG(CBarDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg BOOL OnToolTipText(UINT, NMHDR *, LRESULT *);
	afx_msg LRESULT OnSetMessageString(WPARAM, LPARAM=0L);
	afx_msg LRESULT OnPopMessageString(WPARAM wParam, LPARAM lParam);
	DECLARE_DYNAMIC(CBarDialog)
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_BARDLG_H__D9E740F4_1585_11D1_9C9A_444553540000__INCLUDED_)
