// UT_WhoIsPage.h: interface for the CUT_WhoIsPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UT_WhoIsPage_H__4ADA63E3_716F_11D3_8872_0080C86498A0__INCLUDED_)
#define AFX_UT_WhoIsPage_H__4ADA63E3_716F_11D3_8872_0080C86498A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UCPage.h"
#include "uh_ctrl.h"
#include "ut_clnt.h"
#include "help\context.hh"

const	DWORD dwWhoIsHelpMap[] = {
			IDC_WHO_IS_BTN ,     IDH_10049,
			IDC_WHO_IS_HISTORY,	IDH_10053,		
            IDC_WHOIS_LOG_FILE,IDH_10050,
			IDC_WHOIS_ENABLE_LOOG,	IDH_10051,		
			IDC_WHOISSERVER,	IDH_10052,		
            IDC_WHOIS_QUERY, IDH_10048,
			0,0
	};



class CUT_WhoIsPage;
class myClient : public CUT_WSClient
{

	BOOL IsAborted();
public :
	myClient();
	~myClient();
	CUT_WhoIsPage *m_parent;

};

class CUT_WhoIsPage : public CUCPage  
{
	HFONT m_hFont;
public:
	BOOLEAN m_bEnableLogChecked;
	BOOL m_bAbort;
	HANDLE m_hThread;

	CUT_WhoIsPage(LPTSTR title);
	virtual ~CUT_WhoIsPage();
    virtual void OnHelp(LPARAM lParam);
	virtual void OnClicked(int controlId);
	virtual void OnInitDialog(WPARAM wParam, LPARAM lParam);
	CUH_Control m_HistoryCtrl;
	static unsigned __stdcall WhoIsThread(void * pThis);
};

#endif // !defined(AFX_UT_WhoIsPage_H__4ADA63E3_716F_11D3_8872_0080C86498A0__INCLUDED_)
