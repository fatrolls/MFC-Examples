#include "stdafx.h"
#include "Bar.h"
#include "MDlgBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(MCDialogBar, CDialogBar)
BEGIN_MESSAGE_MAP(MCDialogBar, CDialogBar)
//	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
END_MESSAGE_MAP()

MCDialogBar::MCDialogBar()
{
}

MCDialogBar::~MCDialogBar()
{

}

/*BOOL MCDialogBar::OnToolTipNotify(UINT id, NMHDR* pNMHDR, LRESULT *pResult)
{
    TOOLTIPTEXT *pTTT=(TOOLTIPTEXT *)pNMHDR;
    UINT nID=pNMHDR->idFrom;
	TCHAR szFullText[256];
	CString strTipText;

    if(pTTT->uFlags & TTF_IDISHWND)
    {
        // idFrom is actually the HWND of the tool
        nID=::GetDlgCtrlID((HWND)nID);
        if(nID)
        {
            pTTT->lpszText=MAKEINTRESOURCE(nID);
            pTTT->hinst=AfxGetResourceHandle();
            return(TRUE);
        }
    }
    return FALSE;
}*/