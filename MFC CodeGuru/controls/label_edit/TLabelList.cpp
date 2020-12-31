// TLabelComboBox.cpp: implementation of the CTLabelList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TLabelList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTLabelList::CTLabelList():m_sSeparator(_T(":"))
{
	m_hWndList = NULL;
}

CTLabelList::~CTLabelList()
{
}

CWnd* CTLabelList::GetWindowControl()
{
	return CWnd::FromHandle(m_hWndList);
}

BOOL CTLabelList::IsEditDestroyable()
{
	return FALSE;
}

void CTLabelList::Attach(HWND hwnd)
{
	ASSERT (::IsWindow(hwnd));
	ASSERT (m_hWndList == NULL);
	m_hWndList = hwnd;

	CWnd* pWnd = GetWindowControl();
	CRect rectCenter; GetWindowRect(rectCenter);
	CRect rect; pWnd->GetWindowRect(rect);
	POINT p;
	p.x = rectCenter.left + (rectCenter.Width() - rect.Width())/2;
	p.y = rectCenter.top + (rectCenter.Height() - rect.Height())/2;
	GetParent()->ScreenToClient(&p);
	pWnd->SetWindowPos(0, p.x, p.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_HIDEWINDOW | SWP_FRAMECHANGED);
}

void CTLabelList::Attach(CWnd* pWnd)
{
	ASSERT (pWnd && IsWindow(pWnd->m_hWnd));
	Attach(pWnd->m_hWnd);
}

