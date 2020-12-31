// UT_DNSPage.h: interface for the CUT_DNSPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UT_DNSPAGE_H__3272A6F7_7140_11D3_8871_0080C86498A0__INCLUDED_)
#define AFX_UT_DNSPAGE_H__3272A6F7_7140_11D3_8871_0080C86498A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UCPage.h"
#include "uh_ctrl.h"	//output-history control
#include "ut_clnt.h"	//ultimate tcp/ip client class
#include "DNS_c.h"		//dns client class
#include "help\context.hh"

const	DWORD dwDNSHelpMap[] = {
			IDC_DNSSERVER ,     IDH_10008,
			IDC_LOOKUPBTN,		IDH_10004,		
            IDC_LOOKUP,         IDH_10002,
			IDC_QUERY_COMBO,	IDH_10005,		
			IDC_AUTHLOOKUPBTN,	IDH_10003,		
            IDC_USE_TCP,        IDH_10011,
            IDC_DNS_ENABLE_LOG, IDH_10007,
            IDC_DNS_LOG_FILE,   IDH_10006,
            IDC_HISTORY_DNS,    IDH_10009,
			0,0
	};

class CUT_DNSPage : public CUCPage  
{
	BOOL		m_bUseUDP;
	HFONT		m_hFont;
	BOOLEAN		m_bEnableLogChecked;
	HANDLE		m_hThread;


public:
	void DisplayEntries(CUT_DNSClient &dns);
	int SelectedQuery(int index);
	CUT_DNSPage(LPTSTR);
	virtual ~CUT_DNSPage();
	void OnInitDialog(WPARAM wParam, LPARAM lParam);
	CUH_Control m_HistoryCtrl;
	virtual void OnCommand(WPARAM wParam,LPARAM lParam);
	virtual void OnSelChange(int item ,HWND);
	virtual void OnClicked(int controlId);
	virtual void OnHelp(LPARAM lParam);
		// TODO:  Map your control ID's to context numbers
		// in your help file here.  The format is:
		// <CONTROL_ID>, <HID_HELP_TOPIC>,
		// Wizard property sheet controls
	static unsigned __stdcall AuthLookUpThread(void * pThis);
	static unsigned __stdcall LookUpThread(void * pThis);

};

#endif // !defined(AFX_UT_DNSPAGE_H__3272A6F7_7140_11D3_8871_0080C86498A0__INCLUDED_)
