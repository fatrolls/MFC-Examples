
#ifndef _CINE_MOUSE_HOOK_H_
#define _CINE_MOUSE_HOOK_H_

#include <afxwin.h>
//#include "VolumeControlDlg.h"

typedef bool ( *SetHook_fp )( DWORD ulThreadID );
typedef bool ( *UnsetHook_fp )( );

class CVolumeControlDlg;

class MouseHook:public CWinThread
{
    DECLARE_DYNCREATE( MouseHook )
public:

    MouseHook();
    ~MouseHook();

    bool    EnableHook( HWND hWnd );
    bool    DisableHook();

    // Overrides
    //{{AFX_VIRTUAL(CineMouseHook)
    public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    virtual BOOL PreTranslateMessage( MSG* pMsg );
    //}}AFX_VIRTUAL

private:

    SetHook_fp      m_fpSetHook;
    UnsetHook_fp    m_fpUnsetHook;
    
    HMODULE         m_hModule;
    HWND            m_hWnd;
};

#endif // _CINE_MOUSE_HOOK_H_

