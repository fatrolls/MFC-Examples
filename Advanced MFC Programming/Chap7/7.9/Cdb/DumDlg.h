#if !defined(AFX_DUMDLG_H__0F915D42_0FE4_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DUMDLG_H__0F915D42_0FE4_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class MCDummyDlg : public CDialog
{
public:
	MCDummyDlg(CWnd* pParent = NULL);
	//{{AFX_DATA(MCDummyDlg)
	enum { IDD = IDD_DIALOG_DUMMY };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(MCDummyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(MCDummyDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DUMDLG_H__0F915D42_0FE4_11D1_9C9A_444553540000__INCLUDED_)
