// UT_PingPage.h: interface for the CUT_PingPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UT_PINGPAGE_H__3272A6F9_7140_11D3_8871_0080C86498A0__INCLUDED_)
#define AFX_UT_PINGPAGE_H__3272A6F9_7140_11D3_8871_0080C86498A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UCPage.h"
#include "uh_ctrl.h"
#include "ut_clnt.h"
#include "ut_icmp.h"
#include "help\context.hh"

const	DWORD dwPingHelpMap[] = {
			IDC_PING_BTN ,     IDH_10059,
			IDC_PING_TIME_OUT,	IDH_10061,		
            IDC_PING_DATA_SIZE,IDH_10062,
			IDC_PING_NUMBER_HITS,	IDH_10063,		
			IDC_PING_LOG_FILE,	IDH_10066,		
            IDC_PING_ENABLE_LOG, IDH_10067,
            IDC_PING_SHOW_NAME, IDH_10065,
            IDC_PING_HISTORY,   IDH_10068,
            IDC_PING_NDOMAIN,    IDH_10058,
            IDC_PING_INTERVALS,    IDH_10060,
            IDC_PING_NUMBER_TIMEOUTS,    IDH_10064,
			0,0
	};

class CUT_PingPage;    // declare in advance so we can use it in our class

class myPing : public CUT_ICMP
{

	COLORREF		m_rfTextColor;
	COLORREF		m_rfBackColor;
	void OnReceiveICMP();
	BOOL IsAborted();

    int             m_nAvgResp;
    int             m_nAggResp;
    int             m_nCount;
public :
	myPing();
	~myPing();
	CUT_PingPage *m_parent;
    int GetAvgResponse();
    

};

class CUT_PingPage : public CUCPage  
{
	HFONT m_hFont;
	BOOLEAN m_bEnableLogChecked;
public:
	BOOL m_bAbort;
	BOOL m_bShowName;
	CUT_PingPage(LPTSTR title);
	virtual ~CUT_PingPage();
	virtual void OnHelp(LPARAM lParam);
	virtual void OnClicked(int controlId);
	virtual void OnInitDialog(WPARAM wParam, LPARAM lParam);
	CUH_Control m_HistoryCtrl;
	HANDLE m_hThread;
	static unsigned __stdcall PingThread(void * pThis);

};

#endif // !defined(AFX_UT_PINGPAGE_H__3272A6F9_7140_11D3_8871_0080C86498A0__INCLUDED_)
