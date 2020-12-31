#if !defined(AFX_PROGDLG_H__F2930DE1_1E22_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_PROGDLG_H__F2930DE1_1E22_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include "Percent.h"

class CProgDlg : public CDialog
{
public:
	CProgDlg(CWnd* pParent = NULL);

	//{{AFX_DATA(CProgDlg)
	enum { IDD = IDD_DIALOG };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CProgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	CPercent m_perBar;
	int m_nPercent;

	//{{AFX_MSG(CProgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_PROGDLG_H__F2930DE1_1E22_11D1_9C9A_444553540000__INCLUDED_)
