// XColourPicker.cpp : implementation file
//
// ColourPicker is a drop-in colour picker control. Check out the
// header file or the accompanying HTML doc file for details.
//
// http://www.codeproject.com/miscctrl/colour_picker.asp
// Office 97 style Colour Picker control by Chris Maunder
//
// Written by Chris Maunder (chrismaunder@codeguru.com)
// Extended by Alexander Bischofberger (bischofb@informatik.tu-muenchen.de)
// Copyright (c) 1998.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is
// not sold for profit without the authors written consent, and
// providing that this notice and the authors name is included. If
// the source code in  this file is used in any commercial application
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to your
// computer, causes your pet cat to fall ill, increases baldness or
// makes you car start emitting strange noises when you start it up.
//
// Expect bugs.
//
// Please use and enjoy. Please let me know of any bugs/mods/improvements
// that you have found/implemented and I will fix/incorporate them into this
// file.
//
// Updated 16 May 1998
//         31 May 1998 - added Default text (CJM)
//          9 Jan 1999 - minor vis update

#include "stdafx.h"
#include "XColourPopup.h"
#include "XColourPicker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable : 4996)	// disable bogus deprecation warning

// determine number of elements in an array (not bytes)
#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

void AFXAPI DDX_ColorPicker(CDataExchange * pDX, int nIDC, COLORREF & crColor)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	ASSERT(hWndCtrl != NULL);

	CXColourPicker * pColorPicker = (CXColourPicker *) CWnd::FromHandle(hWndCtrl);

	if (pDX->m_bSaveAndValidate)
	{
		crColor = pColorPicker->GetColor();
	}
	else // initializing
	{
		pColorPicker->SetColor(crColor);
	}
}

void AFXAPI DDX_ColorPickerCustom(CDataExchange * pDX, int nIDC, CString & strCustomColors)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	ASSERT(hWndCtrl != NULL);

	CXColourPicker * pColorPicker = (CXColourPicker *) CWnd::FromHandle(hWndCtrl);

	if (pDX->m_bSaveAndValidate)
	{
		strCustomColors = pColorPicker->GetCustomColors();
	}
	else // initializing
	{
		pColorPicker->SetCustomColors(strCustomColors);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CXColourPicker

IMPLEMENT_DYNCREATE(CXColourPicker, CButton)

BEGIN_MESSAGE_MAP(CXColourPicker, CButton)
//{{AFX_MSG_MAP(CXColourPicker)
	ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(CPN_SELENDOK, OnSelEndOK)
	ON_MESSAGE(CPN_SELENDCANCEL, OnSelEndCancel)
	ON_MESSAGE(CPN_SELCHANGE, OnSelChange)
END_MESSAGE_MAP()

CXColourPicker::CXColourPicker()
{
	m_crEnabledColor = m_crColor = ::GetSysColor(COLOR_3DFACE);    // initial color
	m_bTrackSelection = FALSE;
	m_nSelectedRow = -1;
	m_nSelectedCol = -1;

	m_crColor = RGB(255,255,255);
	m_DefaultColor = ::GetSysColor(COLOR_APPWORKSPACE);
	m_bPopupActive = FALSE;

	for (int i = 0; i < 16; i++)
		m_CustomColors[i] = RGB(255,255,255);
}

CXColourPicker::~CXColourPicker()
{
}

/////////////////////////////////////////////////////////////////////////////
// CXColourPicker message handlers

LONG CXColourPicker::OnSelEndOK(WPARAM wParam, LPARAM lParam)
{
	m_nSelectedRow = LOWORD(lParam);
	m_nSelectedCol = HIWORD(lParam);

	CWnd * pParent = GetParent();
	if (pParent)
	{
		pParent->SendMessage(CPN_CLOSEUP, wParam, (LPARAM) GetDlgCtrlID());
		pParent->SendMessage(CPN_SELENDOK, wParam, (LPARAM) GetDlgCtrlID());
	}

	COLORREF crNewColor = (COLORREF) wParam;
	if (crNewColor != m_crColor)
	{
		SetColor(crNewColor);
		if (pParent)
			pParent->SendMessage(CPN_SELCHANGE, wParam, (LPARAM) GetDlgCtrlID());
	}

	return TRUE;
}

LONG CXColourPicker::OnSelEndCancel(WPARAM wParam, LPARAM)
{
	SetColor((COLORREF) wParam);

	CWnd * pParent = GetParent();
	if (pParent)
	{
		pParent->SendMessage(CPN_CLOSEUP, wParam, (LPARAM) GetDlgCtrlID());
		pParent->SendMessage(CPN_SELENDCANCEL, wParam, (LPARAM) GetDlgCtrlID());
	}

	return TRUE;
}

LONG CXColourPicker::OnSelChange(WPARAM wParam, LPARAM)
{
	if (m_bTrackSelection)
		SetColor((COLORREF) wParam);

	return TRUE;
}

int CXColourPicker::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return - 1;

	return 0;
}

