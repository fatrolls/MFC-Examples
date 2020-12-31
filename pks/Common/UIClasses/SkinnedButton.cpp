// SkinnedButton.cpp : implementation file
//

#include "StdAfx.h"
#include "SkinnedButton.h"
#include "..\Tools\GlobalFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_HAND	MAKEINTRESOURCE(32649)
/////////////////////////////////////////////////////////////////////////////
// CSkinnedButton

CSkinnedButton::CSkinnedButton()
{
	m_bIsDragging = FALSE;
	m_lButtonType = FL_BUTTON_TYPE_NORMAL;
	m_bPressed = FALSE;
	m_bFindEdges = FALSE;
	m_lTextAlign = TEXT_ALIGN_CENTER_HORIZ | TEXT_ALIGN_CENTER_VERT;
	m_hBitmap = NULL;
	m_bIsSliderParent = FALSE;

	m_hRgn = NULL;
	m_hRgnWindow = NULL;
}

CSkinnedButton::~CSkinnedButton()
{	
	DestroyWindow();

	m_hBitmap = NULL;

	if(m_hRgn != NULL)
	{
		::DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
	if(m_hRgnWindow != NULL)
	{
		::DeleteObject(m_hRgnWindow);
		m_hRgnWindow = NULL;
	}
}


BEGIN_MESSAGE_MAP(CSkinnedButton, CWnd)
	//{{AFX_MSG_MAP(CSkinnedButton)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSkinnedButton message handlers

void CSkinnedButton::OnPaint() 
{
	if(m_lButtonType & FL_CONTROL_OWNERDRAWN)
	{
	}
	else
	{
		CPaintDC dc(this); // device context for painting
		
		BltEx();
	}

	// Do not call CWnd::OnPaint() for painting messages
}

void CSkinnedButton::OnLButtonDown(UINT nFlags, CPoint point) 
{	
	if(m_bEnabled)
	{
		SetCurrentState(BUTTON_STATE_PRESSED);
		if(GetID() != -1)
		{
			if(UpdateMemoryDC() != -1)
			{
				Invalidate(TRUE);
			}
		}

		UpdateWindow();

		::PostMessage(m_pParentWnd->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_LBUTTONDOWN, m_nControlID), 0);
	}
	
	m_bIsDragging = TRUE;

	CWnd::OnLButtonDown(nFlags, point);
}

void CSkinnedButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bEnabled)
	{
		if(m_lButtonType == FL_BUTTON_TYPE_NORMAL)
		{
			SetCurrentState(BUTTON_STATE_UNPRESSED);
		}
		else
		{
			if(m_bPressed)
			{
				SetCurrentState(BUTTON_STATE_UNPRESSED);
				m_bPressed = FALSE;
			}
			else
			{
				SetCurrentState(BUTTON_STATE_PRESSED);
				m_bPressed = TRUE;
			}
		}

		if(GetID() != -1)
		{
			if(UpdateMemoryDC() != -1)
			{
				Invalidate(TRUE);
			}
		}

		UpdateWindow();

		m_pParentWnd->SetFocus();

		CRect rcWindow;
		BOOL bMousePointerIn = FALSE;

		if(m_bShape)
		{
			if(m_hRgn != NULL)
			{
				if(PtInRegion(m_hRgn, point.x, point.y))
				{
					bMousePointerIn = TRUE;
				}
			}
		}
		else
		{
			GetClientRect(&rcWindow);
			if(PtInRect(&rcWindow, point))
			{
				bMousePointerIn = TRUE;
			}
		}

		if(bMousePointerIn)
		{
			::PostMessage(m_pParentWnd->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_COMMAND,m_nControlID), 0);
		}
	}
	
	m_bIsDragging = FALSE;

	CWnd::OnLButtonUp(nFlags, point);
}

void CSkinnedButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rcWindow;

	int nLastButtonState = GetCurrentState();
	
	if(m_bEnabled)
	{
		BOOL bMousePointerIn = FALSE;

		if(m_bShape)
		{
			if(m_hRgn != NULL)
			{
				if(PtInRegion(m_hRgn, point.x, point.y))
				{
					bMousePointerIn = TRUE;
				}
			}
		}
		else
		{
			GetClientRect(&rcWindow);
			if(rcWindow.PtInRect(point))
			{
				bMousePointerIn = TRUE;
			}
		}
		
		if(bMousePointerIn)
		{
			SetCursor(::LoadCursor(NULL,IDC_HAND));
			if(GetCapture() != this)
			{
				SetCapture();
			}
			if(GetCurrentState() != BUTTON_STATE_PRESSED)
			{
				SetCurrentState(BUTTON_STATE_HOVER);
			}
		}
		else
		{
			if(!m_bIsDragging)
			{
				if(GetCapture() == this)
				{
					ReleaseCapture();
				}
				if((m_lButtonType & FL_BUTTON_TYPE_NORMAL))
				{
					SetCurrentState(BUTTON_STATE_UNPRESSED);
				}
				else
				{
					if(!m_bPressed)
					{
						SetCurrentState(BUTTON_STATE_UNPRESSED);
					}
				}
			}
			else
			{
				if((m_lButtonType & FL_BUTTON_TYPE_NORMAL))
				{
					SetCurrentState(BUTTON_STATE_UNPRESSED);
				}
				else
				{
					SetCurrentState(BUTTON_STATE_PRESSED);
				}
			}
		}

		if(m_bIsSliderParent == TRUE)
		{
			if(GetCurrentState() != nLastButtonState)
			{
				if(UpdateMemoryDC() != -1)
				{
					Invalidate(TRUE);
				}
			}
		}
		else
		{
			if(UpdateMemoryDC() != -1)
			{
				Invalidate(TRUE);
			}
		}

		if(m_bIsDragging)
		{
			::PostMessage(m_pParentWnd->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_MOVECHILD,m_nControlID), MAKELPARAM(point.x,point.y));			
		}
		else
		{
			::PostMessage(m_pParentWnd->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_MOUSEMOVE, m_nControlID), MAKELPARAM(point.x,point.y));
		}
	}
	else
	{
		if((m_lButtonType & FL_BUTTON_TYPE_TOGGLE))
		{
			ReleaseCapture();
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}


BOOL CSkinnedButton::NotifyCommandToParent()
{
	return TRUE;
}

BOOL CSkinnedButton::CreateSkinControl(LPCTSTR lpszWindowName, LPRECT lpRect, CWnd *pParentWnd, UINT nControlID, long lFlags)
{
	m_csText = lpszWindowName;
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right - lpRect->left;
	m_nHeight = lpRect->bottom - lpRect->top;
	m_pParentWnd = pParentWnd;
	m_nControlID = nControlID;
	
	m_csFontName = "Arial";
	m_nFontSize = 16;
	m_nFontStyle = FONT_NORMAL;
	m_crBackgroundColorHover = RGB(255,255,255);
	m_crBackgroundColorPressed = RGB(255,255,255);
	m_crBackgroundColorUnPressed = RGB(255,255,255);
	m_crForegroundColor = RGB(0,0,0);

	m_lButtonType = lFlags;

	if(m_hWnd != NULL)
	{
		return FALSE;
	}

	if(CWnd::Create(NULL, 
					m_csText, 
					WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS, 
					*lpRect, 
					pParentWnd, 
					nControlID, 
					NULL))
	{
		CWnd::BringWindowToTop();

		return TRUE;
	}
	
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CSkinnedButton message handlers

int CSkinnedButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	CBitmap bmpTemp;

	m_dcMemory.CreateCompatibleDC(&dc);

	if(bmpTemp.CreateCompatibleBitmap(&dc, m_nWidth, m_nHeight) != 0)
	{
		m_dcMemory.SelectObject(&bmpTemp);

		if(PrepareFont())
		{
		}

		UpdateMemoryDC();

		if(m_bShape)
		{
			m_hRgn = CreateRectRgn(0,0,0,0);
			if(m_hRgn != NULL)
			{
				if(GetWindowRgn(m_hRgn) == ERROR)
				{
					m_hRgn = NULL;
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}
	}

	return 0;
}

BOOL CSkinnedButton::PreTranslateMessage(MSG* pMsg) 
{
	return CWnd::PreTranslateMessage(pMsg);
}

void CSkinnedButton::MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags)
{
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right - lpRect->left;
	m_nHeight = lpRect->bottom - lpRect->top;

	MoveWindow(lpRect, bRedraw);
}

void CSkinnedButton::MoveWindowEng(int nLeft, int nTop, BOOL bRedraw, long lFlags)
{
	m_nLeft = nLeft;
	m_nTop = nTop;

	MoveWindow(m_nLeft, m_nTop, m_nWidth, m_nHeight, bRedraw);
}

long CSkinnedButton::SetButtonType(long lButtonType)
{
	long lOldButtonType = m_lButtonType;
	m_lButtonType = lButtonType;

	return lOldButtonType;
}

long CSkinnedButton::GetButtonType()
{
	return m_lButtonType;
}

void CSkinnedButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

}

void CSkinnedButton::OnKillFocus(CWnd *pNewWnd)
{

}

void CSkinnedButton::OnLButtonDblClk(UINT nFlags, CPoint point) 
{	
	if(m_bEnabled)
	{
		::PostMessage(m_pParentWnd->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_DBLCLK, m_nControlID), 0);
	}
	
	CWnd::OnLButtonDblClk(nFlags, point);
}

