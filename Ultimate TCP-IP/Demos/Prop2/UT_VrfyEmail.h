// UT_VrfyEmail.h: interface for the CUT_VrfyEmail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UT_VRFYEMAIL_H__3272A6FA_7140_11D3_8871_0080C86498A0__INCLUDED_)
#define AFX_UT_VRFYEMAIL_H__3272A6FA_7140_11D3_8871_0080C86498A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "uh_ctrl.h"
#include "ut_clnt.h"
#include "mxlookup.h"
#include "UCPage.h"

class CUT_VrfyEmail : public CUCPage  
{
public:
	CUT_VrfyEmail(LPTSTR);
	virtual ~CUT_VrfyEmail();
	HFONT m_hFont;
	BOOL m_bEnableLogChecked;
public:
	BOOL m_bAbort;
	virtual void OnClicked(int controlId);
	virtual void OnInitDialog(WPARAM wParam, LPARAM lParam);
	CUH_Control m_HistoryCtrl;
	HANDLE m_hThread;
	static unsigned __stdcall VerifyThread(void * pThis);
	static int __stdcall SendLikeMailToServer(LPCSTR Server, LPCSTR szEmail,LPCSTR from, CUT_VrfyEmail *page);

};

#endif // !defined(AFX_UT_VRFYEMAIL_H__3272A6FA_7140_11D3_8871_0080C86498A0__INCLUDED_)
