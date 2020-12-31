// UT_TracePage.h: interface for the CUT_TracePage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UT_TRACEPAGE_H__6C254686_7299_11D3_8876_0080C86498A0__INCLUDED_)
#define AFX_UT_TRACEPAGE_H__6C254686_7299_11D3_8876_0080C86498A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UCPage.h"
#include "uh_ctrl.h"
#include "ut_clnt.h"
#include "ut_icmp.h"
#include "help\context.hh"

const	DWORD dwTraceHelpMap[] = {
			IDC_TRACE_BTN ,     IDH_10025,
			IDC_TRACE_TIME_OUT,	IDH_10026,		
            IDC_TRACE_DATA_SIZE,IDH_10027,
			IDC_TRACE_NUMBER_HITS,	IDH_10028,		
			IDC_TRACE_LOG_FILE,	IDH_10030,		
            IDC_TRACE_ENABLE_LOG, IDH_10031,
            IDC_TRACE_SHOW_NAME, IDH_10029,
            IDC_TRACE_HISTORY,   IDH_10032,
            IDC_TRACE_NDOMAIN,    IDH_10024,
			0,0
	};


class CUT_TracePage;    // declare in advance so we can use it in our class

class myTrace : public CUT_ICMP
{

	COLORREF		m_rfTextColor;
	COLORREF		m_rfBackColor;
	void OnReceiveICMP();
	BOOL IsAborted();

    int             m_nAvgResp;
    int             m_nAggResp;
    int             m_nCount;

public :
	myTrace();
	~myTrace();
	CUT_TracePage *m_parent;

    int GetAvgResponse();
};

class CUT_TracePage : public CUCPage  
{
	HFONT m_hFont;
	BOOLEAN m_bEnableLogChecked;
public:
	BOOL m_bAbort;
	BOOL m_bShowName;
	CUT_TracePage(LPTSTR title);
    virtual void OnHelp(LPARAM lParam);
	virtual ~CUT_TracePage();
	virtual void OnClicked(int controlId);
	virtual void OnInitDialog(WPARAM wParam, LPARAM lParam);
	CUH_Control m_HistoryCtrl;
	HANDLE m_hThread;
	static unsigned __stdcall TraceThread(void * pThis);

};


#endif // !defined(AFX_UT_TRACEPAGE_H__6C254686_7299_11D3_8876_0080C86498A0__INCLUDED_)
