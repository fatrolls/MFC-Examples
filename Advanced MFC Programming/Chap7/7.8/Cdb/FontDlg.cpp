#include "stdafx.h"
#include "CDB.h"
#include "FontDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(MCFontDialog, CFontDialog)

MCFontDialog::MCFontDialog(LPLOGFONT lplfInitial, DWORD dwFlags, CDC* pdcPrinter, CWnd* pParentWnd) : 
	CFontDialog(lplfInitial, dwFlags, pdcPrinter, pParentWnd)
{
}


BEGIN_MESSAGE_MAP(MCFontDialog, CFontDialog)
	//{{AFX_MSG_MAP(MCFontDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL MCFontDialog::OnInitDialog() 
{
	CFontDialog::OnInitDialog();
	GetDlgItem(stc4)->ShowWindow(SW_HIDE);
	GetDlgItem(cmb4)->ShowWindow(SW_HIDE);
	return TRUE;
}
