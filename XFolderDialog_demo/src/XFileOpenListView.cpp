// XFileOpenListView.cpp  Version 1.0
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// Description:
//     XFileOpenListView implements CXFileOpenListView, a folder browsing 
//     dialog that uses the new Windows 2000-style dialog.  Please see article 
//     at www.codeproject.com.
//
// History
//     Version 1.0 - 2008 February 22
//     - Initial public release
//
// License:
//     This software is released into the public domain.  You are free to use
//     it in any way you like, except that you may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XFileOpenListView.h"
#include "xwinver.h"

// definitions from commctrl.h
#ifndef LV_VIEW_ICON
#define LV_VIEW_ICON        0x0000
#define LV_VIEW_DETAILS     0x0001
#define LV_VIEW_SMALLICON   0x0002
#define LV_VIEW_LIST        0x0003
#define LV_VIEW_TILE        0x0004
#define LV_VIEW_MAX         0x0004
#endif

#ifndef LVM_GETVIEW
#define LVM_GETVIEW         (LVM_FIRST + 143)
#endif

#ifndef __noop
#if _MSC_VER < 1300
#define __noop ((void)0)
#endif
#endif

#undef TRACE
#define TRACE __noop

//=============================================================================
// if you want to see the TRACE output, uncomment this line:
//#include "XTrace.h"
//=============================================================================

//=============================================================================
//=============================================================================
// CXFileOpenListView - Used to subclass the "SHELLDLL_DefView" window in the
// file open dialog. This window contain the list view and processses
// commands to set different view modes.
//=============================================================================
//=============================================================================


//=============================================================================
// Set the list view to desired mode.
BOOL CXFileOpenListView::SetViewMode(int cmd)
//=============================================================================
{
	TRACE(_T("in CXFileOpenListView::SetViewMode:  0x%X\n"), cmd);

	if (IsWindow(m_hWnd)) 
	{
		// SHELLDLL_DefView window found: send it the command.
		if (cmd == 0)
		{
			if (IsXP())	
				cmd = XLVM_XP_LIST;
			else if (IsVista())
				cmd = XLVM_VISTA_LIST;
		}

		SendMessage(WM_COMMAND, cmd);

		// Send parent dialog a Refresh command (F5) to force repaint.
		// The command ID value was obtained by inspection using Spy++.
		const UINT CMD_REFRESH = 40966;
		GetParent()->SendMessage(WM_COMMAND, CMD_REFRESH);

		return TRUE;
	}
	else
	{
		TRACE(_T("ERROR - no m_hWnd\n"));
	}
	return FALSE;
}

//=============================================================================
// Get current list view mode in the form of WM_COMMAND code that can be
// passed to SetViewMode.
int CXFileOpenListView::GetViewMode()
//=============================================================================
{
	TRACE(_T("in CXFileOpenListView::GetViewMode\n"));

	int nViewMode = 0;

	if (IsWindow(m_hWnd))
	{
		// Get the child list view window.
		HWND hlc = ::FindWindowEx(m_hWnd, NULL, _T("SysListView32"), NULL);
		if (hlc)
		{
			CListCtrl* plc = (CListCtrl*)CWnd::FromHandle(hlc);
			if (plc)
			{
				long lView = (long)plc->SendMessage(LVM_GETVIEW);

				TRACE(_T("lView=%X\n"), lView);

				if (IsXP())	
					nViewMode = GetXpViewMode(lView, plc);
				else if (IsVista())
					nViewMode = GetVistaViewMode(lView, plc);
			}
		}
	}

	return nViewMode;
}

//=============================================================================
int CXFileOpenListView::GetXpViewMode(long lView, CListCtrl* plc)
//=============================================================================
{
	int nViewMode = 0;

	if (lView == LV_VIEW_ICON) 
	{
		// If list view is in ICON mode, look at icon spacing to determine
		// whether Thumbnail or Icon mode.
		CSize sz(0, 0);
		if (plc && IsWindow(plc->m_hWnd))
			sz = CSize((DWORD)plc->SendMessage(LVM_GETITEMSPACING));
		TRACE(_T("sz.cx = %d\n"), sz.cx);

		if (sz.cx > GetSystemMetrics(SM_CXICONSPACING)) 
		{
			nViewMode = XLVM_XP_THUMBNAILS;
		} 
		else 
		{
			nViewMode = XLVM_XP_ICONS;
		}
	} 
	else if (lView == LV_VIEW_DETAILS) 
	{
		nViewMode = XLVM_XP_DETAILS;
	} 
	else if (lView == LV_VIEW_LIST) 
	{
		nViewMode = XLVM_XP_LIST;
	} 
	else if (lView == LV_VIEW_TILE) 
	{
		nViewMode = XLVM_XP_TILES;
	}

	return nViewMode;
}

//=============================================================================
int CXFileOpenListView::GetVistaViewMode(long lView, CListCtrl* plc)
//=============================================================================
{
	int nViewMode = 0;

	if (lView == LV_VIEW_SMALLICON)
	{
		nViewMode = XLVM_VISTA_SMALL_ICONS;
	}
	else if (lView == LV_VIEW_ICON) 
	{
		// If list view is in ICON mode, look at icon spacing to determine
		// whether Thumbnail or Icon mode.
		CSize sz(0, 0);
		if (plc && IsWindow(plc->m_hWnd))
			sz = CSize((DWORD)plc->SendMessage(LVM_GETITEMSPACING));
		int nIconSpacing = GetSystemMetrics(SM_CXICONSPACING);
		//CString s;
		//s.Format(_T("item spacing = (%d, %d), nIconSpacing = %d"), sz.cx, sz.cy, nIconSpacing);
		//::MessageBox(NULL, s, _T("item spacing"), MB_OK);

		if (sz.cx == nIconSpacing) 
		{
			nViewMode = XLVM_VISTA_MEDIUM_ICONS;
		}
		else if (sz.cx > nIconSpacing*2) 
		{
			nViewMode = XLVM_VISTA_EXTRA_LARGE_ICONS;
		} 
		else 
		{
			nViewMode = XLVM_VISTA_LARGE_ICONS;
		}
	} 
	else if (lView == LV_VIEW_DETAILS) 
	{
		nViewMode = XLVM_VISTA_DETAILS;

	} 
	else if (lView == LV_VIEW_LIST) 
	{
		nViewMode = XLVM_VISTA_LIST;

	} 
	else if (lView == LV_VIEW_TILE) 
	{
		nViewMode = XLVM_VISTA_TILES;
	}

	return nViewMode;
}

//=============================================================================
// Process window message from list view. Call default to bypass MFC
// entirely because MFC has all sorts of ASSERT checks that will bomb.
// The only message I care about is WM_DESTROY, to re-initialize myself.
//
// The original version in MSDN only overrode OnCommand; it's necessary to
// override WindowProc to completely bypass MFC.
//
LRESULT CXFileOpenListView::WindowProc(UINT msg, WPARAM, LPARAM)
//=============================================================================
{
	if (msg == WM_DESTROY) 
	{
		m_lastViewMode = GetViewMode();				// save current view mode
		UnsubclassWindow();							// unsubclass myself
	}
	return Default(); // all message: pass to default WndProc, avoid MFC/CWnd
}
