// XBreadCrumbBar.cpp  Version 1.0 - article available at www.codeproject.com
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// History
//     Version 1.0 - 2007 August 7
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
#include "XString.h"
#include "XBreadCrumbBar.h"

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

#if 0  // -----------------------------------------------------------
#ifdef _DEBUG
void* operator new(size_t nSize, LPCSTR lpszFileName, int nLine);
#define DEBUG_NEW new(THIS_FILE, __LINE__)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif // -----------------------------------------------------------

#pragma warning(disable : 4127)	// for _ASSERTE: conditional expression is constant
#pragma warning(disable : 4291)	// no matching operator delete found
#pragma warning(disable : 4996)	// disable bogus deprecation warning

//=============================================================================
CXBreadCrumbBar::CXBreadCrumbBar() : CXHtmlDraw()
//=============================================================================
{
	m_pszSeparator = new TCHAR [16];
	_tcscpy(m_pszSeparator, _T(" >> "));
	m_pDS = 0;
	m_crumbs = 0;
	m_bBoldSeparator = TRUE;
}

//=============================================================================
CXBreadCrumbBar::~CXBreadCrumbBar()
//=============================================================================
{
	CleanUp();
	if (m_pszSeparator)
		delete [] m_pszSeparator;
	m_pszSeparator = 0;
}

//=============================================================================
void CXBreadCrumbBar::CleanUp()
//=============================================================================
{
	if (m_crumbs)
	{
		for (int i = 0; i < m_nCount; i++)
		{
			TCHAR *p = m_crumbs[i];
			if (p)
				delete [] p;
			m_crumbs[i] = 0;
		}
		delete [] m_crumbs;
	}
	m_nCount = 0;

	if (m_pDS)
		delete [] m_pDS;
	m_pDS = 0;
}

//=============================================================================
CXBreadCrumbBar& CXBreadCrumbBar::InitDrawStruct(XHTMLDRAWSTRUCT * pXHDS,
												 BOOL bBoldSeparator /*= TRUE*/)
//=============================================================================
{
	if (m_pDS)
	{
		for (int i = 0; i < m_nCount; i++)
		{
			m_pDS[i] = *pXHDS;
		}

		m_rect = pXHDS->rect;

		m_bBoldSeparator = bBoldSeparator;
	}

	return *this;
}

//=============================================================================
int CXBreadCrumbBar::Draw(HWND hWnd, BOOL bUnderlineUrl, int index /*= -1*/)
//=============================================================================
{
	int rc = 0;

	HDC hDC = GetDC(hWnd);
	if (hDC)
	{
		rc = Draw(hDC, bUnderlineUrl, index);
		ReleaseDC(hWnd, hDC);
	}

	return rc;
}

//=============================================================================
int CXBreadCrumbBar::Draw(HDC hdc, BOOL bUnderlineUrl, int index /*= -1*/)
//=============================================================================
{
	int rc = 0;

	if (!m_pDS)
		return 0;

	XHTMLDRAWSTRUCT ds;

	TCHAR * crumb = 0;

	if (index == -1)
	{
		// draw all
		for (int i = 0; i < m_nCount; i++)
		{
			if (i > 0)
			{
				// draw separator
				ds = m_pDS[i-1];
				ds.rect.left = m_pDS[i-1].nRightX + 1;
				ds.rect.right = m_rect.right;
				if (!m_bBoldSeparator)
					ds.bBold = FALSE;
				CXHtmlDraw::Draw(hdc, m_pszSeparator, &ds, FALSE);
				if ((ds.nRightX + 1) < m_rect.right)
					m_pDS[i].rect.left = ds.nRightX + 1;
			}

			// draw crumb
			crumb = m_crumbs[i];
			if (crumb)
				rc = CXHtmlDraw::Draw(hdc, crumb, &m_pDS[i], bUnderlineUrl);
			if ((m_pDS[i].nRightX + 1) < m_rect.right)
				m_pDS[i].rect.right = m_pDS[i].nRightX + 1;
		}
	}
	else
	{
		// only draw one crumb
		crumb = m_crumbs[index];
		if (crumb)
			rc = CXHtmlDraw::Draw(hdc, crumb, &m_pDS[index], bUnderlineUrl);
	}

	return rc;
}

