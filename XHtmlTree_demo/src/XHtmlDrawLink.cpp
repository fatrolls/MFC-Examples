// XHtmlDrawLink.cpp  Version 1.2 - article available at www.codeproject.com
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// History
//     Version 1.2 - 2007 November 6
//
//     Version 1.1 - 2007 August 8
//     - Changed SetAppCommands() to delete pszCommand buffer
//
//     Version 1.0 - 2007 July 15
//     - Initial public release
//
// License:
//     This software is released into the public domain.  You are free to use
//     it in any way you like, except that you may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this 
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

// NOTE ABOUT PRECOMPILED HEADERS:
// This file does not need to be compiled with precompiled headers (.pch).
// To disable this, go to Project | Settings | C/C++ | Precompiled Headers
// and select "Not using precompiled headers".  Be sure to do this for all
// build configurations.
//#include "stdafx.h"

#include <windows.h>
#include <tchar.h>
#include <crtdbg.h>
#include "XHtmlDrawLink.h"
#include "XString.h"

#ifndef __noop
#if _MSC_VER < 1300
#define __noop ((void)0)
#endif
#endif

#undef TRACE
#define TRACE __noop

// if you want to see the TRACE output, 
// uncomment this line:
//#include "XTrace.h"

#pragma warning(disable : 4127)	// for _ASSERTE: conditional expression is constant
#pragma warning(disable : 4996)	// disable bogus deprecation warning

typedef CXHtmlDraw::XHTMLDRAW_APP_COMMAND AppCommand;


///////////////////////////////////////////////////////////////////////////////
// ctor
CXHtmlDrawLink::CXHtmlDrawLink()
  : m_nAppCommands(0),
	m_paAppCommands(0),
	m_hLinkCursor(0)
{
	SetDefaultCursor();		// Try and load up a "hand" cursor
}

///////////////////////////////////////////////////////////////////////////////
// dtor
CXHtmlDrawLink::~CXHtmlDrawLink()
{
	if (m_paAppCommands && m_nAppCommands)
	{
		for (int i = 0; i < m_nAppCommands; i++)
		{
			if (m_paAppCommands[i].pszCommand)
				delete [] m_paAppCommands[i].pszCommand;
			m_paAppCommands[i].pszCommand = NULL;
		}
	}

	if (m_paAppCommands)
		delete [] m_paAppCommands;
	m_paAppCommands = NULL;

	m_nAppCommands = 0;

	if (m_hLinkCursor)
		DestroyCursor(m_hLinkCursor);
	m_hLinkCursor = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// GoToURL
BOOL CXHtmlDrawLink::GotoURL(LPCTSTR url, int showcmd, LPARAM lParam)
{
	TRACE(_T("in CXHtmlDrawLink::GotoURL\n"));

	BOOL bRet = FALSE;

	if (url && (url[0] != _T('\0')))
	{
		// check if this is "app:" protocol	
		int nAppSize = 0;
		if (_tcsnicmp(url, _T("APP:"), 4) == 0)
			nAppSize = 4;
		else if (_tcsnicmp(url, _T("\"APP:"), 5) == 0)
			nAppSize = 5;
		if (nAppSize)
		{
			bRet = ProcessAppCommand(&url[nAppSize], lParam);
		}
		else
		{
			// not "app" - assume http: or mailto:

			// First try ShellExecute()
			HINSTANCE result = ::ShellExecute(NULL, _T("open"), url, NULL,NULL, showcmd);

			// If it failed, get the .htm regkey and lookup the program
			if (result <= (HINSTANCE)HINSTANCE_ERROR) 
			{
				TCHAR key[MAX_PATH * 2] = { _T('\0') };

				if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS) 
				{
					_tcscat(key, _T("\\shell\\open\\command"));

					if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS) 
					{
						TCHAR *pos = _tcsstr(key, _T("\"%1\""));
						if (pos == NULL) 
							pos = _tcsstr(key, _T("%1"));	// Check for %1, without quotes 

						if (pos == NULL)					// No parameter at all...
							pos = key + lstrlen(key) - 1;
						else
							*pos = _T('\0');				// Remove the parameter
						
						_tcscat(pos, _T(" "));
						_tcscat(pos, url);
						result = (HINSTANCE)(UINT_PTR) WinExec((LPSTR)key, showcmd);
					}
				}
			}

			bRet = result > (HINSTANCE) HINSTANCE_ERROR;
		}
	}

	return bRet;
}

