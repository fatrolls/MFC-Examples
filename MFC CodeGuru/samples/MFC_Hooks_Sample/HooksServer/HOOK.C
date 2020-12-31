#include <windows.h>
#include "hook.h"
#include "HooksServer.h"
#include <malloc.h>

/*
** Non-shared data
*/

PRIVATE HWND ghwndClientHook = NULL;   // the handle back to the client executable
PRIVATE CLIENTMSGDATA gsmd;
PRIVATE COPYDATASTRUCT gcds = { 0, sizeof(CLIENTMSGDATA), &gsmd };
PRIVATE LONG nFindClientCalled = 0;

PRIVATE VOID FindClientWindow(VOID);

VOID DbgPrintf(LPTSTR fmt,...);

BOOL APIENTRY DllMain( PVOID hModule, ULONG ulReason, PCONTEXT pctx )
{
    UNREFERENCED_PARAMETER(hModule);
    UNREFERENCED_PARAMETER(pctx);

    if ( ulReason == DLL_PROCESS_ATTACH )
	{
        FindClientWindow();
    }

    return TRUE;
}

PRIVATE void FindClientWindow()
{
    ghwndClientHook = FindWindow(HOOKWINDOWCLASS, HOOKWINDOWNAME);
}

BOOL WINAPI HookProc( HWND hwnd, UINT uiMessage, WPARAM wParam, LPARAM lParam )
{
	if( (ghwndClientHook == NULL) || (!IsWindow(ghwndClientHook)) )
    {
        // Client has terminated. Find the new window.
		if((++nFindClientCalled) > 50)
			return 0;
		else
	        FindClientWindow();
    }

	if( (ghwndClientHook != NULL) && (hwnd != ghwndClientHook) &&
		(!IsChild(ghwndClientHook, hwnd)) && (IsWindow(ghwndClientHook)) )
	{
        gsmd.wParam = wParam;
        gsmd.lParam = lParam;
        gcds.dwData = uiMessage;

		SendMessage(ghwndClientHook, WM_COPYDATA, (WPARAM)hwnd, (LPARAM)&gcds);
    }

    return FALSE;
}

LRESULT CALLBACK ClientGetMsgProc( INT hc, WPARAM wParam, LPARAM lParam )
{
	PMSG pmsg;
    pmsg = (PMSG)lParam;

	if((hc == HC_ACTION) && (pmsg) && (pmsg->hwnd)) 
	{
		return HookProc(pmsg->hwnd, pmsg->message, pmsg->wParam, pmsg->lParam);
	}
	else if(hc < 0)
	{
		// Note that CallNextHookEx ignores the first parameter (hhook) so
		// it is acceptable (barely) to pass in a NULL.
		return CallNextHookEx(NULL, hc, wParam, lParam);
	}
	
	return 0;
}

LRESULT CALLBACK ClientCallWndProc( INT hc, WPARAM wParam, LPARAM lParam )
{
	PCWPSTRUCT pcwps;
    pcwps = (PCWPSTRUCT)lParam;
	
	if( (hc == HC_ACTION) && (pcwps) && (pcwps->hwnd) && (wParam == 0))
	{
		return HookProc(pcwps->hwnd, pcwps->message, pcwps->wParam, pcwps->lParam);
	}
	else if(hc < 0)
	{
		// Note that CallNextHookEx ignores the first parameter (hhook) so
		// it is acceptable (barely) to pass in a NULL.
		return CallNextHookEx(NULL, hc, wParam, lParam);
	}
	
	return 0;
}

VOID DbgPrintf(LPTSTR fmt,...)
{
    va_list marker;
    TCHAR szBuf[256];

    va_start(marker, fmt);
    wvsprintf(szBuf, fmt, marker);
    va_end(marker);

    OutputDebugString(szBuf);
    OutputDebugString(TEXT("\r\n"));
}
