// EPropertyTextblockWindow.cpp: implementation of the EPropertyTextblockWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EPropertyTextblock.h"
#include "EPropListCtrl.h"
#include "EPropertyTextblockWindow.h"

#define BUTTON_PANEL_HEIGHT 30
#define PANEL_BUTTON_HEIGHT 22

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(EPropertyTextblockWindow, CFrameWnd)
	//{{AFX_MSG_MAP(EPropWndEdit)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED( PTB_ID_BUTTON_OK , OnButtonOk )
	ON_BN_CLICKED( PTB_ID_BUTTON_CANCEL , OnClose )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

EPropertyTextblockWindow::EPropertyTextblockWindow( EPropertyTextblock* pPropertyTextblock , EPropWnd* pCtrl , const CString& sName )
{
	m_pCtrl = pCtrl;
	m_pPropertyTextblock = pPropertyTextblock;
//	SetIcon( AfxGetApp()->LoadIcon(
}

EPropertyTextblockWindow::~EPropertyTextblockWindow()
{
}

BOOL EPropertyTextblockWindow::OnCreateClient( LPCREATESTRUCT lpcs, CCreateContext* pContext )
{
	CRect cr;
	GetClientRect(&cr);

	CRect EditRect = cr;
	EditRect.bottom -= BUTTON_PANEL_HEIGHT;

	CRect PanelRect = cr;
	PanelRect.top = EditRect.bottom;

	//
	// edit panel
	//
	m_Edit.Create( WS_TABSTOP | WS_VSCROLL | ES_MULTILINE | WS_CHILD | WS_VISIBLE , EditRect , this , PTB_ID_EDIT );
	m_Edit.SetFont( m_pCtrl->GetFont() );

	//
	// button panel
	//
	m_ButtonPanel.Create( "" , WS_CHILD | WS_VISIBLE | WS_DLGFRAME , PanelRect , this );
	m_ButtonPanel.GetClientRect(&cr);

	m_ButtonOK.Create( "OK" , WS_CHILD | WS_VISIBLE , CRect(0,0,10,10) , this , PTB_ID_BUTTON_OK );
	m_ButtonOK.SetFont( m_pCtrl->GetFont() );

	m_ButtonCancel.Create( "Cancel" , WS_CHILD | WS_VISIBLE , CRect(0,0,80,80) , this , PTB_ID_BUTTON_CANCEL );
	m_ButtonCancel.SetFont( m_pCtrl->GetFont() );

	return TRUE;
}

//pass on to the property
void EPropertyTextblockWindow::OnButtonOk()
{
	m_pPropertyTextblock->OnWindowButtonOk();
}

//pass on to the property
void EPropertyTextblockWindow::OnClose()
{
	m_pPropertyTextblock->OnWindowButtonCancel();
}

BOOL EPropertyTextblockWindow::OnEraseBkgnd( CDC* pDC )
{
//----
//	CRect cr;
//	GetClientRect(&cr);
//	pDC->FillSolidRect( 0 , 0 , cr.Width() , cr.Height() , RGB(255,0,0) );
//	return TRUE;
//----
	return FALSE;
//----
}

/*
void EPropertyTextblockWindow::OnKillFocus( CWnd* pNewWnd )
{

//	if( IsChild( pNewWnd ) )
//	{
//	}
//	else
//	{
//		m_pPropertyTextblock->OnWindowCancel();
//	}

}
*/

void EPropertyTextblockWindow::OnSize( UINT nType, int cx, int cy )
{
	CRect cr(0,0,cx,cy);

	m_EditRect = cr;
	m_EditRect.bottom -= BUTTON_PANEL_HEIGHT;

	m_PanelRect = cr;
	m_PanelRect.top = m_EditRect.bottom;

	m_Edit       .SetWindowPos( NULL , m_EditRect .left , m_EditRect .top , m_EditRect .Width() , m_EditRect .Height() , SWP_NOZORDER );
	m_ButtonPanel.SetWindowPos( NULL , m_PanelRect.left , m_PanelRect.top , m_PanelRect.Width() , m_PanelRect.Height() , SWP_NOZORDER );

//	m_ButtonPanel.GetClientRect(&cr);

	CRect ButtonRect;
	ButtonRect.top    = m_PanelRect.top + (m_PanelRect.Height() - PANEL_BUTTON_HEIGHT) / 2;
	ButtonRect.bottom = ButtonRect.top + PANEL_BUTTON_HEIGHT;
	ButtonRect.left   = 5;
	ButtonRect.right  = ButtonRect.left + 60;
	m_ButtonOK.SetWindowPos( NULL , ButtonRect.left , ButtonRect.top , ButtonRect.Width() , ButtonRect.Height() , SWP_NOZORDER );

	ButtonRect.left   = ButtonRect.right + 5;
	ButtonRect.right  = ButtonRect.left + 60;
	m_ButtonCancel.SetWindowPos( NULL , ButtonRect.left , ButtonRect.top , ButtonRect.Width() , ButtonRect.Height() , SWP_NOZORDER );

}

CString EPropertyTextblockWindow::GetEditText()
{
	//
	// edit box had \r\n at every \n
	//
	CString s;
	m_Edit.GetWindowText(s);
	s.Remove('\r');
	return s;
}

void EPropertyTextblockWindow::SetEditText( const CString& s )
{
	//
	// edit box needs \r\n at every newline, so every newline must
	// be converted to also contain \r
	// 
	// 1) remove \r
	// 2) replace \n with \r\n
	//
	CString t = s;
	CString u;

	//
	// fjern \r
	//
	t.Remove('\r');

	//
	// insert \r at each \n
	//

	for( int i=0 ; i<t.GetLength() ; i++ )
	{
		char c = t[i];

		if( c == '\n' )
		{
			u += "\r\n";
		}
		else
		{
			u += c;
		}
	}


	m_Edit.SetWindowText(u);
}