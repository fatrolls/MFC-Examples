// MRCEXT: Micro Focus Extension DLL for MFC 2.1+
// Copyright (C)1994-5	Micro Focus Inc, 2465 East Bayshore Rd, Palo Alto, CA 94303.
// 
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation. In addition, you may also charge for any
//  application	using MRCEXT, and are under no obligation to supply source
//  code. You must accredit Micro Focus Inc in the "About Box", or banner
//  of your application. 
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should also have received a copy of the GNU General Public License with this
//  software, also indicating additional rights you have when using MRCEXT.  
//
//
// clrlabel.cpp : implementation file
// $Revision:   1.7  $
// $Date:   29 Oct 1997 16:17:28  $
// $Author:   RES  $
//
// CMRCColorLabel class
//
// This is meant to be a general purpose control (similar to CStatic) that can display either
//  	i) colored text in a specified font
//  or ii) a bitmap (including 256-color bitmaps) 
//
// It can either be contructed direct from C API calls, resource loads, etc with the class
// name "CMRCColorLabel", or from MFC CWnd::Create,CreateEx functions. 

#include "mrcstafx.h"     



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMRCColorLabel

// Custom control style code..
extern "C"
{
LRESULT CALLBACK CMRCColorLabelWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
}
 
BOOL CMRCColorLabel::m_bRegistered = Register();

#define CMRCColorLabel_WNDCLASS 	_T("CMRCColorLabel")		// name of the registered windows class
#define TIMER_KILLWINDOW			1000
 
//-----------------------------------------------------------------------------
BOOL CMRCColorLabel::Register()
//-----------------------------------------------------------------------------
{
    // Register the window class of the control.
    WNDCLASS wc;
    wc.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = CMRCColorLabelWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = NULL;
    wc.hIcon = NULL;
    wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = CMRCColorLabel_WNDCLASS;
    if (!::RegisterClass(&wc))
    {
        ASSERT(0);
        return FALSE;
    } 
    return TRUE;
}


//-----------------------------------------------------------------------------
LRESULT CALLBACK CMRCColorLabelWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam,
                               LPARAM lParam)
//-----------------------------------------------------------------------------
{
    switch (uiMsg)
    {
    	case WM_NCCREATE:
   		{
        	// Create a C++ object to handle the messages.
        	if (CWnd::FromHandlePermanent(hWnd) != NULL)	
        		return TRUE;		// window already has an MFC window (ie was created via CWnd)
        	CMRCColorLabel * pCtl = new CMRCColorLabel;
        	ASSERT(pCtl);
        	// Attach the window handle to the new object.
        	BOOL b = pCtl->SubclassWindow(hWnd);
        	ASSERT(b);
        	return b;
        }
         	break;

    	default:
        	return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
    }
}


//-----------------------------------------------------------------------------
WNDPROC* CMRCColorLabel::GetSuperWndProcAddr()
// Provide a place for MFC's subclassing mechanism to store the super-class pointer.
//-----------------------------------------------------------------------------
{
    static WNDPROC NEAR pfnSuper = NULL;
    return &pfnSuper;
}


//-----------------------------------------------------------------------------
void CMRCColorLabel::OnNcDestroy()
//-----------------------------------------------------------------------------
{
    CWnd::OnNcDestroy();
    // Make sure the window was destroyed.
    ASSERT(m_hWnd == NULL);
    // Destroy this object because it won't be destroyed otherwise.
    delete this;
}


//-----------------------------------------------------------------------------
CMRCColorLabel::CMRCColorLabel()
//-----------------------------------------------------------------------------
{
	m_foreground = RGB(0,0,0);		  // default to BLACK on WHITE
	m_background = RGB(255,255,255); 
	m_pFont = NULL;
	m_pDib = NULL;
	m_pDibPal = NULL;
}


//-----------------------------------------------------------------------------
CMRCColorLabel::~CMRCColorLabel()
//-----------------------------------------------------------------------------
{
	delete m_pDib;
	delete m_pDibPal;
}


