// BCGToolbarMenuButton.cpp: implementation of the CBCGToolbarMenuButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxpriv.h>
#include "resource.h"
#include "BCGToolbarMenuButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static const int SEPARATOR_SIZE = 2;
static const COLORREF clrTransparent = RGB (255, 0, 255);

CImageList CBCGToolbarMenuButton::m_Images;
CSize CBCGToolbarMenuButton::m_sizeImageArrow;

IMPLEMENT_SERIAL(CBCGToolbarMenuButton, CBCGToolbarButton, VERSIONABLE_SCHEMA | 1)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGToolbarMenuButton::CBCGToolbarMenuButton()
{
	m_uiMenuResId = 0;
	m_nID = 0;
}
//*****************************************************************************************
CBCGToolbarMenuButton::CBCGToolbarMenuButton (UINT uiID, UINT uiMenuResID, 
								int iImage, LPCTSTR lpszText, BOOL bUserButton)
{
	m_uiMenuResId = uiMenuResID;
	m_nID = uiID;
	m_nStyle = TBBS_BUTTON;
	m_iImage = iImage;
	m_strText = (lpszText == NULL) ? _T("") : lpszText;
	m_bUserButton = bUserButton;
	m_bDragFromCollection = FALSE;
	m_bText = FALSE;
	m_bImage = TRUE;

	m_rect.SetRectEmpty ();
}
//*****************************************************************************************
CBCGToolbarMenuButton::~CBCGToolbarMenuButton()
{
}

//////////////////////////////////////////////////////////////////////
// Overrides:

void CBCGToolbarMenuButton::CopyFrom (const CBCGToolbarButton& s)
{
	CBCGToolbarButton::CopyFrom (s);

	const CBCGToolbarMenuButton& src = (const CBCGToolbarMenuButton&) s;

	m_uiMenuResId = src.m_uiMenuResId;
	m_nID = 0;
}
//*****************************************************************************************
void CBCGToolbarMenuButton::Serialize (CArchive& ar)
{
	CBCGToolbarButton::Serialize (ar);

	if (ar.IsLoading ())
	{
		ar >> m_uiMenuResId;
	}
	else
	{
		ar << m_uiMenuResId;
	}
}
//*****************************************************************************************
void CBCGToolbarMenuButton::OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
			BOOL bHorz, BOOL bCustomizeMode, BOOL bHighlight)
{
	CRect rectParent = rect;
	CRect rectArrow = rect;

	if (bHorz)
	{
		rectParent.right -= m_sizeImageArrow.cx + SEPARATOR_SIZE;
		rectArrow.left = rectParent.right;
	}

	CBCGToolbarButton::OnDraw (pDC, rectParent, pImages, bHorz, bCustomizeMode, bHighlight);

	if (!bHorz)
	{
		return;
	}

	if (m_nStyle & (TBBS_PRESSED | TBBS_CHECKED))
	{
		rectArrow.OffsetRect (1, 1);
	}

	if (bHighlight)
	{
		//----------------
		// Draw separator:
		//----------------
		CRect rectSeparator = rectArrow;
		rectSeparator.right = rectSeparator.left + SEPARATOR_SIZE;
		rectSeparator.InflateRect (0, -2);

		pDC->Draw3dRect (rectSeparator, ::GetSysColor (COLOR_3DSHADOW),
										::GetSysColor (COLOR_3DHILIGHT));
	}

	BOOL bDisabled = !bCustomizeMode &&
		(m_nStyle & TBBS_DISABLED);

	ASSERT (m_Images.GetSafeHandle () != NULL);

	int iImage = (bDisabled) ? 1 : 0;

	CPoint pointImage (
		rectArrow.left + (rectArrow.Width () - m_sizeImageArrow.cx) / 2,
		rectArrow.top + (rectArrow.Height () - m_sizeImageArrow.cy) / 2);

	m_Images.Draw (pDC, iImage, pointImage, ILD_NORMAL);
}
//*****************************************************************************************
int CBCGToolbarMenuButton::OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz)
{
	if (m_Images.GetSafeHandle () == NULL)
	{
		m_Images.Create (IDB_ARROWS, 9, 0, clrTransparent);

		IMAGEINFO imageInfo;
		m_Images.GetImageInfo (0, &imageInfo);

		CRect rectImage = imageInfo.rcImage;
		m_sizeImageArrow = rectImage.Size ();
	}

	const int iTextMargin = 3;
	int iArrowSize = (bHorz) ? 
		m_sizeImageArrow.cx + SEPARATOR_SIZE - iTextMargin : 
		0;

	return CBCGToolbarButton::OnCalculateSize (pDC, sizeDefault, bHorz) + iArrowSize;
}
//*****************************************************************************************
BOOL CBCGToolbarMenuButton::OnClick (CWnd* pWnd)
{
	ASSERT_VALID(pWnd);

	if (m_uiMenuResId == 0)
	{
		return TRUE;
	}

	CMenu menu;
	VERIFY(menu.LoadMenu (m_uiMenuResId));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CFrameWnd* pParent = pWnd->GetParentFrame ();

	if (pParent != NULL &&
		pParent->IsKindOf (RUNTIME_CLASS (CMiniDockFrameWnd)))
	{
		pParent = pParent->GetParentFrame ();
	}

	ASSERT_VALID (pParent);

	CPoint point (m_rect.left - 1, m_rect.bottom);
	pWnd->ClientToScreen (&point);

	pPopup->TrackPopupMenu (TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, pParent);
	return TRUE;
}
