// ButtonsList.cpp : implementation file
//

#include "stdafx.h"
#include "afxadv.h"
#include <afxpriv.h>
#include "resource.h"
#include "ButtonsList.h"
#include "BCGToolbarButton.h"
#include "BCGToolBarImages.h"
#include "CustToolbarDlg.h"
#include "globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const int iXOffset = 4;
static const int iYOffset = 5;

/////////////////////////////////////////////////////////////////////////////
// CButtonsList

CButtonsList::CButtonsList()
{
	m_pSelButton = NULL;
	m_pImages = NULL;

	m_iScrollOffset = 0;
	m_iScrollTotal = 0;
	m_iScrollPage = 0;

	m_bEnableDragFromList = FALSE;

	m_bInited = FALSE;
}
//**************************************************************************************
CButtonsList::~CButtonsList()
{
}

BEGIN_MESSAGE_MAP(CButtonsList, CButton)
	//{{AFX_MSG_MAP(CButtonsList)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_VSCROLL()
	ON_WM_ENABLE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonsList message handlers

BOOL CButtonsList::OnEraseBkgnd(CDC* pDC) 
{
	CRect rectClient;	// Client area rectangle
	GetClientRect (&rectClient);

	pDC->FillSolidRect (&rectClient, ::GetSysColor (COLOR_3DFACE));
	return TRUE;
}
//*********************************************************************************************
void CButtonsList::DrawItem (LPDRAWITEMSTRUCT lpDIS)
{
	if (!m_bInited)
	{
		RebuildLocations ();
	}

	CDC* pDC = CDC::FromHandle (lpDIS->hDC);
	CRect rectClient = lpDIS->rcItem;

	if (m_pImages != NULL)
	{
		CBCGDrawState ds;
		if (!m_pImages->PrepareDrawImage (ds))
		{
			return;
		}

		for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
		{
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
			ASSERT (pButton != NULL);

			CRect rect = pButton->m_rect;
			rect.OffsetRect (0, -m_iScrollOffset);

			if (rect.top >= rectClient.bottom)
			{
				break;
			}

			if (rect.bottom > rectClient.top)
			{
				int nSaveStyle = pButton->m_nStyle;

				if (!IsWindowEnabled ())
				{
					pButton->m_nStyle |= TBBS_DISABLED;
				}

				pButton->OnDraw (pDC, rect, m_pImages);
				pButton->m_nStyle = nSaveStyle;

				if (pButton == m_pSelButton && IsWindowEnabled ())
				{
					//--------------------
					// Draw selection bar:
					//--------------------
					HWND hwndButton = pButton->GetHwnd ();
					if (hwndButton != NULL)
					{
						rect.InflateRect (0, 2);
					}

					for (int i = 0; i < 2; i ++)
					{
						pDC->DrawFocusRect (&rect);
						rect.InflateRect (-1, -1);
					}
				}
			}
		}

		m_pImages->EndDrawImage (ds);
	}

	pDC->Draw3dRect (rectClient,
					::GetSysColor (COLOR_3DSHADOW),
					::GetSysColor (COLOR_3DHILIGHT));
}
//*********************************************************************************************
void CButtonsList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CBCGToolbarButton* pButton = HitTest (point);
	if (pButton == NULL)
	{
		return;
	}

	SelectButton (pButton);

	if (m_bEnableDragFromList)
	{
		COleDataSource srcItem;

		pButton->m_bDragFromCollection = TRUE;
		pButton->PrepareDrag (srcItem);
		pButton->m_bDragFromCollection = TRUE;

		srcItem.DoDragDrop ();
	}
}
//*********************************************************************************************
void CButtonsList::SetImages (CBCGToolBarImages* pImages)
{
	ASSERT_VALID (pImages);
	m_pImages = pImages;

	m_sizeButton.cx = m_pImages->GetImageSize ().cx + 6;
	m_sizeButton.cy = m_pImages->GetImageSize ().cy + 7;
	
	RemoveButtons ();
}
//*********************************************************************************************
void CButtonsList::AddButton (CBCGToolbarButton* pButton)
{
	ASSERT_VALID (pButton);
	ASSERT (m_pImages != NULL);

	m_Buttons.AddTail (pButton);
	pButton->OnChangeParentWnd (this);

	RebuildLocations ();

	HWND hwnd = pButton->GetHwnd ();
	if (hwnd != NULL)
	{
		::EnableWindow (hwnd, FALSE);
	}
}
//*********************************************************************************************
void CButtonsList::RemoveButtons ()
{
	SelectButton ((CBCGToolbarButton*) NULL);

	m_Buttons.RemoveAll ();

	m_iScrollOffset = 0;
	m_iScrollTotal = 0;
	m_iScrollPage = 0;

	EnableScrollBarCtrl (SB_VERT, FALSE);
	SetScrollRange (SB_VERT, 0, 0);
}
//*********************************************************************************************
CBCGToolbarButton* CButtonsList::HitTest (POINT point) const
{
	CRect rectClient;
	GetClientRect (&rectClient);

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		CRect rect = pButton->m_rect;
		rect.OffsetRect (0, -m_iScrollOffset);

		if (rect.PtInRect (point))
		{
			return pButton;
		}
	}

	return NULL;
}
//*********************************************************************************************
void CButtonsList::SelectButton (CBCGToolbarButton* pButton)
{
	if (m_pSelButton == pButton)
	{
		return;
	}

	CBCGToolbarButton* pOldSel = m_pSelButton;
	m_pSelButton = pButton;

	CRect rectClient;
	GetClientRect (&rectClient);

	CRect rectSelected;
	rectSelected.SetRectEmpty ();

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pListButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pListButton != NULL);

		CRect rect = pListButton->m_rect;
		rect.OffsetRect (0, -m_iScrollOffset);

		if (pListButton == m_pSelButton)
		{
			rectSelected = rect;
		}

		if (pListButton == m_pSelButton ||
			pListButton == pOldSel)
		{
			rect.InflateRect (2, 2);

			CRect rectInter;
			if (rectInter.IntersectRect (rectClient, rect))
			{
				InvalidateRect (&rectInter);
			}
		}
	}

	if (!rectSelected.IsRectEmpty ())
	{
		if (rectSelected.top >= rectClient.bottom || 
			rectSelected.bottom <= rectClient.top)
		{
			int iNewOffset = 
				max (0,
					min (rectSelected.bottom - m_iScrollOffset - rectClient.Height (), 
						m_iScrollTotal));
			SetScrollPos (SB_VERT, iNewOffset);

			m_iScrollOffset = iNewOffset;
			Invalidate ();
		}
	}

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
//*********************************************************************************************
BOOL CButtonsList::SelectButton (int iImage)
{
	if (iImage < 0)
	{
		SelectButton ((CBCGToolbarButton*) NULL);
		return TRUE;
	}

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pListButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pListButton != NULL);

		if (pListButton->m_iImage == iImage)
		{
			SelectButton (pListButton);
			return TRUE;
		}
	}

	return FALSE;
}
//********************************************************************************
void CButtonsList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int iScrollOffset = m_iScrollOffset;

	switch (nSBCode)
	{
	case SB_TOP:
		iScrollOffset = 0;
		break;

	case SB_BOTTOM:
		iScrollOffset = m_iScrollTotal;
		break;

	case SB_LINEUP:
		iScrollOffset -= m_sizeButton.cy + iYOffset;
		break;

	case SB_LINEDOWN:
		iScrollOffset += m_sizeButton.cy + iYOffset;
		break;

	case SB_PAGEUP:
		iScrollOffset -= m_iScrollPage * (m_sizeButton.cy + iYOffset);
		break;

	case SB_PAGEDOWN:
		iScrollOffset += m_iScrollPage * (m_sizeButton.cy + iYOffset);
		break;

	case SB_THUMBPOSITION:
		iScrollOffset = ((m_sizeButton.cy + iYOffset) / 2 + nPos) / 
			(m_sizeButton.cy + iYOffset) * (m_sizeButton.cy + iYOffset);
		break;

	default:
		return;
	}

	iScrollOffset = min (m_iScrollTotal, max (iScrollOffset, 0));

	if (iScrollOffset != m_iScrollOffset)
	{
		m_iScrollOffset = iScrollOffset;
		SetScrollPos (SB_VERT, m_iScrollOffset);

		CRect rectClient;	// Client area rectangle
		GetClientRect (&rectClient);

		rectClient.right -= ::GetSystemMetrics (SM_CXVSCROLL) + 2;
		rectClient.InflateRect (-1, -1);

		InvalidateRect (rectClient);
	}
}
//********************************************************************************
CScrollBar* CButtonsList::GetScrollBarCtrl(int nBar) const
{
	if (nBar == SB_HORZ || m_wndScrollBar.GetSafeHwnd () == NULL)
	{
		return NULL;
	}

	return (CScrollBar* ) &m_wndScrollBar;
}
//********************************************************************************
void CButtonsList::OnEnable(BOOL bEnable) 
{
	CButton::OnEnable(bEnable);
	
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pListButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pListButton != NULL);

	}

	Invalidate ();
	UpdateWindow ();
}
//********************************************************************************
void CButtonsList::OnSysColorChange() 
{
	if (m_pImages == NULL)
	{
		return;
	}

	m_pImages->OnSysColorChange ();

	Invalidate ();
	UpdateWindow ();
}
//*********************************************************************************
void CButtonsList::RebuildLocations ()
{
	if (GetSafeHwnd () == NULL || m_Buttons.IsEmpty ())
	{
		return;
	}

	CRect rectClient;
	GetClientRect (&rectClient);

	CRect rectButtons = rectClient;

	rectButtons.right -= ::GetSystemMetrics (SM_CXVSCROLL) + 1;
	rectButtons.InflateRect (-iXOffset, -iYOffset);

	int x = rectButtons.left;
	int y = rectButtons.top - m_iScrollOffset;

	CClientDC dc (this);

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		int iWidth = pButton->OnCalculateSize (&dc, m_sizeButton, TRUE);

		if (x + iWidth > rectButtons.right)
		{
			if (x == rectButtons.left)
			{
				iWidth = rectButtons.right - rectButtons.left;
			}
			else
			{
				x = rectButtons.left;
				y += m_sizeButton.cy + iYOffset;
			}
		}

		pButton->m_rect = CRect (CPoint (x, y), CSize (iWidth, m_sizeButton.cy));
		pButton->OnMove ();

		x += iWidth + iXOffset;
	}

	CBCGToolbarButton* pLastButton = (CBCGToolbarButton*) m_Buttons.GetTail ();
	ASSERT (pLastButton != NULL);

	int iVisibleRows = rectButtons.Height () / (m_sizeButton.cy + iYOffset);
	int iTotalRows = pLastButton->m_rect.bottom / (m_sizeButton.cy + iYOffset);

	int iNonVisibleRows = iTotalRows - iVisibleRows;
	if (iNonVisibleRows > 0)	// Not enouth space.
	{
		if (m_wndScrollBar.GetSafeHwnd () == NULL)
		{
			CRect rectSB;
			GetClientRect (&rectSB);

			rectSB.InflateRect (-1, -1);
			rectSB.left = rectSB.right - ::GetSystemMetrics (SM_CXVSCROLL) - 1;

			m_wndScrollBar.Create (WS_CHILD | WS_VISIBLE | SBS_VERT,
									rectSB, this, 1);
		}
		
		m_iScrollTotal = iNonVisibleRows * (m_sizeButton.cy + iYOffset);
		m_iScrollPage = iVisibleRows;

		SetScrollRange (SB_VERT, 0, m_iScrollTotal);
	}

	m_bInited = TRUE;
}
//*********************************************************************************
void CButtonsList::OnSize(UINT nType, int cx, int cy) 
{
	CButton::OnSize(nType, cx, cy);
	RebuildLocations ();
}
//*********************************************************************************
HBRUSH CButtonsList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CWnd::OnCtlColor (pDC, pWnd, nCtlColor);

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pButton);

		HWND hwdList = pButton->GetHwnd ();
		if (hwdList == NULL)	// No control
		{
			continue;
		}

		if (hwdList == pWnd->GetSafeHwnd () ||
			::IsChild (hwdList, pWnd->GetSafeHwnd ()))
		{
			HBRUSH hbrButton = pButton->OnCtlColor (pDC, nCtlColor);
			return (hbrButton == NULL) ? hbr : hbrButton;
		}
	}

	return hbr;
}
