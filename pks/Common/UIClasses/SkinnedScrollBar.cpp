// SkinnedScrollBar.cpp : implementation file
//

#include "stdafx.h"
#include "SkinnedScrollBar.h"
#include "..\Tools\GlobalFunctions.h"
#include "..\GlobalConstants.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinnedScrollBar

CSkinnedScrollBar::CSkinnedScrollBar()
{
	m_pcsbtnScrollButton = 0;
	m_pcsbtnScrollUpButton = 0;
	m_pcsbtnScrollDownButton = 0;
	
	m_pcsbtnScrollButton = new CSkinnedButton;
	m_pcsbtnScrollUpButton = new CSkinnedButton;
	m_pcsbtnScrollDownButton = new CSkinnedButton;
	
	m_nMinRange = 0;
	m_nMaxRange = 100;
	m_bFindEdges = TRUE;

	m_hRgn = NULL;
}

CSkinnedScrollBar::~CSkinnedScrollBar()
{
	if(m_pcsbtnScrollButton)
	{
		delete m_pcsbtnScrollButton;
		m_pcsbtnScrollButton = 0;
	}
	if(m_pcsbtnScrollUpButton)
	{
		delete m_pcsbtnScrollUpButton;
		m_pcsbtnScrollUpButton = 0;
	}
	if(m_pcsbtnScrollDownButton)
	{
		delete m_pcsbtnScrollDownButton;
		m_pcsbtnScrollButton = 0;
	}

	if(m_hRgn != NULL)
	{
		::DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
}


BEGIN_MESSAGE_MAP(CSkinnedScrollBar, CWnd)
	//{{AFX_MSG_MAP(CSkinnedScrollBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_WM_CREATE()
		ON_WM_PAINT()
		ON_WM_LBUTTONDOWN()
		ON_WM_LBUTTONUP()
		ON_WM_MOUSEMOVE()
		ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////
// CSkinnedScrollBar message handlers

BOOL CSkinnedScrollBar::CreateSkinControl(LPCTSTR lpszWindowName,
										  LPRECT lpRect, 
										  CWnd *pParentWnd, 
										  UINT nControlID, 
										  long lFlags)
{
	m_csText = lpszWindowName;
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right - lpRect->left;
	m_nHeight = lpRect->bottom - lpRect->top;
	m_nControlID = nControlID;

	CWnd::Create(NULL, 
				m_csText, 
				WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, 
				*lpRect,
				pParentWnd, 
				nControlID, 
				NULL);

	m_pcsbtnScrollButton->SetImageResource(m_nScrollButtonNormalID);
	m_pcsbtnScrollButton->CreateSkinControl("",
											CRect(0,17,m_nWidth-1,17+30),
											this, 
											ID_SCROLL_BUTTON, 
											FL_BUTTON_TYPE_NORMAL|DRAW_STYLE_STRETCHED);
	
	m_pcsbtnScrollUpButton->SetImageResource(m_nScrollUpButtonNormalID);
	m_pcsbtnScrollUpButton->CreateSkinControl("",
											CRect(0,0,m_nWidth-1,17),
											this, 
											ID_SCROLLUP_BUTTON);
	
	m_pcsbtnScrollDownButton->SetImageResource(m_nScrollDownButtonNormalID);
	m_pcsbtnScrollDownButton->CreateSkinControl("",
											CRect(0,m_nHeight-17,m_nWidth-1,m_nHeight),
											this, 
											ID_SCROLLDOWN_BUTTON);
	
	BringWindowToTop();
	return TRUE;
}

void CSkinnedScrollBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting


	CRect rcClient;
	UpdateMemoryDC();
	GetClientRect(&rcClient);
	dc.StretchBlt(0,0,rcClient.Width(),rcClient.Height(),&m_dcMemory,0,0,m_lImageWidth,m_lImageHeight,SRCCOPY);
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CSkinnedScrollBar::BltEx()
{
}

void CSkinnedScrollBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(m_bEnabled)
	{
		SetCurrentState(BUTTON_STATE_PRESSED);		
		
		if(GetID() != -1)
		{
			UpdateMemoryDC();
		}

		CRect rcScrollButton(m_pcsbtnScrollButton->GetLeft(),
			m_pcsbtnScrollButton->GetTop(),
			m_pcsbtnScrollButton->GetLeft() + m_pcsbtnScrollButton->GetWidth(),
			m_pcsbtnScrollButton->GetTop() + m_pcsbtnScrollButton->GetHeight());
		InvalidateRect(&rcScrollButton, TRUE);
		int nYPos = 0;

		if(point.y > rcScrollButton.bottom && point.y < m_pcsbtnScrollDownButton->GetTop())
		{
			nYPos = rcScrollButton.bottom+rcScrollButton.Height();
			MoveScrollButton((short)nYPos);
		}
		else if(point.y < rcScrollButton.top && point.y > m_pcsbtnScrollUpButton->GetTop() + m_pcsbtnScrollUpButton->GetHeight())
		{
			nYPos = rcScrollButton.top-rcScrollButton.Height();
			MoveScrollButton((short)nYPos);
		}
		
		if(GetID() != -1)
		{
			UpdateMemoryDC();
		}

		InvalidateRect(NULL);		

	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CSkinnedScrollBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonUp(nFlags, point);
}

void CSkinnedScrollBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);
}

int CSkinnedScrollBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	m_dcMemory.CreateCompatibleDC(&dc);

	if(m_dcMemory.GetSafeHdc() == NULL)
	{
		return -1;
	}

	UpdateMemoryDC();
	
	CRect rcClient;
	GetClientRect(&rcClient);
	dc.FillSolidRect(rcClient,RGB(255,0,255));

	return 0;
}

BOOL CSkinnedScrollBar::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_USER:
		switch(LOWORD(pMsg->wParam))
		{
		case MSG_COMMAND:
			return TRUE;
		case MSG_MOVECHILD:
			{
				switch(HIWORD(pMsg->wParam))
				{
				case ID_SCROLL_BUTTON:
					{
						short lY = HIWORD(pMsg->lParam);
						lY += (short)m_pcsbtnScrollButton->GetTop();
						
						MoveScrollButton(lY);

						Invalidate(TRUE);
					}
					break;

				default:
					break;
				}
			}
			return TRUE;
		case MSG_LBUTTONDOWN:
			{
				CRect rcScrollButton(m_pcsbtnScrollButton->GetLeft(),
					m_pcsbtnScrollButton->GetTop(),
					m_pcsbtnScrollButton->GetLeft() + m_pcsbtnScrollButton->GetWidth(),
					m_pcsbtnScrollButton->GetTop() + m_pcsbtnScrollButton->GetHeight());

				switch(HIWORD(pMsg->wParam))
				{
				case ID_SCROLLUP_BUTTON:
					MoveScrollButton((short)(rcScrollButton.top));
					break;
				case ID_SCROLLDOWN_BUTTON:
					MoveScrollButton((short)(rcScrollButton.bottom));
					break;
				default:
					break;
				}				
			}
			return TRUE;

		default:
			break;
		}
		break;

	default:
		break;
	}

	return CWnd::PreTranslateMessage(pMsg);
}

void CSkinnedScrollBar::MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags)
{
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right - lpRect->left;
	m_nHeight = lpRect->bottom - lpRect->top;

	MoveWindow(lpRect, bRedraw);

	m_pcsbtnScrollButton->MoveWindowEng(CRect(0,m_nTop+200,m_nWidth-1,m_nTop+230),TRUE);
	m_pcsbtnScrollDownButton->MoveWindowEng(CRect(0,m_nHeight-17,m_nWidth-1,m_nHeight),TRUE);
}