//=============================================================================
CXBreadCrumbBar& CXBreadCrumbBar::SetSeparator(LPCTSTR lpszSep)
//=============================================================================
{
	_ASSERTE(lpszSep);

	if (lpszSep)
	{
		if (m_pszSeparator)
			delete [] m_pszSeparator;
		m_pszSeparator = _tcszdup(lpszSep);
	}

	return *this;
}

//=============================================================================
int CXBreadCrumbBar::GetCrumbs(TCHAR *** crumbs)
//=============================================================================
{
	int rc = 0;

	_ASSERTE(crumbs);

	if (crumbs)
	{
		*crumbs = m_crumbs;
		rc = m_nCount;
	}

	return rc;
}

//=============================================================================
CXBreadCrumbBar& CXBreadCrumbBar::SetCrumbs(const TCHAR * crumbs[], int count)
//=============================================================================
{
	_ASSERTE(crumbs);

	// delete everything
	CleanUp();

	if (crumbs && (count > 0))
	{
		// allocate memory for array of pointers
		m_crumbs = new TCHAR * [count];

		for (int i = 0; i < count; i++)
		{
			// allocate memory and copy crumb
			m_crumbs[i] = _tcszdup(crumbs[i]);
			TRACE(_T("m_crumbs[%d]=<%s>\n"), i, m_crumbs[i]);
		}

		m_nCount = count;

		m_pDS = new XHTMLDRAWSTRUCT [count];
	}

	return *this;
}

//=============================================================================
CXBreadCrumbBar& CXBreadCrumbBar::SetCrumbs(LPCTSTR crumbs, TCHAR sepchar)
//=============================================================================
{
	_ASSERTE(crumbs);

	TRACE("SetCrumbs: %s\n", crumbs);

	// delete everything
	CleanUp();

	if (crumbs)
	{
		int count = _tcsccnt(crumbs, sepchar) + 1;

		// allocate memory for array of pointers
		m_crumbs = new TCHAR * [count];

		const TCHAR *cp = crumbs;

		int i = 0;
		for (i = 0; i < count; i++)
		{
			if (*cp == _T('\0'))
				break;

			const TCHAR *next = _tcschr(cp, sepchar);

			if (!next)
				break;

			size_t len = next - cp;

			// allocate memory and copy crumb
			m_crumbs[i] = _tcsnzdup(cp, len);

			cp = next + 1;
		}

		// if anything left save it
		if (*cp && (i < count))
			m_crumbs[i] = _tcszdup(cp);

		m_nCount = count;

		m_pDS = new XHTMLDRAWSTRUCT [count];
	}

	return *this;
}

//=============================================================================
CXHtmlDraw::XHTMLDRAWSTRUCT * CXBreadCrumbBar::GetDrawStruct(int index)
//=============================================================================
{
	if (!m_pDS || (index < 0) || (index >= m_nCount))
		return 0;

	return &m_pDS[index];
}

//=============================================================================
size_t CXBreadCrumbBar::GetCrumb(int index, 
								 BOOL bStripHtml,
								 LPTSTR pszCrumb,
								 size_t size)		// in TCHARs
//=============================================================================
{
	size_t len = 0;

	if ((index >= 0) && (index < m_nCount))
	{
		TCHAR *cp = m_crumbs[index];
		len = _tcslen(cp);

		// if pszCrumb is NULL, just return length of crumb
		if (pszCrumb && (size != 0))
		{
			pszCrumb[0] = _T('\0');
			if (bStripHtml && (len > 3))		// minimum html string
			{
				TCHAR *s = new TCHAR [len + 16];
				CXHtmlDraw hd;
				hd.GetPlainText(cp, s, len+4);
				_tcsncpy(pszCrumb, s, size-1);
				delete [] s;
			}
			else
			{
				_tcsncpy(pszCrumb, cp, size-1);
			}
			pszCrumb[size-1] = _T('\0');
		}
	}

	return len;
}

