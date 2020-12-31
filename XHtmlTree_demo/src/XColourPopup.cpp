// XColourPopup.cpp : implementation file
//
// Written by Chris Maunder (chrismaunder@codeguru.com)
// Extended by Alexander Bischofberger (bischofb@informatik.tu-muenchen.de)
// Copyright (c) 1998.
//
// Updated 30 May 1998 to allow any number of colours, and to
//                     make the appearance closer to Office 97.
//                     Also added "Default" text area.         (CJM)
//
//         13 June 1998 Fixed change of focus bug (CJM)
//         30 June 1998 Fixed bug caused by focus bug fix (D'oh!!)
//                      Solution suggested by Paul Wilkerson.
//
// ColourPopup is a helper class for the colour picker control
// CColourPicker. Check out the header file or the accompanying
// HTML doc file for details.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is
// not sold for profit without the authors written consent, and
// providing that this notice and the authors name is included.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
//
// Expect bugs.
//
// Please use and enjoy. Please let me know of any bugs/mods/improvements
// that you have found/implemented and I will fix/incorporate them into this
// file.

#include "stdafx.h"
#include <math.h>
#include "XColourPicker.h"
#include "XColourPopup.h"
#include "windowsx.h"		// for GET_X_LPARAM

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DIVIDER_LINE_ROW	9
#define CUSTOM_BUTTON_ROW	10
#define FIRST_CUSTOM_ROW	11


///////////////////////////////////////////////////////////////////////////////
// The following builtin color table is extracted from the complete list of
// X11 colors that are supported by Internet Explorer and Netscape Navigator.
// To see the complete list of colors and color names, read the article by
// Robert Hess at
//        http://www.microsoft.com/workshop/design/color/colorname.asp

