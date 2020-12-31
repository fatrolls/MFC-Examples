
#include "stdafx.h"
#include "SystrayIcon.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SystrayIcon::SystrayIcon( CWnd* pWnd, UINT unCallbackMsg,
						  LPCTSTR szTip, HICON* pIconList )
{
	m_NotifyIcon.cbSize = sizeof( NOTIFYICONDATA );
	m_NotifyIcon.hWnd = pWnd->GetSafeHwnd();
	m_NotifyIcon.uID = 0;
	m_NotifyIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	m_NotifyIcon.uCallbackMessage = unCallbackMsg;
	m_phIcon = pIconList;
	m_NotifyIcon.hIcon = m_phIcon[0];
	strcpy ( m_NotifyIcon.szTip, szTip );
	
	Shell_NotifyIcon ( NIM_ADD,&m_NotifyIcon );	
}
SystrayIcon::~SystrayIcon()
{
	Shell_NotifyIcon( NIM_DELETE, &m_NotifyIcon );
}

void SystrayIcon::SetState( HICON hIcon )
{
	m_NotifyIcon.hIcon = hIcon;
	Shell_NotifyIcon( NIM_MODIFY, &m_NotifyIcon );
}

void SystrayIcon::SetState( int id, char* cpToolTip )
{
	m_NotifyIcon.hIcon = m_phIcon[id];
	Shell_NotifyIcon( NIM_MODIFY, &m_NotifyIcon );
}
