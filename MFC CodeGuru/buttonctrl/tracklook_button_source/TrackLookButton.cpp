// CTrackLookButton.cpp : implementation file
//

#include "stdafx.h"
#include "Button.h"
#include "TrackLookButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RGB_BUTTON_BLACK    (GetSysColor(COLOR_WINDOWFRAME))
#define RGB_BUTTON_WHITE    (GetSysColor(COLOR_BTNHIGHLIGHT))
#define RGB_BUTTON_LIGHT    (GetSysColor(COLOR_BTNFACE))
#define RGB_BUTTON_DARK     (GetSysColor(COLOR_BTNSHADOW))

#define BORDER_CLEAR		0x0000L
#define BORDER_PUSHED		0x0001L
#define BORDER_NONPUSHED	0x0002L

/////////////////////////////////////////////////////////////////////////////
// CTrackLookButton

CTrackLookButton::CTrackLookButton()
{
	m_bMouseCaptured=FALSE;
	m_bLButtonDown=FALSE;
	m_bHasFocus=FALSE;
	m_bDisabled=FALSE;

	m_TextAlign=AlignLeft;
	m_nBorder=BORDER_CLEAR;
	m_bRaised=FALSE;
}

CTrackLookButton::~CTrackLookButton()
{

}


BEGIN_MESSAGE_MAP(CTrackLookButton, CButton)
	//{{AFX_MSG_MAP(CTrackLookButton)
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrackLookButton message handlers

void CTrackLookButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	CButton::OnMouseMove(nFlags,point);
	if (!m_bMouseCaptured || GetCapture()!=this || m_nBorder==BORDER_CLEAR)
	{
		SetCapture();
		m_bMouseCaptured=TRUE;
		OnMouseEnter(nFlags,point);
	} else
	{
		CRect rc;
		this->GetClientRect(&rc);
		if (!rc.PtInRect(point))
		{
			OnMouseLeave(nFlags,point);
			m_bMouseCaptured=FALSE;
			ReleaseCapture();
		}
	}
}

void CTrackLookButton::OnKillFocus(CWnd* pNewWnd) 
{
	m_nBorder=BORDER_CLEAR;
	m_bHasFocus=FALSE;
	m_bRaised=FALSE;
	CButton::OnKillFocus(pNewWnd);
	Invalidate();
	UpdateWindow();
}

void CTrackLookButton::OnSetFocus(CWnd* pOldWnd) 
{
	m_nBorder=m_bLButtonDown?BORDER_PUSHED:BORDER_NONPUSHED;
	m_bHasFocus=TRUE;
	m_bRaised=TRUE;
	CButton::OnSetFocus(pOldWnd);
	Invalidate();
	UpdateWindow();
}

void CTrackLookButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	int	 iSaveDC;
	CDC* pDC;
	CBrush brush(RGB_BUTTON_LIGHT);
	CRect rc;
	CString	strTitle;
	UINT	nFormat; //For DrawText
	UINT	nFlags;	//For DrawBitmap
	CBitmap*	pBitmap=NULL;
	
	pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	VERIFY(pDC);
	rc.CopyRect(&lpDrawItemStruct->rcItem);
	GetWindowText(strTitle);
	nFormat=DT_SINGLELINE;
	iSaveDC=pDC->SaveDC();
	
	switch (m_TextAlign)
	{
		case AlignAbove: nFormat|=DT_CENTER|DT_TOP;break;	
		case AlignBelow: nFormat|=DT_CENTER|DT_BOTTOM;break;
		case AlignLeft:
		case AlignRight: nFormat|=DT_LEFT|DT_VCENTER;break;
		default: ASSERT(FALSE); // should not be called;
	}
	
	
	pDC->SetBkMode(TRANSPARENT);
	
	Draw3DBorder(pDC,rc,m_nBorder);
	rc.InflateRect(-5,-2); //We assert we have a 5 points offset from border
	
	if (m_bHasFocus)
	{
		pDC->SetTextColor(RGB(0,0,255));
		pBitmap=&m_bitmapFocus;
		if (pBitmap->m_hObject==NULL) pBitmap=&m_bitmap; //Simulate some bitmap;
	}
	else
	{
		pDC->SetTextColor(RGB_BUTTON_BLACK);
		pBitmap=&m_bitmap;
	}
	
	if (m_bRaised)
	{
		pBitmap=&m_bitmapFocus;
		if (pBitmap->m_hObject==NULL) pBitmap=&m_bitmap; //Simulate some bitmap;
	} 
	
	if (m_bDisabled=(::GetWindowLong(m_hWnd,GWL_STYLE) & WS_DISABLED))
	{
		pBitmap=&m_bitmapDisabled;
	}
	else if (m_bLButtonDown) rc.OffsetRect(1,1);
	
	CRect rcText(rc);

	if (pBitmap->m_hObject)
		{
			CRect rcBitmap(rc);
			BITMAP	bmpInfo;			
			CSize	size;

			switch (m_TextAlign)
			{
				case AlignLeft:
					{
						size=pDC->GetTextExtent(strTitle);
						rcBitmap.OffsetRect(size.cx+5,0);
						nFlags=DB_VCENTER;
						break;
					}

			case AlignAbove:
					{
						size=pDC->GetTextExtent(strTitle);
						rcBitmap.OffsetRect(0,size.cy+5);
						nFlags=DB_HCENTER;
						break;
					}

				case AlignRight:
					{
						pBitmap->GetBitmap(&bmpInfo);	
						rcText.OffsetRect(bmpInfo.bmWidth+5,0);
						nFlags=DB_VCENTER;
						break;
					}

				case AlignBelow:
					{
						nFlags=DB_HCENTER;
						break;
					}
			default: ASSERT(FALSE);break;
			}

			DrawBitmap(pDC,rcBitmap,nFlags,pBitmap);
		}
	
	if (m_bDisabled)
	{
		rcText.OffsetRect(1,1);
		pDC->SetTextColor(RGB_BUTTON_WHITE);
		pDC->DrawText(strTitle,rcText,nFormat);
		rcText.OffsetRect(-1,-1);
		pDC->SetTextColor(RGB_BUTTON_DARK);
		pDC->DrawText(strTitle,rcText,nFormat);
	} else
			pDC->DrawText(strTitle,rcText,nFormat);
	
	pDC->RestoreDC(iSaveDC);
}

void	CTrackLookButton::OnMouseEnter(UINT nFlags,CPoint point)
{
	m_bLButtonDown=(nFlags & MK_LBUTTON);
	m_nBorder=m_bLButtonDown?BORDER_PUSHED:BORDER_NONPUSHED;
	//if (m_bLButtonDown)
	//{
	m_bRaised=TRUE;
	Invalidate();
	UpdateWindow();
}

void	CTrackLookButton::OnMouseLeave(UINT nFlags,CPoint point)
{
	m_nBorder=BORDER_CLEAR;
	m_bLButtonDown=FALSE;
	m_bRaised=FALSE;
	Invalidate();
	UpdateWindow();
}

void CTrackLookButton::Draw3DBorder(CDC* pDC,CRect rc,UINT nOptions)
{
	switch (nOptions)
	{
	case BORDER_CLEAR:
						pDC->Draw3dRect(rc,RGB_BUTTON_LIGHT,RGB_BUTTON_LIGHT);
						break;
	case BORDER_PUSHED:
						pDC->Draw3dRect(rc,RGB_BUTTON_DARK,RGB_BUTTON_WHITE);
						break;
	case BORDER_NONPUSHED:
						pDC->Draw3dRect(rc,RGB_BUTTON_WHITE,RGB_BUTTON_DARK);
						break;
	default:			break;
	}
}

void CTrackLookButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bLButtonDown=TRUE;
	m_bRaised=FALSE;
	if (GetFocus()!=this)
	{
		this->SetFocus();
		return;
	}
	m_nBorder=BORDER_PUSHED;

	CButton::OnLButtonDown(nFlags,point);
	Invalidate();
	UpdateWindow();
}


void CTrackLookButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLButtonDown=FALSE;
	m_bRaised=TRUE;
	if (GetFocus()!=this)
	{
		
		this->SetFocus();
	
	} else
	{
		m_nBorder=BORDER_NONPUSHED;
		Invalidate();
		UpdateWindow();
	}
	
	GetParent()->SendMessage(WM_COMMAND,
				MAKEWPARAM(GetDlgCtrlID(),BN_CLICKED),
				(LPARAM) m_hWnd);
}