ColorTableEntry CXColourPopup::m_crColors[] =
{
	// row 0
	RGB(128,   0,  64), _T("Light Maroon"),        -1,
	RGB(139,   0,   0), _T("Dark Red"),            -1,
	RGB(255,   0,   0), _T("Red"),                 -1,
	RGB(255,   0, 128), _T("Deep Pink"),           -1,
	RGB(255,   0, 255), _T("Magenta"),             -1,
	RGB(255, 128, 192), _T("Pink"),                -1,
	RGB(255, 128, 255), _T("Light Pink"),          -1,
	RGB(255, 208, 232), _T("Very Light Pink"),     -1,

	// row 1
	RGB(255, 140,   0), _T("Dark Orange"),         -1,
	RGB(255, 165,   0), _T("Orange"),              -1,
	RGB(255, 128, 128), _T("Light Salmon"),        -1,
	RGB(255, 224, 160), _T("Light Orange"),        -1,
	RGB(255, 215,   0), _T("Gold"),                -1,
	RGB(255, 255,   0), _T("Yellow"),              -1,
	RGB(255, 255, 128), _T("Desert Yellow"),       -1,
	RGB(255, 255, 184), _T("Pale Yellow"),         -1,

	// row 2
	RGB(  0,  64,   0), _T("Dark Green"),          -1,
	RGB(  0,  64,  64), _T("Medium Green"),        -1,
	RGB(  0, 128,   0), _T("Green"),               -1,
	RGB(  0, 128,  64), _T("Dark Teal"),           -1,
	RGB(128, 128,   0), _T("Olive"),               -1,
	RGB(  0, 128, 128), _T("Teal"),                -1,
	RGB( 64, 128, 128), _T("Turquoise"),           -1,
	RGB(  0, 255,  64), _T("Medium Spring Green"), -1,

	// row 3
	RGB(128, 255,   0), _T("Mint Green"),          -1,
	RGB(  0, 255,   0), _T("Lime"),                -1,
	RGB(  0, 255, 128), _T("Spring Green"),        -1,
	RGB(152, 251, 152), _T("Pale Green"),          -1,
	RGB(127, 255, 212), _T("Aquamarine"),          -1,
	RGB(192, 220, 192), _T("Very Pale Green"),     -1,
	RGB( 64,   0,  64), _T("Deep Purple"),         -1,
	RGB(128,   0, 128), _T("Purple"),              -1,

	// row 4
	RGB( 64,   0, 128), _T("Deep Violet"),         -1,
	RGB(  0,   0,  64), _T("Midnight Blue"),       -1,
	RGB(  0,   0, 160), _T("Dark Blue"),           -1,
	RGB(  0,   0, 128), _T("Navy"),                -1,
	RGB(128,   0, 255), _T("Violet"),              -1,
	RGB(  0,   0, 255), _T("Blue"),                -1,
	RGB(  0,  64, 128), _T("Medium Blue"),         -1,
	RGB(  0, 128, 255), _T("Light Sky Blue"),      -1,

	// row 5
	RGB(100, 149, 237), _T("Cornflower Blue"),     -1,
	RGB(128, 128, 192), _T("Sky Blue"),            -1,
	RGB(  0, 128, 192), _T("Dark Cyan"),           -1,
	RGB(128, 128, 255), _T("Medium Slate Blue"),   -1,
	RGB(128, 255, 255), _T("Light Blue"),          -1,
	RGB(  0, 255, 255), _T("Cyan"),                -1,
	RGB(176, 224, 230), _T("Powder Blue"),         -1,
	RGB(224, 255, 255), _T("Light Cyan"),          -1,

	// row 6
	RGB(  0,   0,   0), _T("Black"),               -1,
	RGB(128, 128, 128), _T("Gray"),                -1,
	RGB(152, 152, 152), _T("Gray 40%"),            -1,
	RGB(192, 192, 192), _T("Silver"),              -1,
	RGB(211, 211, 211), _T("Light Gray"),          -1,
	RGB(245, 245, 220), _T("Beige"),               -1,
	RGB(255, 251, 240), _T("Floral White"),        -1,
	RGB(255, 255, 255), _T("White"),               -1,

	// row 7 - window system colors
	RGB(  0,   0,   0), _T("Window"),              COLOR_WINDOW,
	RGB(  0,   0,   0), _T("WindowText"),          COLOR_WINDOWTEXT,
	RGB(  0,   0,   0), _T("InfoBk"),              COLOR_INFOBK,
	RGB(  0,   0,   0), _T("InfoText"),            COLOR_INFOTEXT,
	RGB(  0,   0,   0), _T("ActiveCaption"),       COLOR_ACTIVECAPTION,
	RGB(  0,   0,   0), _T("CaptionText"),         COLOR_CAPTIONTEXT,
	RGB(  0,   0,   0), _T("InactiveCaption"),     COLOR_INACTIVECAPTION,
	RGB(  0,   0,   0), _T("InactiveCaptionText"), COLOR_INACTIVECAPTIONTEXT,

	// row 8 - window system colors, row #2
	RGB(  0,   0,   0), _T("BtnFace"),             COLOR_BTNFACE,
	RGB(  0,   0,   0), _T("BtnText"),             COLOR_BTNTEXT,
	RGB(  0,   0,   0), _T("BtnShadow"),           COLOR_BTNSHADOW,
	RGB(  0,   0,   0), _T("BtnHighlight"),        COLOR_BTNHIGHLIGHT,
	RGB(  0,   0,   0), _T("Highlight"),           COLOR_HIGHLIGHT,
	RGB(  0,   0,   0), _T("HighlightText"),       COLOR_HIGHLIGHTTEXT,
	RGB(  0,   0,   0), _T("3DLight"),             COLOR_3DLIGHT,
	RGB(  0,   0,   0), _T("Desktop"),             COLOR_DESKTOP,

	// row 9 - divider line
	RGB(192, 192, 192), _T("1"),                   -1,
	RGB(192, 192, 192), _T("2"),                   -1,
	RGB(192, 192, 192), _T("3"),                   -1,
	RGB(192, 192, 192), _T("4"),                   -1,
	RGB(192, 192, 192), _T("5"),                   -1,
	RGB(192, 192, 192), _T("6"),                   -1,
	RGB(192, 192, 192), _T("7"),                   -1,
	RGB(192, 192, 192), _T("8"),                   -1,

	// row 10 - custom button
	RGB(192, 192, 192), _T("9"),                   -1,
	RGB(192, 192, 192), _T("10"),                  -1,
	RGB(192, 192, 192), _T("11"),                  -1,
	RGB(192, 192, 192), _T("12"),                  -1,
	RGB(192, 192, 192), _T("13"),                  -1,
	RGB(192, 192, 192), _T("14"),                  -1,
	RGB(192, 192, 192), _T("15"),                  -1,
	RGB(192, 192, 192), _T("16"),                  -1,

	// custom colors
	// row 11
	(unsigned long)-1, _T("Custom color 1"),       -1,
	(unsigned long)-1, _T("Custom color 2"),       -1,
	(unsigned long)-1, _T("Custom color 3"),       -1,
	(unsigned long)-1, _T("Custom color 4"),       -1,
	(unsigned long)-1, _T("Custom color 5"),       -1,
	(unsigned long)-1, _T("Custom color 6"),       -1,
	(unsigned long)-1, _T("Custom color 7"),       -1,
	(unsigned long)-1, _T("Custom color 8"),       -1,

	// row 12
	(unsigned long)-1, _T("Custom color 9"),       -1,
	(unsigned long)-1, _T("Custom color 10"),      -1,
	(unsigned long)-1, _T("Custom color 11"),      -1,
	(unsigned long)-1, _T("Custom color 12"),      -1,
	(unsigned long)-1, _T("Custom color 13"),      -1,
	(unsigned long)-1, _T("Custom color 14"),      -1,
	(unsigned long)-1, _T("Custom color 15"),      -1,
	(unsigned long)-1, _T("Custom color 16"),      -1
};


