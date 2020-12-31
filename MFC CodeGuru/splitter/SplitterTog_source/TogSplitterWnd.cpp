/*
** Author: Guy Gascoigne - Piggford
** Internet: guy@wyrdrune.com
**
** You can use this source in any way you like as long as you don't try to sell it.
**
** Any attempt to sell this in source code form must have the permission
** of the original author. You can produce commercial executables with
** this source, but you may not sell it.
**
** Copyright, 1994-98 Guy Gascoigne - Piggford
**
*/

#include "stdafx.h"
#include "resource.h"

#include "TogSplitterWnd.h"

#define new DEBUG_NEW

CTogSplitterWnd::CTogSplitterWnd()
{
}

BOOL CTogSplitterWnd::CreateStatic( CWnd* pParentWnd, int nRows, int nCols )
{
	ASSERT(pParentWnd != NULL);
	ASSERT(nCols > 1 || nRows > 1);     // 1x1 is not permitted
	m_nMaxCols = 2;
	m_nMaxRows = 2;
	ASSERT( nRows > 0 && nRows <= m_nMaxRows );
	ASSERT( nCols > 0 && nCols <= m_nMaxCols );
	m_nRows = nRows;
	m_nCols = nCols;
	// create with zero minimum pane size
	if (!CreateCommon(pParentWnd, CSize(0, 0), WS_CHILD | WS_VISIBLE, AFX_IDW_PANE_FIRST ))
		return FALSE;

	// all panes must be created with explicit calls to CreateView
	return TRUE;
}

void CTogSplitterWnd::Toggle()
{
	if ( BarIsHorizontal() )
	{
#if defined(WIN32)
		SetWindowLong( GetPane( 1, 0 )->m_hWnd, GWL_ID, AFX_IDW_PANE_FIRST + 1 );
#else
		SetWindowWord( GetPane( 1, 0 )->m_hWnd, GWW_ID, AFX_IDW_PANE_FIRST + 1 );
#endif
		m_nRows = 1;
		m_nCols = 2;
	}
	else
	{
#if defined(WIN32)
		SetWindowLong( GetPane( 0, 1 )->m_hWnd, GWL_ID, AFX_IDW_PANE_FIRST + 16 );
#else
		SetWindowWord( GetPane( 0, 1 )->m_hWnd, GWW_ID, AFX_IDW_PANE_FIRST + 16 );
#endif
		m_nRows = 2;
		m_nCols = 1;
	}
}

void CTogSplitterWnd::UpdateSizes( CSize & sz1, CSize & sz2 )
{
	int dummy, min;

	if ( BarIsHorizontal() )
	{
		GetRowInfo( 0, dummy, min );
		SetRowInfo( 0, sz1.cy, min );
		GetRowInfo( 1, dummy, min );
		SetRowInfo( 1, sz2.cy, min );
	}
	else
	{
		GetColumnInfo( 0, dummy, min );
		SetColumnInfo( 0, sz1.cx, min );
		GetColumnInfo( 1, dummy, min );
		SetColumnInfo( 1, sz2.cx, min );
	}
	RecalcLayout();
}

