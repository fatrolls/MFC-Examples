// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "SoundManager.h"
#include "MyStatic.h"

#include "OXHookWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStatic

CMyStatic::CMyStatic()
{
	m_bPressedDown=FALSE;
}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, COXStaticText)
	//{{AFX_MSG_MAP(CMyStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
    ON_MESSAGE(HWM_MOUSEENTER, OnMouseEnter)
    ON_MESSAGE(HWM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyStatic message handlers

LONG CMyStatic::OnMouseEnter(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	CWnd* pParentWnd=GetParent();
	ASSERT(pParentWnd);
	CRect rect;
	GetWindowRect(rect);
	rect.OffsetRect(-1,-1);
	pParentWnd->ScreenToClient(rect);
	MoveWindow(rect);

	SetTextColor(RGB(192,0,0),TRUE);

	return (LONG)0;
}

LONG CMyStatic::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	CWnd* pParentWnd=GetParent();
	ASSERT(pParentWnd);
	CRect rect;
	GetWindowRect(rect);
	if(m_bPressedDown)
	{
		rect.OffsetRect(-1,-1);
		m_bPressedDown=FALSE;
	}
	else
		rect.OffsetRect(1,1);
	pParentWnd->ScreenToClient(rect);
	MoveWindow(rect);

	SetTextColor(::GetSysColor(COLOR_BTNTEXT),TRUE);

	return (LONG)0;
}

void CMyStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CWnd* pParentWnd=GetParent();
	ASSERT(pParentWnd);
	CRect rect;
	GetWindowRect(rect);
	rect.OffsetRect(2,2);
	pParentWnd->ScreenToClient(rect);
	MoveWindow(rect);

	m_bPressedDown=TRUE;

	COXStaticText::OnLButtonDown(nFlags, point);
}

void CMyStatic::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	if(m_bPressedDown)
	{
		CWnd* pParentWnd=GetParent();
		ASSERT(pParentWnd);
		CRect rect;
		GetWindowRect(rect);
		rect.OffsetRect(-2,-2);
		pParentWnd->ScreenToClient(rect);
		MoveWindow(rect);

		CWnd* pWnd=GetParent();
		if(pWnd)
		{
			CString sText;
			GetWindowText(sText);
			if(sText==_T("Customize"))
				pWnd->PostMessage(WM_APP_CUSTOMIZE);
			else if(sText==_T("Exit"))
				pWnd->PostMessage(WM_APP_CLOSE);
		}
		
		m_bPressedDown=FALSE;
	}

	COXStaticText::OnLButtonUp(nFlags, point);
}