//-----------------------------------------------------------------------------
void CMRCColorLabel::SetColors(COLORREF foreground, COLORREF background)
//-----------------------------------------------------------------------------
{
	m_foreground = foreground;
	m_background = background;
	InvalidateRect(NULL);
}


//-----------------------------------------------------------------------------
void CMRCColorLabel::SetFont(CFont * pFont)
//-----------------------------------------------------------------------------
{
	m_pFont = pFont;    
	InvalidateRect(NULL);
}


BEGIN_MESSAGE_MAP(CMRCColorLabel, CWnd)
	//{{AFX_MSG_MAP(CMRCColorLabel)
	ON_WM_PAINT()
	ON_WM_NCDESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CMRCColorLabel message handlers

//-----------------------------------------------------------------------------
void CMRCColorLabel::DoPaint(CDC * pDC)
//-----------------------------------------------------------------------------
{
	
	CString str;
	CFont * pOldFont = NULL;
	CRect rect;

	GetClientRect(&rect);
	int style = GetStyle();
	
	// draw fake border round the window. 
	if (style & CLBS_BORDER_RAISED)
	{
		::DrawBorderRaisedOuter(pDC, &rect);
		::DrawBorderRaisedInner(pDC, &rect);
	}
	else
		if (style & CLBS_BORDER_SUNKEN)
		{
			::DrawBorderSunkenOuter(pDC, &rect);
			::DrawBorderSunkenInner(pDC, &rect);
		}


	if (style & CLBS_BITMAP)		// is it a bitmap ?
	{
		if (m_pDib != NULL)
		{
			CPoint pt;
			CPalette * pOldPal = NULL;
    		if (m_pDibPal != NULL) 		// if there's a palette, realize it
			{						   
    			pOldPal = pDC->SelectPalette(m_pDibPal, FALSE);
    			pDC->RealizePalette();
			}
		
			if (style & CLBS_CENTER)
			{
				pt.x = (rect.right + rect.left - m_pDib->DibWidth()) / 2;
				pt.y = (rect.bottom + rect.top - m_pDib->DibHeight()) / 2;
			}
			else		// draw top left
			{
				pt.x = rect.left;
				pt.y = rect.top;
			}

			if (style & CLBS_BITMAP_STRETCH)
				m_pDib->Draw(pDC, 0, 0, rect.right, rect.bottom);
			else
				m_pDib->Draw(pDC, pt.x, pt.y);
			
			if (pOldPal != NULL) 
				pDC->SelectPalette(pOldPal, FALSE);
 	 	}
	}
	else		
	{		// it's just text
		UINT DrawStyle = DT_WORDBREAK; 
		if (style & CLBS_CENTER)   
			DrawStyle = DT_SINGLELINE | DT_CENTER | DT_VCENTER;
	
		pDC->SetTextColor(m_foreground);
	// If we've filled the background, just draw the text opaque
		if (style & CLBS_FILLBACKGROUND)
			pDC->SetBkMode(TRANSPARENT);
		else
			pDC->SetBkColor(m_background);
	
		if (m_pFont != NULL)
			pOldFont = pDC->SelectObject(m_pFont);
		else 
			pOldFont = pDC->SelectObject(GetParent()->GetFont());
	
		GetWindowText(str);
		pDC->DrawText(str, str.GetLength(), &rect, DrawStyle);		
		if (pOldFont)
			pDC->SelectObject(pOldFont);
	}
}


//-----------------------------------------------------------------------------
void CMRCColorLabel::OnPaint() 
//-----------------------------------------------------------------------------
{
	CPaintDC dc(this); // device context for painting
	DoPaint(&dc);
}



//---------------------------------------------------------------------------------
BOOL CMRCColorLabel::OnEraseBkgnd(CDC* pDC) 
//---------------------------------------------------------------------------------
{
	int style = GetStyle();
	// explicitly fill the background with the background brush
	// if style no specified then the window will not draw into the background
	if (style & CLBS_FILLBACKGROUND)
	{
		CRect rect;
		pDC->GetClipBox(&rect);
		CBrush brush(m_background);
		pDC->FillRect(&rect, &brush);
		return TRUE;
	}
	else
		return TRUE;
}


