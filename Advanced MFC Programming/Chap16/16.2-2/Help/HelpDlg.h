#if !defined(AFX_HELPDLG_H__79855C4F_4C51_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_HELPDLG_H__79855C4F_4C51_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CHelpDlg : public CDialog
{
public:
	void SetContextHelpId();
	CHelpDlg(CWnd* pParent = NULL);
	//{{AFX_DATA(CHelpDlg)
	enum { IDD = IDD_DIALOG };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CHelpDlg)
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_HELPDLG_H__79855C4F_4C51_11D1_9C9A_444553540000__INCLUDED_)
