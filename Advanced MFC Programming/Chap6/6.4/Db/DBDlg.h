#if !defined(AFX_DBDLG_H__6F1FA2F3_130A_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DBDLG_H__6F1FA2F3_130A_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CDBDlg : public CDialog
{
public:
	CDBDlg(CWnd* pParent = NULL);
	//{{AFX_DATA(CDBDlg)
	enum { IDD = IDD_DB_DIALOG };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CDBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;
	//{{AFX_MSG(CDBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DBDLG_H__6F1FA2F3_130A_11D1_9C9A_444553540000__INCLUDED_)
