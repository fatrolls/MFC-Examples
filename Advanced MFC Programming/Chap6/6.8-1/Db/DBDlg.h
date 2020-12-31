#if !defined(AFX_DBDLG_H__6F43A6C3_1487_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DBDLG_H__6F43A6C3_1487_11D1_9C9A_444553540000__INCLUDED_

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
	CStatusBar m_wndStatusBar;
	CToolBar m_wndToolBar;
	//{{AFX_MSG(CDBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	afx_msg BOOL OnToolTipText(UINT, NMHDR *, LRESULT *);
	afx_msg LRESULT OnSetMessageString(WPARAM, LPARAM=0L);
	afx_msg LRESULT OnPopMessageString(WPARAM wParam, LPARAM lParam);
	DECLARE_DYNAMIC(CDBDlg)
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DBDLG_H__6F43A6C3_1487_11D1_9C9A_444553540000__INCLUDED_)
