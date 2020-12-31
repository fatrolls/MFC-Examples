
#include <StdAfx.h>
#include "MouseHook.h"

#define WM_MOUSEWHEEL_MSG WM_APP+1
#define WM_MBUTTON_MSG WM_APP+2

IMPLEMENT_DYNCREATE( MouseHook, CWinThread )

MouseHook::MouseHook():
m_fpSetHook( 0 ),
m_fpUnsetHook( 0 ),
m_hModule( 0 ),
m_hWnd( 0 )
{

}

MouseHook::~MouseHook()
{
    if( m_hModule )
    {
        ::FreeLibrary( m_hModule );
        m_hModule = 0;
    }
}

BOOL MouseHook::InitInstance()
{
    return TRUE;
}

int MouseHook::ExitInstance()
{
    if( m_hModule )
    {
        ::FreeLibrary( m_hModule );
        m_hModule = 0;
    }
    return CWinThread::ExitInstance();
}

bool MouseHook::EnableHook( HWND hWnd )
{

    m_hWnd = hWnd;

    if( !m_hModule )
    {
        m_hModule = ::LoadLibrary( "MouseHookProc.dll" );
        if( !m_hModule )
        {
            return false;
        }
        m_fpSetHook = ( SetHook_fp )::GetProcAddress( m_hModule, "SetHook" );
        m_fpUnsetHook = ( UnsetHook_fp )::GetProcAddress( m_hModule, "UnsetHook" );
    }
    
    if( m_fpSetHook || m_fpUnsetHook )
    {
        if( !( m_fpSetHook )( this->m_nThreadID ))
        {
            ::FreeLibrary( m_hModule );
            m_hModule = 0;
            return false;
        }
        return true;
    }
    else
    {
        ::FreeLibrary( m_hModule );
        m_hModule = 0;
        return false;
    }
}

bool MouseHook::DisableHook()
{
    if( m_fpUnsetHook )
    {
        if( !( m_fpUnsetHook )())
        {
            ::FreeLibrary( m_hModule );
            m_hModule = 0;
            return false;
        }
        return true;
    }
    ::FreeLibrary( m_hModule );
    m_hModule = 0;
    return false;
}

BOOL MouseHook::PreTranslateMessage( MSG* pMsg ) 
{
    switch ( pMsg->message )
    {   
        case WM_MOUSEWHEEL_MSG:
        {
			PostMessage( m_hWnd, WM_MOUSEWHEEL, pMsg->wParam, pMsg->lParam );

            break;
        }

        case WM_MBUTTON_MSG:
        {
			PostMessage( m_hWnd, WM_MBUTTONUP, pMsg->wParam, pMsg->lParam );
            break;
        }   
    }
    return CWinThread::PreTranslateMessage( pMsg );
}