// On mouse click, create and show a CXColorPopup window for color selection
BOOL CXColourPicker::OnClicked()
{
	CRect rect;
	GetWindowRect(rect);

	// note that m_CustomColors will be updated by CXColorPopup handler
	// when user selects a color
	new CXColourPopup(this, CPoint(rect.left, rect.bottom), m_crColor, m_CustomColors);

	CWnd * pParent = GetParent();
	if (pParent)
		pParent->SendMessage(CPN_DROPDOWN, (LPARAM)m_crColor, (WPARAM) GetDlgCtrlID());

	// docs say I should return FALSE to stop the parent also getting the message.
	// HA! What a joke.
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CXColourPicker overrides

void CXColourPicker::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);        // Make it owner drawn
	CButton::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CXColourPicker implementation

CSize CXColourPicker::GetArrowSize()
{
	// Get size dimensions of edges
	CSize MarginSize(::GetSystemMetrics(SM_CXEDGE), ::GetSystemMetrics(SM_CYEDGE));

	// Get size of dropdown arrow
	int nArrowWidth  = ::GetSystemMetrics(SM_CXHTHUMB) / 3 + 2;
	int nArrowHeight = ::GetSystemMetrics(SM_CYVTHUMB) / 3 + 2;
	CSize ArrowSize(max(nArrowWidth, nArrowHeight), max(nArrowWidth, nArrowHeight));

	// Make sure arrow size is an odd number (just looks neater)
	if ((ArrowSize.cx & 1) == 0)
	{
		ArrowSize.cx++;
		ArrowSize.cy++;
	}

	return ArrowSize;
}

void CXColourPicker::SetColor(COLORREF crColor)
{
	m_crEnabledColor = m_crColor = crColor;
	RedrawWindow();
}

COLORREF CXColourPicker::GetColor()
{
	return m_crColor;
}

void CXColourPicker::SetCustomColors(COLORREF * pCustomColors)
{
	ASSERT(pCustomColors);
	for (int i = 0; i < 16; i++)
		m_CustomColors[i] = pCustomColors[i];
}

void CXColourPicker::GetCustomColors(COLORREF * pCustomColors)
{
	ASSERT(pCustomColors);
	for (int i = 0; i < 16; i++)
		pCustomColors[i] = m_CustomColors[i];
}

void CXColourPicker::SetCustomColors(LPCTSTR lpszCustomColors)
{
	int i = 0;

	// initialize to white
	for (i = 0; i < 16; i++)
		m_CustomColors[i] = RGB(255,255,255);

	ASSERT(lpszCustomColors);
	if (lpszCustomColors == NULL)
		return;

	TCHAR szCustomColors[256];
	memset(szCustomColors, 0, sizeof(szCustomColors));
	_tcsncpy(szCustomColors, lpszCustomColors, _countof(szCustomColors)-2);

	TCHAR *cp = NULL;
	cp = _tcstok(szCustomColors, _T(" "));

	for (i = 0; i < 16; i++)
	{
		if (!cp)
			break;
		m_CustomColors[i] = _tcstoul(cp, NULL, 16);
		cp = _tcstok(NULL, _T(" "));
	}
}

CString CXColourPicker::GetCustomColors()
{
	CString strCustomColors = _T("");
	CString str = _T("");
	for (int i = 0; i < 16; i++)
	{
		str.Format(_T("%06X"), m_CustomColors[i]);
		if (!strCustomColors.IsEmpty())
			strCustomColors += _T(" ");
		strCustomColors += str;
	}
	return strCustomColors;
}

