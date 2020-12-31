// bcgtoolbar.cpp : definition of CBCGToolBar
//
// This code is based on the Microsoft Visual C++ sample file
// TOOLBAR.C from the OLDBARS example
//

#include "stdafx.h"
#include "resource.h"
#include <afxpriv.h>
#include <..\\src\\afximpl.h>
#include "BCGtoolbar.h"
#include "globals.h"
#include "BCGToolbarButton.h"
#include "BCGToolbarMenuButton.h"
#include "BCGToolbarDropSource.h"
#include "BCGToolBarImages.h"
#include "ButtonAppearanceDlg.h"
#include "CBCGToolbarCustomize.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//#define GRIPPER_SIZE		6
#define TEXT_MARGIN			3
#define STRETCH_DELTA		6
#define BUTTON_MIN_WIDTH	5
#define LINE_OFFSET			5

#define REG_SECTION_FMT		_T("%s-BCGToolBar-%d")
#define REG_ENTRY_NAME		_T("Buttons")

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGToolBar notification messages:

UINT BCGM_TOOLBARMENU		= ::RegisterWindowMessage (_T("BCGTOOLBAR_POPUPMENU"));
UINT BCGM_CUSTOMIZETOOLBAR	= ::RegisterWindowMessage (_T("BCGTOOLBAR_CUSTOMIZE"));

/////////////////////////////////////////////////////////////////////////////
// All CBCGToolBar collection:
CObList	gAllToolbars;

BOOL CBCGToolBar::m_bCustomizeMode = FALSE;
BOOL CBCGToolBar::m_bShowTooltips = TRUE;

extern CBCGToolbarCustomize* g_pWndCustomize;


/////////////////////////////////////////////////////////////////////////////
// CBCGToolBar
IMPLEMENT_SERIAL(CBCGToolBar, CControlBar, VERSIONABLE_SCHEMA | 1)

CBCGToolBar::CBCGToolBar()
{
	m_iButtonCapture = -1;      // nothing captured
	m_iHighlighted = -1;
	m_iSelected = -1;

	m_iDragIndex = -1;
	m_rectDrag.SetRectEmpty ();
	m_pDragButton = NULL;
	m_ptStartDrag = CPoint (-1, -1);

	//---------------------
	// UISG standard sizes:
	//---------------------
	m_sizeButton.cx = 23;
	m_sizeButton.cy = 22;
	m_sizeImage.cx = 16;
	m_sizeImage.cy = 15;
	m_cyTopBorder = m_cyBottomBorder = 3;   // 3 pixel for top/bottom gaps
	m_cxDefaultGap = 8;

	m_bStretchButton = FALSE;
	m_rectTrack.SetRectEmpty ();
}
//******************************************************************************************
CBCGToolBar::~CBCGToolBar()
{
	RemoveAllButtons ();
}
//******************************************************************************************
BOOL CBCGToolBar::Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID)
{
	if (pParentWnd != NULL)
		ASSERT_VALID(pParentWnd);   // must have a parent

	//----------------
	// Save the style:
	//----------------
	m_dwStyle = dwStyle;
	if (nID == AFX_IDW_TOOLBAR)
	{
		m_dwStyle |= CBRS_HIDE_INPLACE;
	}

	//----------------------------
	// Initialize common controls:
	//----------------------------
	VERIFY (AfxDeferRegisterClass (AFX_WNDCOMMCTLS_REG));

	//-----------------
	// Create the HWND:
	//-----------------
	CRect rect;
	rect.SetRectEmpty();

	LPCTSTR lpszClass = ::AfxRegisterWndClass (
		CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_BTNFACE + 1), NULL);
	ASSERT (lpszClass != NULL);

	return CWnd::Create (lpszClass, NULL, dwStyle, rect, pParentWnd, nID);
}
//******************************************************************************************
void CBCGToolBar::SetSize (SIZE sizeButton)
{
	ASSERT_VALID(this);
	ASSERT(sizeButton.cx > 0 && sizeButton.cy > 0);

	//-----------------------------------------------------------------
	// Button must be big enough to hold image + 3 pixels on each side:
	//-----------------------------------------------------------------
	ASSERT(sizeButton.cx >= m_sizeImage.cx + 6);
	ASSERT(sizeButton.cy >= m_sizeImage.cy + 6);

	m_sizeButton = sizeButton;

	if (GetSafeHwnd () != NULL)
	{
		Invalidate ();
	}
}
//******************************************************************************************
void CBCGToolBar::SetHeight(int cyHeight)
{
	ASSERT_VALID(this);

	int nHeight = cyHeight;
	
	if (m_dwStyle & CBRS_BORDER_TOP)
	{
		cyHeight -= globalData.cyBorder2;
	}

	if (m_dwStyle & CBRS_BORDER_BOTTOM)
	{
		cyHeight -= globalData.cyBorder2;
	}

	m_cyBottomBorder = (cyHeight - m_sizeButton.cy) / 2;
	
	//-------------------------------------------------------
	// If there is an extra pixel, m_cyTopBorder will get it:
	//-------------------------------------------------------
	m_cyTopBorder = cyHeight - m_sizeButton.cy - m_cyBottomBorder;
	
	if (m_cyTopBorder < 0)
	{
		TRACE1(_T("Warning: CBCGToolBar::SetHeight(%d) is smaller than button.\n"),
			nHeight);
		m_cyBottomBorder += m_cyTopBorder;
		m_cyTopBorder = 0;  // will clip at bottom
	}

	if (GetSafeHwnd () != NULL)
	{
		Invalidate ();
	}
}
//******************************************************************************************
BOOL CBCGToolBar::SetImages (CBCGToolBarImages* pImages,
							CBCGToolBarImages* pUserImages)
{
	ASSERT (pImages != NULL);
	if (!pImages->IsValid ())
	{
		return FALSE;
	}

	if (pUserImages != NULL && !pUserImages->IsValid ())
	{
		return FALSE;
	}

	m_pImages = pImages;
	m_sizeImage = pImages->GetImageSize ();

	if (pUserImages != NULL &&
		m_sizeImage == pUserImages->GetImageSize ())
	{
		m_pUserImages = pUserImages;
	}

	return TRUE;
}
//******************************************************************************************
BOOL CBCGToolBar::SetButtons(const UINT* lpIDArray, int nIDCount)
{
	ASSERT_VALID(this);
	ASSERT(nIDCount >= 1);  // must be at least one of them
	ASSERT(lpIDArray == NULL ||
		AfxIsValidAddress(lpIDArray, sizeof(UINT) * nIDCount, FALSE));

	RemoveAllButtons ();

	if (lpIDArray == NULL)
	{
		return TRUE;
	}

	int iImage = 0;

	//--------------------------------
	// Go through them adding buttons:
	//--------------------------------
	for (int i = 0; i < nIDCount; i ++)
	{
		int iCmd = *lpIDArray ++;

		if (iCmd == 0)	// Separator
		{
			InsertSeparator ();
		}
		else
		{
			InsertButton (CBCGToolbarButton (iCmd, iImage ++));
		}
	}

	return TRUE;
}
//******************************************************************************************
BOOL CBCGToolBar::LoadToolBar(UINT uiResID)
{
	struct CToolBarData
	{
		WORD wVersion;
		WORD wWidth;
		WORD wHeight;
		WORD wItemCount;

		WORD* items()
			{ return (WORD*)(this+1); }
	};

	ASSERT_VALID(this);

	if (m_pImages == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	if (m_pImages->GetResID () != uiResID)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	LPCTSTR lpszResourceName = MAKEINTRESOURCE (uiResID);
	ASSERT(lpszResourceName != NULL);

	//---------------------------------------------------
	// determine location of the bitmap in resource fork:
	//---------------------------------------------------
	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, RT_TOOLBAR);
	HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, RT_TOOLBAR);
	if (hRsrc == NULL)
		return FALSE;

	HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
	if (hGlobal == NULL)
		return FALSE;

	CToolBarData* pData = (CToolBarData*)LockResource(hGlobal);
	if (pData == NULL)
		return FALSE;
	ASSERT(pData->wVersion == 1);

	UINT* pItems = new UINT[pData->wItemCount];
	for (int i = 0; i < pData->wItemCount; i++)
		pItems[i] = pData->items()[i];
	BOOL bResult = SetButtons(pItems, pData->wItemCount);
	delete[] pItems;

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	return bResult;
}
//*****************************************************************************************
int CBCGToolBar::InsertButton (const CBCGToolbarButton& button, int iInsertAt)
{
	CRuntimeClass* pClass = button.GetRuntimeClass ();
	ASSERT (pClass != NULL);

	CBCGToolbarButton* pButton = (CBCGToolbarButton*) pClass->CreateObject ();
	ASSERT_VALID(pButton);

	pButton->CopyFrom (button);

	int iIndex = InsertButton (pButton, iInsertAt);
	if (iIndex == -1)
	{
		delete pButton;
	}

	return iIndex;
}
//******************************************************************************************
int CBCGToolBar::InsertButton (CBCGToolbarButton* pButton, int iInsertAt)
{
	ASSERT (pButton != NULL);

	if (iInsertAt != -1 &&
		(iInsertAt < 0 || iInsertAt > m_Buttons.GetCount ()))
	{
		return -1;
	}

	int iIndex = -1;

	if (iInsertAt == -1 || iInsertAt == m_Buttons.GetCount ())
	{
		//-------------------------
		// Add to the toolbar tail:
		//-------------------------
		m_Buttons.AddTail (pButton);
		pButton->OnChangeParentWnd (this);
		iIndex = m_Buttons.GetCount () - 1;
	}
	else
	{
		int i = 0;
		for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; i ++)
		{
			if (i == iInsertAt)
			{
				m_Buttons.InsertBefore (pos, pButton);
				pButton->OnChangeParentWnd (this);
				iIndex = i;
				break;
			}

			m_Buttons.GetNext (pos);
		}
	}

	if (iIndex != -1)
	{
		pButton->m_bDragFromCollection = FALSE;

		HWND hwnd = pButton->GetHwnd ();
		if (hwnd != NULL)
		{
			::EnableWindow (hwnd, !m_bCustomizeMode);
		}
	}

	return iIndex;
}
//******************************************************************************************
int CBCGToolBar::InsertSeparator (int iInsertAt)
{
	CBCGToolbarButton* pButton = new CBCGToolbarButton;
	ASSERT (pButton != NULL);

	pButton->m_nStyle = TBBS_SEPARATOR;

	int iNewButtonOndex = InsertButton (pButton, iInsertAt);
	if (iNewButtonOndex == -1)
	{
		delete pButton;
	}

	return iNewButtonOndex;
}
//******************************************************************************************
void CBCGToolBar::RemoveAllButtons ()
{
	while (!m_Buttons.IsEmpty ())
	{
		delete m_Buttons.RemoveHead ();
	}
}
//******************************************************************************************
BOOL CBCGToolBar::RemoveButton (int iIndex)
{
	POSITION pos = m_Buttons.FindIndex (iIndex);
	if (pos == NULL)
	{
		return FALSE;
	}

	CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetAt (pos);
	ASSERT_VALID (pButton);

	m_Buttons.RemoveAt (pos);
	delete pButton;

	if (iIndex == m_iSelected)
	{
		m_iSelected = -1;
	}
	else if (iIndex < m_iSelected)
	{
		m_iSelected --;
	}

	//-----------------------------------------
	// If last button is separator - remove it:
	//-----------------------------------------
	if (!m_Buttons.IsEmpty ())
	{
		CBCGToolbarButton* pLastButton = (CBCGToolbarButton*) m_Buttons.GetTail ();
		ASSERT_VALID (pLastButton);

		if (pLastButton->m_nStyle & TBBS_SEPARATOR)
		{
			delete m_Buttons.RemoveTail ();
		}
	}

	return TRUE;
}

