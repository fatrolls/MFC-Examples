#if !defined(AFX_CUSFDLG_H__B9161301_0D88_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CUSFDLG_H__B9161301_0D88_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class MCCusFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(MCCusFileDialog)

public:
	MCCusFileDialog(BOOL bOpenFileDialog,
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(MCCusFileDialog)
	//}}AFX_MSG
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CUSFDLG_H__B9161301_0D88_11D1_9C9A_444553540000__INCLUDED_)