int CSkinnedButton::UpdateMemoryDC()
{
	BITMAP bmpTemp;

	memset(&bmpTemp, 0, sizeof(BITMAP));

	if(m_dcMemory == NULL)
	{
		return -1;
	}

#ifdef	USE_GIF_IMAGES
	if(m_hBitmap != NULL && m_hBitmap == GetCurrentStateBitmap())
	{
		return -1;
	}
	m_hBitmap = GetCurrentStateBitmap();
#else
	hBitmap = GetCurrentStateBitmap();
#endif

	if(m_hBitmap != NULL)
	{
		::GetObject(m_hBitmap, sizeof(BITMAP), &bmpTemp);

		m_lImageWidth = bmpTemp.bmWidth;
		m_lImageHeight = bmpTemp.bmHeight;
		
		::SelectObject(m_dcMemory.GetSafeHdc(),m_hBitmap/*GetCurrentStateBitmap()*/);
	}
	else if(m_nPressedID == -1 && m_nUnPressedID == -1 && m_nHoverID == -1)
	{
		CClientDC dc(this);

		m_dcMemory.SetMapMode(dc.GetMapMode());
		m_dcMemory.SetWindowExt(dc.GetWindowExt());
		m_dcMemory.SetViewportExt(dc.GetViewportExt());
		m_dcMemory.SetWindowOrg(0, 0);
		
		CBitmap cbmpTemp;

		cbmpTemp.CreateCompatibleBitmap(&dc, m_nWidth, m_nHeight);
		
		if(m_dcMemory.SelectObject(&cbmpTemp) != NULL)
		{
			m_dcMemory.FillSolidRect(0, 0, m_nWidth, m_nHeight, GetCurrentBackgroundColor());
		}
	}

	if(m_bShape != -1 && m_bFindEdges)
	{
		m_bFindEdges = FALSE;
		FindControlEdge(this, &m_dcMemory, COLOR_MAGENTA, m_hRgnWindow);
	}
	return 0;
}

