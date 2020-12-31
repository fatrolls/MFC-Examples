// SkinnedSliderCtrl.cpp: implementation of the CSkinnedSliderCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkinnedSliderCtrl.h"
#include "..\tools\StringEx.h"
#include "..\tools\GlobalFunctions.h"
#include "..\GlobalConstants.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkinnedSliderCtrl::CSkinnedSliderCtrl()
{
	m_pcsbtnSliderButton = 0;
	m_nMinRange = 0;
	m_nMaxRange = 100;
	m_bFindEdges = TRUE;
	m_nSliderButtonWidth = 0;
	m_nSliderButtonHeight = 0;
	m_bShape = FALSE;
	m_bDisplayTicks = FALSE;
	m_crTicksForegroundColor = RGB(100, 100, 100);
	m_nTicksLength = 5;
	m_lPreviousPos = -1;
	m_hBitmap = NULL;
	m_hRgn = NULL;
}

CSkinnedSliderCtrl::~CSkinnedSliderCtrl()
{
	if(m_pcsbtnSliderButton != NULL)
	{
		delete m_pcsbtnSliderButton;
		m_pcsbtnSliderButton = 0;
	}

	DestroyWindow();

	m_hBitmap = NULL;

	if(m_hRgn != NULL)
	{
		::DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
}

BEGIN_MESSAGE_MAP(CSkinnedSliderCtrl, CWnd)
	//{{AFX_MSG_MAP(CSkinnedSliderCtrl)`
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSkinnedSliderCtrl::CreateSkinControl(LPCTSTR lpszWindowName, 
										   LPRECT lpRect, 
										   CWnd *pParentWnd, 
										   UINT nControlID, 
										   long lFlags/*=FL_SLIDER_HORIZONTAL*/)
{	
	m_csText = lpszWindowName;
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right - lpRect->left;
	m_nHeight = lpRect->bottom - lpRect->top;
	m_pParentWnd = pParentWnd;
	m_nControlID = nControlID;

	m_csFontName = "Arial";
	m_nFontSize = 12;
	m_nFontStyle = FONT_NORMAL;
	m_crBackgroundColorHover = RGB(255,255,255);
	m_crBackgroundColorPressed = RGB(255,255,255);
	m_crBackgroundColorUnPressed = RGB(255,255,255);
	m_crForegroundColor = RGB(0,0,0);

	m_lFlags = lFlags;

	if(m_bShape == TRUE)
	{
		m_nSliderButtonWidth -= 8;
		m_nSliderButtonHeight -= 8;
	}

	if(m_hWnd != NULL)
	{
		return FALSE;
	}

	if(CWnd::Create(NULL, 
					m_csText, 
					WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, 
					*lpRect,
					pParentWnd, 
					nControlID, 
					NULL))
	{
		RECT rcButton;

		if(m_lFlags & FL_SLIDER_HORIZONTAL)
		{
			if(m_nSliderButtonWidth != 0 && m_nSliderButtonHeight != 0)
			{
				rcButton.left = 0;
				rcButton.top = 7;
				rcButton.right = 16;
				rcButton.bottom = 7+27;
			}
			else
			{
				rcButton.left = 0;
				rcButton.top = (m_nHeight - m_nSliderButtonHeight) / 2;
				rcButton.right = m_nSliderButtonWidth;
				rcButton.bottom = ((m_nHeight - m_nSliderButtonHeight) / 2) + m_nSliderButtonHeight;
			}
		}
		else
		{
			if(m_nSliderButtonWidth != 0 && m_nSliderButtonHeight != 0)
			{
				rcButton.left = 7;
				rcButton.right = 7+28;
				rcButton.top = m_nHeight-15;
				rcButton.bottom = m_nHeight;
			}
			else
			{
				rcButton.left = (m_nWidth - m_nSliderButtonWidth) / 2;
				rcButton.top = m_nHeight - m_nSliderButtonHeight;
				rcButton.right = ((m_nWidth - m_nSliderButtonWidth) / 2) + m_nSliderButtonWidth;
				rcButton.bottom = m_nHeight;
			}
		}

		if(m_bShape == TRUE && (m_lFlags & FL_SLIDER_HORIZONTAL))
		{			
			rcButton.left -= 4;
			rcButton.right -= 4;
			rcButton.top -= 4;
			rcButton.bottom -= 4;
		}

		m_pcsbtnSliderButton = new CSkinnedButton;
		m_pcsbtnSliderButton->SetImageResource(m_nSliderButtonNormalID);
		m_pcsbtnSliderButton->SetShapedFlag(m_bShape);
		m_pcsbtnSliderButton->CreateSkinControl("", &rcButton, this, ID_SLIDER_BUTTON);
		m_pcsbtnSliderButton->m_bIsSliderParent = TRUE;

		BringWindowToTop();
		return TRUE;
	}
	
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CSkinnedSliderCtrl message handlers

void CSkinnedSliderCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rcClient;
	GetClientRect(&rcClient);

	dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), &m_dcMemory, 0, 0, SRCCOPY);

	if(m_bDisplayTicks)
	{
		long lLength;

		CPen pen, *pPenOld;
		pen.CreatePen(PS_SOLID, 1, m_crTicksForegroundColor);
		pPenOld = dc.SelectObject(&pen);

		if(m_lFlags & FL_SLIDER_HORIZONTAL)
		{
			lLength = m_nMaxRange - m_nMinRange;
			lLength = (lLength != 0)?lLength:1;
			double dPixelWidthPerValue = ((((double)m_nWidth - m_pcsbtnSliderButton->GetWidth()) / (double)(lLength) ));
			
			if(((int)dPixelWidthPerValue) <= 0)
			{
				dPixelWidthPerValue = 1;
			}

			for(double dX=m_pcsbtnSliderButton->GetWidth()/2; dX<=m_nWidth-(m_pcsbtnSliderButton->GetWidth()/2); dX+=dPixelWidthPerValue)
			{
				int nNewX = (int)dX;
				dc.MoveTo(nNewX,0);
				dc.LineTo(nNewX,m_nTicksLength);
			}
		}
		else
		{
			lLength = m_nMaxRange - m_nMinRange;
			lLength = (lLength != 0)?lLength:1;
			double dPixelHeightPerValue = ((((double)m_nHeight - m_pcsbtnSliderButton->GetHeight()) / (double)(lLength) ));
			
			if(((int)dPixelHeightPerValue) <= 0)
			{
				dPixelHeightPerValue = 1;
			}

			for(double dY=m_pcsbtnSliderButton->GetHeight()/2; dY<=m_nHeight-(m_pcsbtnSliderButton->GetHeight()/2); dY+=dPixelHeightPerValue)
			{
				dc.MoveTo(0,(int)dY);
				dc.LineTo(m_nTicksLength,(int)dY);
			}
		}

		dc.SelectObject(pPenOld);
		pen.DeleteObject();
	}
	// Do not call CWnd::OnPaint() for painting messages
}

void CSkinnedSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(m_bEnabled)
	{
		SetCurrentState(BUTTON_STATE_PRESSED);		

		if(m_lFlags & FL_SLIDER_HORIZONTAL)
		{
			MoveSliderButtonHorizontally((short)point.x);
		}
		else
		{
			MoveSliderButtonVertically((short)point.y);
		}
	}

	::PostMessage((this->GetParent())->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_COMMAND, m_nControlID), GetPos());
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CSkinnedSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bEnabled)
	{
		if(GetCapture() != this)
		{
			SetCapture();
			SetCurrentState(BUTTON_STATE_HOVER);
		}
		else
		{
			ReleaseCapture();
			SetCurrentState(BUTTON_STATE_UNPRESSED);
		}
	}
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CSkinnedSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);
}

int CSkinnedSliderCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	CBitmap bmpTemp;

	m_dcMemory.CreateCompatibleDC(&dc);

	bmpTemp.CreateCompatibleBitmap(&dc, m_nWidth, m_nHeight);

	if(m_dcMemory.GetSafeHdc() == NULL)
	{
		return -1;
	}

	m_dcMemory.SelectObject(&bmpTemp);

	UpdateMemoryDC();
	return 0;
}

BOOL CSkinnedSliderCtrl::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
		case WM_USER:
			switch(LOWORD(pMsg->wParam))
			{
				case MSG_MOVECHILD:
					{
						if(m_lFlags & FL_SLIDER_HORIZONTAL)
						{
							short lX = LOWORD(pMsg->lParam);
							lX += m_pcsbtnSliderButton->GetLeft();

							if(m_bShape)
							{
								lX -= 4;
							}

							if(m_lPreviousPos == lX)
							{
								return TRUE;
							}

							MoveSliderButtonHorizontally(lX);
							m_lPreviousPos = lX;
						}
						else
						{
							short lY = HIWORD(pMsg->lParam);
							lY += m_pcsbtnSliderButton->GetTop();

							if(m_lPreviousPos == lY)
							{
								return TRUE;
							}

							MoveSliderButtonVertically(lY);
							m_lPreviousPos = lY;
						}

						::PostMessage((this->GetParent())->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_COMMAND, m_nControlID), GetPos());
					}
					return TRUE;

				case MSG_LBUTTONDOWN:
					::PostMessage((this->GetParent())->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_LBUTTONDOWN, m_nControlID), 0L);
					return TRUE;
			}
			break;
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}

