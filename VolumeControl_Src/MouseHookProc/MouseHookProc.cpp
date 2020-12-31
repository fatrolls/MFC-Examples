
#include<windows.h>
#include<Windowsx.h>
#include<zmouse.h>

#pragma data_seg( ".mousehookproc" )
    DWORD  m_dwThreadID = 0;  
#pragma data_seg()
#pragma comment( linker, "/SECTION:.mousehookproc,RWS" )

#define WM_MOUSEWHEEL_MSG WM_APP+1
#define WM_MBUTTON_MSG WM_APP+2


HINSTANCE g_hInstance = 0;
HHOOK     g_hHook = 0;

extern "C" bool __declspec( dllexport ) SetHook( DWORD dwThreadID );
extern "C" bool __declspec( dllexport ) UnsetHook();

static LRESULT CALLBACK LowLevelMouseProc( int nCode,
                                          WPARAM wParam, LPARAM lParam );

BOOL APIENTRY DllMain( HINSTANCE hInstance_i, DWORD dwReasonForCall_i,
                       LPVOID lpReserved_i )
{ 
    switch ( dwReasonForCall_i )
    {
        case DLL_PROCESS_ATTACH:
            g_hInstance = hInstance_i;
            g_hHook = 0;
            break;
        case DLL_PROCESS_DETACH:
            UnsetHook();
            break;
    }
    return TRUE;
}

bool SetHook( DWORD dwThreadID )
{
    if ( m_dwThreadID )
    {
        return true;
    }

    g_hHook = ::SetWindowsHookEx( WH_MOUSE_LL, ( HOOKPROC )LowLevelMouseProc, 
                                        g_hInstance, 0 );
    if( g_hHook )
    {
        m_dwThreadID = dwThreadID;
        return true;
    }
    return false;
}

bool UnsetHook()
{
    if ( !m_dwThreadID )
    {
        return false;
    }

    if ( g_hHook )
    {        
        ::UnhookWindowsHookEx( g_hHook );
        m_dwThreadID = 0;
        g_hHook = 0;
        return true;
    }
    return false;   
}

static LRESULT CALLBACK LowLevelMouseProc( int nCode,
                                          WPARAM wParam, LPARAM lParam )
{
	if ( 0 > nCode && g_hHook )
    {
        ::CallNextHookEx( g_hHook, nCode, wParam, lParam );
        return 0;
    }    

    if( WM_MBUTTONDOWN == wParam )
    {
        if(( 0x8000 & ::GetKeyState( VK_CONTROL )) && 
		   ( 0x8000 & ::GetKeyState( VK_SHIFT )))
        {
			PMSLLHOOKSTRUCT pstLLHook = ( PMSLLHOOKSTRUCT )lParam;

            ::PostThreadMessage( m_dwThreadID, WM_MBUTTON_MSG, 0,
				MAKELPARAM( pstLLHook->pt.x, pstLLHook->pt.y ) ); 

			return -1;
        }
    }

	if( WM_MOUSEWHEEL == wParam )
    {		
        if(( 0x8000 & ::GetKeyState( VK_CONTROL )) && 
		   ( 0x8000 & ::GetKeyState( VK_SHIFT )))
        {
			PMSLLHOOKSTRUCT pstLLHook = ( PMSLLHOOKSTRUCT )lParam;

            ::PostThreadMessage( m_dwThreadID, WM_MOUSEWHEEL_MSG, 
				pstLLHook->mouseData, 
				MAKELPARAM( pstLLHook->pt.x, pstLLHook->pt.y )); 
			
			return -1;
        }
    }
    

    return ::CallNextHookEx( g_hHook, nCode, wParam, lParam );
	
}
