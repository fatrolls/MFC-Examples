// UT_Finger.h: interface for the CUT_Finger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UT_FINGER_H__3272A6F8_7140_11D3_8871_0080C86498A0__INCLUDED_)
#define AFX_UT_FINGER_H__3272A6F8_7140_11D3_8871_0080C86498A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ut_clnt.h"
#include "uh_ctrl.h"
#include "UCPage.h"
#include "help\context.hh"

const	DWORD dwFingerHelpMap[] = {
			IDC_FINGER_BTN ,     IDH_10017,
			IDC_FINGER_HISTORY,	IDH_10019,		
            IDC_FINGER_LOG_FILE,IDH_10020,
			IDC_FINGER_ENABLE_LOG,	IDH_10022,		
            IDC_USER_NDOMAIN, IDH_10016,
			0,0
	};

class CUT_FingerPage : public CUCPage  
{
	HFONT m_hFont;
	BOOLEAN m_bEnableLogChecked;
public:
	CUT_FingerPage(LPTSTR title);
	virtual ~CUT_FingerPage();
    virtual void OnHelp(LPARAM lParam);
	virtual void OnClicked(int controlId);
	virtual void OnInitDialog(WPARAM wParam, LPARAM lParam);
	CUH_Control m_HistoryCtrl;

};

#endif // !defined(AFX_UT_FINGER_H__3272A6F8_7140_11D3_8871_0080C86498A0__INCLUDED_)
