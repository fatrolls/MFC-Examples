// SingleInstanceApp.cpp : implementation file
//
// CWinApp with single-instance support
//
// Copyright (C) 1997, 1998 Giancarlo Iovino (giancarlo@saria.com)
// All rights reserved. May not be sold for profit.
//
// Thanks to Kevin Lussier for the base idea.
//
// This code was developed for MFC Programmers SourceBook
// (http://www.codeguru.com)
//

#include "stdafx.h"
#include "SingleInstanceApp.h"

CSingleInstanceApp::CSingleInstanceApp()
{
	// Set our default values
	m_hMutex = NULL;
}

CSingleInstanceApp::~CSingleInstanceApp()
{
	// Release the mutex
	if ( m_hMutex != NULL ) {
		ReleaseMutex( m_hMutex );
	}
}

BOOL CSingleInstanceApp::CheckSingleInstance(UINT nID) {
	CString strFullString;

	// Generate a synthetic name for this class using the
	// AfxRegisterWndClass convention
	HINSTANCE hInst = AfxGetInstanceHandle();
	UINT nClassStyle = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;	
	HCURSOR hCursor = LoadCursor(IDC_ARROW );
	HICON	hIcon = LoadIcon(MAKEINTRESOURCE( nID ) );
	HBRUSH hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);

	LPCTSTR lpstrAppName = AfxGetAppName();
	ASSERT(lpstrAppName != NULL);

	if (hCursor == NULL && hbrBackground == NULL && hIcon == NULL)
		m_strClassName.Format(_T("%s:%x:%x"), lpstrAppName,
			(UINT)hInst, nClassStyle);
	else
		m_strClassName.Format(_T("%s:%x:%x:%x:%x"), lpstrAppName,
			(UINT)hInst, nClassStyle, (UINT)hCursor, (UINT)hbrBackground);
	
	// Create the mutex with the class name
	m_hMutex = CreateMutex(NULL, FALSE, m_strClassName);
	// Check for errors
	if ( GetLastError() == ERROR_ALREADY_EXISTS ) {
		// Reset our mutex handle (just in case)
		m_hMutex = NULL;
		// The mutex already exists: an instance is already
		// running. Find the app window and bring it to foreground
		HWND hWnd = FindWindowEx(NULL, NULL, m_strClassName, NULL);
		if ( hWnd != NULL ) {
			ShowWindow( hWnd, SW_RESTORE );
			BringWindowToTop( hWnd );
			SetForegroundWindow( hWnd );
		}
	
		// Return failure
		return FALSE;
	}

	// Register the unique window class name
	WNDCLASS wndclass;	
	ZeroMemory(&wndclass, sizeof(WNDCLASS));

	wndclass.style = nClassStyle;
	wndclass.lpfnWndProc = AfxWndProc;
	wndclass.hInstance = hInst;
	wndclass.hIcon = hIcon; 
	wndclass.hCursor = hCursor;
	wndclass.hbrBackground = hbrBackground;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = m_strClassName; // The class name
	
	// Use AfxRegisterClass to register the class, exit if it fails
	if(!AfxRegisterClass(&wndclass)) {
		AfxMessageBox( _T("Failed to register window class!"), MB_ICONSTOP | MB_OK );
		// Return failure
		return FALSE;
	}

	// Return success
	return TRUE;
}

CString CSingleInstanceApp::GetClassName() const
{
	return m_strClassName;
}