//=============================================================================
int CXBreadCrumbBar::GetCrumb(LPCTSTR lpszCrumb, BOOL bStripHtml)
//=============================================================================
{
	_ASSERTE(lpszCrumb);

	int rc = -1;

	if (lpszCrumb)
	{
		CXHtmlDraw hd;

		for (int i = 0; i < m_nCount; i++)
		{
			TCHAR *crumb = m_crumbs[i];
			size_t len = _tcslen(crumb);
			TCHAR *s = _tcszdup(crumb);

			if (bStripHtml && (len > 3))		// minimum html string
				hd.GetPlainText(crumb, s, len+4);

			int ret = _tcsicmp(s, lpszCrumb);
			delete [] s;

			if (ret == 0)
			{
				rc = i;
				break;
			}
		}
	}

	return rc;
}

//=============================================================================
CXBreadCrumbBar& CXBreadCrumbBar::SetAppCommands(
							CXHtmlDraw::XHTMLDRAW_APP_COMMAND * paAppCommands, 
							int nAppCommands)
//=============================================================================
{
	m_Links.SetAppCommands(paAppCommands, nAppCommands);
	return *this;
}

//=============================================================================
int CXBreadCrumbBar::IsOverAnchor(HWND hWnd)
//=============================================================================
{
	int rc = -1;

	if (m_pDS)
	{
		for (int i = 0; i < m_nCount; i++)
		{
			if (CXHtmlDraw::IsOverAnchor(hWnd, &m_pDS[i]))
			{
				rc = i;
				break;
			}
		}
	}

	return rc;
}

//=============================================================================
int CXBreadCrumbBar::IsAnchorUnderlined()
//=============================================================================
{
	int rc = -1;

	if (m_pDS)
	{
		for (int i = 0; i < m_nCount; i++)
		{
			if (m_pDS[i].bAnchorIsUnderlined)
			{
				rc = i;
				break;
			}
		}
	}

	return rc;
}

//=============================================================================
BOOL CXBreadCrumbBar::RelayClick(HWND hWnd)
//=============================================================================
{
	BOOL rc = FALSE;

	if (m_pDS && hWnd && ::IsWindow(hWnd))
	{
		int index = IsOverAnchor(hWnd);

		if ((index >= 0) && (index < m_nCount))
		{
			XHTMLDRAWSTRUCT * pDS = &m_pDS[index];

			TRACE(_T("over crumb %d [%s]\n"), index, pDS->pszAnchor);

			if (pDS->pszAnchor)
			{
				HDC hDC = GetDC(hWnd);
				if (hDC)
				{
					Draw(hDC, FALSE, index);	// erase underline
					ReleaseDC(hWnd, hDC);
				}
				rc = m_Links.GotoURL(pDS->pszAnchor, SW_SHOW, pDS->nID);
			}
		}
	}

	return rc;
}

//=============================================================================
void CXBreadCrumbBar::RelayMouseMove(HWND hWnd)
//=============================================================================
{
	if (m_pDS && hWnd && ::IsWindow(hWnd))
	{
		int index_over = IsOverAnchor(hWnd);
		int index_underlined = IsAnchorUnderlined();

		if (index_over >= 0)
		{
			m_Links.SetLinkCursor();		// set cursor to hand

			// mouse is over a crumb
			if (index_underlined != index_over)
			{
				// mouse is over a different crumb
				if (index_underlined >= 0)
				{
					// remove any existing underlining
					Draw(hWnd, FALSE, index_underlined);
				}

				Draw(hWnd, TRUE, index_over);	// underline crumb
			}
		}
		else
		{
			// mouse is not over a crumb -- remove any existing underlining
			if (index_underlined >= 0)
				Draw(hWnd, FALSE, index_underlined);
		}
	}
}