/////////////////////////////////////////////////////////////////////////////
// CXColourPopup

BEGIN_MESSAGE_MAP(CXColourPopup, CWnd)
	//{{AFX_MSG_MAP(CXColourPopup)
	ON_WM_NCDESTROY()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CXColourPopup::CXColourPopup()
{
	Init();
}

CXColourPopup::CXColourPopup(CWnd * pParentWnd,
						 CPoint p,
						 COLORREF crColor,
						 COLORREF * pCustomColors,
						 int nSelectedRow,
						 int nSelectedCol,
						 LPCTSTR szCustomText /* = NULL */)
{
	Init();

	m_nSelectedRow  = nSelectedRow;
	m_nSelectedCol  = nSelectedCol;
	m_crColor       = m_crInitialColor = crColor;
	m_pParent       = pParentWnd;

	int i;
	if (nSelectedRow == -1 || nSelectedCol == -1)
	{
		// no selection specified - look thru the color table for a match
		for (i = 0; i < m_nNumColors; i++)
		{
			if (m_crColors[i].crColor == crColor)
			{
				m_nSelectedRow = i / 8;
				m_nSelectedCol = i % 8;
				break;
			}
		}
	}

	if (pCustomColors)
	{
		m_pCustomColors = pCustomColors;

		for (i = 0; i < 16; i++)
		{
			m_crColors[FIRST_CUSTOM_ROW * 8 + i].crColor = m_pCustomColors[i];
		}
	}

	Create(p, crColor, pParentWnd, szCustomText);
}

void CXColourPopup::Init()
{
	m_nNumColors    = sizeof(m_crColors) / sizeof(ColorTableEntry);
	ASSERT(m_nNumColors == 104);
	m_nNumColumns   = 0;
	m_nNumRows      = 0;
	m_nBoxSize      = 18;
	m_nMargin       = ::GetSystemMetrics(SM_CXEDGE);
	m_nCurrentRow   = -1;
	m_nCurrentCol   = -1;
	m_nSelectedRow  = -1;
	m_nSelectedCol  = -1;
	m_crColor       = m_crInitialColor = RGB(255, 255, 255);
	m_pCustomColors = NULL;
	m_bShowCustom   = TRUE;
	m_strCustomText = _T("Custom...");
	m_pParent       = NULL;

	// Make sure the color square is at least 5 x 5;
	if (m_nBoxSize - 2 * m_nMargin - 2 < 5)
		m_nBoxSize = 5 + 2 * m_nMargin + 2;

	// set system colors
	for (int i = 0; i < m_nNumColors; i++)
		if (m_crColors[i].nSystemColor != -1)
			m_crColors[i].crColor = GetSysColor(m_crColors[i].nSystemColor);
}

