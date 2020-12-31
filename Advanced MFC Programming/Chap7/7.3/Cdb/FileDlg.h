#if !defined(AFX_FILEDLG_H__C117EF81_0CAA_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_FILEDLG_H__C117EF81_0CAA_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class MCFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(MCFileDialog)

public:
	MCFileDialog
	(
		BOOL bOpenFileDialog=FALSE,
		LPCTSTR lpszDefExt=NULL,
		LPCTSTR lpszFileName=NULL,
		DWORD dwFlags=OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter=NULL,
		CWnd* pParentWnd=NULL
	);

protected:
	//{{AFX_MSG(MCFileDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_FILEDLG_H__C117EF81_0CAA_11D1_9C9A_444553540000__INCLUDED_)
