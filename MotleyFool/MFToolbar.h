//MFToolbar.h : Declaration of the CMFToolbar

//***************************************************************************//
//                                                                           //
//  This file was created using the CWindowImpl ATL Object Wizard            //
//  By Erik Thompson © 2000                                                  //
//	Version 1.1                                                              //
//  Email questions and comments to ErikT@RadBytes.com                       //
//                                                                           //
//***************************************************************************//

#ifndef __MFTOOLBAR_H_
#define __MFTOOLBAR_H_

#include <commctrl.h>
#include "EditQuote.h"

/////////////////////////////////////////////////////////////////////////////
// CMFToolbar
class CMFToolbar : public CWindowImpl<CMFToolbar>
{
public:

	
	DECLARE_WND_SUPERCLASS(TEXT("MOTLEYFOOLTOOLBAR"), TOOLBARCLASSNAME)

	BEGIN_MSG_MAP(CMFToolbar)
		CHAIN_MSG_MAP_MEMBER(m_EditWnd)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		MESSAGE_HANDLER(WM_GETQUOTE, OnGetQuote)
	END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetQuote(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	CMFToolbar();
	virtual ~CMFToolbar();
	inline CEditQuote& GetEditBox() {return m_EditWnd;};
	void SetBrowser(IWebBrowser2* pBrowser);
	
private:
	CEditQuote m_EditWnd;
	HIMAGELIST m_hImageList;
	IWebBrowser2* m_pBrowser;
	void GetQuote();
};

#endif //__MFTOOLBAR_H_