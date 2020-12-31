//
// popupcalendar.cpp : implementation file
//

#include "stdafx.h"
#include "..\ConfigListCtrl.h"
#include "..\utilities.h"
#include "popupcalendar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupCalendar

CPopupCalendar::CPopupCalendar()
{
}

CPopupCalendar::~CPopupCalendar()
{
}

BEGIN_MESSAGE_MAP(CPopupCalendar, CListCtrlCellWnd)
	//{{AFX_MSG_MAP(CPopupCalendar)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupCalendar message handlers

void CPopupCalendar::Create(HWND hParentWnd, CCellDateCtrl *pCellDateCtrl)
{
	CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW|CS_PARENTDC,
                                              0,
                                              (HBRUSH) (COLOR_BTNFACE+1), 
                                              0);
	const RECT rect = {0,0,0,0};

	m_hMainCtrlWnd = hParentWnd;

	BOOL bCreated = CreateEx(0, szClassName, _T(""), WS_POPUP, rect, FromHandle(hParentWnd)->GetParent(), 0, NULL);

	if (bCreated)
	{
		DWORD dwStyle = WS_CHILD | WS_TABSTOP | WS_VISIBLE;
		if (!IsAppThemed()) dwStyle |= WS_BORDER;

		bCreated = m_MonthCalCtrl.Create(dwStyle, rect, this, 0);

		if (bCreated)
			m_MonthCalCtrl.SetPopupCalendar(this);
	}
}

void CPopupCalendar::GetBoundingRect(const RECT &rcCellBounding, RECT &rcBounding, BOOL Downwards /*= TRUE*/)
{
	RECT rcBound;
	m_MonthCalCtrl.GetMinReqRect(&rcBound);

	if (Downwards)
	{
		rcBounding.top = rcCellBounding.bottom;
		rcBounding.bottom = rcCellBounding.bottom + rcBound.bottom - rcBound.top;
	}
	else
	{
		rcBounding.bottom = rcCellBounding.top;
		rcBounding.top = rcCellBounding.top - rcBound.bottom + rcBound.top;
	}	
	rcBounding.right = rcCellBounding.right;
	rcBounding.left = rcCellBounding.right - rcBound.right + rcBound.left;
}

void CPopupCalendar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	RECT							rcBounding;

	GetClientRect(&rcBounding);
	m_MonthCalCtrl.SetWindowPos(NULL,rcBounding.left, rcBounding.top,
		rcBounding.right - rcBounding.left, rcBounding.bottom - rcBounding.top, SWP_SHOWWINDOW);
}

void CPopupCalendar::OpenDropDown(const LPSYSTEMTIME pDateTime)
{
	m_MonthCalCtrl.SetCurSel(pDateTime);
}

void CPopupCalendar::OnMCSelect(NMHDR* pNMHDR, LRESULT* pResult)
{
	SYSTEMTIME DateTime;

	m_MonthCalCtrl.GetCurSel(&DateTime);

	DWORD dwDate = DateUtils::GetDWordFromDMY(DateTime.wDay, DateTime.wMonth, DateTime.wYear);

	::SendMessage(FromHandle(m_hMainCtrlWnd)->m_hWnd, WM_CELL_CTRL_MSG, ID_POPUP_SELCLOSE, dwDate); 
}

void CPopupCalendar::OnMCSelchange(NMHDR* pNMHDR, LRESULT* pResult)
{
	SYSTEMTIME DateTime;

	m_MonthCalCtrl.GetCurSel(&DateTime);

	DWORD dwDate = DateUtils::GetDWordFromDMY(DateTime.wDay, DateTime.wMonth, DateTime.wYear);

	::SendMessage(FromHandle(m_hMainCtrlWnd)->m_hWnd, WM_CELL_CTRL_MSG, ID_POPUP_SELCHANGE, dwDate); 
}

void CPopupCalendar::OnSetFocus(CWnd* pOldWnd)
{
	m_MonthCalCtrl.SetFocus();
	CListCtrlCellWnd::OnSetFocus(pOldWnd);
}

void CPopupCalendar::OnThemeChanged()
{
	BOOL isThemed = IsAppThemed();
	VERIFY(ModifyStyle(isThemed? WS_BORDER : 0, !isThemed? WS_BORDER : 0));
}