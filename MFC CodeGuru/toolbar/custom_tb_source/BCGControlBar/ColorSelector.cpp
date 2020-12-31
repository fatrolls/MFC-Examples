// ColorSelector.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ColorSelector.h"
#include "BCGToolBarImages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorSelector

CColorSelector::CColorSelector()
{
	m_bReady = FALSE;
	m_iSel = 0;

	InitColors ();
}
//*******************************************************************************
CColorSelector::~CColorSelector()
{
}

BEGIN_MESSAGE_MAP(CColorSelector, CButton)
	//{{AFX_MSG_MAP(CColorSelector)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorSelector message handlers

void CColorSelector::DrawItem (LPDRAWITEMSTRUCT lpDIS)
{
	if (!m_bReady)
	{
		Adjust ();
	}

	CDC* pDC = CDC::FromHandle (lpDIS->hDC);
	ASSERT_VALID (pDC);

	CRect rectClient = lpDIS->rcItem;
	rectClient.bottom = m_Rect [COLORS_NUM - 1].bottom + 5;

	pDC->Draw3dRect (rectClient,
					::GetSysColor (COLOR_3DSHADOW),
					::GetSysColor (COLOR_3DHILIGHT));

	//--------------
	// Draw palette:
	//--------------
	for (int i = 0; i < COLORS_NUM; i ++)
	{
		CRect rect = m_Rect [i];
		rect.InflateRect (-1, -1);

		if (i == m_iSel)	// Selected color:
		{
			pDC->Draw3dRect (rect,
							::GetSysColor (COLOR_3DDKSHADOW),
							::GetSysColor (COLOR_3DLIGHT));
			rect.InflateRect (-1, -1);
			pDC->Draw3dRect (rect,
							::GetSysColor (COLOR_3DSHADOW),
							::GetSysColor (COLOR_3DHILIGHT));
		}
		else
		{
			pDC->Draw3dRect (rect,
							::GetSysColor (COLOR_3DHILIGHT),
							::GetSysColor (COLOR_3DSHADOW));
			rect.InflateRect (-1, -1);
		}

		rect.InflateRect (-2, -2);
		pDC->FillSolidRect (&rect, m_rgbColors [i]);
	}
}
//*******************************************************************************
void CColorSelector::Adjust () 
{
	const int iSelectedSize = 30;	// Bad!

	CRect rectClient;	// Client area rectangle
	GetClientRect (&rectClient);

	rectClient.InflateRect (-5, -5);

	CRect rectColors = rectClient;

	int x = rectColors.left;
	int y = rectColors.top;

	int dx;
	int dy;

	if (rectClient.Width () > rectClient.Height ())
	{
		dx = rectColors.Width () / 5;	// Assume COLORS_NUM = 20! :-(
		dy = rectColors.Height () / 4;	// Assume COLORS_NUM = 20! :-(
	}
	else
	{
		dx = rectColors.Width () / 4;	// Assume COLORS_NUM = 20! :-(
		dy = rectColors.Height () / 5;	// Assume COLORS_NUM = 20! :-(
	}

	int delta = min (dx, dy);
	for (int i = 0; i < COLORS_NUM; i ++)
	{
		m_Rect [i] = CRect (x, y, x + delta, y + delta);

		x += delta;
		if (x + delta > rectColors.right)
		{
			x = rectColors.left;
			y += delta;
		}
	}

	m_bReady = TRUE;
}
//*******************************************************************************
BOOL CColorSelector::OnEraseBkgnd(CDC* pDC) 
{
	CRect rectClient;	// Client area rectangle
	GetClientRect (&rectClient);

	pDC->FillSolidRect (&rectClient, ::GetSysColor (COLOR_3DFACE));
	return TRUE;
}
//********************************************************************************
int CColorSelector::HitTest (POINT point) const
{
	for (int i = 0; i < COLORS_NUM; i ++)
	{
		if (m_Rect [i].PtInRect (point))
		{
			return i;
		}
	}

	return -1;
}
//********************************************************************************
void CColorSelector::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int iHit = HitTest (point);
	if (iHit == -1)
	{
		return;
	}

	if (iHit == m_iSel)
	{
		return;
	}

	int iPrevSel = m_iSel;
	m_iSel = iHit;

	InvalidateRect (m_Rect [iPrevSel]);
	InvalidateRect (m_Rect [m_iSel]);
	UpdateWindow ();

	//-------------------------------------------------------
	// Trigger mouse up event (to button click notification):
	//-------------------------------------------------------
	CWnd* pParent = GetParent ();
	if (pParent != NULL)
	{
		pParent->SendMessage (	WM_COMMAND,
								MAKEWPARAM (GetDlgCtrlID (), BN_CLICKED), 
								(LPARAM) m_hWnd);
	}
}
//********************************************************************************
void CColorSelector::OnSize(UINT nType, int cx, int cy) 
{
	CButton::OnSize(nType, cx, cy);
	Adjust ();
}
//********************************************************************************
void CColorSelector::InitColors ()
{
	CPalette* pPalSystem = CPalette::FromHandle (
		(HPALETTE) ::GetStockObject (DEFAULT_PALETTE));
	ASSERT (pPalSystem != NULL);

	PALETTEENTRY palEntry;
	for (int i = 0; i < COLORS_NUM; i ++)
	{
		pPalSystem->GetPaletteEntries (i, 1, &palEntry);
		m_rgbColors [i] = CBCGToolBarImages::MapToSysColor (
			RGB (palEntry.peRed, palEntry.peGreen, palEntry.peBlue),
			FALSE);
	}
}
//********************************************************************************
void CColorSelector::OnSysColorChange() 
{
	CButton::OnSysColorChange();
	InitColors ();
}
