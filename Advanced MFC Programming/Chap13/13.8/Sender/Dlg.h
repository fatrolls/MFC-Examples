#if !defined(AFX_DLG_H__D649DA66_3EFC_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DLG_H__D649DA66_3EFC_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CSenderDlg : public CDialog
{
public:
	CSenderDlg(CWnd* pParent = NULL);
	//{{AFX_DATA(CSenderDlg)
	enum { IDD = IDD_SENDER_DIALOG };
	int		m_nSent;
	int		m_nCount;
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CSenderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;

	//{{AFX_MSG(CSenderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSend();
	//}}AFX_MSG
	afx_msg LONG OnReceive(UINT, LONG);
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DLG_H__D649DA66_3EFC_11D1_9C9A_444553540000__INCLUDED_)
