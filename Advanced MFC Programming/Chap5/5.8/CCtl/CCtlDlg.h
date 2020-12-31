#if !defined(AFX_CCTLDLG_H__234A7886_0274_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CCTLDLG_H__234A7886_0274_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CCCtlDlg : public CDialog
{
public:
	CCCtlDlg(CWnd* pParent = NULL);
	//{{AFX_DATA(CCCtlDlg)
	enum { IDD = IDD_CCTL_DIALOG };
	CComboBox	m_cbSimple;
	CComboBox	m_cbDropList;
	CComboBox	m_cbDropDown;
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CCCtlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;
	//{{AFX_MSG(CCCtlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCloseupComboDropdown();
	afx_msg void OnCloseupComboDroplist();
	afx_msg void OnSelchangeComboSimple();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CCTLDLG_H__234A7886_0274_11D1_9C9A_444553540000__INCLUDED_)
