// SkinnedStatic.cpp : implementation file
//

#include "stdafx.h"
#include "SkinnedStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinnedStatic

CSkinnedStatic::CSkinnedStatic()
{
	m_hWnd			= NULL;
	m_bFindEdges	= TRUE;
	m_lTextAlign	= TEXT_ALIGN_CENTER_HORIZ | TEXT_ALIGN_CENTER_VERT | TEXT_ALIGN_SINGLELINE;
	m_lStaticType	= -1;
	m_hBitmap		= NULL;
	m_hRgn			= NULL;
}

CSkinnedStatic::~CSkinnedStatic()
{
	DestroyWindow();

	m_hBitmap = NULL;

	if(m_hRgn != NULL)
	{
		::DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
}


BEGIN_MESSAGE_MAP(CSkinnedStatic, CWnd)
	//{{AFX_MSG_MAP(CSkinnedStatic)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSkinnedStatic message handlers

void CSkinnedStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	BltEx();
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CSkinnedStatic::BltEx()
{
	CClientDC dc(this);
	
	CRect rcClient;
	CSize cszFontSize;

	UpdateMemoryDC();
	GetClientRect(&rcClient);

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
	if(m_lTextAlign & TEXT_ALIGN_SINGLELINE && !(m_lTextAlign & TEXT_ALIGN_MULTILINE))
	{
		nAlign |= DT_SINGLELINE;
	}

	switch(m_lStaticType)
	{
		case DRAW_STYLE_NORMAL:
			dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_dcMemory, 0, 0, SRCCOPY);//m_lImageWidth, m_lImageHeight, SRCCOPY);
			break;

		case DRAW_STYLE_TILED:
			{
				for(int nY=0; nY<=m_nHeight; nY+=m_lImageHeight)
				{
					for(int nX=0; nX<=m_nWidth; nX+=m_lImageWidth)
					{
						dc.BitBlt(nX, nY, m_lImageWidth, m_lImageHeight, &m_dcMemory, 0, 0, SRCCOPY);
					}
				}
			}
			break;

		case DRAW_STYLE_STRETCHED:
			dc.StretchBlt(0, 0, m_nWidth, m_nHeight, &m_dcMemory, 0, 0, m_lImageWidth, m_lImageHeight, SRCCOPY);
			break;
	}

	dc.SelectObject(&m_cfFaceTextFont);
	dc.SetTextColor(m_crForegroundColor);
	dc.SetBkMode(TRANSPARENT);

	cszFontSize = dc.GetTextExtent(m_csText);

	if(nAlign != -1)
	{
		CRect rcClient(0,0,m_nWidth, m_nHeight);
		nAlign = nAlign | DT_EXPANDTABS | DT_END_ELLIPSIS;
		int ret = dc.DrawText(m_csText, rcClient, nAlign);
	}
	else
	{
		dc.TextOut(m_lPaddingLeft, m_lPaddingTop, m_csText);
	}
}

BOOL CSkinnedStatic::CreateSkinControl(LPCTSTR lpszWindowName,
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
	m_pParentWnd = pParentWnd;
	m_nControlID = nControlID;
	
	m_csFontName = "Arial";
	m_nFontSize = 16;
	m_nFontStyle = FONT_NORMAL;
	m_crBackgroundColorHover = RGB(255,255,255);
	m_crBackgroundColorPressed = RGB(255,255,255);
	m_crBackgroundColorUnPressed = RGB(255,255,255);
	m_crForegroundColor = RGB(0,0,0);

	m_lStaticType = lFlags;
	
	if(CWnd::Create(NULL, 
					m_csText, 
					WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS, 
					*lpRect, 
					pParentWnd, 
					nControlID, 
					NULL))
	{
		CWnd::BringWindowToTop();
		if(PrepareFont())	//Prepare the font object used for displaying the face text
		{
			CSize cszFontSize;
			CRect rcClient;
						
			SetFont(&m_cfFaceTextFont, TRUE);

			GetClientRect(&rcClient);
			m_dcMemory.SelectObject(&m_cfFaceTextFont);
			cszFontSize = m_dcMemory.GetTextExtent(m_csText);

			SetPadding((rcClient.Width() - cszFontSize.cx)/2,
						(rcClient.Height() - cszFontSize.cy)/2);
		}

		return TRUE;
	}
	
	return FALSE;
}