void CSkinnedSliderCtrl::MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags)
{
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right;
	m_nHeight = lpRect->bottom;

	MoveWindow(lpRect, bRedraw);
}

void CSkinnedSliderCtrl::MoveWindowEng(int nLeft, int nTop, BOOL bRedraw, long lFlags)
{
	m_nLeft = nLeft;
	m_nTop = nTop;

	MoveWindow(m_nLeft, m_nTop, m_nWidth, m_nHeight, bRedraw);
}

void CSkinnedSliderCtrl::MoveWindowEng(HWND hWnd, LPRECT lpRect, BOOL bRedraw, long lFlags)
{
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right;
	m_nHeight = lpRect->bottom;

	::MoveWindow(hWnd, m_nLeft, m_nTop, m_nWidth, m_nHeight, bRedraw);
}

void CSkinnedSliderCtrl::MoveWindowEng(HWND hWnd, int nLeft, int nTop, BOOL bRedraw, long lFlags)
{
	m_nLeft = nLeft;
	m_nTop = nTop;

	::MoveWindow(hWnd, m_nLeft, m_nTop, m_nWidth, m_nHeight, bRedraw);
}

void CSkinnedSliderCtrl::MoveSliderButtonVertically(short nYPosition)
{
	int nNewTop;

	nNewTop = nYPosition - (m_pcsbtnSliderButton->GetHeight()/2);
	if(nNewTop < 0)
	{
		nNewTop = 0;
	}
	else if(nNewTop >= m_nHeight - (m_pcsbtnSliderButton->GetHeight()))
	{
		nNewTop = m_nHeight - m_pcsbtnSliderButton->GetHeight();
	}

	CRect rcNew(m_pcsbtnSliderButton->GetLeft(),
		nNewTop,
		m_pcsbtnSliderButton->GetLeft() + m_pcsbtnSliderButton->GetWidth(),
		nNewTop + m_pcsbtnSliderButton->GetHeight());

	m_pcsbtnSliderButton->MoveWindowEng(CRect(m_pcsbtnSliderButton->GetLeft(),
										nNewTop,
										m_pcsbtnSliderButton->GetLeft() + m_pcsbtnSliderButton->GetWidth(),
										nNewTop + m_pcsbtnSliderButton->GetHeight()), TRUE);
}

void CSkinnedSliderCtrl::MoveSliderButtonHorizontally(short nXPosition)
{
	int nNewLeft=0;

	nNewLeft = nXPosition - (m_pcsbtnSliderButton->GetWidth()/2);
	if(nNewLeft < 0)
	{		
		nNewLeft = 0;

		if(m_bShape)
		{
			nNewLeft -= 4;
		}
	}
	else if(nNewLeft >= (m_nWidth - (m_pcsbtnSliderButton->GetWidth())))
	{
		if(m_bShape)
		{
			nNewLeft = (m_nWidth - m_pcsbtnSliderButton->GetWidth()+3);
		}
		else
		{
			nNewLeft = (m_nWidth - m_pcsbtnSliderButton->GetWidth());
		}
	}
	
	double dPixelWidthPerValue=0;
	long lLength = m_nMaxRange - m_nMinRange;
	lLength = (lLength != 0)?lLength:1;
	dPixelWidthPerValue = ((((double)m_nWidth - m_pcsbtnSliderButton->GetWidth()) / (double)(lLength)));

	if(m_lFlags & FL_SLIDER_GRAPHEX)
	{
		int nDiv = (int)((float)nNewLeft/dPixelWidthPerValue);
		nNewLeft = (int)(nDiv * dPixelWidthPerValue);
	}

	CRect rcNew(nNewLeft,
		m_pcsbtnSliderButton->GetTop(),
		nNewLeft + m_pcsbtnSliderButton->GetWidth(),
		m_pcsbtnSliderButton->GetTop() + m_pcsbtnSliderButton->GetHeight());

	m_pcsbtnSliderButton->MoveWindowEng(rcNew, TRUE);

	UpdateWindow();
}