BOOL CXColourPicker::OnEraseBkgnd(CDC* pDC)
{
    CRect rectClient;        // Rectangle for entire client area
    GetClientRect(&rectClient);

    // Fill the rectangle
    pDC->FillSolidRect(&rectClient, m_crColor);

	return TRUE;
}

void CXColourPicker::OnEnable(BOOL bEnable)
{
	if (bEnable)
	{
		m_crColor = m_crEnabledColor;
	}
	else
	{
		m_crEnabledColor = m_crColor;
		m_crColor = RGB(192,192,192);
	}
	RedrawWindow();

	CButton::OnEnable(bEnable);
}

//const int g_ciArrowSizeX = 4 ;
//const int g_ciArrowSizeY = 2 ;
const int g_ciArrowSizeX = 7;
const int g_ciArrowSizeY = 4;

void CXColourPicker::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct);

	CDC*    pDC      = CDC::FromHandle(lpDrawItemStruct->hDC);
	UINT    state    = lpDrawItemStruct->itemState;
    CRect   rDraw    = lpDrawItemStruct->rcItem;
	CRect	rArrow;

	if (m_bPopupActive)
		state |= ODS_SELECTED|ODS_FOCUS;

	//******************************************************
	//**                  Draw Outer Edge
	//******************************************************
	UINT uFrameState = DFCS_BUTTONPUSH|DFCS_ADJUSTRECT;

	if (state & ODS_SELECTED)
		uFrameState |= DFCS_PUSHED;

	if (state & ODS_DISABLED)
		uFrameState |= DFCS_INACTIVE;

	pDC->DrawFrameControl(&rDraw,
						  DFC_BUTTON,
						  uFrameState);


	if (state & ODS_SELECTED)
		rDraw.OffsetRect(1,1);

	//******************************************************
	//**                     Draw Focus
	//******************************************************
	if (state & ODS_FOCUS)
    {
		RECT rFocus = {rDraw.left,
					   rDraw.top,
					   rDraw.right - 1,
					   rDraw.bottom};

        pDC->DrawFocusRect(&rFocus);
    }

	rDraw.DeflateRect(::GetSystemMetrics(SM_CXEDGE),
					  ::GetSystemMetrics(SM_CYEDGE));

	//******************************************************
	//**                     Draw Arrow
	//******************************************************
	rArrow.left		= rDraw.right - g_ciArrowSizeX - 2*::GetSystemMetrics(SM_CXEDGE);///2;
	rArrow.right	= rArrow.left + g_ciArrowSizeX;
	rArrow.top		= (rDraw.bottom + rDraw.top)/2 - g_ciArrowSizeY / 2;
	rArrow.bottom	= (rDraw.bottom + rDraw.top)/2 + g_ciArrowSizeY / 2;


	CSize SizeArrow = GetArrowSize();
	int nArrowWidth = SizeArrow.cx; //g_ciArrowSizeX;
	int nArrowLeft = rArrow.left + 1;
	int nArrowTop = rArrow.top;
	while (nArrowWidth > 0)
	{
		CPoint point(nArrowLeft, nArrowTop);
		nArrowLeft += 1;
		nArrowTop += 1;
		pDC->MoveTo(point);
		point.x += nArrowWidth;
		nArrowWidth -= 2;
		pDC->LineTo(point);
	}

	rDraw.right = rArrow.left - ::GetSystemMetrics(SM_CXEDGE)/2;

	//******************************************************
	//**                   Draw Separator
	//******************************************************
	pDC->DrawEdge(&rDraw,
				  EDGE_ETCHED,
				  BF_RIGHT);

	rDraw.right -= (::GetSystemMetrics(SM_CXEDGE) * 2) + 1 ;

	//******************************************************
	//**                     Draw Color
	//******************************************************
	if ((state & ODS_DISABLED) == 0)
	{
		pDC->FillSolidRect(&rDraw,
						   (m_crColor == CLR_DEFAULT)
						   ? m_DefaultColor
						   : m_crColor);

		::FrameRect(pDC->m_hDC,
					&rDraw,
					(HBRUSH)::GetStockObject(BLACK_BRUSH));
	}
}
