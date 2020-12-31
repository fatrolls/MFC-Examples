// UCPage.cpp: implementation of the CUCPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UCPage.h"
#include <stdio.h>

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996 )


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
WNDPROC CUCPage::PrevButtProc=NULL;



CUCPage::CUCPage(int Templ,TCHAR *temTitle)
{
	lstrcpy(Title,temTitle);
	psp.dwSize = sizeof(PROPSHEETPAGE);
    psp.dwFlags = PSP_USETITLE | PSP_USECALLBACK;
    psp.hInstance = GetInstan();
    psp.pszTemplate = MAKEINTRESOURCE(Templ);
    psp.pszIcon = MAKEINTRESOURCE(IDI_ICON1);
    psp.pfnDlgProc = (DLGPROC)DialogProc;
    psp.pszTitle = Title; 
	psp.lParam = (long)(ULONG_PTR)this;
    psp.pfnCallback =NULL;//PagePatternProc;


}

CUCPage::~CUCPage()
{

}


void CUCPage::OnDrawItem(LPDRAWITEMSTRUCT)
{


}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : HandleSelectionState(LPDRAWITEMSTRUCT, int)                *
 *                                                                          *
 *  PURPOSE    : Handles a change in an item selection state. If an item is *
 *               selected, a black rectangular frame is drawn around that   *
 *               item; if an item is de-selected, the frame is removed.     *
 *                                                                          *
 *  COMMENT    : The black selection frame is slightly larger than the gray *
 *               focus frame so they won't paint over each other.           *
 *                                                                          *
 ****************************************************************************/
void CUCPage::HandleSelectionState(
        LPDRAWITEMSTRUCT        lpdis,
        INT                     inflate)
{
        RECT    rc;
        HBRUSH  hbr;

        /* Resize rectangle to place selection frame outside of the focus
         * frame and the item.
         */
        CopyRect ((LPRECT)&rc, (LPRECT)&lpdis->rcItem);
        InflateRect ((LPRECT)&rc, inflate, inflate);

        if (lpdis->itemState & ODS_SELECTED)
        {
                /* selecting item -- paint a black frame */
                hbr = (HBRUSH)GetStockObject(BLACK_BRUSH);
        }
        else
        {
                /* de-selecting item -- remove frame */
                hbr = (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_WINDOW));
        }
        FrameRect(lpdis->hDC, (LPRECT)&rc, hbr);
        DeleteObject (hbr);
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : HandleFocusState(LPDRAWITEMSTRUCT, int)                    *
 *                                                                          *
 *  PURPOSE    : Handle a change in item focus state. If an item gains the  *
 *               input focus, a gray rectangular frame is drawn around that *
 *               item; if an item loses the input focus, the gray frame is  *
 *               removed.                                                   *
 *                                                                          *
 *  COMMENT    : The gray focus frame is slightly smaller than the black    *
 *               selection frame so they won't paint over each other.       *
 *                                                                          *
 ****************************************************************************/
void CUCPage::HandleFocusState(
        LPDRAWITEMSTRUCT        lpdis,
        INT                     inflate)
{
        RECT    rc;
        HBRUSH  hbr;

        /* Resize rectangle to place focus frame between the selection
         * frame and the item.
         */
        CopyRect ((LPRECT)&rc, (LPRECT)&lpdis->rcItem);
        InflateRect ((LPRECT)&rc, inflate, inflate);

        if (lpdis->itemState & ODS_FOCUS)
        {
                /* gaining input focus -- paint a gray frame */
                hbr = (HBRUSH)GetStockObject(GRAY_BRUSH);
        }
        else
        {
                /* losing input focus -- remove (paint over) frame */
                hbr = (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_WINDOW));
        }
        FrameRect(lpdis->hDC, (LPRECT)&rc, hbr);
        DeleteObject (hbr);
}

void CUCPage::OnInitDialog(WPARAM /* wParam */, LPARAM /* lParam */)
{
}


void CUCPage::OnPaint(HDC /* dc */)
{
	PAINTSTRUCT lpPaint;
	BeginPaint(m_hWnd,&lpPaint);
	EndPaint(m_hWnd,&lpPaint);
}


BOOL CUCPage::SetItemInt(int nID, int nValue)
{
	return SetDlgItemInt(m_hWnd, nID, (UINT) nValue, nValue < 0);
}

BOOL CUCPage::GetItemInt(int nID, int &nValue)
{
	BOOL bResult;
	nValue=GetDlgItemInt(m_hWnd, nID, &bResult, nValue < 0);
	return bResult;
}

BOOL CUCPage::SetItemFloat(int nID, float fValue)
{
	TCHAR strInitValue[50];

	_stprintf(strInitValue,_T("%.4f"),fValue);
	return SetWindowText(GetItemHWND(nID),strInitValue);
}

BOOL CUCPage::GetItemFloat(int nID, float &fValue)
{
	TCHAR strValue[50];
	BOOL bResult;
	bResult=GetWindowText(GetItemHWND(nID),strValue,49);
	fValue=(float)_tcstod(strValue,NULL);

	return bResult;
}

HWND CUCPage::GetItemHWND(int item)
{
	return GetDlgItem(m_hWnd,item);
}

BOOL CUCPage::IsButtonChecked(int nID)
{
	return (::IsDlgButtonChecked(m_hWnd, nID) == BST_CHECKED);
}

void CUCPage::Apply()
{
	HWND wnd;
	wnd=GetParent(m_hWnd);
	PropSheet_Changed(wnd,m_hWnd);
	m_bChanged=TRUE;

}

int CUCPage::GetItemInt(int nID)
{
	return GetDlgItemInt(m_hWnd,nID,NULL,TRUE);
}

LRESULT CALLBACK CUCPage::ButtonProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CUCPage *WndC;
	LPMSG lMsg;
	lMsg=(LPMSG)lParam;
	//int i;
	switch (message) 
	{
	case WM_GETDLGCODE:
		if(lParam==0) return PrevButtProc(hWnd, message, wParam, lParam);
		WndC=(CUCPage *)Vtable.FindClass(GetParent(hWnd));		// Find the CUCWnd class by HWND handle.
			if(WndC!=NULL && lMsg->message==WM_KEYDOWN)
				WndC->OnKeyDown(lMsg->hwnd,(int)lMsg->wParam);
			else return PrevButtProc(hWnd, message, wParam, lParam);
		break;
	default:
		return PrevButtProc(hWnd, message, wParam, lParam);
   }
   return 1;
}

void CUCPage::OnKeyDown(HWND /* hWnd */,int /* nVirtKey */)
{

}

#pragma warning ( pop )