CXColourPopup::~CXColourPopup()
{
	if (m_Font.GetSafeHandle())
		m_Font.DeleteObject();
}

///////////////////////////////////////////////////////////////////////////////
// Create
BOOL CXColourPopup::Create(CPoint p,
						 COLORREF crColor,
						 CWnd * pParentWnd,
						 LPCTSTR szCustomText /* = NULL */)
{
	ASSERT(pParentWnd && ::IsWindow(pParentWnd->GetSafeHwnd()));

	m_pParent  = pParentWnd;
	m_crColor  = m_crInitialColor = crColor;

	// Get the class name and create the window
	CString szClassName = AfxRegisterWndClass(
		CS_CLASSDC | CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW,
		0, (HBRUSH)GetStockObject(LTGRAY_BRUSH), 0);

	if (!CWnd::CreateEx(0, szClassName, _T(""), WS_VISIBLE | WS_POPUP,
			p.x, p.y, 100, 100, // size updated soon
		pParentWnd->GetSafeHwnd(), 0, NULL))
	{
		return FALSE;
	}

	// Store the Custom text
	if (szCustomText != NULL)
		m_strCustomText = szCustomText;

	// Set the window size
	SetWindowSize();

	// Create the tooltips
	CreateToolTips();

	// Capture all mouse events for the life of this window
	SetCapture();

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// PreTranslateMessage - for tooltips
BOOL CXColourPopup::PreTranslateMessage(MSG * pMsg)
{
	m_ToolTip.RelayEvent(pMsg);
	return CWnd::PreTranslateMessage(pMsg);
}

///////////////////////////////////////////////////////////////////////////////
// OnKeyDown - if an arrow key is pressed, then move the selection
void CXColourPopup::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int row = m_nCurrentRow;
	int col = m_nCurrentCol;

	if (row == -1 || col == -1)
	{
		row = m_nSelectedRow;
		col = m_nSelectedCol;
	}

	if (nChar == VK_DOWN)
	{
		row++;
		if (row < 0)
		{
			row = 0;
			col = 0;
		}
		else if (row == DIVIDER_LINE_ROW)
		{
			row++;
		}
		else if (row >= m_nNumRows)
		{
			row = 0;
		}
		ChangeSelection(row, col);
	}

	if (nChar == VK_UP)
	{
		row--;
		if (row < 0)
		{
			row = m_nNumRows - 1;
		}
		else if (row == DIVIDER_LINE_ROW)
		{
			row--;
		}
		ChangeSelection(row, col);
	}

	if (nChar == VK_RIGHT)
	{
		if (col < 0)
		{
			row = 0;
			col = 0;
		}
		else if (col < m_nNumColumns - 1)
		{
			col++;
		}
		else
		{
			col = 0;
		}
		ChangeSelection(row, col);
	}

	if (nChar == VK_LEFT)
	{
		if (col < 0)
		{
			row = m_nNumRows - 1;
			col = m_nNumColumns - 1;
		}
		else if (col > 0)
		{
			col--;
		}
		else
		{
			col = m_nNumColumns - 1;
		}
		ChangeSelection(row, col);
	}

	if (nChar == VK_ESCAPE)
	{
		m_crColor = m_crInitialColor;
		EndSelection(CPN_SELENDCANCEL);
		return;
	}

	if (nChar == VK_RETURN)
	{
		EndSelection(CPN_SELENDOK);
		return;
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

///////////////////////////////////////////////////////////////////////////////
// OnNcDestroy - auto-deletion
void CXColourPopup::OnNcDestroy()
{
	CWnd::OnNcDestroy();
	delete this;
}

///////////////////////////////////////////////////////////////////////////////
// OnPaint
void CXColourPopup::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// Draw color cells
	for (int row = 0; row < m_nNumRows; row++)
		for (int col = 0; col < m_nNumColumns; col++)
			DrawCell(&dc, row, col);

	// Draw raised window edge (ex-window style WS_EX_WINDOWEDGE is sposed to do this,
	// but for some reason isn't
	CRect rect;
	GetClientRect(rect);
	dc.DrawEdge(rect, EDGE_RAISED, BF_RECT);
}

///////////////////////////////////////////////////////////////////////////////
// OnMouseMove
void CXColourPopup::OnMouseMove(UINT nFlags, CPoint point)
{
	int row, col;

	if (point.x < 0 || point.y < 0)
	{
		ChangeSelection(-1, -1);
		CWnd::OnMouseMove(nFlags, point);
		return;
	}

	// Translate points to be relative raised window edge
	point.x -= m_nMargin;
	point.y -= m_nMargin;

	// First check we aren't in text box
	if (m_bShowCustom && m_TextRect.PtInRect(point))
	{
		row = CUSTOM_BUTTON_ROW;        // Special value meaning Custom button (hack!)
		col = 0;
	}
	else if (m_bShowCustom && m_DividerRect.PtInRect(point))
	{
		row = DIVIDER_LINE_ROW;        // Special value meaning divider line
		col = 0;
	}
	else
	{
		// Get the row and column
		row = point.y / m_nBoxSize,
		col = point.x / m_nBoxSize;

		// In range? If not, default and exit
		if (row < 0 || row >= m_nNumRows || row == DIVIDER_LINE_ROW ||
				col < 0 || col >= m_nNumColumns)
		{
			ChangeSelection(-1, -1);
			CWnd::OnMouseMove(nFlags, point);
			return;
		}
	}

	// OK - we have the row and column of the current selection (may be TEXT_BOX_VALUE)
	// Has the row/col selection changed? If yes, then redraw old and new cells.
	if (row != m_nCurrentRow || col != m_nCurrentCol)
	{
		ChangeSelection(row, col);
	}

	CWnd::OnMouseMove(nFlags, point);
}

///////////////////////////////////////////////////////////////////////////////
// OnLButtonUp - end selection on LButtonUp
void CXColourPopup::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);

	DWORD pos = GetMessagePos();
	point = CPoint(GET_X_LPARAM(pos), GET_Y_LPARAM(pos));

	if (m_WindowRect.PtInRect(point))
		EndSelection(CPN_SELENDOK);
	else
		EndSelection(CPN_SELENDCANCEL);
}