int CSkinnedSliderCtrl::SetRangeMax(int nMax, BOOL bRedraw)
{
	int nOldMaxRange = m_nMaxRange;

	m_nMaxRange = nMax;

	return nOldMaxRange;
}

int CSkinnedSliderCtrl::SetRangeMin(int nMin, BOOL bRedraw)
{
	int nOldMinRange = m_nMinRange;

	m_nMinRange = nMin;

	return nOldMinRange;
}

void CSkinnedSliderCtrl::SetRange(int nMin, int nMax, BOOL bRedraw)
{
	m_nMinRange = nMin;
	m_nMaxRange = nMax;
}

int CSkinnedSliderCtrl::GetRangeMax()
{
	return m_nMaxRange;
}

int CSkinnedSliderCtrl::GetRangeMin()
{
	return m_nMinRange;
}

int CSkinnedSliderCtrl::GetPos()
{
	float nPos;
	int nPercentage;

	if(m_lFlags & FL_SLIDER_HORIZONTAL)
	{
		long lLength = m_nMaxRange - m_nMinRange;
		lLength = (lLength != 0)?lLength:1;
		double dPixelWidthPerValue = ((((double)m_nWidth - m_pcsbtnSliderButton->GetWidth()) / (double)(lLength) ));
		double dVal = (float)(m_pcsbtnSliderButton->GetLeft() * 100) / (m_nWidth - m_pcsbtnSliderButton->GetWidth());
		nPercentage = RoundEx(dVal);
		nPos = (m_nMaxRange - m_nMinRange) * ((float)nPercentage /100);
	}
	else
	{
		nPercentage = (m_pcsbtnSliderButton->GetTop() * 100) / (m_nHeight - m_pcsbtnSliderButton->GetHeight());
		nPercentage = 100 - nPercentage;
		nPos = (m_nMaxRange - m_nMinRange) * ((float)nPercentage /100);
	}

	return m_nMinRange + RoundEx(nPos);
}

void CSkinnedSliderCtrl::GetRange(int &nMin, int &nMax)
{
	nMin = m_nMinRange;
	nMax = m_nMaxRange;
}

void CSkinnedSliderCtrl::BltEx()
{

}

void CSkinnedSliderCtrl::SetPos(long lValue)
{
	long lLength;

	if(lValue >= m_nMinRange && lValue <= m_nMaxRange)
	{		
		if(m_lFlags & FL_SLIDER_HORIZONTAL)
		{
			int nTop;
			double dPixelWidthPerValue, lNewPos;

			nTop = m_pcsbtnSliderButton->GetTop();

			lLength = m_nMaxRange - m_nMinRange;
			lLength = (lLength != 0)?lLength:1;
			dPixelWidthPerValue = ((((double)m_nWidth - m_pcsbtnSliderButton->GetWidth()) / (double)(lLength) ));
			lNewPos =  dPixelWidthPerValue * (lValue - m_nMinRange);
			m_pcsbtnSliderButton->MoveWindowEng((int)lNewPos, nTop, TRUE);
			UpdateWindow();
		}
		else
		{
			int nLeft;
			double dPixelHeightPerValue, lNewPos;

			nLeft = m_pcsbtnSliderButton->GetLeft();

			lLength = m_nMaxRange - m_nMinRange;
			lLength = (lLength != 0)?lLength:1;
			dPixelHeightPerValue = ((((double)m_nHeight - m_pcsbtnSliderButton->GetHeight()) / (double)(lLength) ));
			lNewPos =  dPixelHeightPerValue * (m_nMaxRange - lValue);// - m_nMinRange);
			m_pcsbtnSliderButton->MoveWindowEng(nLeft, (int)lNewPos, TRUE);
			UpdateWindow();
		}
	}
}

int CSkinnedSliderCtrl::UpdateMemoryDC()
{
	CBitmap cbmpTemp;
	BITMAP bmpTemp;

	memset(&bmpTemp, 0, sizeof(BITMAP));

	if(m_dcMemory == NULL)
	{
		return -1;
	}

	UINT nID = GetID();
	if(nID == -1)
	{
		return -1;
	}

#ifdef	USE_GIF_IMAGES
	m_hBitmap = GetCurrentStateBitmap();
#else
	hBitmap = LoadBitmap(GetDllInstance((LPTSTR)(LPCTSTR)m_csDLLFileName), MAKEINTRESOURCE(nID));
#endif
	
	if(m_hBitmap != NULL)
	{
		cbmpTemp.Attach(m_hBitmap);
		cbmpTemp.GetBitmap(&bmpTemp);

		m_lImageWidth = bmpTemp.bmWidth;
		m_lImageHeight = bmpTemp.bmHeight;
		cbmpTemp.Detach();

		::SelectObject(m_dcMemory.GetSafeHdc(),m_hBitmap);
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
		FindControlEdge(this, &m_dcMemory, COLOR_MAGENTA, m_hRgn);
	}
	return 0;
}

