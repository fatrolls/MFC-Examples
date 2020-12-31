
#include "stdafx.h"
#include "Resource.h"
#include "SkinSliderCtrl.h"
#include "DrawHelpers.h"

CSkinImage CSkinSliderCtrl::m_ImageDefSlider; // 滑动条

IMPLEMENT_DYNAMIC(CSkinSliderCtrl, CSliderCtrl)

BEGIN_MESSAGE_MAP(CSkinSliderCtrl, CSliderCtrl)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()

CSkinSliderCtrl::CSkinSliderCtrl()
{
	m_nPos = m_nMin = 0;
	m_nMax = 100;
	m_nPage = 20;
	m_crBackColor = CLR_NONE;

	m_bLButtonDown = FALSE;
	m_bVertical = FALSE;

	if (!m_ImageDefSlider.IsValid())
	{
		HMODULE hModule = GetModuleHandle(SKIN_CONTROLS_DLL_NAME);
		m_ImageDefSlider.LoadFromResource(hModule, MAKEINTRESOURCE(IDB_SLIDER));
	}
}

CSkinSliderCtrl::~CSkinSliderCtrl()
{
}

void CSkinSliderCtrl::SetBackImage(LPCTSTR pszFileName, BitmapFormat bf)
{
	m_ImageBack.DestroyImage();
	m_ImageBack.LoadFromFile(pszFileName);
	ASSERT(m_ImageBack.IsValid());
	SetWindowPos(NULL, 0,0, m_ImageBack.GetWidth(), !m_ImageThumb.IsValid()?0:m_ImageThumb.GetHeight(), SWP_NOZORDER|SWP_NOMOVE);
}

void CSkinSliderCtrl::SetBackImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf)
{
	m_ImageBack.DestroyImage();
	m_ImageBack.LoadFromResource(hInst, lpszResource);
	ASSERT(m_ImageBack.IsValid());
	SetWindowPos(NULL, 0,0, m_ImageBack.GetWidth(), !m_ImageThumb.IsValid()?0:m_ImageThumb.GetHeight(), SWP_NOZORDER|SWP_NOMOVE);
}

void CSkinSliderCtrl::SetBackImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf)
{
	m_ImageBack.DestroyImage();
	m_ImageBack.LoadFromMemory(pBuffer, dwBufferSize);
	ASSERT(m_ImageBack.IsValid());
	SetWindowPos(NULL, 0,0, m_ImageBack.GetWidth(), !m_ImageThumb.IsValid()?0:m_ImageThumb.GetHeight(), SWP_NOZORDER|SWP_NOMOVE);
}

void CSkinSliderCtrl::SetBack2Image(LPCTSTR pszFileName, BitmapFormat bf)
{
	m_ImageBack2.DestroyImage();
	m_ImageBack2.LoadFromFile(pszFileName, bf);
	ASSERT(m_ImageBack2.IsValid());
}

void CSkinSliderCtrl::SetBack2Image(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf)
{
	m_ImageBack2.DestroyImage();
	m_ImageBack2.LoadFromResource(hInst, lpszResource, bf);
	ASSERT(m_ImageBack2.IsValid());
}

void CSkinSliderCtrl::SetBack2Image(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf)
{
	m_ImageBack2.DestroyImage();
	m_ImageBack2.LoadFromMemory(pBuffer, dwBufferSize, bf);
	ASSERT(m_ImageBack2.IsValid());
}

void CSkinSliderCtrl::SetThumbImage(LPCTSTR pszFileName, BitmapFormat bf)
{
	m_ImageThumb.DestroyImage();
	m_ImageThumb.LoadFromFile(pszFileName, bf);
	ASSERT(m_ImageThumb.IsValid());
	SetWindowPos(NULL, 0,0, !m_ImageBack.IsValid()?0:m_ImageBack.GetWidth(), m_ImageThumb.GetHeight(), SWP_NOZORDER|SWP_NOMOVE);
}

void CSkinSliderCtrl::SetThumbImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf)
{
	m_ImageThumb.DestroyImage();
	m_ImageThumb.LoadFromResource(hInst, lpszResource, bf);
	ASSERT(m_ImageThumb.IsValid());
	SetWindowPos(NULL, 0,0, !m_ImageBack.IsValid()?0:m_ImageBack.GetWidth(), m_ImageThumb.GetHeight(), SWP_NOZORDER|SWP_NOMOVE);
}

