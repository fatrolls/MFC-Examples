//=========================================================
//	TITLE:		Global 
//				for WinNT, MSVC 5.0, MFC 4.1
//				Copyright (C) Matrix Baltic Software
//				Vilnius, Lithuania
//	MODULE:		AppIdle.cpp
//	PURPOSE:	
//
//	AUTHOR:		Audrius Vasiliauskas
// 
//	NOTES:		
//
//=========================================================

#include "StdAfx.h"
#include "AppIdle.h"


void AppIdle()
{
	CWinApp* pApp = AfxGetApp();

	pApp->OnIdle(0);   // updates user interface
	pApp->OnIdle(1);   // frees temporary objects
}


int CheckMessageQueue(CWnd* pWnd)
{
	CWinApp* pApp = AfxGetApp();
	MSG msg;
	
	while (::PeekMessage(&msg, pWnd->GetSafeHwnd(), 0, 0, PM_REMOVE))
	{
		if (!pApp->PreTranslateMessage(&msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		AppIdle();
	}
/*
    MSG msg;
    while(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
    {
        if (msg.message == WM_QUIT)
		{
                return FALSE;
		}
        else
        {
                GetMessage(&msg, NULL, 0, 0);
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }
    }
*/
    return TRUE;
}