///////////////////////////////////////////////////////////////////////////////
// ProcessAppCommand
BOOL CXHtmlDrawLink::ProcessAppCommand(LPCTSTR lpszCommand, LPARAM lParam)
{
	TRACE(_T("in CXHtmlDrawLink::ProcessAppCommand:  %s  %d\n"), lpszCommand, lParam);

	BOOL bRet = FALSE;

	_ASSERTE(lpszCommand);

	if (lpszCommand)
	{
		size_t nLen = _tcslen(lpszCommand);
		TCHAR * pszCmd = new TCHAR [nLen + 2];
		memset(pszCmd, 0, sizeof(TCHAR)*(nLen + 2));
		_tcsncpy(pszCmd, lpszCommand, nLen);

		TCHAR *cp = pszCmd;

		if (cp[0] == _T('"'))
			cp++;

		nLen = _tcslen(cp);
		if (nLen > 0)
		{
			nLen--;		// last char index

			if (cp[nLen] == _T('"'))
				cp[nLen] = _T('\0');

			if ((m_nAppCommands > 0) && (m_paAppCommands != NULL))
			{
				for (int i = 0; i < m_nAppCommands; i++)
				{
					if (_tcsicmp(m_paAppCommands[i].pszCommand, cp) == 0)
					{
						TRACE(_T("found app command %s\n"), cp);
						if (m_paAppCommands[i].hWnd &&
							::IsWindow(m_paAppCommands[i].hWnd))
						{
							TRACE(_T("sending app command message\n"));
							::SendMessage(m_paAppCommands[i].hWnd, 
										  m_paAppCommands[i].uMessage, 
										  m_paAppCommands[i].wParam,
										  lParam);
							bRet = TRUE;
							break;
						}
					}
				}
			}
		}
		if (pszCmd)
			delete [] pszCmd;
	}

	return bRet;
}

///////////////////////////////////////////////////////////////////////////////
// SetAppCommands
void CXHtmlDrawLink::SetAppCommands(AppCommand * paAppCommands, 
									int nAppCommands)
{
	if (m_paAppCommands && m_nAppCommands)
	{
		for (int i = 0; i < m_nAppCommands; i++)
		{
			if (m_paAppCommands[i].pszCommand)
				delete [] m_paAppCommands[i].pszCommand;
			m_paAppCommands[i].pszCommand = NULL;
		}
	}

	if (m_paAppCommands)
		delete [] m_paAppCommands;

	m_paAppCommands = NULL;
	m_nAppCommands = 0;

	if (paAppCommands && (nAppCommands > 0))
	{
		m_paAppCommands = new AppCommand [nAppCommands];
		_ASSERTE(m_paAppCommands);

		for (int i = 0; i < nAppCommands; i++)
		{
			m_paAppCommands[i].hWnd       = paAppCommands[i].hWnd;
			m_paAppCommands[i].uMessage   = paAppCommands[i].uMessage;
			m_paAppCommands[i].wParam     = paAppCommands[i].wParam;
			m_paAppCommands[i].pszCommand = NULL;

			if (paAppCommands[i].pszCommand)
				m_paAppCommands[i].pszCommand = 
					_tcszdup(paAppCommands[i].pszCommand);
		}

		m_nAppCommands = nAppCommands;
	}
}

///////////////////////////////////////////////////////////////////////////////
// GetRegKey
LONG CXHtmlDrawLink::GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR lpData)
{
	HKEY hkey;
	LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);
	
	*lpData = 0;

	if (retval == ERROR_SUCCESS) 
	{
		long datasize = MAX_PATH;
		TCHAR data[MAX_PATH] = { 0 };
		retval = RegQueryValue(hkey, NULL, data, &datasize);
		if (retval == ERROR_SUCCESS) 
		{
			lstrcpy(lpData, data);
			RegCloseKey(hkey);
		}
	}
	
	return retval;
}

///////////////////////////////////////////////////////////////////////////////
// SetDefaultCursor
void CXHtmlDrawLink::SetDefaultCursor()
{
	if (m_hLinkCursor == NULL)			// No cursor handle - try to load one
	{
		// First try to load the Win98 / Windows 2000 hand cursor

		TRACE(_T("loading from IDC_HAND\n"));
		m_hLinkCursor = ::LoadCursor(NULL, IDC_HAND);

		if (m_hLinkCursor == NULL)			// Still no cursor handle - 
											// load the WinHelp hand cursor
		{
			// The following appeared in Paul DiLascia's Jan 1998 MSJ articles.
			// It loads a "hand" cursor from the winhlp32.exe module.

			TRACE(_T("loading from winhlp32\n"));

			// Get the windows directory
			TCHAR szWinDir[MAX_PATH*2] = { _T('\0') };
			GetWindowsDirectory(szWinDir, MAX_PATH*2-2);

			_tcscat(szWinDir, _T("\\winhlp32.exe"));

			// This retrieves cursor #106 from winhlp32.exe, which is a hand pointer
			HMODULE hModule = LoadLibrary(szWinDir);
			if (hModule) 
			{
				HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
				if (hHandCursor)
					m_hLinkCursor = CopyCursor(hHandCursor);
				FreeLibrary(hModule);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// SetLinkCursor
BOOL CXHtmlDrawLink::SetLinkCursor()
{
	if (m_hLinkCursor)
	{
		::SetCursor(m_hLinkCursor);
		return TRUE;
	}
	return FALSE;
}
