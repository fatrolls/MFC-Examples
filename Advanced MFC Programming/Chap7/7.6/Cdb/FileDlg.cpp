#include "stdafx.h"
#include "CDB.h"
#include "FileDlg.h"
#include "Dlgs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(MCFileDialog, CFileDialog)

MCFileDialog::MCFileDialog
(
	BOOL bOpenFileDialog, 
	LPCTSTR lpszDefExt, 
	LPCTSTR lpszFileName,
	DWORD dwFlags, 
	LPCTSTR lpszFilter, 
	CWnd* pParentWnd
) :	CFileDialog
(
	bOpenFileDialog, 
	lpszDefExt, 
	lpszFileName, 
	dwFlags, 
	lpszFilter, 
	pParentWnd
)
{
}

BEGIN_MESSAGE_MAP(MCFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(MCFileDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL MCFileDialog::OnInitDialog() 
{
	CListBox *ptrListBox;	

	GetDlgItem(stc1)->ShowWindow(SW_HIDE);
	GetDlgItem(stc2)->ShowWindow(SW_HIDE);
	GetDlgItem(stc3)->ShowWindow(SW_HIDE);
	GetDlgItem(edt1)->ShowWindow(SW_HIDE);
	GetDlgItem(lst1)->ShowWindow(SW_HIDE);
	GetDlgItem(cmb1)->ShowWindow(SW_HIDE);
	GetDlgItem(65535)->ShowWindow(SW_HIDE);
	SetDlgItemText(edt1, "DummyString");

	ptrListBox=(CListBox *)GetDlgItem(lst2);
	ptrListBox->SetFocus();
	CFileDialog::OnInitDialog();

	ptrListBox->SetCurSel(0);

	return FALSE;
}

void MCFileDialog::OnOK()
{
	CFileDialog::OnOK();
	CFileDialog::OnOK();
}