void CSkinnedButton::BltEx()
{
	CClientDC dc(this);
	
	CRect rcClient;
	CSize cszFontSize;

	GetClientRect(&rcClient);

	if(m_dcMemory.GetSafeHdc() == NULL)
	{
		return;
	}

	CFont *pcfOldFont = m_dcMemory.SelectObject(&m_cfFaceTextFont);
	m_dcMemory.SetTextColor(m_crForegroundColor);
	m_dcMemory.SetBkMode(TRANSPARENT);

	cszFontSize = m_dcMemory.GetTextExtent(m_csText);

	int nAlign = 0;

	if(m_lTextAlign & TEXT_ALIGN_NONE)
	{
		nAlign = -1;
	}

	if(m_lTextAlign & TEXT_ALIGN_TOP)
	{
		nAlign |= DT_TOP;
	}

	if(m_lTextAlign & TEXT_ALIGN_BOTTOM)
	{
		nAlign |= DT_BOTTOM;
	}

	if(m_lTextAlign & TEXT_ALIGN_LEFT)
	{
		nAlign |= DT_LEFT;
	}

	if(m_lTextAlign & TEXT_ALIGN_RIGHT)
	{
		nAlign |= DT_RIGHT;
	}

	if(m_lTextAlign & TEXT_ALIGN_CENTER_HORIZ)
	{
		nAlign |= DT_CENTER;
	}

	if(m_lTextAlign & TEXT_ALIGN_CENTER_VERT)
	{
		nAlign |= DT_VCENTER;
	}

	if(nAlign != -1)
	{
		CRect rcClient(0,0,m_nWidth, m_nHeight);
		nAlign |= DT_SINGLELINE | DT_EXPANDTABS | DT_WORDBREAK | DT_END_ELLIPSIS;
		rcClient.left += 5;
		rcClient.right -= 5;
		int ret = m_dcMemory.DrawText(m_csText, rcClient, nAlign);
	}
	else
	{
		m_dcMemory.TextOut(m_lPaddingLeft, m_lPaddingTop, m_csText);
	}
	
	if(m_lButtonType & DRAW_STYLE_STRETCHED)
	{
		dc.StretchBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_dcMemory, 0, 0, m_lImageWidth, m_lImageHeight, SRCCOPY);
	}
	else
	{
		dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_dcMemory, 0, 0, SRCCOPY);
	}

	m_dcMemory.SelectObject(pcfOldFont);
}

BOOL CSkinnedButton::OnEraseBkgnd(CDC* pDC) 
{
	return CWnd::OnEraseBkgnd(pDC);
}

void CSkinnedButton::SetButtonText(LPTSTR lpszText)
{
	m_csText = lpszText;
	BltEx();
}

void CSkinnedButton::SetEnabled(BOOL bEnabled)
{
	if(GetCapture() == this)
	{
		ReleaseCapture();
		m_bIsDragging = FALSE;
	}

	CSkinControl::SetEnabled(bEnabled);
	if(UpdateMemoryDC() != -1)
	{
		Invalidate(TRUE);
	}
}

void CSkinnedButton::SetShapedFlag(BOOL bShaped)
{
	m_bShape = bShaped;
	m_bFindEdges = TRUE;
}

void CSkinnedButton::SetToggleButtonState(int nState)
{
	if(m_lButtonType & FL_BUTTON_TYPE_TOGGLE)
	{
		m_nCurrentState = nState;

		if(m_nCurrentState == BUTTON_STATE_UNPRESSED)
		{
			m_bPressed = FALSE;
		}
		else
		{
			m_bPressed = TRUE;
		}
	}

	if(UpdateMemoryDC() != -1)
	{
		Invalidate(TRUE);
	}
}

void CSkinnedButton::SetTextAlignment(int nAlignment)
{
	m_lTextAlign = nAlignment;

	if(m_hWnd != NULL)
	{
		if (UpdateMemoryDC() != -1)
		{
			Invalidate(TRUE);
		}
	}
}

long CSkinnedButton::GetTextalignment()
{
	return m_lTextAlign;
}

void CSkinnedButton::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CWnd::OnShowWindow(bShow, nStatus);
}

CDC* CSkinnedButton::GetControlDC()
{
	if(m_hWnd != NULL)
	{
		return GetDC();
	}
	else
	{
		return NULL;
	}
}