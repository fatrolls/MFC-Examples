// OXStaticMenuItem.cpp : implementation file
//

#include "stdafx.h"
#include "OXStaticMenuItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COXStaticMenuItem

COXStaticMenuItem::COXStaticMenuItem()
{
	m_bPressedDown=FALSE;
	m_clrActive=RGB(192,0,0);
	m_clrNormalText=GetTextColor();
}

COXStaticMenuItem::~COXStaticMenuItem()
{
	if(::IsWindow(GetSafeHwnd()))
		DestroyWindow();
}


BEGIN_MESSAGE_MAP(COXStaticMenuItem, COXStaticText)
	//{{AFX_MSG_MAP(COXStaticMenuItem)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
    ON_MESSAGE(HWM_MOUSEENTER, OnMouseEnter)
    ON_MESSAGE(HWM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COXStaticMenuItem message handlers

static BOOL bIsCreating=FALSE;

int COXStaticMenuItem::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	bIsCreating=TRUE;

	if(COXStaticText::OnCreate(lpCreateStruct)==-1)
		return -1;

	m_MouseSpy.HookWindow(this);
	// call this function in oder to get HWM_MOUSEENTER and HWM_MOUSELEAVE messages
	m_MouseSpy.InstallSpy();

	return 0;
}

void COXStaticMenuItem::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	if(!bIsCreating)
	{
		m_MouseSpy.HookWindow(this);
		// call this function in oder to get HWM_MOUSEENTER and 
		// HWM_MOUSELEAVE messages
		m_MouseSpy.InstallSpy();
	}

	COXStaticText::PreSubclassWindow();
}

LONG COXStaticMenuItem::OnMouseEnter(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	CWnd* pParentWnd=GetParent();
	ASSERT(pParentWnd);
	CRect rect;
	GetWindowRect(rect);
	rect.InflateRect(1,1,0,0);
	pParentWnd->ScreenToClient(rect);
	MoveWindow(rect);

	m_clrNormalText=GetTextColor();
	SetTextColor(m_clrActive,TRUE);

	NotifyParent(SMIN_ACTIVATED);

	return (LONG)0;
}

LONG COXStaticMenuItem::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	CWnd* pParentWnd=GetParent();
	ASSERT(pParentWnd);
	CRect rect;
	GetWindowRect(rect);
	if(m_bPressedDown)
	{
		rect.OffsetRect(-2,-2);
		m_bPressedDown=FALSE;
	}
	rect.DeflateRect(1,1,0,0);
	pParentWnd->ScreenToClient(rect);
	MoveWindow(rect);

	SetTextColor(m_clrNormalText,TRUE);

	NotifyParent(SMIN_DEACTIVATED);

	return (LONG)0;
}

void COXStaticMenuItem::OnLButtonDown(UINT nFlags, CPoint point) 
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

void COXStaticMenuItem::OnLButtonUp(UINT nFlags, CPoint point) 
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

		m_bPressedDown=FALSE;

		NotifyParent(SMIN_CLICKED);
	}

	COXStaticText::OnLButtonUp(nFlags, point);
}

void COXStaticMenuItem::SetProperties(COLORREF clrText/*=::GetSysColor(COLOR_BTNTEXT)*/,
									  COLORREF clrBack/*=::GetSysColor(COLOR_BTNFACE)*/, 
									  COLORREF clrActive/*=RGB(192,0,0)*/, 
									  int nFontHeight/*=12*/, 
									  int nFontWeight/*=FW_NORMAL*/, 
									  CString sFontName/*=_T("MS Sans Serif")*/, 
									  BOOL bEmboss/*=TRUE*/, 
									  int nHorzAlignment/*=OX_ALIGNHORZ_LEFT*/, 
									  int nVertAlignment/*=OX_ALIGNVERT_CENTER*/)
{
	SetTextColor(clrText);
	SetBkColor(clrBack);
	m_clrActive=clrActive;
	LOGFONT lf;
	if(GetLogFont(&lf))
	{
		lf.lfHeight=nFontHeight;
		lf.lfWeight=nFontWeight;
		SetLogFont(&lf);
	}
	SetFontName(sFontName);

	SetEmboss(bEmboss);
	SetHorzAlignment(nHorzAlignment);
	SetVertAlignment(nVertAlignment);
	SetCharSet(ANSI_CHARSET,TRUE);
}


void COXStaticMenuItem::NotifyParent(int nEventID)
{
	ASSERT(IsWindow(GetSafeHwnd()));
	ASSERT(nEventID==SMIN_ACTIVATED || nEventID==SMIN_DEACTIVATED || 
		nEventID==SMIN_CLICKED);

	CWnd* pParentWnd=GetParent();
	ASSERT(pParentWnd!=NULL);

	NMHDR nmhdr;
	nmhdr.code=nEventID;
	nmhdr.hwndFrom=GetSafeHwnd();
	nmhdr.idFrom=GetDlgCtrlID();
	pParentWnd->SendMessage(WM_NOTIFY,nmhdr.idFrom,(LPARAM)&nmhdr);
}