///////////////////////////////////////////////////////////////////////////////
// GetCellRect - gets the dimensions of the color cell given by (row,col)
BOOL CXColourPopup::GetCellRect(int row, int col, const LPRECT & rect)
{
	if (row < 0 || row >= m_nNumRows || col < 0 || col >= m_nNumColumns)
		return FALSE;

	rect->left = col * m_nBoxSize + m_nMargin;
	rect->top  = row * m_nBoxSize + m_nMargin;

	rect->right = rect->left + m_nBoxSize;
	rect->bottom = rect->top + m_nBoxSize;

	if (row == DIVIDER_LINE_ROW)
		return FALSE;
	else
		return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// SetWindowSize - works out an appropriate size and position of this window
void CXColourPopup::SetWindowSize()
{
	CSize TextSize;

	// If we are showing a custom text area, get the font and text size.
	if (m_bShowCustom)
	{
		// Create the font
		if (m_Font.GetSafeHandle() == NULL)
		{
			NONCLIENTMETRICS ncm;
			ncm.cbSize = sizeof(NONCLIENTMETRICS);
			VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
						sizeof(NONCLIENTMETRICS), &ncm, 0));
			m_Font.CreateFontIndirect(&(ncm.lfMessageFont));
		}

		// Get the size of the custom text
		CClientDC dc(this);
		CFont * pOldFont = (CFont *) dc.SelectObject(&m_Font);
		TextSize = dc.GetTextExtent(m_strCustomText)
			+ CSize(2 * m_nMargin, 2 * m_nMargin);
		dc.SelectObject(pOldFont);
	}

	// Get the number of columns and rows
	m_nNumColumns = 8;
	m_nNumRows = (m_nNumColors / m_nNumColumns);
	if (m_nNumColors % m_nNumColumns)
		m_nNumRows++;

	// Get the current window position, and set the new size
	CRect rect;
	GetWindowRect(rect);

	m_WindowRect.SetRect(rect.left, rect.top,
		rect.left + m_nNumColumns * m_nBoxSize + 2 * m_nMargin,
		rect.top + m_nNumRows * m_nBoxSize + 2 * m_nMargin);

	// if custom text, then expand window if necessary, and set text width as
	// window width
	if (m_bShowCustom)
	{
		//m_WindowRect.bottom += (m_nMargin + TextSize.cy);
		if (TextSize.cx > m_WindowRect.Width())
			m_WindowRect.right = m_WindowRect.left + TextSize.cx;
		TextSize.cx = m_WindowRect.Width() - 2 * m_nMargin;

		// Work out the text area
		m_TextRect.SetRect(m_nMargin,
						   m_nMargin + CUSTOM_BUTTON_ROW*m_nBoxSize,
						   m_nMargin + TextSize.cx,
						   m_nMargin + CUSTOM_BUTTON_ROW*m_nBoxSize + TextSize.cy);
		m_DividerRect.SetRect(m_nMargin,
						   m_nMargin + DIVIDER_LINE_ROW*m_nBoxSize,
						   m_nMargin + TextSize.cx,
						   m_nMargin + DIVIDER_LINE_ROW*m_nBoxSize + m_nBoxSize);
	}

	// Set the window size and position
	MoveWindow(m_WindowRect, TRUE);
}