void CSkinSliderCtrl::SetThumbImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf)
{
	m_ImageThumb.DestroyImage();
	m_ImageThumb.LoadFromMemory(pBuffer, dwBufferSize, bf);
	ASSERT(m_ImageThumb.IsValid());
	SetWindowPos(NULL, 0,0, !m_ImageBack.IsValid()?0:m_ImageBack.GetWidth(), m_ImageThumb.GetHeight(), SWP_NOZORDER|SWP_NOMOVE);
}

void CSkinSliderCtrl::SetRangeMax(int nMax, BOOL bRedraw)
{
	m_nMax = nMax;
	if(bRedraw)
		Invalidate(FALSE);
}

void CSkinSliderCtrl::SetRangeMin(int nMin, BOOL bRedraw)
{
	m_nMin = nMin;
	if(bRedraw)
		Invalidate(FALSE);
}

void CSkinSliderCtrl::SetRange(int nMin, int nMax, BOOL bRedraw)
{
	SetRangeMin( nMin, FALSE );
	SetRangeMax( nMax, bRedraw );
}

void CSkinSliderCtrl::SetPos(int nPos)
{
	m_nPos = nPos;

	if(m_nPos > m_nMax)
		m_nPos = m_nMax;
	if(m_nPos < m_nMin)
		m_nPos = m_nMin;

	Invalidate(FALSE);
	UpdateWindow();
}

// 控件子类化
void CSkinSliderCtrl::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	SetWindowLong(m_hWnd,GWL_STYLE,GetStyle()|SS_NOTIFY);

	if (!m_ImageBack.IsValid() || !m_ImageThumb.IsValid())
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		if (m_bVertical) SetWindowPos(NULL, 0, 0, 16, rcClient.Height(), SWP_NOMOVE);
		SetWindowPos(NULL, 0, 0, rcClient.Width(), 9, SWP_NOMOVE);
	}

	return;
}

int CSkinSliderCtrl::Pos2Pixel( int nPos )
{
	CRect rcClient;
	GetClientRect(&rcClient);
	if (!m_ImageBack.IsValid() || !m_ImageThumb.IsValid())
	{
		if (m_bVertical)
			return (rcClient.Height()-9) * (m_nPos-m_nMin)/(m_nMax-m_nMin)+9/2;
		else
			return (rcClient.Width()-16) * (m_nPos-m_nMin)/(m_nMax-m_nMin) + 16/2;
	}
	else
	{
		if (m_bVertical)
			return (rcClient.Height()-m_ImageThumb.GetHeight()) * (m_nPos-m_nMin)/(m_nMax-m_nMin)+m_ImageThumb.GetHeight()/2;
		else
			return (rcClient.Width()-m_ImageThumb.GetWidth()) * (m_nPos-m_nMin)/(m_nMax-m_nMin) + m_ImageThumb.GetWidth()/2;
	}
}

int CSkinSliderCtrl::Pixel2Pos( int nPixel )
{
	CRect rcClient;
	GetClientRect(&rcClient);

	INT nThumbWidth = (!m_ImageBack.IsValid() || !m_ImageThumb.IsValid()) ? 16 : m_ImageThumb.GetWidth();
	INT nThumbHeight = (!m_ImageBack.IsValid() || !m_ImageThumb.IsValid()) ? 9 : m_ImageThumb.GetHeight();

	if( m_bVertical ) {

		return (int)(
			m_nMin +
			(double)( nPixel - nThumbHeight/2) /
			(rcClient.Height()- nThumbHeight) *
			(m_nMax - m_nMin)
			);

	} else {

		return (int)(
			m_nMin +
			(double)( nPixel - nThumbWidth/2) /
			(rcClient.Width() - nThumbWidth) *
			(m_nMax - m_nMin)
			);
	}
}

// 建立消息
int CSkinSliderCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	SetWindowLong(m_hWnd,GWL_STYLE,GetStyle()|SS_NOTIFY);

	return 0;
}

void CSkinSliderCtrl::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	if (!m_ImageBack.IsValid() || !m_ImageThumb.IsValid())
	{
		if (m_bVertical) SetWindowPos(NULL, 0, 0, 16, cy, SWP_NOMOVE);
		SetWindowPos(NULL, 0, 0, cx, 9, SWP_NOMOVE);
	}
}