void CTrackLookButton::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	m_bLButtonDown=TRUE;
	if (GetFocus()!=this)
	{
		this->SetFocus();
		return;
	}
	m_nBorder=BORDER_PUSHED;

	Invalidate();
	UpdateWindow();
	CButton::OnLButtonDblClk(nFlags,point);	
	m_nBorder=BORDER_CLEAR;
}

int CTrackLookButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_bDisabled=(lpCreateStruct->style & WS_DISABLED);
	return 0;
}

void CTrackLookButton::OnEnable(BOOL bEnable) 
{
	m_bDisabled=!bEnable;
	CButton::OnEnable(bEnable);
}

BOOL CTrackLookButton::LoadBitmaps(UINT nBitmap, UINT nBitmapFocus, UINT nBitmapDisabled)
{
	return LoadBitmaps(MAKEINTRESOURCE(nBitmap),
						MAKEINTRESOURCE(nBitmapFocus),
						MAKEINTRESOURCE(nBitmapDisabled));
}

CTrackLookButton::TextAlign CTrackLookButton::GetTextAlignment() const
{
	return m_TextAlign;
}

void CTrackLookButton::SetTextAlignment(TextAlign nTextAlign)
{
	m_TextAlign=nTextAlign;
}

void CTrackLookButton::DrawBitmap(CDC * pDC, CRect rc,UINT nFlags,CBitmap * pBitmap)
{
	//Centers a bitmap in a given rectangle
	//If necessary clips the bitmap if outfits the rc
	CDC memDC;
	CBitmap* pOld=NULL;
	memDC.CreateCompatibleDC(pDC);
	BITMAP	bmpInfo;
	int Width;
	int Height;
	int xSrc=0;
	int ySrc=0;
	int xDesired;
	int yDesired;

	ASSERT(pBitmap->m_hObject!=NULL);
	pBitmap->GetBitmap(&bmpInfo);
	
	pOld=memDC.SelectObject((CBitmap*) pBitmap);
	if (pOld==NULL) return; //Destructors will clean up
	
	Width=(bmpInfo.bmWidth-rc.Width())/2;
	Height=(bmpInfo.bmHeight-rc.Height())/2;
	
	if ((nFlags & DB_HCENTER))
	{
		if (Width>0) //If the bitmap Width is larger then rc
		{
			xDesired=rc.left;
			xSrc=abs(Width);
		}
		else xDesired=rc.left+ abs(Width);
	}
		else xDesired=rc.left;
	
	if ((nFlags & DB_VCENTER))
	{
		if (Height>0) //If the bitmap Height is larger then rc
		{
			yDesired=rc.top;
			ySrc=abs(Height);
		}
		else yDesired=rc.top+abs(Height);
	} else
		yDesired=rc.top;
	
	pDC->BitBlt(xDesired,yDesired,rc.Width(),rc.Height(),&memDC,xSrc,ySrc,SRCCOPY);
	
	memDC.SelectObject(pOld);	
}

BOOL CTrackLookButton::LoadBitmaps(LPCSTR lpszBitmap, LPCSTR lpszBitmapFocus, LPCSTR lpszBitmapDisabled)
{
	//Delete old ones
	m_bitmap.DeleteObject();
	m_bitmapFocus.DeleteObject();
	m_bitmapDisabled.DeleteObject();
	m_bitmapRaised.DeleteObject();
	
	if (!m_bitmap.LoadBitmap(lpszBitmap))
	{
		TRACE0("Failed to Load First bitmap of CButton\n");
		return FALSE;
	}

	BOOL bAllLoaded=TRUE;
	if (lpszBitmapFocus!=NULL)
	{
		if (!m_bitmapFocus.LoadBitmap(lpszBitmapFocus))
		{
			TRACE0("Failed to Load First bitmap of CButton\n");
			return bAllLoaded=FALSE;
		}
	}
	
	if (lpszBitmapDisabled!=NULL)
	{
		if (!m_bitmapDisabled.LoadBitmap(lpszBitmapDisabled))
		{
			TRACE0("Failed to Load bitmap of CButton\n");
			return bAllLoaded=FALSE;
		}
	}

	return bAllLoaded;
}
