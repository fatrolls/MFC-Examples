//
// listctrlcellwnd.cpp : implementation file
//

#include "stdafx.h"
#include "..\ConfigListCtrl.h"
#include "listctrlcellwnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlCellWnd

CListCtrlCellWnd::CListCtrlCellWnd()
{
}

CListCtrlCellWnd::~CListCtrlCellWnd()
{
}


BEGIN_MESSAGE_MAP(CListCtrlCellWnd, CWnd)
	//{{AFX_MSG_MAP(CListCtrlCellWnd)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CListCtrlCellWnd message handlers

void CListCtrlCellWnd::Close()
{
	CWnd *pWnd = FromHandle(m_hMainCtrlWnd);

	::SendMessage(pWnd->m_hWnd, WM_CELL_CTRL_MSG, ID_POPUP_CLOSE, 0); 
	ReleaseCapture();

	ShowWindow(SW_HIDE);
}

void CListCtrlCellWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
		case VK_F4:
			Close();
		break;
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
