#if !defined(AFX_DLG_H__D649DA88_3EFC_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DLG_H__D649DA88_3EFC_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CZOrderDlg : public CDialog
{
public:
	CZOrderDlg(CWnd* pParent = NULL);
	//{{AFX_DATA(CZOrderDlg)
	enum { IDD = IDD_ZORDER_DIALOG };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CZOrderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;
	//{{AFX_MSG(CZOrderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRadioBottom();
	afx_msg void OnRadioNotopmost();
	afx_msg void OnRadioTop();
	afx_msg void OnRadioTopmost();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DLG_H__D649DA88_3EFC_11D1_9C9A_444553540000__INCLUDED_)