void CSkinnedScrollBar::MoveScrollButton(short nYPosition)
{
	int nNewTop;

	nNewTop = nYPosition - (m_pcsbtnScrollButton->GetHeight()/2 + m_pcsbtnScrollUpButton->GetHeight());
	nNewTop += m_pcsbtnScrollUpButton->GetHeight()/2;

	if(nNewTop < m_pcsbtnScrollUpButton->GetHeight())
	{
		nNewTop = m_pcsbtnScrollUpButton->GetHeight();
	}
	else if(nNewTop >= m_nHeight - (m_pcsbtnScrollButton->GetHeight() + m_pcsbtnScrollUpButton->GetHeight()))
	{
		nNewTop = m_nHeight - (m_pcsbtnScrollButton->GetHeight() + m_pcsbtnScrollUpButton->GetHeight());
	}

	CRect rcNew(m_pcsbtnScrollButton->GetLeft(),
		nNewTop,
		m_pcsbtnScrollButton->GetLeft() + m_pcsbtnScrollButton->GetWidth(),
		nNewTop + m_pcsbtnScrollButton->GetHeight());

	m_pcsbtnScrollButton->MoveWindowEng(rcNew, TRUE);
	m_pcsbtnScrollButton->UpdateWindow();

	::PostMessage((GetParent())->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_SCROLL, m_nControlID), GetPos());
}

int CSkinnedScrollBar::SetRangeMax(int nMax, BOOL bRedraw)
{
	int nOldMaxRange = m_nMaxRange;

	m_nMaxRange = nMax;

	if(bRedraw)
	{
		Invalidate(TRUE);
	}

	return nOldMaxRange;
}

int CSkinnedScrollBar::SetRangeMin(int nMin, BOOL bRedraw)
{
	int nOldMinRange = m_nMinRange;

	m_nMinRange = nMin;

	if(bRedraw)
	{
		Invalidate(TRUE);
	}

	return nOldMinRange;
}

void CSkinnedScrollBar::SetRange(int nMin, int nMax, BOOL bRedraw)
{
	m_nMinRange = nMin;
	m_nMaxRange = nMax;

	if(bRedraw)
	{
		Invalidate(TRUE);
	}
}

int CSkinnedScrollBar::GetRangeMax()
{
	return m_nMaxRange;
}

int CSkinnedScrollBar::GetRangeMin()
{
	return m_nMinRange;
}

int CSkinnedScrollBar::GetPos()
{
	float nPos;
	int nPercentage;

	int nButtonPos = m_pcsbtnScrollButton->GetTop() - m_pcsbtnScrollUpButton->GetHeight();
	long nAllButtonsHeight = m_pcsbtnScrollButton->GetHeight()+m_pcsbtnScrollUpButton->GetHeight()+m_pcsbtnScrollDownButton->GetHeight();

	nPercentage = (nButtonPos * 100) / (m_nHeight - nAllButtonsHeight);
	nPos = (m_nMaxRange - m_nMinRange) * ((float)nPercentage /100);

	return m_nMinRange+(int)nPos;
}

void CSkinnedScrollBar::GetRange(int &nMin, int &nMax)
{
	nMin = m_nMinRange;
	nMax = m_nMaxRange;
}

int CSkinnedScrollBar::UpdateMemoryDC()
{

	HBITMAP hBitmap;
	CBitmap cbmpTemp;
	BITMAP bmpTemp;

	UINT nID = GetID();
	if(nID == -1)
	{
		return -1;
	}
#ifdef	USE_GIF_IMAGES
	hBitmap = LoadGIF(GetDllInstance((LPTSTR)(LPCTSTR)m_csDLLFileName), MAKEINTRESOURCE(nID));
#else
	hBitmap = LoadBitmap(GetDllInstance((LPTSTR)(LPCTSTR)m_csDLLFileName), MAKEINTRESOURCE(nID));
#endif
	if(hBitmap != NULL)
	{
		cbmpTemp.Detach();
		cbmpTemp.Attach(hBitmap);
		cbmpTemp.GetBitmap(&bmpTemp);

		m_lImageWidth = bmpTemp.bmWidth;
		m_lImageHeight = bmpTemp.bmHeight;

		::SelectObject(m_dcMemory.GetSafeHdc(),hBitmap);
		::DeleteObject(hBitmap);
	}
	else if(m_nPressedID == -1 && m_nUnPressedID == -1 && m_nHoverID == -1)
	{		
		m_dcMemory.SelectObject(&m_bmpMemory);
		m_dcMemory.FillSolidRect(0, 0, m_nWidth, m_nHeight, GetCurrentBackgroundColor());
	}

	if(!m_bShape && m_bFindEdges)
	{
		m_bFindEdges = FALSE;
		FindControlEdge(this, &m_dcMemory, COLOR_MAGENTA, m_hRgn);
	}
	return 0;
}