#ifdef AFX_CORE3_SEG
#pragma code_seg(AFX_CORE3_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGToolBar attribute access

int CBCGToolBar::CommandToIndex(UINT nIDFind) const
{
	ASSERT_VALID(this);

	int i = 0;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; i ++)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		if (pButton->m_nID == nIDFind)
		{
			return i;
		}
	}

	return -1;
}
//*****************************************************************
UINT CBCGToolBar::GetItemID(int nIndex) const
{
	ASSERT_VALID(this);

	return GetButton (nIndex)->m_nID;
}
//*****************************************************************
void CBCGToolBar::GetItemRect(int nIndex, LPRECT lpRect) const
{
	ASSERT_VALID(this);
	ASSERT(nIndex >= 0 && nIndex < m_Buttons.GetCount ());
	ASSERT(AfxIsValidAddress(lpRect, sizeof(RECT)));

	CBCGToolbarButton* pButton = GetButton (nIndex);
	ASSERT (pButton != NULL);

	*lpRect = pButton->m_rect;
}
//*****************************************************************
UINT CBCGToolBar::GetButtonStyle(int nIndex) const
{
	return GetButton (nIndex)->m_nStyle;
}
//*****************************************************************
int CBCGToolBar::ButtonToIndex (const CBCGToolbarButton* pButton) const
{
	ASSERT_VALID (this);
	ASSERT_VALID (pButton);

	int i = 0;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; i ++)
	{
		CBCGToolbarButton* pListButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pListButton != NULL);

		if (pListButton == pButton)
		{
			return i;
		}
	}

	return -1;
}
//*****************************************************************
void CBCGToolBar::SetButtonStyle(int nIndex, UINT nStyle)
{
	CBCGToolbarButton* pButton = GetButton (nIndex);
	UINT nOldStyle = pButton->m_nStyle;
	if (nOldStyle != nStyle)
	{
		// update the style and invalidate
		pButton->m_nStyle = nStyle;

		// invalidate the button only if both styles not "pressed"
		if (!(nOldStyle & nStyle & TBBS_PRESSED))
			InvalidateButton(nIndex);
	}
}
//****************************************************************
CSize CBCGToolBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	DWORD dwMode = bStretch ? LM_STRETCH : 0;
	dwMode |= bHorz ? LM_HORZ : 0;

	return CalcLayout (dwMode);
}
//*************************************************************************************
CSize CBCGToolBar::CalcDynamicLayout (int nLength, DWORD dwMode)
{
	if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
		((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
	{
		return CalcFixedLayout(dwMode & LM_STRETCH, dwMode & LM_HORZDOCK);
	}

	return CalcLayout(dwMode, nLength);
}
//*************************************************************************************
void CBCGToolBar::GetButtonInfo(int nIndex, UINT& nID, UINT& nStyle, int& iImage) const
{
	ASSERT_VALID(this);

	CBCGToolbarButton* pButton = GetButton(nIndex);
	nID = pButton->m_nID;
	nStyle = pButton->m_nStyle;
	iImage = pButton->m_iImage;
}
//*************************************************************************************
void CBCGToolBar::SetButtonInfo(int nIndex, UINT nID, UINT nStyle, int iImage)
{
	ASSERT_VALID(this);

	CBCGToolbarButton* pButton = GetButton(nIndex);
	pButton->m_nID = nID;
	pButton->m_iImage = iImage;
	pButton->m_nStyle = nStyle;
	InvalidateButton(nIndex);
}
//*************************************************************************************
void CBCGToolBar::DoPaint(CDC* pDC)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	//----------------------------------------------
	// if no toolbar loaded, don't draw any buttons:
	//----------------------------------------------
	if (m_pImages == NULL)
	{
		return;
	}

	BOOL bHorz = m_dwStyle & CBRS_ORIENT_HORZ ? TRUE : FALSE;

	CRect rectClient;
	GetClientRect (rectClient);
	if (rectClient.Width () < 2 * m_sizeButton.cx)
	{
		bHorz = FALSE;
	}

	
	pDC->SetTextColor (globalData.clrBtnText);
	pDC->SetBkMode (TRANSPARENT);

	CRect rect;
	GetClientRect(rect);

	//-----------------------------------
	// Force the full size of the button:
	//-----------------------------------
	if (bHorz)
	{
		rect.bottom = rect.top + m_sizeButton.cy;
	}
	else
	{
		rect.right = rect.left + m_sizeButton.cx;
	}

	CBCGToolBarImages* pImages = m_pImages;

	CBCGDrawState ds;
	if (!m_pImages->PrepareDrawImage (ds))
	{
		return;     // something went wrong
	}

	CFont* pOldFont;
	if (bHorz)
	{
		pOldFont = (CFont*) pDC->SelectStockObject (DEFAULT_GUI_FONT);
	}
	else
	{
		pOldFont = (CFont*) pDC->SelectObject (&m_fontVert);
	}

	//--------------
	// Draw buttons:
	//--------------
	int iButton = 0;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; iButton ++)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		rect = pButton->m_rect;

		BOOL bHighlighted = (iButton == m_iHighlighted) ||
							(iButton == m_iButtonCapture);
		if (m_bCustomizeMode)
		{
			bHighlighted = FALSE;
		}
		if (m_iButtonCapture != -1 &&
			iButton != m_iButtonCapture)
		{
			bHighlighted = FALSE;
		}

		ASSERT(pButton != NULL);
		if (pButton->m_nStyle & TBBS_SEPARATOR)
		{
			CRect rectSeparator = rect;
			if (bHorz)
			{
				rectSeparator.left += rectSeparator.Width () / 2;
				rectSeparator.right = rectSeparator.left + 2;
			}
			else
			{
				rectSeparator.top += rectSeparator.Height () / 2;
				rectSeparator.bottom = rectSeparator.top + 2;
			}

			pDC->Draw3dRect (rectSeparator, globalData.clrBtnShadow,
											globalData.clrBtnHilite);
		}
		else
		{
			if (pDC->RectVisible(&rect))
			{
				if (m_pUserImages != NULL)
				{
					CBCGToolBarImages* pNewImages =
								(pButton->m_bUserButton) ?
									m_pUserImages : m_pImages;
					if (pNewImages != pImages)
					{
						pImages->EndDrawImage (ds);
						pNewImages->PrepareDrawImage (ds);

						pImages = pNewImages;
					}
				}

				DrawButton (pDC, pButton, bHighlighted);
			}
		}
	}

	//-------------------------------------------------------------
	// Highlight selected button in the toolbar customization mode:
	//-------------------------------------------------------------
	if (m_bCustomizeMode && m_iSelected >= 0)
	{
		CBCGToolbarButton* pSelButton = GetButton (m_iSelected);
		ASSERT (pSelButton != NULL);

		CRect rectDrag = pSelButton->m_rect;

		if (pSelButton->GetHwnd () != NULL)
		{
			rectDrag.InflateRect (0, 2);
		}

		pDC->DrawDragRect (&rectDrag, CSize (2, 2), NULL, CSize (2, 2));
	}

	if (m_bCustomizeMode && m_iDragIndex >= 0)
	{
		DrawDragMarker (pDC);
	}

	pDC->SelectObject (pOldFont);
	pImages->EndDrawImage(ds);
}
//*************************************************************************************
BOOL CBCGToolBar::DrawButton(CDC* pDC, CBCGToolbarButton* pButton,
							BOOL bHighlighted)
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);

	if (pButton->GetHwnd () != NULL &&
		(CWnd::FromHandle (pButton->GetHwnd ())->GetStyle () & WS_VISIBLE))
	{
		return TRUE;;
	}

	BOOL bHorz = m_dwStyle & CBRS_ORIENT_HORZ ? TRUE : FALSE;

	CRect rectClient;
	GetClientRect (rectClient);
	if (rectClient.Width () < 2 * m_sizeButton.cx)
	{
		bHorz = FALSE;
	}

	CBCGToolBarImages* pImages = (pButton->m_bUserButton) ?
								m_pUserImages : m_pImages;

	CRect rect = pButton->m_rect;

	//---------------
	// Interior grey:
	//---------------
	pDC->FillSolidRect (&rect, globalData.clrBtnFace);

	if (!m_bCustomizeMode && !bHighlighted &&
		(pButton->m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE)))
	{
		CRect rectDither = rect;
		rectDither.InflateRect (-globalData.cxBorder2, -globalData.cyBorder2);

		CBCGToolBarImages::FillDitheredRect (pDC, rectDither);
	}

	//--------------------
	// Draw button border:
	//--------------------
	if (!m_bCustomizeMode)
	{
		if (pButton->m_nStyle & (TBBS_PRESSED | TBBS_CHECKED))
		{
			//-----------------------
			// Pressed in or checked:
			//-----------------------
			pDC->Draw3dRect (&rect,
				globalData.clrBtnShadow,
				globalData.clrBtnHilite);
		}
		else if (bHighlighted && !(pButton->m_nStyle & TBBS_DISABLED) &&
			!(pButton->m_nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE)))
		{
			pDC->Draw3dRect (&rect, globalData.clrBtnHilite,
									globalData.clrBtnShadow);
		}
	}

	//---------------------
	// Draw button context:
	//---------------------
	pButton->OnDraw (pDC, rect, pImages, bHorz, m_bCustomizeMode, bHighlighted);
	return TRUE;
}
//*************************************************************************************
inline CBCGToolbarButton* CBCGToolBar::GetButton(int nIndex) const
{
	POSITION pos = m_Buttons.FindIndex (nIndex);
	ASSERT (pos != NULL);

	CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetAt (pos);
	ASSERT (pButton != NULL);

	return pButton;
}
//*************************************************************************************
void CBCGToolBar::InvalidateButton(int nIndex)
{
	ASSERT_VALID(this);

	CRect rect;
	GetItemRect(nIndex, &rect);
	rect.InflateRect (3, 3);

	InvalidateRect (rect);
}
//*************************************************************************************
int CBCGToolBar::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	ASSERT_VALID(this);

	if (!m_bShowTooltips)
	{
		return -1;
	}

	// check child windows first by calling CControlBar
	int nHit = CControlBar::OnToolHitTest(point, pTI);
	if (nHit != -1)
		return nHit;

	// now hit test against CBCGToolBar buttons
	nHit = ((CBCGToolBar*)this)->HitTest(point);
	if (nHit != -1)
	{
		CBCGToolbarButton* pButton = GetButton(nHit);
		if (pTI != NULL)
		{
			if (pButton->m_nID == 0)
			{
				if (pButton->m_strText.IsEmpty ())
				{
					return -1;
				}

				pTI->lpszText = new TCHAR [pButton->m_strText.GetLength () + 1];
				strcpy (pTI->lpszText, pButton->m_strText);
			}
			else
			{
				pTI->lpszText = LPSTR_TEXTCALLBACK;
			}
			GetItemRect(nHit, &pTI->rect);
			pTI->uId = pButton->m_nID;
			pTI->hwnd = m_hWnd;
		}
		nHit = pButton->m_nID;
	}
	return nHit;
}
//*************************************************************************************
int CBCGToolBar::HitTest(CPoint point) // in window relative coords
{
	int iButton = 0;
	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; iButton ++)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		if (pButton->m_rect.PtInRect (point))
		{
			return (pButton->m_nStyle & TBBS_SEPARATOR) ? -1 : iButton;
		}
	}

	return -1;      // nothing hit
}