BOOL CSkinSliderCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CSkinSliderCtrl::OnPaint() 
{
	CPaintDC dc(this);
	
	CRect rcClient;
	GetClientRect(&rcClient);

	CBufferDC BufferDC(dc.m_hDC, rcClient);

	if (m_crBackColor != CLR_NONE) BufferDC.FillSolidRect(rcClient, m_crBackColor);

	if (!m_ImageBack.IsValid() || !m_ImageThumb.IsValid())
	{
		// 暂时只有水平方向的
		/*if (m_bVertical == TRUE)
		{
			m_ImageBack.Draw(BufferDC.m_hDC, (rcClient.Width()-m_ImageBack.GetWidth())/2, rcClient.top);
			if (m_ImageBack2.IsValid())
				m_ImageBack2.Draw(BufferDC.m_hDC, (rcClient.Width()-m_ImageBack2.GetWidth())/2, m_ImageBack2.GetWidth(),rcClient.top + Pos2Pixel(m_nPos), m_ImageBack2.GetHeight());
		}
		else*/
		{
			m_ImageDefSlider.DrawImage(&BufferDC, rcClient.left, (rcClient.Height() - 5) / 2, 3, 5, 0, 0, 3, 5, MASK_COLOR);
			for (int x = 3; x < rcClient.right - 3; x++)
			{
				m_ImageDefSlider.DrawImage(&BufferDC, x, (rcClient.Height() - 5) / 2, 1, 5, 3, 0, 1, 5, MASK_COLOR);
			}
			m_ImageDefSlider.DrawImage(&BufferDC, rcClient.right - 3, (rcClient.Height()-5) / 2, 3, 5, 4, 0, 3, 5, MASK_COLOR);
			
			m_ImageDefSlider.DrawImage(&BufferDC, rcClient.left, (rcClient.Height()-5)/2, 3, 5, 7, 0, 3, 5, MASK_COLOR);
			for (int x = 3; x < rcClient.right - 3; x++)
			{
				m_ImageDefSlider.DrawImage(&BufferDC, x, (rcClient.Height()-5)/2, 1, 5, 10, 0, 1, 5, MASK_COLOR);
			}
			m_ImageDefSlider.DrawImage(&BufferDC, rcClient.right - 3, (rcClient.Height()-5)/2, 3, 5, 11, 0, 3, 5, MASK_COLOR);
		}

		/*if (m_bVertical == TRUE)
		{
			m_ImageThumb.Draw(BufferDC.m_hDC, (rcClient.Width()-m_ImageThumb.GetWidth())/2, Pos2Pixel(m_nPos)-m_ImageThumb.GetHeight()/2);
		}
		else*/
		{
			m_ImageDefSlider.DrawImage(&BufferDC, Pos2Pixel(m_nPos)-8, (rcClient.Height()-9) / 2, 16, 9, 14, 0, 16, 9, MASK_COLOR);
		}
	}
	else
	{
		if (m_bVertical == TRUE)
		{
			m_ImageBack.DrawImage(&BufferDC, (rcClient.Width()-m_ImageBack.GetWidth())/2, rcClient.top, MASK_COLOR);
			if (m_ImageBack2.IsValid())
				m_ImageBack2.DrawImage(&BufferDC, (rcClient.Width()-m_ImageBack2.GetWidth())/2, 0, m_ImageBack2.GetWidth(), rcClient.top + Pos2Pixel(m_nPos), MASK_COLOR);
		}
		else
		{
			m_ImageBack.DrawImage(&BufferDC, rcClient.left, (rcClient.Height() - m_ImageBack.GetHeight()) / 2);
			if (m_ImageBack2.IsValid())
				m_ImageBack2.DrawImage(&BufferDC, rcClient.left, (rcClient.Height() - m_ImageBack2.GetHeight()) / 2,
				Pos2Pixel(m_nPos), m_ImageBack2.GetHeight(), MASK_COLOR);
		}

		if (m_bVertical == TRUE)
		{
			m_ImageThumb.DrawImage(&BufferDC, (rcClient.Width() - m_ImageThumb.GetWidth()) / 2, Pos2Pixel(m_nPos) - m_ImageThumb.GetHeight()/2, MASK_COLOR);
		}
		else
		{
			m_ImageThumb.DrawImage(&BufferDC, Pos2Pixel(m_nPos)-m_ImageThumb.GetWidth()/2, (rcClient.Height()-m_ImageThumb.GetHeight())/2, MASK_COLOR);
		}
	}
}

void CSkinSliderCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();

	m_bLButtonDown = TRUE;
	long lThumbWidth = (!m_ImageBack.IsValid() || !m_ImageThumb.IsValid()) ? 16 : m_ImageThumb.GetWidth();
	long lThumbHeight = (!m_ImageBack.IsValid() || !m_ImageThumb.IsValid()) ? 9 : m_ImageThumb.GetHeight();

	if(m_bVertical)
	{
		if(abs(point.y - Pos2Pixel(m_nPos)) <= (int)lThumbHeight / 2)
			m_nMouseOffset = point.y - Pos2Pixel( m_nPos );
		else
			m_nMouseOffset = 0;
	}
	else
	{
		if(abs(point.x - Pos2Pixel(m_nPos)) <= (int)lThumbWidth / 2)
			m_nMouseOffset = point.x - Pos2Pixel(m_nPos);
		else
			m_nMouseOffset = 0;
	}

	OnMouseMove(nFlags, point);
	Invalidate(FALSE);
	UpdateWindow();

	__super::OnLButtonDown(nFlags, point);
}

void CSkinSliderCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_bLButtonDown)
		return;

	int nPixel;
	CRect rcClient;
	GetClientRect(&rcClient);

	INT nThumbWidth = (!m_ImageBack.IsValid() || !m_ImageThumb.IsValid()) ? 16 : m_ImageThumb.GetWidth();
	INT nThumbHeight = (!m_ImageBack.IsValid() || !m_ImageThumb.IsValid()) ? 9 : m_ImageThumb.GetHeight();

	if(m_bVertical)
	{
		nPixel = point.y - m_nMouseOffset;

		if(nPixel > rcClient.Height() -nThumbHeight/2)
			nPixel = rcClient.Height() - nThumbHeight/2;

		if(nPixel < rcClient.Height()/2)
			nPixel = rcClient.Height()/2;
	}
	else
	{
		nPixel = point.x - m_nMouseOffset;

		if(nPixel < nThumbWidth/2)
			nPixel = nThumbWidth/2;

		if(nPixel > rcClient.Width() - nThumbWidth/2)
			nPixel = rcClient.Width() - nThumbWidth/2;
	}

	if( Pos2Pixel(m_nPos) != nPixel )
	{
		SetPos(Pixel2Pos(nPixel));

		::PostMessage(
			GetParent()->GetSafeHwnd(), WM_SKINSLIDER_MOVING,
			GetDlgCtrlID(), m_nPos);
	}

	__super::OnMouseMove(nFlags, point);
}

void CSkinSliderCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	m_bLButtonDown = FALSE;

	Invalidate(FALSE);
	UpdateWindow();

	::PostMessage(
		GetParent()->GetSafeHwnd(),	WM_SKINSLIDER_MOVED,
		GetDlgCtrlID(), m_nPos );

	__super::OnLButtonUp(nFlags, point);
}

UINT CSkinSliderCtrl::OnGetDlgCode() 
{
	if( GetKeyState(VK_TAB) >= 0 ) 
	{
		return DLGC_WANTALLKEYS;
	}

	return CStatic::OnGetDlgCode();
}

void CSkinSliderCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch( nChar ) 
	{
	case VK_LEFT :
	case VK_UP :
		SetPos( m_nPos-1 );
		break;
	case VK_RIGHT :
	case VK_DOWN :

		SetPos( m_nPos+1 );
		break;
	case VK_HOME :
		SetPos( m_nMin );
		break;
	case VK_END :
		SetPos( m_nMax );
		break;
	case VK_PRIOR :
		SetPos( m_nPos - m_nPage );
		break;
	case VK_NEXT :
		SetPos( m_nPos + m_nPage );
		break;
	default :

		__super::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
	}

	::PostMessage(
		GetParent()->GetSafeHwnd(),	WM_SKINSLIDER_MOVED,
		GetDlgCtrlID(), m_nPos);

	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSkinSliderCtrl::OnDestroy() 
{
	__super::OnDestroy();
}
