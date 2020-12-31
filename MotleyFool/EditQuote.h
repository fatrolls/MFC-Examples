//EditQuote.h : Declaration of the CEditQuote

//***************************************************************************//
//                                                                           //
//  This file was created using the CWindowImpl ATL Object Wizard            //
//  By Erik Thompson © 2000                                                  //
//	Version 1.1                                                              //
//  Email questions and comments to ErikT@RadBytes.com                       //
//                                                                           //
//***************************************************************************//

#ifndef __EDITQUOTE_H_
#define __EDITQUOTE_H_

#include <commctrl.h>

const int WM_GETQUOTE = WM_USER + 1024;

class CStockBar;

/////////////////////////////////////////////////////////////////////////////
// CEditQuote
class CEditQuote : public CWindowImpl<CEditQuote>
{
public:

	
	DECLARE_WND_SUPERCLASS(TEXT("EDITQUOTE"), TEXT("EDIT"))

	BEGIN_MSG_MAP(CEditQuote)
		COMMAND_CODE_HANDLER(EN_SETFOCUS, OnSetFocus)
	END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnSetFocus(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	CEditQuote();
	virtual ~CEditQuote();
	STDMETHOD(TranslateAcceleratorIO)(LPMSG lpMsg);
	void SetBand(CStockBar* pBand);
private:
	CStockBar* m_pBand;

};

#endif //__EDITQUOTE_H_