/////////////////////////////////////////////////////////////////////////////
// CBCGToolBar message handlers

BEGIN_MESSAGE_MAP(CBCGToolBar, CControlBar)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CBCGToolBar)
	ON_WM_MOUSEMOVE()
	ON_WM_CANCELMODE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_MOVE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_TOOLBAR_APPEARANCE, OnToolbarAppearance)
	ON_COMMAND(ID_TOOLBAR_DELETE, OnToolbarDelete)
	ON_COMMAND(ID_TOOLBAR_IMAGE, OnToolbarImage)
	ON_COMMAND(ID_TOOLBAR_IMAGE_AND_TEXT, OnToolbarImageAndText)
	ON_COMMAND(ID_TOOLBAR_START_GROUP, OnToolbarStartGroup)
	ON_COMMAND(ID_TOOLBAR_TEXT, OnToolbarText)
	ON_WM_LBUTTONUP()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_CTLCOLOR()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CBCGToolBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bCustomizeMode)
	{
		SetFocus ();
	}

	int iButton = HitTest(point);

	if (iButton < 0) // nothing hit
	{
		m_iButtonCapture = -1;

		if (m_bCustomizeMode)
		{
			int iSelected = m_iSelected;
			m_iSelected = -1;

			if (iSelected != -1)
			{
				InvalidateButton (iSelected);
				UpdateWindow ();
			}
		}

		CControlBar::OnLButtonDown(nFlags, point);
		return;
	}

	CBCGToolbarButton* pButton = GetButton(iButton);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	if (!m_bCustomizeMode)
	{
		m_iButtonCapture = iButton;

		// update the button before checking for disabled status
		UpdateButton(m_iButtonCapture);
		if (pButton->m_nStyle & TBBS_DISABLED)
		{
			m_iButtonCapture = -1;
			return;     // don't press it
		}

		pButton->m_nStyle |= TBBS_PRESSED;

		InvalidateButton (iButton);
		UpdateWindow(); // immediate feedback

		GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)pButton->m_nID);
	}
	else
	{
		int iSelected = m_iSelected;
		m_iSelected = iButton;

		CRect rect;
		GetItemRect (iButton, &rect);

		if (iSelected != -1)
		{
			InvalidateButton (iSelected);
		}

		m_pDragButton = GetButton (m_iSelected);
		ASSERT (m_pDragButton != NULL);

		InvalidateButton (iButton);
		UpdateWindow(); // immediate feedback

		if (m_pDragButton->CanBeStretched () &&
			abs (point.x - rect.right) <= STRETCH_DELTA)
		{
			m_bStretchButton = TRUE;

			m_rectTrack = m_pDragButton->m_rect;

			if (m_pDragButton->GetHwnd () != NULL)
			{
				m_rectTrack.InflateRect (2, 2);
			}

			SetCapture ();
			::SetCursor (m_hcurStretch);
		}
		else
		{
			COleDataSource srcItem;
			m_pDragButton->PrepareDrag (srcItem);

			GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)pButton->m_nID);

			m_DropSource.m_bDragStarted = FALSE;
			m_ptStartDrag = point;

			DROPEFFECT dropEffect = srcItem.DoDragDrop 
				(DROPEFFECT_COPY|DROPEFFECT_MOVE, &rect, &m_DropSource);

			if (m_DropSource.m_bDragStarted)
			{
				CPoint ptDrop;
				::GetCursorPos (&ptDrop);
				ScreenToClient (&ptDrop);

				if (dropEffect != DROPEFFECT_COPY && 
					m_pDragButton != NULL &&
					!m_DropSource.m_bEscapePressed &&
					!rect.PtInRect (ptDrop))
				{
					//---------------------
					// Remove source button:
					//---------------------
					RemoveButton (ButtonToIndex (m_pDragButton));

					CFrameWnd* pParent = GetParentFrame ();
					if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
					{
						pParent->RecalcLayout ();
						AdjustLocations ();
					}

					Invalidate ();
				}
			}

			m_pDragButton = NULL;
			m_ptStartDrag = CPoint (-1, -1);
		}
	}
}
//**************************************************************************************
void CBCGToolBar::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bCustomizeMode)
	{
		if (m_bStretchButton)
		{
			ASSERT_VALID (m_pDragButton);

			if (point.x - m_pDragButton->m_rect.left >= BUTTON_MIN_WIDTH)
			{
				CClientDC dc (this);

				CRect rectTrackOld = m_rectTrack;
				m_rectTrack.right = point.x;
				dc.DrawDragRect (&m_rectTrack, CSize (2, 2), &rectTrackOld, CSize (2, 2));
			}

			::SetCursor (m_hcurStretch);
		}

		return;
	}

	int iPrevHighlighted = m_iHighlighted;
	m_iHighlighted = HitTest (point);

	CBCGToolbarButton* pButton = m_iHighlighted == -1 ?
							NULL : GetButton (m_iHighlighted);
	if (pButton != NULL &&
		(pButton->m_nStyle & TBBS_SEPARATOR || pButton->m_nStyle & TBBS_DISABLED))
	{
		m_iHighlighted = -1;
	}

	if (iPrevHighlighted != m_iHighlighted)
	{
		BOOL bNeedUpdate = FALSE;

		if (m_iButtonCapture != -1)
		{
			CBCGToolbarButton* pTBBCapt = GetButton (m_iButtonCapture);
			ASSERT (pTBBCapt != NULL);
			ASSERT (!(pTBBCapt->m_nStyle & TBBS_SEPARATOR));

			UINT nNewStyle = (pTBBCapt->m_nStyle & ~TBBS_PRESSED);
			if (m_iHighlighted == m_iButtonCapture)
			{
				nNewStyle |= TBBS_PRESSED;
			}

			if (nNewStyle != pTBBCapt->m_nStyle)
			{
				SetButtonStyle (m_iButtonCapture, nNewStyle);
				bNeedUpdate = TRUE;
			}
		}

		if ((m_iButtonCapture == -1 || iPrevHighlighted == m_iButtonCapture) &&
			iPrevHighlighted != -1)
		{
			InvalidateButton (iPrevHighlighted);
			bNeedUpdate = TRUE;
		}

		if ((m_iButtonCapture == -1 || m_iHighlighted == m_iButtonCapture) &&
			m_iHighlighted != -1)
		{
			InvalidateButton (m_iHighlighted);
			bNeedUpdate = TRUE;
		}

		if (bNeedUpdate)
		{
			UpdateWindow ();
		}

		if (m_iHighlighted != -1)
		{
			ASSERT (pButton != NULL);
			GetOwner()->SendMessage (WM_SETMESSAGESTRING, (WPARAM)pButton->m_nID);

			if (iPrevHighlighted == -1)
			{
				SetCapture ();
			}
		}
		else
		{
			if (m_iButtonCapture == -1)
			{
				::ReleaseCapture ();
				GetOwner()->SendMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
			}
		}
	}
}
//*************************************************************************************
void CBCGToolBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bCustomizeMode)
	{
		if (m_bStretchButton)
		{
			ASSERT_VALID (m_pDragButton);

			CRect rect = m_pDragButton->m_rect;
			rect.right = point.x;

			if (rect.Width () >= BUTTON_MIN_WIDTH &&
				abs (m_pDragButton->m_rect.right - point.x) > STRETCH_DELTA)
			{
				m_pDragButton->OnSize (rect.Width ());

				CFrameWnd* pParent = GetParentFrame ();
				if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
				{
					pParent->RecalcLayout ();
					AdjustLocations ();
				}
			}

			m_rectTrack.SetRectEmpty ();

			m_pDragButton = NULL;
			m_bStretchButton = FALSE;

			Invalidate ();
			::ReleaseCapture ();
		}

		return;
	}

	if (m_iButtonCapture == -1)
	{
		CControlBar::OnLButtonUp(nFlags, point);
		return;     // not captured
	}

	ReleaseCapture();
	m_iHighlighted = HitTest (point);

	CBCGToolbarButton* pButton = GetButton(m_iButtonCapture);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));
	UINT nIDCmd = 0;

	UINT nNewStyle = (pButton->m_nStyle & ~TBBS_PRESSED);
	if (m_iButtonCapture == m_iHighlighted)
	{
		// we did not lose the capture
		if (HitTest(point) == m_iButtonCapture)
		{
			// give button a chance to update
			UpdateButton(m_iButtonCapture);

			// then check for disabled state
			if (!(pButton->m_nStyle & TBBS_DISABLED))
			{
				// pressed, will send command notification
				nIDCmd = pButton->m_nID;

				if (pButton->m_nStyle & TBBS_CHECKBOX)
				{
					// auto check: three state => down
					if (nNewStyle & TBBS_INDETERMINATE)
						nNewStyle &= ~TBBS_INDETERMINATE;

					nNewStyle ^= TBBS_CHECKED;
				}
			}
		}
	}

	GetOwner()->SendMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);

	int iButtonCapture = m_iButtonCapture;
	m_iButtonCapture = -1;
	m_iHighlighted = -1;

	if (HitTest(point) == iButtonCapture &&
		!pButton->OnClick (this) && nIDCmd != 0)
	{
		GetOwner()->SendMessage(WM_COMMAND, nIDCmd);    // send command
	}

	SetButtonStyle(iButtonCapture, nNewStyle);
	UpdateButton(iButtonCapture);
	InvalidateButton (iButtonCapture);

	UpdateWindow(); // immediate feedback
}
//*************************************************************************************
void CBCGToolBar::OnCancelMode()
{
	CControlBar::OnCancelMode();

	if (m_bStretchButton)
	{
		m_pDragButton = NULL;
		m_bStretchButton = FALSE;

		m_rectTrack.SetRectEmpty ();

		::ReleaseCapture ();
	}

	if (m_iButtonCapture >= 0 ||
		m_iHighlighted >= 0)
	{
		if (m_iButtonCapture >= 0)
		{
			CBCGToolbarButton* pButton = GetButton(m_iButtonCapture);
			ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));
			UINT nNewStyle = (pButton->m_nStyle & ~TBBS_PRESSED);
			if (GetCapture() == this)
				ReleaseCapture();
			SetButtonStyle(m_iButtonCapture, nNewStyle);
		}

		m_iButtonCapture = -1;
		m_iHighlighted = -1;
	}

	Invalidate ();
	UpdateWindow();
}
//*************************************************************************************
void CBCGToolBar::OnSysColorChange()
{
	globalData.UpdateSysColors ();
	globalData.UpdateSysMetrics();

	if (m_pImages != NULL)
	{
		m_pImages->OnSysColorChange ();
	}

	if (m_pUserImages != NULL)
	{
		m_pUserImages->OnSysColorChange ();
	}

	Invalidate ();
}

