#if !defined(AFX_DBDLG_H__6F1FA2CC_130A_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DBDLG_H__6F1FA2CC_130A_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include "Page.h"

class CDBDlg : public CPropertySheet
{
public:
	CDBDlg(CWnd* pParent = NULL);

	//{{AFX_DATA(CDBDlg)
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CDBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;

	CPage1 m_page1;
	CPage2 m_page2;
	CPage3 m_page3;
	//{{AFX_MSG(CDBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DBDLG_H__6F1FA2CC_130A_11D1_9C9A_444553540000__INCLUDED_)
