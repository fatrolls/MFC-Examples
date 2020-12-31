//
// MCCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MCCtrl.h"
#include "popupcalendar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMCCtrl

CMCCtrl::CMCCtrl() : m_pPopupCalendar(NULL)
{
}

CMCCtrl::~CMCCtrl()
{
}


BEGIN_MESSAGE_MAP(CMCCtrl, CMonthCalCtrl)
	//{{AFX_MSG_MAP(CMCCtrl)
	ON_NOTIFY_REFLECT(MCN_SELECT, OnSelect)
	ON_NOTIFY_REFLECT(MCN_SELCHANGE, OnSelchange)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMCCtrl message handlers

void CMCCtrl::OnSelect(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_pPopupCalendar)
		m_pPopupCalendar->OnMCSelect(pNMHDR, pResult);

	*pResult = 0;
}

void CMCCtrl::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_pPopupCalendar)
		m_pPopupCalendar->OnMCSelchange(pNMHDR, pResult);

	*pResult = 0;
}

void CMCCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_F4)
		m_pPopupCalendar->OnKeyDown(nChar, nRepCnt, nFlags);
	else
		CMonthCalCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}