int CSkinnedStatic::UpdateMemoryDC()
{
	CBitmap cbmpTemp;
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
	hBitmap = ::LoadBitmap(GetDllInstance((LPCTSTR)m_csDLLFileName), MAKEINTRESOURCE(GetID()));
#endif
	if(m_hBitmap != NULL)
	{
		cbmpTemp.Attach(m_hBitmap);
		cbmpTemp.GetBitmap(&bmpTemp);

		m_lImageWidth = bmpTemp.bmWidth;
		m_lImageHeight = bmpTemp.bmHeight;
		cbmpTemp.Detach();
		
		::SelectObject(m_dcMemory.GetSafeHdc(), m_hBitmap);
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

	if(!m_bShape && m_bFindEdges && (m_lStaticType & DRAW_STYLE_NORMAL))
	{
		m_bFindEdges = FALSE;
		FindControlEdge(this, &m_dcMemory, COLOR_MAGENTA, m_hRgn);
	}
	return 0;
}

int CSkinnedStatic::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CClientDC dc(this);

	if(m_dcMemory.CreateCompatibleDC(&dc) == 0)	//if failed
	{
		return -1;
	}

	if(PrepareFont())
	{
		SetFont(&m_cfFaceTextFont, TRUE);
	}

	UpdateMemoryDC();
	
	return 0;
}

void CSkinnedStatic::MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags)
{
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right - lpRect->left;
	m_nHeight = lpRect->bottom - lpRect->top;

	MoveWindow(lpRect, bRedraw);
}

void CSkinnedStatic::MoveWindowEng(int nLeft, int nTop, BOOL bRedraw, long lFlags)
{
	m_nLeft = nLeft;
	m_nTop = nTop;

	MoveWindow(m_nLeft, m_nTop, m_nWidth, m_nHeight, bRedraw);
}

void CSkinnedStatic::SetEnabled(BOOL bEnabled)
{
	CSkinControl::SetEnabled(bEnabled);
	Invalidate(TRUE);
}

void CSkinnedStatic::SetTextAlignment(int nAlignment)
{
	m_lTextAlign = nAlignment;

	if(m_hWnd != NULL)
	{
		Invalidate(TRUE);
	}
}

long CSkinnedStatic::GetTextAlignment()
{
	return m_lTextAlign;
}

void CSkinnedStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(nFlags == MK_LBUTTON)
	{
		::PostMessage((GetParent())->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_MOVECHILD,m_nControlID), MAKELPARAM(point.x,point.y));
	}
	else
	{
		::PostMessage((GetParent())->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_MOUSEMOVE,m_nControlID), MAKELPARAM(point.x,point.y));
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

CSize CSkinnedStatic::GetTextExtentEng()
{
	CStringArray csArray;
	CSize size;

	CString csLine;
	CClientDC dc(this);

	size.cx = 0;
	size.cy = 0;

	//if multilined
	if(m_csText.Find("\n") != -1)
	{
		SplitStringEx((LPTSTR)(LPCTSTR)m_csText, "\n", &csArray);

		for(int nCount=0; nCount<csArray.GetSize(); nCount++)
		{
			csLine = csArray.GetAt(nCount);

			CSize sizeTemp;
			sizeTemp = dc.GetTextExtent(csLine);

			size.cy += sizeTemp.cy;

			if(sizeTemp.cx > size.cx)
			{
				size.cx = sizeTemp.cx;
			}
		}
	}
	else
	{
		size = dc.GetTextExtent(m_csText);
	}

	return size;
}

void CSkinnedStatic::SetImageResource(INT nUnPressedID, INT nHoverID, INT nPressedID, INT nDisabledID)
{
	if(m_hWnd != NULL)
	{
		CClientDC dc(this);
		CBitmap bmpTemp;

		bmpTemp.CreateCompatibleBitmap(&dc, m_nWidth, m_nHeight);
		//this is done bcoz if any of the id is -1 then
		//skincontrol class will delete the old one(which might be currently
		//selected) and set it to null
		dc.SelectObject(&bmpTemp);
	}

	CSkinControl::SetImageResource(nUnPressedID, nHoverID, nPressedID, nDisabledID);
}

void CSkinnedStatic::Redraw()
{
	UpdateMemoryDC();
	Invalidate(TRUE);
}