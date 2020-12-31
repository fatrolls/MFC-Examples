// ItemOverlayEdit.cpp : implementation file
//

#include "stdafx.h"
#include "EPropListCtrl.h"
#include "EPropWndEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EPropWndEdit

EPropWndEdit::EPropWndEdit()
{
}

EPropWndEdit::~EPropWndEdit()
{
}


BEGIN_MESSAGE_MAP(EPropWndEdit, CEdit)
	//{{AFX_MSG_MAP(EPropWndEdit)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EPropWndEdit message handlers

BOOL EPropWndEdit::PreTranslateMessage( MSG* pMsg )
{

// this is handled default by the edit control. accelerators in application may have been the reason for implementing this?

//	if( pMsg->message == WM_KEYDOWN )
//	{
//
//		TRACE("EPropWndEdit::PreTranslateMessage WM_KEYDOWN: ");
//
//		bool bControl = (GetKeyState(VK_CONTROL)&0x80000000) != 0;
//		bool bShift   = (GetKeyState(VK_SHIFT)  &0x80000000) != 0;
//
//		if( bControl && !bShift )
//		{
//			TRACE("\n" );
//
//			if(pMsg->wParam == VK_C)
//			{
//				Copy();
//				return TRUE;
//			}
//			else if(pMsg->wParam == VK_V)
//			{
//				Paste();
//				return TRUE;
//			}
//			else if(pMsg->wParam == VK_INSERT)
//			{
//				Copy();
//				return TRUE;
//			}
//		}
//		else if( bShift && !bControl )
//		{
//			TRACE("\n" );
//
//			if(pMsg->wParam == VK_INSERT)
//			{
//				Paste();
//				return TRUE;
//			}
//		}
//		else if( pMsg->wParam == VK_DELETE )
//		{
//			TRACE("DELETE\n" );
//			
//			int nFrom, nTo;
//			GetSel(nFrom, nTo);
//			if(nFrom == nTo)
//				SetSel(nFrom,nFrom+1);
//			Cut();
//			return TRUE;
//		}
//		else if( pMsg->wParam == VK_RETURN )
//		{
//			TRACE("VK_RETURN\n" );
//		}
//		else if(pMsg->wParam == VK_ESCAPE)
//		{
//			TRACE("VK_ESCAPE\n" );
//		}
//		else if(pMsg->wParam == VK_UP)
//		{
//			TRACE("VK_UP\n" );
//		}
//		else if(pMsg->wParam == VK_DOWN )
//		{
//			TRACE("VK_DOWN\n" );
//		}
//		else if(pMsg->wParam == VK_TAB )
//		{
//			TRACE("VK_TAB\n" );
//		}
//		else
//		{
//			TRACE("????\n" );
//		}
//	}

	//
	// pass message on...
	//

	return CEdit::PreTranslateMessage(pMsg);
}

void EPropWndEdit::OnKillFocus( CWnd* pWnd )
{
	bool bNextFocusIsButton = false;
	
	if( pWnd != NULL )
	{
		int nID = pWnd->GetDlgCtrlID();
		bNextFocusIsButton = (nID==601);
	}

	EPropWnd* pPropWnd = (EPropWnd*)GetParent();

	if( bNextFocusIsButton )
	{
		pPropWnd->m_bCloseOnKillFocus = false;
		pPropWnd->m_bApplyOnKillFocus = false;
	}

//	GetParent()->PostMessage( UWM_PROPERTY_LOOSING_FOCUS , nID==601 );

	CEdit::OnKillFocus(pWnd);
}