//---------------------------------------------------------------------------------
BOOL CMRCColorLabel::LoadDIB(LPCTSTR lpszResource, DWORD dwStyle)
// Loads a bitmap and creates a palette for it
//---------------------------------------------------------------------------------
{
	// delete old dib's/palettes
	delete m_pDib;			
	delete m_pDibPal;
	m_pDibPal = NULL;

	m_pDib = new CMRCDib;
	if ( !m_pDib->LoadFromResource(lpszResource))
	{
		delete m_pDib;
		m_pDib = NULL;
		return FALSE;
	}
	return SetDibInfo(dwStyle);
}	


//---------------------------------------------------------------------------------
BOOL CMRCColorLabel::LoadDIBFromFile(LPCTSTR lpszFile, DWORD dwStyle)
// Loads a bitmap and creates a palette for it
//---------------------------------------------------------------------------------
{
	m_pDib = new CMRCDib;
	if ( !m_pDib->LoadFileName(lpszFile))
	{
		delete m_pDib;
		m_pDib = NULL;
		return FALSE;
	}
	return SetDibInfo(dwStyle);
}	


//---------------------------------------------------------------------------------
BOOL CMRCColorLabel::SetDibInfo(DWORD dwStyle)
// helper function to cope after a dib has been loaded
//---------------------------------------------------------------------------------
{
	DWORD style = GetStyle();
	if (dwStyle != 0x70000000) 		// if new style specified, attempt to changed it
	{
		style &= ~(CLBS_BITMAP_STYLES);
		style |= dwStyle;
	}
	style |= CLBS_BITMAP;		// make sure it's a bitmap
	::SetWindowLong(m_hWnd, GWL_STYLE, style);		// set the window style
	
	// if palette required, load it
	if (style & CLBS_BITMAP_PALETTE)	
	{	
		m_pDibPal = new CMRCDibPal;
		if (!m_pDibPal->Create(m_pDib))
		{
			delete m_pDibPal;
			m_pDibPal = NULL;
			return FALSE;
		}
	}
	
	// check for auto sizing
	if (style & CLBS_BITMAP_AUTOSIZE)
	{
		ASSERT((style & CLBS_BITMAP_STRETCH) == 0);	// can't stretch and auto size !

		CRect rect;
		CWnd * pParentWnd = GetParent();
		CSize size(m_pDib->DibWidth(), m_pDib->DibHeight());
		UINT SWPflags;
		// centering means we actually move the window to where we think it should be
		if (style & CLBS_CENTER && pParentWnd)
		{
			pParentWnd->GetClientRect(rect);
			rect.left = (rect.Width() - size.cx ) / 2;
			rect.top  = (rect.Height() - size.cy ) / 2;
			SWPflags = SWP_NOZORDER;
		}
		else
			SWPflags = SWP_NOZORDER | SWP_NOMOVE;

		SetWindowPos(NULL, rect.left, rect.top, size.cx, size.cy, SWPflags);
	}
	return TRUE;
}


//-----------------------------------------------------------------------------------
int CMRCColorLabel::OnCreate(LPCREATESTRUCT lpCS) 
//-----------------------------------------------------------------------------------
{
	if (CWnd::OnCreate(lpCS) == -1)
		return -1;
	
	// check to see if user has asked us to load a bitmap from the ID.
	if (lpCS->style & CLBS_BITMAP_FROMTITLE)
	{
		ASSERT((lpCS->style & CLBS_BITMAP_FROMID) == 0);		// invalid combination of styles

		int nResourceID = atoi(lpCS->lpszName);
		BOOL status;
		if (nResourceID == 0)
			status = LoadDIB(lpCS->lpszName);
		else
			status = LoadDIB(nResourceID);
		if (status == FALSE)
		{
			TRACE("CMRCColorLabel: Failed to load bitmap via caption: \"%s\"\n", lpCS->lpszName);
			return -1;
		}
	}		
	else
		if (lpCS->style & CLBS_BITMAP_FROMID)
		{
			if (!LoadDIB((UINT)lpCS->hMenu))
			{
				TRACE("CMRCColorLabel: Failed to load bitmap via ID: %d\n", (int)lpCS->hMenu);
				return -1;
			}
		}
	return 0;
}