void CSkinnedScrollBar::SetScrollButtonImageResource(int nNormalID, int nPressedID, int nHoverID, int nDisabledID)
{
	m_nScrollButtonDisabledID = nDisabledID;
	m_nScrollButtonHoverID = nHoverID;
	m_nScrollButtonNormalID = nNormalID;
	m_nScrollButtonPressedID = nPressedID;

	HBITMAP hBitmap;
	CBitmap cbmpTemp;
	BITMAP bmpTemp;

	hBitmap = LoadBitmap(GetDllInstance((LPTSTR)(LPCTSTR)m_csDLLFileName), MAKEINTRESOURCE(m_nScrollButtonNormalID));
	if(hBitmap != NULL)
	{
		cbmpTemp.Attach(hBitmap);
		cbmpTemp.GetBitmap(&bmpTemp);

		m_nScrollButtonWidth = bmpTemp.bmWidth;
		m_nScrollButtonHeight = bmpTemp.bmHeight;
	}
}

void CSkinnedScrollBar::SetScrollUpButtonImageResource(int nNormalID, int nPressedID, int nHoverID, int nDisabledID)
{
	m_nScrollUpButtonDisabledID = nDisabledID;
	m_nScrollUpButtonHoverID = nHoverID;
	m_nScrollUpButtonNormalID = nNormalID;
	m_nScrollUpButtonPressedID = nPressedID;

	HBITMAP hBitmap;
	CBitmap cbmpTemp;
	BITMAP bmpTemp;

	hBitmap = LoadBitmap(GetDllInstance((LPTSTR)(LPCTSTR)m_csDLLFileName), MAKEINTRESOURCE(m_nScrollUpButtonNormalID));
	if(hBitmap != NULL)
	{
		cbmpTemp.Attach(hBitmap);
		cbmpTemp.GetBitmap(&bmpTemp);

		m_nScrollUpButtonWidth = bmpTemp.bmWidth;
		m_nScrollUpButtonHeight = bmpTemp.bmHeight;
	}
}

void CSkinnedScrollBar::SetScrollDownButtonImageResource(int nNormalID, int nPressedID, int nHoverID, int nDisabledID)
{
	m_nScrollDownButtonDisabledID = nDisabledID;
	m_nScrollDownButtonHoverID = nHoverID;
	m_nScrollDownButtonNormalID = nNormalID;
	m_nScrollDownButtonPressedID = nPressedID;

	HBITMAP hBitmap;
	CBitmap cbmpTemp;
	BITMAP bmpTemp;

	hBitmap = LoadBitmap(GetDllInstance((LPTSTR)(LPCTSTR)m_csDLLFileName), MAKEINTRESOURCE(m_nScrollDownButtonNormalID));
	if(hBitmap != NULL)
	{
		cbmpTemp.Attach(hBitmap);
		cbmpTemp.GetBitmap(&bmpTemp);

		m_nScrollDownButtonWidth = bmpTemp.bmWidth;
		m_nScrollDownButtonHeight = bmpTemp.bmHeight;
	}

}

void CSkinnedScrollBar::OnDestroy() 
{
	CWnd::OnDestroy();
}

void CSkinnedScrollBar::SetPos(int nPos)
{
	int nLeft;
	long lButtonsHeight;
	double lNewPos;

	nLeft = m_pcsbtnScrollButton->GetLeft();
	lButtonsHeight = m_pcsbtnScrollButton->GetHeight() + 
						m_pcsbtnScrollUpButton->GetHeight() +
						m_pcsbtnScrollDownButton->GetHeight();

	lNewPos = m_pcsbtnScrollUpButton->GetHeight() + 
				((m_nHeight - lButtonsHeight) * ((float)(nPos) / 100));

	m_pcsbtnScrollButton->MoveWindowEng(nLeft, (int)lNewPos, TRUE);
	UpdateWindow();
}