///////////////////////////////////////////////////////////////////////////////
// CreateToolTips
void CXColourPopup::CreateToolTips()
{
	// Create the tool tip
	if (!m_ToolTip.Create(this))
		return;

	// Add a tool for each cell
	for (int row = 0; row < m_nNumRows; row++)
	{
		if (row == DIVIDER_LINE_ROW)
			continue;

		if (row == CUSTOM_BUTTON_ROW)
		{
			m_ToolTip.AddTool(this, _T("Selects a custom color"), m_TextRect, 1);
			continue;
		}

		for (int col = 0; col < m_nNumColumns; col++)
		{
			CRect rect;
			if (!GetCellRect(row, col, rect))
			{
				continue;
			}
			VERIFY(m_ToolTip.AddTool(this, GetColorName(row, col), rect, 1));
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// ChangeSelection
void CXColourPopup::ChangeSelection(int row, int col)
{
	CClientDC dc(this);        // device context for drawing

	//int row = (row1 < 5) ? row1 : row1 + 1;

	if ((m_nCurrentRow >= 0 && m_nCurrentRow < m_nNumRows &&
			m_nCurrentCol >= 0 && m_nCurrentCol < m_nNumColumns) ||
		(m_nCurrentRow == CUSTOM_BUTTON_ROW) ||
		(m_nCurrentRow == DIVIDER_LINE_ROW))
	{
		// Set Current selection as invalid and redraw old selection (this way
		// the old selection will be drawn unselected)
		int OldRow = m_nCurrentRow;
		int OldCol = m_nCurrentCol;
		m_nCurrentRow = m_nCurrentCol = -1;
		DrawCell(&dc, OldRow, OldCol);
	}

	if (row == -1 || col == -1)
		return;

	// Set the current selection as row/col and draw (it will be drawn selected)
	m_nCurrentRow = row;
	m_nCurrentCol = col;

	if (row == DIVIDER_LINE_ROW)
		return;

	DrawCell(&dc, row, col);

	// Store the current color
	if (m_nCurrentRow == CUSTOM_BUTTON_ROW)// && m_nCurrentCol == TEXT_BOX_VALUE)
	{
		m_pParent->SendMessage(CPN_SELCHANGE, (WPARAM) m_crInitialColor, 0);
	}
	else
	{
		m_crColor = GetColor(m_nCurrentRow, m_nCurrentCol);
		m_pParent->SendMessage(CPN_SELCHANGE, (WPARAM) m_crColor, 0);
	}
}

///////////////////////////////////////////////////////////////////////////////
// EndSelection
void CXColourPopup::EndSelection(int nMessage)
{
	ReleaseCapture();

	if (nMessage != CPN_SELENDCANCEL && m_nCurrentRow == DIVIDER_LINE_ROW)
	{
		// ignore click on divider line
		SetCapture();
		return;
	}
	else if (nMessage != CPN_SELENDCANCEL && m_nCurrentRow == CUSTOM_BUTTON_ROW)
	{
		// if custom text selected, perform a custom color selection
		COLORREF rgb[16];
		int i, row, col;
		for (i = 0, row = FIRST_CUSTOM_ROW; row < FIRST_CUSTOM_ROW+2; row++)
			for (col = 0; col < 8; col++)
				rgb[i++] = GetColor(row, col);

		CColorDialog dlg(m_crInitialColor, CC_FULLOPEN | CC_ANYCOLOR, this);
		dlg.m_cc.lStructSize  = sizeof(CHOOSECOLOR);
		dlg.m_cc.hwndOwner    = m_hWnd;
		dlg.m_cc.lpCustColors = rgb;
		dlg.m_cc.Flags        |= CC_FULLOPEN | CC_ANYCOLOR;

		if (dlg.DoModal() == IDOK)
		{
			m_crColor = dlg.GetColor();
			for (i = 0, row = FIRST_CUSTOM_ROW; row < FIRST_CUSTOM_ROW+2; row++)
				for (col = 0; col < 8; col++)
					SetColor(row, col, rgb[i++]);
			Invalidate();
		}
		SetCapture();
		return;
	}

	if (nMessage == CPN_SELENDCANCEL)
		m_crColor = m_crInitialColor;

	m_nSelectedRow = m_nCurrentRow;
	m_nSelectedCol = m_nCurrentCol;

	if (m_pCustomColors)
	{
		for (int i = 0; i < 16; i++)
		{
			m_pCustomColors[i] = m_crColors[FIRST_CUSTOM_ROW * 8 + i].crColor;
		}
	}

	m_pParent->SendMessage(nMessage, (WPARAM) m_crColor,
		MAKELONG((WORD)m_nSelectedRow, (WORD)m_nSelectedCol));

	DestroyWindow();
}

///////////////////////////////////////////////////////////////////////////////
// DrawCell
void CXColourPopup::DrawCell(CDC * pDC, int row, int col)
{
	// This is a special hack for the text box
	if (m_bShowCustom && row == CUSTOM_BUTTON_ROW)// && row == TEXT_BOX_VALUE)
	{
		pDC->FillSolidRect(m_TextRect, ::GetSysColor(COLOR_3DFACE));
		if (m_nCurrentRow == row && m_nCurrentCol == col)
			pDC->DrawEdge(m_TextRect, EDGE_RAISED, BF_RECT);

		// Draw custom text
		CFont * pOldFont = (CFont *) pDC->SelectObject(&m_Font);
		pDC->DrawText(m_strCustomText, m_TextRect,
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SelectObject(pOldFont);

		return;
	}

	// row/col in range?
	ASSERT(row >= 0 && row < m_nNumRows);
	ASSERT(col >= 0 && col < m_nNumColumns);

	CRect rect;
	if (!GetCellRect(row, col, rect))
	{
		pDC->FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
		if (row != DIVIDER_LINE_ROW)
			return;

		// we're trying to draw divider line
		CRect divider(rect);
		int h = divider.Height();
		GetCellRect(row, 7, rect);
		divider.right = rect.right;
		divider.top += (h/2) - 2;
		divider.bottom -= (h/2) - 2;
		UINT nFlags = BF_BOTTOM | BF_TOP;
		if (col == 0)
			nFlags |= BF_LEFT;
		if (col == 7)
			nFlags |= BF_RIGHT;
		pDC->DrawEdge(divider, EDGE_SUNKEN, nFlags);
		return;
	}

	// fill background
	pDC->FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));

	// Draw raised edge if selected
	if (m_nCurrentRow == row && m_nCurrentCol == col)
		pDC->DrawEdge(rect, EDGE_RAISED, BF_RECT);
	else if (m_nSelectedRow == row && m_nSelectedCol == col)
		pDC->DrawEdge(rect, EDGE_SUNKEN, BF_RECT);

	COLORREF rgbCell = GetColor(row, col);
	if (rgbCell == -1)
		rgbCell = RGB(255, 255, 255);
	CBrush brush(rgbCell);
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));

	CBrush * pOldBrush = (CBrush *) pDC->SelectObject(&brush);
	CPen * pOldPen = (CPen *) pDC->SelectObject(&pen);

	// Draw the cell color
	rect.DeflateRect(m_nMargin + 1, m_nMargin + 1);
	pDC->Rectangle(rect);

	// restore DC and cleanup
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}
