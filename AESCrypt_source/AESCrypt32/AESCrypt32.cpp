/*
 *  AESCrypt32.cpp
 *
 *  Copyright (C) 2006, 2008
 *  Paul E. Jones <paulej@packetizer.com>
 *  All Rights Reserved.
 *
 ******************************************************************************
 *  $Id: AESCrypt32.cpp,v 1.3 2008/09/01 10:41:04 paulej Exp $
 ******************************************************************************
 *
 *  This is the Win32 application that accepts a list of filenames
 *  and calls the encryption code that resides in the AESCrypt.dll file.
 *  This program is relatively simple and relies entirely on the DLL
 *  to perform processing in the background.
 *
 */

#include "stdafx.h"
#include "AESCrypt32.h"

/*
 *  Application name
 */
const wchar_t *application_name = _T("AES Crypt"); 

/*
 *  Windows Callback Procedure
 */
LRESULT CALLBACK WindowProc(HWND hwnd,
                            UINT uMsg,
                            WPARAM wParam,
                            LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_PAINT:
        case WM_CREATE:
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/*
 *  Windows Main Procedure
 */
int APIENTRY _tWinMain( HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPTSTR    lpCmdLine,
                        int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
    WNDCLASS wndclass;
    HWND hWnd;
    MSG msg;
    LPWSTR *szArglist;
    int nArgs;
    bool encrypt = false;
    StringList *file_list = NULL;

    // Allocate memory for the file list
    try
    {
        file_list = new StringList;
    }
    catch(...)
    {
        return 0;
    }

    // Try to get the command-line argument string
    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    if(szArglist == NULL)
    {
        delete file_list;
        return FALSE;
    }

    // Create the window class and application window (hidden)
    if (!hPrevInstance)
    {
        wndclass.style          = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc    = WindowProc;
        wndclass.cbClsExtra     = 0;
        wndclass.cbWndExtra     = 0;
        wndclass.hInstance      = hInstance;
        wndclass.hIcon          = LoadIcon( hInstance, 
                                            MAKEINTRESOURCE(IDI_AESCRYPT32));
        wndclass.hCursor        = LoadCursor(   NULL,
                                                IDC_ARROW);
        wndclass.hbrBackground  = (HBRUSH) GetStockObject(WHITE_BRUSH);
        wndclass.lpszMenuName   = NULL;
        wndclass.lpszClassName  = application_name;

        RegisterClass(&wndclass);
    }

    hWnd = CreateWindow(application_name,
                        application_name,
                        WS_OVERLAPPED,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

    ShowWindow(hWnd, SW_HIDE);
    UpdateWindow(hWnd);

    // Process the command-line arguments
    for(int i=1; i < nArgs; i++)
    {
        if (i==1)
        {
            if (!_tcscmp(szArglist[i],_T("/d")))
            {
                encrypt = false;
            }
            else if (!_tcscmp(szArglist[i],_T("-d")))
            {
                encrypt = false;
            }
            else if (!_tcscmp(szArglist[i],_T("/e")))
            {
                encrypt = true;
            }
            else if (!_tcscmp(szArglist[i],_T("-e")))
            {
                encrypt = true;
            }
            else
            {
                file_list->push_back(szArglist[i]);
            }
        }
        else
        {
            file_list->push_back(szArglist[i]);
        }
    }

    // Report an error if the file list is empty
    if (file_list->empty())
    {
        ::MessageBox(   NULL,
                        _T("Usage: aescrypt32 [/d|/e] filename ..."),
                        MAKEINTRESOURCE(IDS_APP_TITLE),
                        MB_ICONERROR | MB_OK);
        SendMessage(hWnd, WM_DESTROY, 0, 0);
    }
    else
    {
        // Initiate file processing
        ProcessFiles(file_list, encrypt);
        
        // The file list will be consumed and freed by the worker thread
        // ultimately processes the list of files.
        file_list = NULL;
    }

    while(true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                break;
            }
        }
        else
        {
            // If the AES library is busy, we will sleep.  Otherwise
            // we will send a WM_DESTROY message to terminate the main
            // window processing loop.
            if (AESLibBusy())
            {
                Sleep(200);
            }
            else
            {
                SendMessage(hWnd, WM_DESTROY, 0, 0);
            }
        }
    }

    // Free allocated memory
    LocalFree(szArglist);
    if (file_list != NULL)
    {
        delete file_list;
    }

    return (int) msg.wParam;
}

