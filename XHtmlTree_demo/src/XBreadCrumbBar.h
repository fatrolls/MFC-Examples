// XBreadCrumbBar.h  Version 1.0 - article available at www.codeproject.com
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
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

#ifndef XBREADCRUMBBAR_H
#define XBREADCRUMBBAR_H

#include "XHtmlDraw.h"
#include "XHtmlDrawLink.h"

//=============================================================================
class CXBreadCrumbBar : public CXHtmlDraw
//=============================================================================
{
//=============================================================================
// Construction
//=============================================================================
public:
	CXBreadCrumbBar();
	virtual ~CXBreadCrumbBar();

//=============================================================================
// Attributes
//=============================================================================
public:
	BOOL				GetBoldSeparator() { return m_bBoldSeparator; }
	int					GetCount() { return m_nCount; }
	XHTMLDRAWSTRUCT *	GetDrawStruct(int index);
	size_t				GetCrumb(int index, BOOL bStripHtml,
							LPTSTR pszCrumb, size_t size);
	int					GetCrumb(LPCTSTR lpszCrumb, BOOL bStripHtml);
	CXHtmlDrawLink *	GetLinks() { return &m_Links; }
	int					GetCrumbs(TCHAR *** crumbs);
	TCHAR *				GetSeparator() { return m_pszSeparator; }
	CXBreadCrumbBar&	InitDrawStruct(XHTMLDRAWSTRUCT * pXHDS, 
							BOOL bBoldSeparator = TRUE);
	CXBreadCrumbBar&	SetAppCommands(XHTMLDRAW_APP_COMMAND * paAppCommands, 
							int nAppCommands);
	CXBreadCrumbBar&	SetBoldSeparator(BOOL bBold) 
						{ m_bBoldSeparator = bBold; return *this; }
	CXBreadCrumbBar&	SetCrumbs(const TCHAR * crumbs[], int count);
	CXBreadCrumbBar&	SetCrumbs(LPCTSTR crumbs, TCHAR sepchar);
	CXBreadCrumbBar&	SetSeparator(LPCTSTR lpszSep);

//=============================================================================
// Operations
//=============================================================================
public:
	int		Draw(HWND hWnd, BOOL bUnderlineUrl, int index = -1);
	int		Draw(HDC hdc, BOOL bUnderlineUrl, int index = -1);
	int		IsAnchorUnderlined();
	int		IsOverAnchor(HWND hWnd);
	BOOL	RelayClick(HWND hWnd);
	void	RelayMouseMove(HWND hWnd);

//=============================================================================
// Implementation
//=============================================================================
protected:
	void	CleanUp();

	TCHAR **			m_crumbs;				// array of breadcrumbs
	int					m_nCount;				// no. of breadcrumbs
	TCHAR *				m_pszSeparator;			// separator string
	BOOL				m_bBoldSeparator;		// TRUE = separator will be bold 
												// if crumbs are bold
	RECT				m_rect;					// rect of entire CXBreadCrumbBar
	CXHtmlDrawLink		m_Links;				// links for web and APP:
	XHTMLDRAWSTRUCT *	m_pDS;					// array of draw structs
};

#endif //XBREADCRUMBBAR_H