/////////////////////////////////////////////////////////////////////////////
// CBCGToolBar idle update through CToolCmdUI class

#define CToolCmdUI COldToolCmdUI

class CToolCmdUI : public CCmdUI        // class private to this file !
{
public: // re-implementations only
	virtual void Enable(BOOL bOn);
	virtual void SetCheck(int nCheck);
	virtual void SetText(LPCTSTR lpszText);
};

void CToolCmdUI::Enable(BOOL bOn)
{
	m_bEnableChanged = TRUE;
	CBCGToolBar* pToolBar = (CBCGToolBar*)m_pOther;
	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CBCGToolBar, pToolBar);
	ASSERT(m_nIndex < m_nIndexMax);

	UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) & ~TBBS_DISABLED;

	if (!bOn)
		nNewStyle |= TBBS_DISABLED;
	ASSERT(!(nNewStyle & TBBS_SEPARATOR));
	pToolBar->SetButtonStyle(m_nIndex, nNewStyle);
}
//*************************************************************************************
void CToolCmdUI::SetCheck(int nCheck)
{
	ASSERT (nCheck >= 0);
	if (nCheck > 2)
	{
		nCheck = 1;
	}

	CBCGToolBar* pToolBar = (CBCGToolBar*)m_pOther;
	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CBCGToolBar, pToolBar);
	ASSERT(m_nIndex < m_nIndexMax);

	UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) &
				~(TBBS_CHECKED | TBBS_INDETERMINATE);
	if (nCheck == 1)
		nNewStyle |= TBBS_CHECKED;
	else if (nCheck == 2)
		nNewStyle |= TBBS_INDETERMINATE;
	ASSERT(!(nNewStyle & TBBS_SEPARATOR));
	pToolBar->SetButtonStyle(m_nIndex, nNewStyle | TBBS_CHECKBOX);
}
//*************************************************************************************
void CToolCmdUI::SetText(LPCTSTR)
{
	// ignore it
}
//*************************************************************************************
void CBCGToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CToolCmdUI state;
	state.m_pOther = this;

	state.m_nIndexMax = (UINT)m_Buttons.GetCount ();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	  state.m_nIndex++)
	{
		CBCGToolbarButton* pButton = GetButton(state.m_nIndex);
		state.m_nID = pButton->m_nID;

		// ignore separators
		if (!(pButton->m_nStyle & TBBS_SEPARATOR))
			state.DoUpdate(pTarget, bDisableIfNoHndler);
	}

	// update the dialog controls added to the toolbar
	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}
