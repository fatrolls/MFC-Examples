#include "stdafx.h"
#include "CDB.h"
#include "ColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(MCMLColorDlg, CColorDialog)

MCMLColorDlg::MCMLColorDlg(COLORREF clrInit, DWORD dwFlags, CWnd* pParentWnd) :
	CColorDialog(clrInit, dwFlags, pParentWnd)
{
}

BEGIN_MESSAGE_MAP(MCMLColorDlg, CColorDialog)
	//{{AFX_MSG_MAP(MCMLColorDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