void CSkinnedSliderCtrl::SetSliderButtonImageResource(int nNormalID, int nPressedID, int nHoverID, int nDisabledID)
{
	//The thumb button is not created when this function is called.
	//This function sets the ids into member variables for use during CreateSkinControl
	//This function also finds the width and height of the thumb button from the image that
	//has been set
	m_nSliderButtonDisabledID = nDisabledID;
	m_nSliderButtonHoverID = nHoverID;
	m_nSliderButtonNormalID = nNormalID;
	m_nSliderButtonPressedID = nPressedID;

	HBITMAP hBitmap;
	CBitmap cbmpTemp;
	BITMAP bmpTemp;

#ifdef	USE_GIF_IMAGES
	hBitmap = LoadGIF(GetDllInstance((LPTSTR)(LPCTSTR)m_csDLLFileName), MAKEINTRESOURCE(m_nSliderButtonNormalID));
#else
	hBitmap = LoadBitmap(GetDllInstance((LPTSTR)(LPCTSTR)m_csDLLFileName), MAKEINTRESOURCE(m_nSliderButtonNormalID));
#endif

	//Finding the width and height of the image, this value
	//will be used while creating the thumb button in CreateSkinControl
	if(hBitmap != NULL)
	{		
		cbmpTemp.Attach(hBitmap);
		cbmpTemp.GetBitmap(&bmpTemp);

		m_nSliderButtonWidth = bmpTemp.bmWidth;
		m_nSliderButtonHeight = bmpTemp.bmHeight;

		cbmpTemp.Detach();
		::DeleteObject(hBitmap);
	}
}

void CSkinnedSliderCtrl::SetSliderButtonDimensions(int nWidth, int nHeight)
{
	m_pcsbtnSliderButton->SetDimensions(nWidth, nHeight);

	m_pcsbtnSliderButton->MoveWindowEng(
			CRect(m_pcsbtnSliderButton->GetLeft(),
					m_pcsbtnSliderButton->GetTop(),
					m_pcsbtnSliderButton->GetLeft() + nWidth,
					m_pcsbtnSliderButton->GetTop() + nHeight),
			TRUE);
}

void CSkinnedSliderCtrl::PositionSliderButtonHorizontally(int nLeft)
{
	if(!(m_lFlags & FL_SLIDER_HORIZONTAL))
	{
		m_pcsbtnSliderButton->MoveWindowEng(nLeft, m_pcsbtnSliderButton->GetTop(), TRUE);
	}
}

void CSkinnedSliderCtrl::PositionSliderButtonVertically(int nTop)
{
	if(!(m_lFlags & FL_SLIDER_VERTICAL))
	{
		m_pcsbtnSliderButton->MoveWindowEng(m_pcsbtnSliderButton->GetLeft(), nTop, TRUE);
	}
}

void CSkinnedSliderCtrl::SetEnabled(BOOL bEnabled)
{
	m_bEnabled = bEnabled;

	m_pcsbtnSliderButton->SetEnabled(bEnabled);
	m_pcsbtnSliderButton->EnableWindow(bEnabled);
}


void CSkinnedSliderCtrl::SetShapedFlag(BOOL bShaped)
{
	m_bShape = bShaped;
}

void CSkinnedSliderCtrl::ShowTicks(BOOL nShow)
{
	m_bDisplayTicks = nShow;
}

void CSkinnedSliderCtrl::SetTicksColor(COLORREF crTicksColor)
{
	m_crTicksForegroundColor = crTicksColor;
}

void CSkinnedSliderCtrl::SetTicksLength(int nLength)
{
	m_nTicksLength = nLength;
}

int CSkinnedSliderCtrl::GetPosInPixels()
{
	int nPixelPos;

	nPixelPos = m_pcsbtnSliderButton->GetLeft() + m_pcsbtnSliderButton->GetWidth()/2;

	return nPixelPos;
}