#if !defined(AFX_PRNDLG_H__98B02821_30CF_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_PRNDLG_H__98B02821_30CF_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CPrnDlg : public CPrintDialog
{
public:
	CPrnDlg::CPrnDlg
	(
		BOOL bPrintSetupOnly,
		DWORD dwFlags=PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_HIDEPRINTTOFILE,
		CWnd *pParentWnd=NULL
	);

	//{{AFX_DATA(CPrnDlg)
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CPrnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPrnDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_PRNDLG_H__98B02821_30CF_11D1_9C9A_444553540000__INCLUDED_)
