// MenuItemWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MenuItemWnd.h"
#include "freemenu.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuItemWnd

CMenuItemWnd::CMenuItemWnd()
{
}

CMenuItemWnd::~CMenuItemWnd()
{
}


BEGIN_MESSAGE_MAP(CMenuItemWnd, CWnd)
	//{{AFX_MSG_MAP(CMenuItemWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMenuItemWnd message handlers

LRESULT CMenuItemWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	freeMenu->WindowProc(message, wParam, lParam);
	return CWnd::WindowProc(message, wParam, lParam);
}

BOOL CMenuItemWnd::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	 

// Create( LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	return CWnd::Create(AfxRegisterWndClass(CS_CLASSDC), 
		"", WS_CHILD|WS_VISIBLE, rect, pParentWnd, nID, pContext);
}

void CMenuItemWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
/*	CRect rect;
	GetClientRect(&rect);
	dc.FillRect(&rect,new CBrush(RGB(192,192,0)));*/
	if(freeMenu->m_IsVisible)
		freeMenu->DrawMenu();
}
