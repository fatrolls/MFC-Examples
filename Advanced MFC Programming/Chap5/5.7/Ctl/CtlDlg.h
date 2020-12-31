#if !defined(AFX_CTLDLG_H__F2267948_01AE_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CTLDLG_H__F2267948_01AE_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CCtlDlg : public CDialog
{
public:
	CCtlDlg(CWnd* pParent = NULL);
	//{{AFX_DATA(CCtlDlg)
	enum { IDD = IDD_CTL_DIALOG };
	CListBox	m_listDir;
	CListBox	m_listMCBox;
	CListBox	m_listBox;
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CCtlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;
	//{{AFX_MSG(CCtlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDblclkListDir();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CTLDLG_H__F2267948_01AE_11D1_9C9A_444553540000__INCLUDED_)