//*************************************************************************************
void CBCGToolBar::UpdateButton(int nIndex)
{
	// determine target of command update
	CFrameWnd* pTarget = (CFrameWnd*)GetOwner();
	if (pTarget == NULL || !pTarget->IsFrameWnd())
		pTarget = GetParentFrame();

	// send the update notification
	if (pTarget != NULL)
	{
		CToolCmdUI state;
		state.m_pOther = this;
		state.m_nIndex = nIndex;
		state.m_nIndexMax = (UINT)m_Buttons.GetCount ();
		CBCGToolbarButton* pButton = GetButton(nIndex);
		state.m_nID = pButton->m_nID;
		state.DoUpdate(pTarget, pTarget->m_bAutoMenuEnable);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGToolBar diagnostics

#ifdef _DEBUG
void CBCGToolBar::AssertValid() const
{
	CControlBar::AssertValid();
}

void CBCGToolBar::Dump(CDumpContext& dc) const
{
	CControlBar::Dump(dc);

	dc << "\nm_iButtonCapture = " << m_iButtonCapture;
	dc << "\nm_sizeButton = " << m_sizeButton;
	dc << "\nm_sizeImage = " << m_sizeImage;

	if (dc.GetDepth() > 0)
	{
		int i = 0;
		for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; i ++)
		{
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
			ASSERT (pButton != NULL);

			dc << "\ntoolbar button[" << i << "] = {";
			dc << "\n\tnID = " << pButton->m_nID;
			dc << "\n\tnStyle = " << pButton->m_nStyle;
			if (pButton->m_nStyle & TBBS_SEPARATOR)
				dc << "\n\tiImage (separator width) = " << pButton->m_iImage;
			else
				dc <<"\n\tiImage (bitmap image index) = " << pButton->m_iImage;
			dc << "\n}";
		}
	}

	dc << "\n";
}
#endif

#undef new
#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

void CBCGToolBar::OnMove(int x, int y) 
{
	CControlBar::OnMove(x, y);
}
//**********************************************************************************************
void CBCGToolBar::DrawGripper (CDC* pDC)
{
	const int iGripperOffset = 3;
	const int iLinesNum = (m_dwDockStyle & CBRS_ALIGN_ANY) ? 2 : 1;

	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) ? TRUE : FALSE;

	CRect rectGripper;
	
	GetWindowRect (&rectGripper);
	ScreenToClient (&rectGripper);

	rectGripper.OffsetRect (-rectGripper.left, -rectGripper.top);
	rectGripper.DeflateRect (iGripperOffset + 1, iGripperOffset + 1);

	if (bHorz)
	{
		//-----------------
		// Gripper at left:
		//-----------------
		rectGripper.right = rectGripper.left + iGripperOffset;
        
		for (int i = 0; i < iLinesNum; i ++)
		{
			pDC->Draw3dRect (rectGripper, 
							globalData.clrBtnHilite, 
							globalData.clrBtnShadow);
			rectGripper.OffsetRect (iGripperOffset, 0);
		}
	} 
	else 
	{
		//----------------
		// Gripper at top:
		//----------------
		rectGripper.bottom = rectGripper.top + iGripperOffset;

		for (int i = 0; i < iLinesNum; i ++)
		{
			pDC->Draw3dRect (rectGripper,
							globalData.clrBtnHilite,
							globalData.clrBtnShadow);
			rectGripper.OffsetRect (0, iGripperOffset);
		}
	}
}
//******************************************************************************************
int CBCGToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_DropTarget.Register (this);
	m_penDrag.CreatePen (PS_SOLID, 1, globalData.clrBtnText);

	m_hcurStretch = AfxGetApp ()->LoadCursor (AFX_IDC_HSPLITBAR);
	m_hcurDelete = AfxGetApp ()->LoadCursor (IDC_DELETE);

	m_DropSource.m_hcurDelete = m_hcurDelete;

	CFont font;
	if (font.CreateStockObject (DEFAULT_GUI_FONT))
	{
		LOGFONT lf;
		
		if (font.GetLogFont (&lf) != 0)
		{
			lf.lfOrientation = 900;
			lf.lfEscapement = 900;
			strcpy (lf.lfFaceName, _T("Arial"));
			m_fontVert.CreateFontIndirect (&lf);
		}
	}

	gAllToolbars.AddTail (this);
	return 0;
}
//****************************************************************************************
DROPEFFECT CBCGToolBar::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	m_iDragIndex = -1;
	m_DropSource.m_bDeleteOnDrop = FALSE;

	return OnDragOver(pDataObject, dwKeyState, point);
}
//****************************************************************************************
void CBCGToolBar::OnDragLeave() 
{
	m_iDragIndex = -1;
	
	CRect rect = m_rectDrag;
	rect.InflateRect (2, 2);
	InvalidateRect (&rect);

	UpdateWindow ();

	m_rectDrag.SetRectEmpty ();
	m_iDragIndex = -1;

	m_DropSource.m_bDeleteOnDrop = TRUE;
}
//****************************************************************************************
DROPEFFECT CBCGToolBar::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	BOOL bCopy = (dwKeyState & MK_CONTROL);

	if (m_pDragButton == NULL)	// Drag from the other toolbar
	{
		//------------------
		// Remove selection:
		//------------------
		int iSelected = m_iSelected;
		m_iSelected = -1;

		if (iSelected != -1)
		{
			InvalidateButton (iSelected);
			UpdateWindow ();
		}
	}

	//---------------------
	// Find the drop place:
	//---------------------
	CRect rect = m_rectDrag;
	int iIndex = FindDropIndex (point, m_rectDrag);

	if (rect != m_rectDrag)
	{
		//--------------------
		// Redraw drop marker:
		//--------------------
		m_iDragIndex = iIndex;

		rect.InflateRect (2, 2);
		InvalidateRect (&rect);

		rect = m_rectDrag;
		rect.InflateRect (2, 2);
		InvalidateRect (&m_rectDrag);

		UpdateWindow ();
	}

	return (bCopy) ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
}
//****************************************************************************************
BOOL CBCGToolBar::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	ASSERT_VALID(this);

	int iDragIndex = m_iDragIndex;
	ASSERT (iDragIndex >= 0);

	CBCGToolbarButton* pDragButton = m_pDragButton;
	m_pDragButton = NULL;

	OnDragLeave();

	//----------------------------------------------------
	// Create a button object from the OLE clipboard data:
	//----------------------------------------------------
	CBCGToolbarButton* pButton = CBCGToolbarButton::CreateFromOleData (pDataObject);
	ASSERT (pButton != NULL);

	if (pButton->m_bDragFromCollection && pButton->m_bUserButton)
	{
		ASSERT (pDragButton == NULL);

		//----------------------------------------------
		// User-defined button by defaulr have no image:
		//----------------------------------------------
		CButtonAppearanceDlg dlg (pButton, m_pUserImages, this);
		if (dlg.DoModal () != IDOK)
		{
			delete pButton;
			return FALSE;
		}
	}

	if (pDragButton != NULL && dropEffect != DROPEFFECT_COPY)
	{
		int iOldIndex = ButtonToIndex (pDragButton);
		if (iDragIndex == iOldIndex || iDragIndex == iOldIndex + 1)
		{
			AddRemoveSeparator (pDragButton, m_ptStartDrag, point);
			delete pButton;
			return TRUE;
		}
		
		RemoveButton (iOldIndex);
		if (iDragIndex > iOldIndex)
		{
			iDragIndex --;
		}
	}

	if (InsertButton (pButton, iDragIndex) == -1)
	{
		ASSERT (FALSE);
		delete pButton;
		return FALSE;
	}

	CFrameWnd* pParent = GetParentFrame ();
	if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
	{
		pParent->RecalcLayout ();
		AdjustLocations ();
	}

	m_iSelected = -1;
	Invalidate ();
	return TRUE;
}
//****************************************************************************************
BOOL CBCGToolBar::SetCustomizeMode (BOOL bSet)
{
	if (m_bCustomizeMode == bSet)
	{
		return FALSE;
	}

	m_bCustomizeMode = bSet;

	for (POSITION posTlb = gAllToolbars.GetHeadPosition (); posTlb != NULL;)
	{
		CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (posTlb);
		ASSERT_VALID(pToolBar);

		pToolBar->m_iButtonCapture = -1;
		pToolBar->m_iHighlighted = -1;
		pToolBar->m_iSelected = -1;

		for (POSITION pos = pToolBar->m_Buttons.GetHeadPosition (); pos != NULL;)
		{
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) pToolBar->m_Buttons.GetNext (pos);
			ASSERT (pButton != NULL);

			HWND hwnd = pButton->GetHwnd ();
			if (hwnd != NULL)
			{
				::EnableWindow (hwnd, !bSet);
			}
		}

		pToolBar->Invalidate ();
		pToolBar->UpdateWindow ();
	}

	return TRUE;
}
//********************************************************************************
int CBCGToolBar::GetCommandButtons (UINT uiCmd, CObList& listButtons)
{
	listButtons.RemoveAll ();
	if (uiCmd == 0)
	{
		return 0;
	}

	for (POSITION posTlb = gAllToolbars.GetHeadPosition (); posTlb != NULL;)
	{
		CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (posTlb);
		ASSERT_VALID(pToolBar);

		for (POSITION pos = pToolBar->m_Buttons.GetHeadPosition (); pos != NULL;)
		{
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) pToolBar->m_Buttons.GetNext (pos);
			ASSERT (pButton != NULL);

			if (pButton->m_nID == uiCmd)
			{
				listButtons.AddTail (pButton);
			}
		}
	}

	return listButtons.GetCount ();
}
//********************************************************************************
int CBCGToolBar::FindDropIndex (const CPoint p, CRect& rectDrag) const
{
	int iDragButton = -1;
	rectDrag.SetRectEmpty ();

	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) ? TRUE : FALSE;

	CPoint point = p;
	if (point.y < 0)
	{
		point.y = 0;
	}

	if (m_Buttons.IsEmpty ())
	{
		GetClientRect (&rectDrag);
		iDragButton = 0;
	}
	else
	{
		if (bHorz)
		{
			int iOffset = m_sizeButton.cy;
			int iButton = 0;
			CRect rectPrev;

			POSITION pos;
			for (pos = m_Buttons.GetHeadPosition (); pos != NULL; iButton ++)
			{
				CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
				ASSERT (pButton != NULL);

				CRect rect = pButton->m_rect;

				if (iButton > 0 && rect.top != rectPrev.top)
				{
					iOffset	= rect.top - rectPrev.bottom;
					break;
				}

				rectPrev = rect;
			}

			int iCursorRow = point.y / (m_sizeButton.cy + iOffset);
			int iRow = 0;
			int iCol;
			iButton = 0;

			for (pos = m_Buttons.GetHeadPosition (); pos != NULL; iButton ++, iCol ++)
			{
				CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
				ASSERT (pButton != NULL);

				CRect rect = pButton->m_rect;
				
				if (iButton > 0 && rect.top != rectPrev.top)
				{
					iRow ++;
					iCol = 0;
				}

				if (iRow > iCursorRow)
				{
					rectDrag = rectPrev;
					rectDrag.left = rectDrag.right;
					iDragButton = iButton - 1;
					break;
				}

				if (iRow == iCursorRow)
				{
					if (point.x < rect.left)
					{
						iDragButton = iButton;
						rectDrag = rect;
						rectDrag.right = rectDrag.left;
						break;
					}
					else if (point.x <= rect.right)
					{
						rectDrag = rect;
						if (point.x - rect.left > rect.right - point.x)
						{
							iDragButton = iButton + 1;
							rectDrag.left = rectDrag.right;
						}
						else
						{
							iDragButton = iButton;
							rectDrag.right = rectDrag.left;
						}
						break;
					}
				}

				rectPrev = rect;
			}

			if (iDragButton == -1 && iRow == iCursorRow)
			{
				rectDrag = rectPrev;
				rectDrag.left = rectDrag.right;
				iDragButton = iButton;
			}
		}
		else
		{
			int iButton = 0;
			for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL; iButton ++)
			{
				CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
				ASSERT (pButton != NULL);

				CRect rect = pButton->m_rect;

				if (point.y < rect.top)
				{
					iDragButton = iButton;
					rectDrag = rect;
					rectDrag.bottom = rectDrag.top;
					break;
				}
				else if (point.y <= rect.bottom)
				{
					rectDrag = rect;
					if (point.y - rect.top > rect.bottom - point.y)
					{
						iDragButton = iButton + 1;
						rectDrag.top = rectDrag.bottom;
					}
					else
					{
						iDragButton = iButton;
						rectDrag.bottom = rectDrag.top;
					}
					break;
				}
			}
		}
	}

	if (iDragButton >= 0)
	{
		const int iCursorSize = 6;

		CRect rectClient;	// Client area rectangle
		GetClientRect (&rectClient);

		if (bHorz)
		{
			rectDrag.left = 
				max (rectClient.left, rectDrag.left - iCursorSize / 2);

			rectDrag.right = rectDrag.left + iCursorSize;
			if (rectDrag.right > rectClient.right)
			{
				rectDrag.right = rectClient.right;
				rectDrag.left = rectDrag.right - iCursorSize;
			}
		}
		else
		{
			rectDrag.top = 
				max (rectClient.top, rectDrag.top - iCursorSize / 2);

			rectDrag.bottom = rectDrag.top + iCursorSize;
			if (rectDrag.bottom > rectClient.bottom)
			{
				rectDrag.bottom = rectClient.bottom;
				rectDrag.top = rectDrag.bottom - iCursorSize;
			}
		}
	}

	return iDragButton;
}
//***********************************************************************
void CBCGToolBar::DrawDragMarker (CDC* pDC)
{
	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) ? TRUE : FALSE;

	CPen* pOldPen = (CPen*) pDC->SelectObject (&m_penDrag);

	for (int i = 0; i < 2; i ++)
	{
		if (bHorz)
		{
			pDC->MoveTo (m_rectDrag.left + m_rectDrag.Width () / 2 + i - 1, m_rectDrag.top);
			pDC->LineTo (m_rectDrag.left + m_rectDrag.Width () / 2 + i - 1, m_rectDrag.bottom);

			pDC->MoveTo (m_rectDrag.left + i, m_rectDrag.top + i);
			pDC->LineTo (m_rectDrag.right - i, m_rectDrag.top + i);

			pDC->MoveTo (m_rectDrag.left + i, m_rectDrag.bottom - i - 1);
			pDC->LineTo (m_rectDrag.right - i, m_rectDrag.bottom - i - 1);
		}
		else
		{
			pDC->MoveTo (m_rectDrag.left, m_rectDrag.top + m_rectDrag.Height () / 2 + i - 1);
			pDC->LineTo (m_rectDrag.right, m_rectDrag.top + m_rectDrag.Height () / 2 + i - 1);

			pDC->MoveTo (m_rectDrag.left + i, m_rectDrag.top + i);
			pDC->LineTo (m_rectDrag.left + i, m_rectDrag.bottom - i);

			pDC->MoveTo (m_rectDrag.right - i - 1, m_rectDrag.top + i);
			pDC->LineTo (m_rectDrag.right - i - 1, m_rectDrag.bottom - i);
		}
	}

	pDC->SelectObject (pOldPen);
}
//********************************************************************
void CBCGToolBar::OnDestroy() 
{
	CControlBar::OnDestroy();

	::DeleteObject (m_hcurStretch);
	::DeleteObject (m_hcurDelete);

	for (POSITION pos = gAllToolbars.GetHeadPosition (); pos != NULL;)
	{
		POSITION posSave = pos;

		CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (pos);
		ASSERT_VALID(pToolBar);

		if (pToolBar == this)
		{
			gAllToolbars.RemoveAt (posSave);
			break;
		}
	}

}
//********************************************************************
void CBCGToolBar::Serialize (CArchive& ar)
{
	CControlBar::Serialize (ar);

	if (ar.IsLoading ())
	{
		RemoveAllButtons ();
	}

	m_Buttons.Serialize (ar);

	if (ar.IsLoading ())
	{
		for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
		{
			CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
			ASSERT (pButton != NULL);

			pButton->OnChangeParentWnd (this);
		}
		
		AdjustLocations ();
	}

	if (ar.IsLoading ())
	{
		ar >> m_bShowTooltips;
	}
	else
	{
		ar << m_bShowTooltips;
	}
}
//*********************************************************************
BOOL CBCGToolBar::SaveState (LPCTSTR lpszProfileName, int nIndex)
{
	BOOL bResult = FALSE;

	CWinApp* pApp = AfxGetApp ();

	CString strSection;
	strSection.Format (REG_SECTION_FMT, lpszProfileName, nIndex);

	try
	{
		CMemFile file;

		{
			CArchive ar (&file, CArchive::store);

			Serialize (ar);
			ar.Flush ();
		}

		UINT uiDataSize = file.GetLength ();
		LPBYTE lpbData = file.Detach ();

		if (lpbData != NULL)
		{
			bResult = pApp->WriteProfileBinary (strSection, REG_ENTRY_NAME,
												lpbData, uiDataSize);
			free (lpbData);
		}
	}
	catch (CMemoryException* pEx)
	{
		pEx->Delete ();
		TRACE(_T("Memory exception in CBCGToolBar::SaveState ()!\n"));
	}

	return bResult;
}
//*********************************************************************
BOOL CBCGToolBar::LoadState (LPCTSTR lpszProfileName, int nIndex)
{
	BOOL bResult = FALSE;

	CWinApp* pApp = AfxGetApp ();

	CString strSection;
	strSection.Format (REG_SECTION_FMT, lpszProfileName, nIndex);

	LPBYTE	lpbData = NULL;
	UINT	uiDataSize;

	if (!pApp->GetProfileBinary (strSection, REG_ENTRY_NAME, &lpbData, &uiDataSize))
	{
		return FALSE;
	}

	try
	{
		CMemFile file (lpbData, uiDataSize);
		CArchive ar (&file, CArchive::load);

		Serialize (ar);
		bResult = TRUE;
	}
	catch (CMemoryException* pEx)
	{
		pEx->Delete ();
		TRACE(_T("Memory exception in CBCGToolBar::LoadState ()!\n"));
	}
	catch (CArchiveException* pEx)
	{
		pEx->Delete ();
		TRACE(_T("CArchiveException exception in CBCGToolBar::LoadState ()!\n"));
	}

	if (lpbData != NULL)
	{
		delete lpbData;
	}

	CFrameWnd* pParent = GetParentFrame ();
	if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
	{
		pParent->RecalcLayout ();
		AdjustLocations ();
	}

	return bResult;
}
//*******************************************************************************************
void CBCGToolBar::OnContextMenu(CWnd*, CPoint point)
{
	CPoint ptClient = point;
	ScreenToClient (&ptClient);

	int iButton = HitTest(ptClient);

	if (!m_bCustomizeMode)
	{
		BOOL bShowMenu = TRUE;

		if (iButton != -1)
		{
			CBCGToolbarButton* pButton = GetButton(iButton);
			ASSERT (pButton != NULL);

			bShowMenu = (pButton->m_nStyle & TBBS_DISABLED);
		}

		if (bShowMenu)
		{
			CFrameWnd* pParentFrame = (m_pDockSite == NULL) ?
				GetDockingFrame() : m_pDockSite;
			ASSERT_VALID(pParentFrame);

			pParentFrame->SendMessage (BCGM_TOOLBARMENU,
				(WPARAM) GetSafeHwnd (),
				MAKELPARAM(point.x, point.y));
		}

		return;
	}

	int iSelected = m_iSelected;
	m_iSelected = iButton;

	if (iSelected != -1)
	{
		InvalidateButton (iSelected);
	}

	if (m_iSelected != -1)
	{
		InvalidateButton (m_iSelected);
	}

	UpdateWindow ();

	if (iButton < 0) // nothing hit
	{
		return;
	}

	CBCGToolbarButton* pButton = GetButton(m_iSelected);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_POPUP_BCGTOOL_BAR));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		if (!pButton->m_bUserButton)
		{
			pPopup->EnableMenuItem (ID_TOOLBAR_APPEARANCE, MF_GRAYED | MF_BYCOMMAND);
			pPopup->EnableMenuItem (ID_TOOLBAR_IMAGE, MF_GRAYED | MF_BYCOMMAND);
			pPopup->EnableMenuItem (ID_TOOLBAR_IMAGE_AND_TEXT, MF_GRAYED | MF_BYCOMMAND);
			pPopup->EnableMenuItem (ID_TOOLBAR_TEXT, MF_GRAYED | MF_BYCOMMAND);
		}
		else
		{
			if (pButton->m_bText)
			{
				if (pButton->m_bImage)
				{
					pPopup->CheckMenuItem (ID_TOOLBAR_IMAGE_AND_TEXT, MF_CHECKED  | MF_BYCOMMAND);
				}
				else
				{
					pPopup->CheckMenuItem (ID_TOOLBAR_TEXT, MF_CHECKED  | MF_BYCOMMAND);
				}
			}
			else
			{
				ASSERT (pButton->m_bImage);
				pPopup->CheckMenuItem (ID_TOOLBAR_IMAGE, MF_CHECKED  | MF_BYCOMMAND);
			}
		}

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}
//*******************************************************************************************
void CBCGToolBar::OnToolbarAppearance() 
{
	ASSERT (m_bCustomizeMode);
	ASSERT (m_iSelected >= 0);

	CBCGToolbarButton* pButton = GetButton(m_iSelected);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	CButtonAppearanceDlg dlg (pButton, m_pUserImages, this);
	if (dlg.DoModal () == IDOK)
	{
		CFrameWnd* pParent = GetParentFrame ();
		if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
		{
			pParent->RecalcLayout ();
			AdjustLocations ();
		}
	}
}
//*******************************************************************************************
void CBCGToolBar::OnToolbarDelete() 
{
	ASSERT (m_iSelected >= 0);
	RemoveButton (m_iSelected);
	
	m_iSelected = -1;
	CFrameWnd* pParent = GetParentFrame ();
	if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
	{
		pParent->RecalcLayout ();
		AdjustLocations ();
	}
}
//*******************************************************************************************
void CBCGToolBar::OnToolbarImage() 
{
	ASSERT (m_bCustomizeMode);
	ASSERT (m_iSelected >= 0);

	CBCGToolbarButton* pButton = GetButton(m_iSelected);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	BOOL bSaveText = pButton->m_bText;
	BOOL bSaveImage = pButton->m_bImage;

	pButton->m_bText = FALSE;
	pButton->m_bImage = TRUE;

	if (pButton->m_iImage < 0)
	{
		CButtonAppearanceDlg dlg (pButton, m_pUserImages, this);
		if (dlg.DoModal () != IDOK)
		{
			pButton->m_bText = bSaveText;
			pButton->m_bImage = bSaveImage;
			return;
		}
	}

	CFrameWnd* pParent = GetParentFrame ();
	if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
	{
		pParent->RecalcLayout ();
		AdjustLocations ();
	}
}
//*******************************************************************************************
void CBCGToolBar::OnToolbarImageAndText() 
{
	ASSERT (m_bCustomizeMode);
	ASSERT (m_iSelected >= 0);

	CBCGToolbarButton* pButton = GetButton(m_iSelected);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	BOOL bSaveText = pButton->m_bText;
	BOOL bSaveImage = pButton->m_bImage;

	pButton->m_bText = TRUE;
	pButton->m_bImage = TRUE;

	if (pButton->m_iImage < 0)
	{
		CButtonAppearanceDlg dlg (pButton, m_pUserImages, this);
		if (dlg.DoModal () != IDOK)
		{
			pButton->m_bText = bSaveText;
			pButton->m_bImage = bSaveImage;
			return;
		}
	}

	CFrameWnd* pParent = GetParentFrame ();
	if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
	{
		pParent->RecalcLayout ();
		AdjustLocations ();
	}
}
//*******************************************************************************************
void CBCGToolBar::OnToolbarStartGroup() 
{
	ASSERT (m_iSelected >= 0);
	InsertSeparator (m_iSelected + 1);

	CFrameWnd* pParent = GetParentFrame ();
	if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
	{
		pParent->RecalcLayout ();
		AdjustLocations ();
	}
}
//*******************************************************************************************
void CBCGToolBar::OnToolbarText() 
{
	ASSERT (m_bCustomizeMode);
	ASSERT (m_iSelected >= 0);

	CBCGToolbarButton* pButton = GetButton(m_iSelected);
	ASSERT (pButton != NULL);
	ASSERT(!(pButton->m_nStyle & TBBS_SEPARATOR));

	pButton->m_bText = TRUE;
	pButton->m_bImage = FALSE;

	CFrameWnd* pParent = GetParentFrame ();
	if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
	{
		pParent->RecalcLayout ();
		AdjustLocations ();
	}
}
//************************************************************************************
void CBCGToolBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CControlBar::OnWindowPosChanged(lpwndpos);

	if (!m_bCustomizeMode || g_pWndCustomize == NULL)
	{
		return;
	}

	if (lpwndpos->flags & SWP_HIDEWINDOW)
	{
		g_pWndCustomize->ShowToolBar (this, FALSE);
	}
	
	if (lpwndpos->flags & SWP_SHOWWINDOW)
	{
		g_pWndCustomize->ShowToolBar (this, TRUE);
	}
}
//**************************************************************************************
HBRUSH CBCGToolBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CControlBar::OnCtlColor (pDC, pWnd, nCtlColor);
	if (!m_bCustomizeMode)
	{
		return hbr;
	}

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
//**************************************************************************************
int CBCGToolBar::GetCount () const
{
	return m_Buttons.GetCount ();
}
//*************************************************************************************
BOOL CBCGToolBar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	BOOL bStretch = m_bStretchButton;

	if (!bStretch && m_bCustomizeMode && m_iSelected != -1)
	{
		CPoint ptCursor;
		::GetCursorPos (&ptCursor);
		ScreenToClient (&ptCursor);

		if (HitTest (ptCursor) == m_iSelected)
		{
			CBCGToolbarButton* pButton = GetButton (m_iSelected);
			ASSERT_VALID (pButton);

			if (pButton->CanBeStretched () &&
				abs (ptCursor.x - pButton->m_rect.right) <= STRETCH_DELTA)
			{
				bStretch = TRUE;
			}
		}
	}

	if (bStretch)
	{
		::SetCursor (m_hcurStretch);
		return TRUE;
	}
	
	return CControlBar::OnSetCursor(pWnd, nHitTest, message);
}
//****************************************************************************************
BOOL CBCGToolBar::PreTranslateMessage(MSG* pMsg) 
{
	if (m_bStretchButton &&
		pMsg->message == WM_KEYDOWN &&
		pMsg->wParam == VK_ESCAPE)
	{
		OnCancelMode ();
		return TRUE;
	}

	return CControlBar::PreTranslateMessage(pMsg);
}
//**************************************************************************************
BOOL CBCGToolBar::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (m_bCustomizeMode)
	{
		return CControlBar::OnCommand (wParam, lParam);
	}

	BOOL bAccelerator = FALSE;
	int nNotifyCode = HIWORD (wParam);

	// Find the control send the message:
	HWND hWndCtrl = (HWND)lParam;
	if (hWndCtrl == NULL)
	{
		if (wParam == IDCANCEL)	// ESC was pressed
		{
			GetOwner()->SetFocus ();
			return TRUE;
		}

		if (wParam != IDOK ||
			(hWndCtrl = ::GetFocus ()) == NULL)
		{
			return FALSE;
		}

		bAccelerator = TRUE;
		nNotifyCode = 0;
	}

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT_VALID (pButton);

		HWND hwdList = pButton->GetHwnd ();
		if (hwdList == NULL)	// No control
		{
			continue;
		}

		if (hwdList == hWndCtrl || ::IsChild (hwdList, hWndCtrl))
		{
			if (!bAccelerator)
			{
				ASSERT (LOWORD (wParam) == pButton->m_nID);
				if (!pButton->NotifyCommand (nNotifyCode))
				{
					break;
				}
			}

			GetOwner()->SendMessage (WM_COMMAND, 
				MAKEWPARAM (pButton->m_nID, nNotifyCode), 
					bAccelerator ? (LPARAM) hwdList : 0);
			return TRUE;
		}
	}

	return TRUE;
}
//*************************************************************************************
CBCGToolBar* CBCGToolBar::FromHandlePermanent (HWND hwnd)
{
	for (POSITION posTlb = gAllToolbars.GetHeadPosition (); posTlb != NULL;)
	{
		CBCGToolBar* pToolBar = (CBCGToolBar*) gAllToolbars.GetNext (posTlb);
		ASSERT_VALID(pToolBar);

		if (pToolBar->GetSafeHwnd () == hwnd)
		{
			return pToolBar;
		}
	}

	return NULL;
}
//**********************************************************************************
CSize CBCGToolBar::CalcLayout(DWORD dwMode, int nLength)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(m_hWnd));
	
	if (dwMode & LM_HORZDOCK)
	{
		ASSERT(dwMode & LM_HORZ);
	}

	CSize sizeResult(0,0);
	BOOL bHorz = (dwMode & LM_HORZ);

	if (!(m_dwStyle & CBRS_SIZE_FIXED))
	{
		BOOL bDynamic = m_dwStyle & CBRS_SIZE_DYNAMIC;

		if (bDynamic && (dwMode & LM_MRUWIDTH))
			SizeToolBar(m_nMRUWidth);
		else if (bDynamic && (dwMode & LM_HORZDOCK))
			SizeToolBar(32767);
		else if (bDynamic && (dwMode & LM_VERTDOCK))
		{
			SizeToolBar(0);
		}
		else if (bDynamic && (nLength != -1))
		{
			CRect rect; rect.SetRectEmpty();
			CalcInsideRect(rect, (dwMode & LM_HORZ));
			BOOL bVert = (dwMode & LM_LENGTHY);

			int nLen = nLength + (bVert ? rect.Height() : rect.Width());

			SizeToolBar(nLen, bVert);
		}
		else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
			SizeToolBar(m_nMRUWidth);
		else
			SizeToolBar((dwMode & LM_HORZ) ? 32767 : 0);
	}

	sizeResult = CalcSize();

	if (dwMode & LM_COMMIT)
	{
		if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
			m_nMRUWidth = sizeResult.cx;
	}

	//BLOCK: Adjust Margins
	{
		CRect rect; rect.SetRectEmpty();
		CalcInsideRect(rect, (dwMode & LM_HORZ));
		sizeResult.cy -= rect.Height();
		sizeResult.cx -= rect.Width();

		CSize size = CControlBar::CalcFixedLayout((dwMode & LM_STRETCH), (dwMode & LM_HORZ));
		sizeResult.cx = max(sizeResult.cx, size.cx);
		sizeResult.cy = max(sizeResult.cy, size.cy);
	}

	return sizeResult;
}
//**********************************************************************************
CSize CBCGToolBar::CalcSize ()
{
	CSize sizeResult (m_sizeButton.cx, m_sizeButton.cy);

	int iStartX = 0;
	int iStartY = 0;

	BOOL bVertDock = (m_dwStyle & CBRS_ORIENT_HORZ) == 0;
	CPoint cur (iStartX, iStartY);

	CClientDC dc (this);
	CFont* pOldFont = (CFont*) dc.SelectStockObject (DEFAULT_GUI_FONT);
	ASSERT (pOldFont != NULL);

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		int iSize = pButton->OnCalculateSize (&dc, m_sizeButton, !bVertDock);
		if (!bVertDock)
		{
			if (cur.x == iStartX && pButton->m_nStyle & TBBS_SEPARATOR)
			{
				iSize = 0;
			}

			sizeResult.cx = max (cur.x + iSize, sizeResult.cx);
			sizeResult.cy = max (cur.y + m_sizeButton.cy, sizeResult.cy);

			cur.x += iSize;

			if (pButton->m_bWrap)
			{
				cur.x = iStartX;
				cur.y += m_sizeButton.cy + LINE_OFFSET;
			}
		}
		else
		{
			sizeResult.cx = max (cur.x + m_sizeButton.cx, sizeResult.cx);
			sizeResult.cy = max (cur.y + iSize, sizeResult.cy);

			cur.x = iStartX;
			cur.y += iSize;
		}
	}

	dc.SelectObject (pOldFont);
	return sizeResult;
}
//**********************************************************************************
int CBCGToolBar::WrapToolBar (int nWidth)
{
	int nResult = 0;
	
	BOOL bVertDock = (m_dwStyle & CBRS_ORIENT_HORZ) == 0;

	CClientDC dc (this);

	CFont* pOldFont = (CFont*) dc.SelectStockObject (DEFAULT_GUI_FONT);
	ASSERT (pOldFont != NULL);

	CBCGToolbarButton* pPrevButton = NULL;

	CRect rect;
	GetClientRect(rect);

	int x = 0;
	int y = rect.top;

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		pButton->m_bWrap = FALSE;

		int dx = pButton->OnCalculateSize (&dc, m_sizeButton, !bVertDock);
		if (x + dx > nWidth)
		{
			if (pPrevButton != NULL)
			{
				pPrevButton->m_bWrap = TRUE;
				x = 0;
				y += m_sizeButton.cy + LINE_OFFSET;
				nResult ++;
			}

			if (pButton->m_nStyle & TBBS_SEPARATOR)
			{
				// Don't show separator on the first column!
				dx = 0;
			}
		}

		pPrevButton = pButton;
		x += dx;
	}

	dc.SelectObject (pOldFont);
	return nResult + 1;
}
//**********************************************************************************
void  CBCGToolBar::SizeToolBar (int nLength, BOOL bVert)
{
	CSize size;

	if (!bVert)
	{
		int nMin, nMax, nTarget, nCurrent, nMid;

		// Wrap ToolBar vertically
		nMin = 0;
		nCurrent = WrapToolBar(nMin);

		// Wrap ToolBar as specified
		nMax = nLength;
		nTarget = WrapToolBar(nMax);

		if (nCurrent != nTarget)
		{
			while (nMin < nMax)
			{
				nMid = (nMin + nMax) / 2;
				nCurrent = WrapToolBar(nMid);

				if (nCurrent == nTarget)
					nMax = nMid;
				else
				{
					if (nMin == nMid)
					{
						WrapToolBar(nMax);
						break;
					}
					nMin = nMid;
				}
			}
		}

		size = CalcSize ();
		WrapToolBar (size.cx);
	}
	else
	{
		int iWidth = 32767;
		WrapToolBar (iWidth);

		size = CalcSize();
		if (size.cy <= nLength)
		{
			iWidth = 0;
			do
			{
				iWidth += m_sizeButton.cx;
				WrapToolBar (iWidth);
				size = CalcSize();
			}
			while (size.cy > nLength);
		}

		WrapToolBar (size.cx);
	}
}
//**********************************************************************************
void CBCGToolBar::OnSize(UINT nType, int cx, int cy) 
{
	CControlBar::OnSize(nType, cx, cy);
	
	if (m_bCustomizeMode)
	{
		OnCancelMode ();
	}

	AdjustLocations ();
}
//**********************************************************************************
void CBCGToolBar::AdjustLocations ()
{
	ASSERT_VALID(this);

	BOOL bHorz = m_dwStyle & CBRS_ORIENT_HORZ ? TRUE : FALSE;

	CRect rect;
	GetClientRect(rect);

	CRect rectClient;
	GetClientRect (rectClient);
	if (rectClient.Width () < 2 * m_sizeButton.cx)
	{
		bHorz = FALSE;
	}

	CClientDC dc (this);
	CFont* pOldFont;
	if (bHorz)
	{
		pOldFont = (CFont*) dc.SelectStockObject (DEFAULT_GUI_FONT);
	}
	else
	{
		pOldFont = (CFont*) dc.SelectObject (&m_fontVert);
	}
	
	ASSERT (pOldFont != NULL);

	int iStartOffset;
	if (bHorz)
	{
		iStartOffset = rect.left;
	}
	else
	{
		iStartOffset = rect.top;
	}

	int iOffset = iStartOffset;
	int y = rect.top;

	for (POSITION pos = m_Buttons.GetHeadPosition (); pos != NULL;)
	{
		CBCGToolbarButton* pButton = (CBCGToolbarButton*) m_Buttons.GetNext (pos);
		ASSERT (pButton != NULL);

		int iSize = pButton->OnCalculateSize (&dc, m_sizeButton, bHorz);
		if (iOffset == iStartOffset && pButton->m_nStyle & TBBS_SEPARATOR)
		{
			iSize = 0;
		}

		CRect rectButton;
		if (bHorz)
		{
			rectButton.left = iOffset;
			rectButton.right = iOffset + iSize;
			rectButton.top = y;
			rectButton.bottom = rectButton.top + m_sizeButton.cy;
		}
		else
		{
			rectButton.left = rect.left;
			rectButton.right = rect.left + m_sizeButton.cx;
			rectButton.top = iOffset;
			rectButton.bottom = iOffset + iSize;
		}

		pButton->m_rect = rectButton;
		pButton->OnMove ();

		iOffset += iSize;
		if (pButton->m_bWrap && bHorz && IsFloating ())
		{
			iOffset = iStartOffset;
			y += m_sizeButton.cy + LINE_OFFSET;
		}
	}

	dc.SelectObject (pOldFont);

	Invalidate ();
	UpdateWindow ();
}
//**********************************************************************************
void CBCGToolBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;

	//---------------------------------------------------------
	// Calculate border space (will add to top/bottom, subtract 
	// from right/bottom):
	//---------------------------------------------------------
	CRect rect;
	rect.SetRectEmpty ();
	CalcInsideRect (rect, bHorz);

	//-----------------------------------------
	// Adjust non-client area for border space:
	//-----------------------------------------
	lpncsp->rgrc [0].left += rect.left;
	lpncsp->rgrc [0].top += rect.top;
	lpncsp->rgrc [0].right += rect.right;
	lpncsp->rgrc [0].bottom += rect.bottom;

	//---------------------------------------------------
	// Adjust non-client area for gripper at left or top:
	//---------------------------------------------------
	if (bHorz) 
	{
		lpncsp->rgrc [0].left += 4;
		lpncsp->rgrc [0].right += 4;
	} 
	else
	{
		lpncsp->rgrc [0].top += 6;
		lpncsp->rgrc [0].bottom += 6;
	}
}
//**********************************************************************************
void CBCGToolBar::OnNcPaint() 
{
	CControlBar::EraseNonClient();

    if (!IsFloating ())
	{
		CWindowDC dc (this);
		DrawGripper (&dc);
	}
}
//**********************************************************************************
UINT CBCGToolBar::OnNcHitTest(CPoint point) 
{
	return HTCLIENT;
}
//**********************************************************************************
DWORD CBCGToolBar::RecalcDelayShow(AFX_SIZEPARENTPARAMS* lpLayout)
{
	DWORD dwRes = CControlBar::RecalcDelayShow (lpLayout);

	if (!IsFloating ())
	{
		AdjustLocations ();
	}

	return dwRes;
}
//*********************************************************************************
void CBCGToolBar::AddRemoveSeparator (const CBCGToolbarButton* pButton,
						const CPoint& ptStart, const CPoint& ptDrop)
{
	ASSERT_VALID (pButton);
	
	int iIndex = ButtonToIndex (pButton);
	if (iIndex <= 0)
	{
		return;
	}

	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
	int iDelta = (bHorz) ? ptDrop.x - ptStart.x : ptDrop.y - ptStart.y;

	if (abs (iDelta) < STRETCH_DELTA)
	{
		// Ignore small move....
		return;
	}

	if (iDelta > 0)	// Add a separator left of button
	{
		const CBCGToolbarButton* pLeftButton = GetButton (iIndex - 1);
		ASSERT_VALID (pLeftButton);

		if (pLeftButton->m_nStyle & TBBS_SEPARATOR)
		{
			// Already have separator, do nothing...
			return;
		}

		InsertSeparator (iIndex);
	}
	else	// Remove a separator in the left size
	{
		const CBCGToolbarButton* pLeftButton = GetButton (iIndex - 1);
		ASSERT_VALID (pLeftButton);

		if ((pLeftButton->m_nStyle & TBBS_SEPARATOR) == 0)
		{
			// Not a separator, do nothing...
			return;
		}

		RemoveButton (iIndex - 1);
	}

	CFrameWnd* pParent = GetParentFrame ();
	if (pParent != NULL && pParent->GetSafeHwnd () != NULL)
	{
		pParent->RecalcLayout ();
		AdjustLocations ();
	}

	m_iSelected = -1;
	Invalidate ();
}