//---------------------------------------------------------------------------------
BOOL CMRCColorLabel::CreateSplashTimed(LPCTSTR lpszResource, DWORD dwStyle, BOOL bBorder, int nSecs)
//---------------------------------------------------------------------------------
{
	dwStyle |= WS_POPUP | CLBS_CENTER;
	if (bBorder)
		dwStyle |= CLBS_BORDER_RAISED | CLBS_FILLBACKGROUND;

    DWORD dwExStyle = WS_EX_TOOLWINDOW; 
#ifndef _DEBUG	
	if (nSecs != -1)
		dwExStyle |= WS_EX_TOPMOST;
#endif
	if (!CreateEx(dwExStyle,
	 		 CMRCColorLabel_WNDCLASS, NULL,
			 dwStyle,
			 0, 0, 0, 0, NULL, 0))
	{
		TRACE("CMRCColorLabel:CreateSplashTimed failed\n");
		return FALSE;
	}
	// now load the bitmap...
	if (!LoadDIB(lpszResource, dwStyle))
	{
		DestroyWindow();
	 	TRACE("CMRCColorLabel:CreateSplash failed to load bitmap\n");
		return FALSE;
	}
	
    ASSERT(m_pDib != NULL);

	// position in center and force drawing.
	CRect deskrect;

	int winHt, winWd, winx, winy;
	winHt = m_pDib->DibHeight();
	winWd = m_pDib->DibWidth();
	if (bBorder)
	{
		m_background = GetSysColor(COLOR_BTNFACE);
		winHt += 7;
		winWd += 7;
	}

	// did try using the correct system metrics, but Microsoft forgot to define them...
	// winx = ((GetSystemMetric(SM_CXWORKAREA) - winWd ) / 2) + GetSystemMetric(SM_XWORKAREA);
	// winy = ((GetSystemMetric(SM_CYWORKAREA) - winHt ) / 2) + GetSystemMetric(SM_YWORKAREA);
	// so use API code instead...
	::GetWindowRect(::GetDesktopWindow(), &deskrect);
	winx = ((deskrect.right - winWd ) / 2) ;
	winy = ((deskrect.bottom - winHt ) / 2) ;

	SetWindowPos(NULL, winx, winy, winWd, winHt, SWP_SHOWWINDOW); 
	
	InvalidateRect(NULL, FALSE);		// force paint of window
	UpdateWindow();
	if (nSecs != -1)
		SetTimer(TIMER_KILLWINDOW, nSecs, NULL);			// show for 1 second after app appears... 
	return TRUE;
}


//---------------------------------------------------------------------------------
BOOL CMRCColorLabel::CreateSplash(LPCTSTR lpszResource, DWORD dwStyle, BOOL bBorder)
// Creates a TOPMOST, visible window, centred in the display - really meant as a 
// splash screen. 
//---------------------------------------------------------------------------------
{
	return CreateSplashTimed(lpszResource, dwStyle, bBorder, -1);
}  

//---------------------------------------------------------------------------------
BOOL CMRCColorLabel::Create(LPCTSTR lpszWindowName, DWORD dwStyle, RECT & rect,
						 CWnd *pParentWnd, UINT nID)
//---------------------------------------------------------------------------------
{
	// add these to get the total border for the window....
	return (CWnd::Create(CMRCColorLabel_WNDCLASS, lpszWindowName, dwStyle,
					 		rect, pParentWnd, nID));
}


//---------------------------------------------------------------------------------
void CMRCColorLabel::OnTimer(UINT nIDEvent)
//---------------------------------------------------------------------------------
{
	if (nIDEvent == TIMER_KILLWINDOW)
	{
		KillTimer(nIDEvent);
		DestroyWindow();
	}
}

// Borrowed from MFCUSEFL.cpp

// widths/heights of rectangle borders. Probably will always be 1, but you never know
#define bheight 1
#define bwidth  1

