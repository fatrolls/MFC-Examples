#include "HookLib.h"
#include <stdio.h>

#pragma data_seg("SHARDATA")
static HWND g_hWnd=NULL;
static HHOOK g_hHookKeyboard=NULL;
static HHOOK g_hHookRec=NULL;
static HHOOK g_hHookPlay=NULL;
#pragma data_seg()

DWORD dwStartRecordTime;
EVENTNODE *lpEventHead=NULL;
EVENTNODE *lpEventTail=NULL;
EVENTNODE *lpEventPlay=NULL;
UINT uMsgFinishJournal=0;

BOOL CALLBACK LibMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	return TRUE;
}

int CALLBACK WEP (int bSystemExit)
{
    return TRUE;
}

STDENTRY_(void) RegisterMessage()
{
	uMsgFinishJournal=RegisterWindowMessage(WM_FINISHJOURNAL);
}

STDENTRY_(BOOL) SetKeyboardHook(HWND hWnd, HINSTANCE hInstance)
{
	g_hHookKeyboard=SetWindowsHookEx
	(
		WH_KEYBOARD,
		KeyboardProc,
		hInstance,
		0
	);
	if(g_hHookKeyboard == FALSE)
	{
		return FALSE;
	}
	g_hWnd=hWnd;

	return TRUE;
}

BOOL UnsetKeyboardHook()
{
	return UnhookWindowsHookEx(g_hHookKeyboard); 
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if(code < 0 || code != HC_ACTION)
	{
		return CallNextHookEx(g_hHookKeyboard, code, wParam, lParam);
	}
	if(code == HC_ACTION)
	{
		if(lParam & 0x80000000 || lParam & 0x40000000)
		{
			return CallNextHookEx(g_hHookKeyboard, code, wParam, lParam);
		}
		if(wParam == VK_F3 && HIBYTE(GetKeyState(VK_CONTROL)))
		{
			if(IsWindow(g_hWnd))
			{
				if(IsWindowVisible(g_hWnd) == FALSE)
				{
					ShowWindow(g_hWnd, SW_SHOW);
				}
			}
			UnsetKeyboardHook();
		}
	}

	return CallNextHookEx(g_hHookKeyboard, code, wParam, lParam);
}

STDENTRY_(BOOL) SetJournalPlaybackHook(HWND hWnd, HINSTANCE hInstance)
{
	g_hHookPlay=SetWindowsHookEx
	(
		WH_JOURNALPLAYBACK,
		JournalPlaybackProc,
		hInstance,
		0
	);
	if(g_hHookPlay == FALSE)
	{
		return FALSE;
	}
	g_hWnd=hWnd;
	
	return TRUE;
}

STDENTRY_(BOOL) SetJournalRecordHook(HWND hWnd, HINSTANCE hInstance)
{
	g_hHookRec=SetWindowsHookEx
	(
		WH_JOURNALRECORD,
		JournalRecordProc,
		hInstance,
		0
	);
	if(g_hHookRec == FALSE)
	{
		return FALSE;
	}
	g_hWnd=hWnd;

	return TRUE;
}

BOOL UnsetJournalPlaybackHook()
{
	return UnhookWindowsHookEx(g_hHookPlay); 
}

BOOL UnsetJournalRecordHook()
{
	return UnhookWindowsHookEx(g_hHookRec); 
}

LRESULT CALLBACK JournalPlaybackProc(int code, WPARAM wParam, LPARAM lParam)
{
	static DWORD dwTimeAdjust;
	LPEVENTMSG lpEvent;
	long lReturnValue;

	if(code >= 0)
	{
		if(lpEventHead == NULL)
		{
			 return CallNextHookEx(g_hHookPlay, code, wParam, lParam );
		}
		if(lpEventPlay == NULL)
		{
			lpEventPlay=lpEventHead;
			lpEventTail=NULL;
			dwTimeAdjust=GetTickCount()-dwStartRecordTime;
		}
		if(code == HC_SKIP) 
		{
			if(lpEventPlay->lpNextEvent == NULL)
			{
				free(lpEventHead);
				lpEventHead=lpEventPlay=NULL;
				UnsetJournalPlaybackHook();
				PostMessage(g_hWnd, uMsgFinishJournal, (WPARAM)TRUE, (LPARAM)NULL);
			}
			else
			{
				lpEventPlay=lpEventPlay->lpNextEvent;
				free(lpEventHead);
				lpEventHead=lpEventPlay;
			}
		}
		else if(code == HC_GETNEXT)
		{
			lpEvent=(LPEVENTMSG)lParam;
			lpEvent->message=lpEventPlay->Event.message;
			lpEvent->paramL=lpEventPlay->Event.paramL;
			lpEvent->paramH=lpEventPlay->Event.paramH;
			lpEvent->time=lpEventPlay->Event.time+dwTimeAdjust;
			lReturnValue=lpEvent->time-GetTickCount();
			if(lReturnValue < 0L)
			{
				lReturnValue=0L;
				lpEvent->time=GetTickCount();
			}
			return lReturnValue;
		}
	}
	return CallNextHookEx(g_hHookPlay, code, wParam, lParam);
}

LRESULT CALLBACK JournalRecordProc(int code, WPARAM wParam, LPARAM lParam)
{
	LPEVENTNODE lpEventNode;
	LPEVENTMSG lpEvent;

	if(code >= 0)
	{
		lpEvent=(LPEVENTMSG)lParam;
		if
		(
			lpEvent->message == WM_KEYDOWN && 
			LOBYTE(lpEvent->paramL) == VK_F3 &&
			HIBYTE(GetKeyState(VK_CONTROL))
		)
		{
			UnsetJournalRecordHook();
			PostMessage(g_hWnd, uMsgFinishJournal, (WPARAM)FALSE, (LPARAM)NULL);
			return FALSE;
		}
		if((lpEventNode=(LPEVENTNODE)malloc(sizeof(EVENTNODE))) == NULL)
		{
			UnsetJournalRecordHook();
			PostMessage(g_hWnd, uMsgFinishJournal, (WPARAM)FALSE, (LPARAM)NULL);
			return FALSE;
		}
		if(lpEventTail == NULL)
		{
			dwStartRecordTime=(DWORD)GetTickCount();
			lpEventHead=lpEventNode;
		}
		else 
		{
			lpEventTail->lpNextEvent=lpEventNode;
		}
		lpEventTail=lpEventNode;
		lpEventTail->lpNextEvent=NULL;
		lpEventTail->Event.message=lpEvent->message;
		lpEventTail->Event.paramL=lpEvent->paramL;
		lpEventTail->Event.paramH=lpEvent->paramH;
		lpEventTail->Event.time=lpEvent->time;

		return FALSE;
	}
	return CallNextHookEx(g_hHookRec, code, wParam, lParam);
}
