#if !defined(AFX_CCTLDLG_H__FF97C4A6_0431_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CCTLDLG_H__FF97C4A6_0431_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#define COMBO_BUTTON	0
#define COMBO_BIGSMILE	1

#define LIST_SMILE_1	0
#define LIST_SMILE_2	1
#define LIST_SMILE_3	2
#define LIST_SMILE_4	3

class CCCtlDlg : public CDialog
{
public:
	CCCtlDlg(CWnd* pParent = NULL);
	//{{AFX_DATA(CCCtlDlg)
	enum { IDD = IDD_CCTL_DIALOG };
	CListBox	m_lbBmp;
	CComboBox	m_cbBmp;
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
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CCTLDLG_H__FF97C4A6_0431_11D1_9C9A_444553540000__INCLUDED_)
