//ReflectionWnd.h : Declaration of the CReflectionWnd

//***************************************************************************//
//                                                                           //
//  This file was created using the CWindowImpl ATL Object Wizard            //
//  By Erik Thompson © 2000                                                  //
//	Version 1.1                                                              //
//  Email questions and comments to ErikT@RadBytes.com                       //
//                                                                           //
//***************************************************************************//

#ifndef __REFLECTIONWND_H_
#define __REFLECTIONWND_H_

#include <commctrl.h>
#include "MFToolbar.h"


/////////////////////////////////////////////////////////////////////////////
// CReflectionWnd
class CReflectionWnd : public CWindowImpl<CReflectionWnd>
{
public:

	
	DECLARE_WND_CLASS(NULL)

	BEGIN_MSG_MAP(CReflectionWnd)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_MSG_MAP_MEMBER(m_ToolbarWnd)
	END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	CReflectionWnd();
	virtual ~CReflectionWnd();
	inline CMFToolbar& GetToolBar() { return m_ToolbarWnd;};

private:
	CMFToolbar m_ToolbarWnd;

};

#endif //__REFLECTIONWND_H_