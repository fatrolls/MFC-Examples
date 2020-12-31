//ReflectionWnd.cpp : Implementation of CReflectionWnd

//***************************************************************************//
//                                                                           //
//  This file was created using the CWindowImpl ATL Object Wizard            //
//  By Erik Thompson © 2000                                                  //
//	Version 1.1                                                              //
//  Email questions and comments to ErikT@RadBytes.com                       //
//                                                                           //
//***************************************************************************//

#include "stdafx.h"
#include "ReflectionWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CReflectionWnd

CReflectionWnd::CReflectionWnd()
{
}

CReflectionWnd::~CReflectionWnd()
{
	if (IsWindow())	DestroyWindow();
}

const DWORD DEFAULT_TOOLBAR_STYLE = 
		/*Window styles:*/ WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | WS_TABSTOP |
		/*Toolbar styles:*/ TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | TBSTYLE_TRANSPARENT | TBSTYLE_LIST | TBSTYLE_CUSTOMERASE |
							TBSTYLE_WRAPABLE |
		/*Common Control styles:*/ CCS_TOP | CCS_NODIVIDER | CCS_NOPARENTALIGN | CCS_NORESIZE;

LRESULT CReflectionWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	RECT rect;
	GetClientRect(&rect);
	m_ToolbarWnd.Create(m_hWnd, rect, NULL, DEFAULT_TOOLBAR_STYLE);
	return 0;
}