//-----------------------------------------------------------------------------------------
void DrawBorderSunkenInner(CDC *pDC, RECT * prect)
//-----------------------------------------------------------------------------------------
{
	DrawRectBorder(pDC, prect, ::GetSysColor(COLOR_WINDOWFRAME), ::GetSysColor(COLOR_BTNFACE));
}

//-----------------------------------------------------------------------------------------
void DrawBorderSunkenOuter(CDC *pDC, RECT * prect)
//-----------------------------------------------------------------------------------------
{
	DrawRectBorder(pDC, prect, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHIGHLIGHT));
}

//-----------------------------------------------------------------------------------------
void DrawBorderRaisedInner(CDC *pDC, RECT * prect)
//-----------------------------------------------------------------------------------------
{
	DrawRectBorder(pDC, prect, ::GetSysColor(COLOR_BTNHIGHLIGHT), ::GetSysColor(COLOR_BTNSHADOW));
}

//-----------------------------------------------------------------------------------------
void DrawBorderRaisedOuter(CDC *pDC, RECT * prect)
//-----------------------------------------------------------------------------------------
{
	DrawRectBorder(pDC, prect, ::GetSysColor(COLOR_BTNFACE), ::GetSysColor(COLOR_WINDOWFRAME));
}

//-----------------------------------------------------------------------------------------
void DrawRectBorder(CDC *pDC, RECT *prect, COLORREF crTopLeft, COLORREF crBottomRight)
// draws a rectangle. Top & Right edges drawn with one brush, Bottom & Left edges drawn
// with another. Generic function used to give different border types, as described by
// Chicago style guide.
//-----------------------------------------------------------------------------------------
{
	RECT rect;
	CBrush TopLeftBrush (crTopLeft);  
	CBrush BottomRightBrush (crBottomRight);

// draw top side
	rect.top    = prect->top;
	rect.bottom = prect->top + bheight;
	rect.left   = prect->left;
	rect.right  = prect->right - bwidth;
	pDC->FillRect(&rect, &TopLeftBrush);	
	
// draw left side
	rect.top    = prect->top + bheight;
	rect.bottom = prect->bottom - bheight;
	rect.left   = prect->left;
	rect.right  = prect->left + bwidth;
	pDC->FillRect(&rect, &TopLeftBrush);	
		
// draw right side
	rect.top    = prect->top;
	rect.bottom = prect->bottom - bheight;
	rect.left   = prect->right - bwidth;
	rect.right  = prect->right;
	pDC->FillRect(&rect, &BottomRightBrush);	
	
// draw bottom side
	rect.top    = prect->bottom - bheight;
	rect.bottom = prect->bottom;
	rect.left   = prect->left;
	rect.right  = prect->right;
	pDC->FillRect(&rect, &BottomRightBrush);	

// shrink the rectangle
	prect->top += bheight;
	prect->bottom -= bheight;
	prect->left += bwidth;
	prect->right -= bwidth;
}




//-----------------------------------------------------------------------------------
int GetNumberSystemColors()	
// Returns color capability of the screen. Used to distinguish 16/256 color displays. 
//-----------------------------------------------------------------------------------
{
	static NumColors = 0;

	if (NumColors == 0)
	{		
	// Get number of colors screen DC can display - this is only done once
		HDC hdc = ::GetDC(NULL);
		int nBits = ::GetDeviceCaps(hdc, BITSPIXEL );
        // SJR FIX: for true color mode (nBits = 32), bit shift below returns 1, switching 
        // caller into 16 colour mode
        if (nBits == 32)
            nBits -= 2;  // -1 gives negative, we are using an int
		NumColors = 1 << nBits;
		::ReleaseDC(NULL,hdc);
	}
	return(NumColors);
}



//-----------------------------------------------------------------------------------
BOOL CMRCColorLabel::OnQueryNewPalette() 
//-----------------------------------------------------------------------------------
// Get the palette realized and redrawn, note this won'y be called unless we're a top
// level window, otherwise the dialog box we're on will have to call it manually
{
	Invalidate(FALSE);
	UpdateWindow();
	return CWnd::OnQueryNewPalette();
}
