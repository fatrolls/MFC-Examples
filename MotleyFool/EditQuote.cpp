//EditQuote.cpp : Implementation of CEditQuote

//***************************************************************************//
//                                                                           //
//  This file was created using the CWindowImpl ATL Object Wizard            //
//  By Erik Thompson © 2000                                                  //
//	Version 1.1                                                              //
//  Email questions and comments to ErikT@RadBytes.com                       //
//                                                                           //
//***************************************************************************//

#include "stdafx.h"
#include "EditQuote.h"
#include "MotleyFool.h"
#include "StockBar.h"

/////////////////////////////////////////////////////////////////////////////
// CEditQuote

CEditQuote::CEditQuote()
: m_pBand(NULL)
{
}

CEditQuote::~CEditQuote()
{
}

STDMETHODIMP CEditQuote::TranslateAcceleratorIO(LPMSG lpMsg)
{
	int nVirtKey = (int)(lpMsg->wParam);
	if (VK_RETURN == nVirtKey)
	{
		// remove system beep on enter key by setting key code to 0
		lpMsg->wParam = 0;
		::PostMessage(GetParent(), WM_GETQUOTE, 0, 0);
		return S_OK;
	}
	else if (WM_KEYDOWN == lpMsg->message && nVirtKey == VK_TAB)
	{
		if (m_pBand) m_pBand->FocusChange(FALSE);
		return S_FALSE;
	}

	TranslateMessage(lpMsg);
	DispatchMessage(lpMsg);
	return S_OK;
}

void CEditQuote::SetBand(CStockBar* pBand)
{
	m_pBand = pBand;
}

LRESULT CEditQuote::OnSetFocus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	//Notify host that our band has the focus so TranslateAcceleratorIO 
	//messages are directed towards our band.
	if (m_pBand) m_pBand->FocusChange(TRUE);
	return 0;
}
