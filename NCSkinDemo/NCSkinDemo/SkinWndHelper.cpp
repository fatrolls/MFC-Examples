#include "StdAfx.h"
#include "SkinWndHelper.h"

#define  ID_CLOSE_BTN 110
#define  ID_MAX_BTN   111
#define  ID_MIN_BTN   112

static TCHAR g_szPropSkinWnd[] = TEXT("PROP_SkinWndLQS");

CSkinWndHelper::CSkinWndHelper(void)
{
	m_nTitleHeight = 38;
	m_nFrameWidth = 3;

	Image *pImage = CSkinManager::GetInstance()->GetSkinItem(_T("dialog\\dlg_minimize_button.bmp"));
	m_WindowBtnImage.push_back(pImage);

	pImage = CSkinManager::GetInstance()->GetSkinItem(_T("dialog\\dlg_maxmize_button.bmp"));
	m_WindowBtnImage.push_back(pImage);

	pImage = CSkinManager::GetInstance()->GetSkinItem(_T("dialog\\dlg_close_btn.bmp"));
	m_WindowBtnImage.push_back(pImage);

	m_pBkImage = CSkinManager::GetInstance()->GetSkinItem(_T("dialog\\DialogBkg.png"));

	m_iXButtonHovering = -1;

	m_bNCHovering = FALSE;
	m_bNCTracking = FALSE;
	m_hWnd = NULL;

	m_bHaveMaxBox = FALSE;
	m_bHaveMinBox = FALSE;
	m_bHaveCloseBtn = FALSE;

	m_rcIcon = CRect(15,13,15+GetSystemMetrics(SM_CXSMICON),13+GetSystemMetrics(SM_CYSMICON));
}

CSkinWndHelper::~CSkinWndHelper(void)
{
}


void  CSkinWndHelper::DoNcPaint()
{
	CDC dc;
	HDC hdc = GetWindowDC(m_hWnd);
	dc.Attach(hdc);

	if (m_pBkImage==NULL)
	{
		return;
	}

	CDC MemDC;

	// 获取位置
	CRect rcWindow;
	GetWindowRect(m_hWnd,&rcWindow);
	rcWindow.OffsetRect( -rcWindow.left, -rcWindow.top);


	CRect rcClient;
	GetClientRect(m_hWnd,&rcClient);

	//剪除掉客户区
	rcClient.OffsetRect(m_nFrameWidth, m_nTitleHeight);
	dc.ExcludeClipRect(rcClient.left, rcClient.top,
		rcClient.right, rcClient.bottom);


	MemDC.CreateCompatibleDC(&dc);


	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc,rcWindow.Width(),rcWindow.Height());
	MemDC.SelectObject(&bmp);
	MemDC.SetBkMode(TRANSPARENT);

	Gdiplus::Graphics graphics(MemDC.GetSafeHdc());
	RectF destRect;

	//绘制底部和边框
	destRect.X = 0;
	destRect.Y = rcWindow.Height() - m_nFrameWidth;
	destRect.Width = rcWindow.Width();
	destRect.Height = m_nFrameWidth;
	graphics.DrawImage(m_pBkImage,destRect,m_nTitleHeight,m_pBkImage->GetHeight()-m_nFrameWidth,m_nFrameWidth,m_nFrameWidth,UnitPixel);

	destRect.X = rcWindow.right-m_nTitleHeight;
	destRect.Y = rcWindow.bottom - m_nTitleHeight;
	destRect.Width = m_nTitleHeight;
	destRect.Height = m_nTitleHeight;
	graphics.DrawImage(m_pBkImage,destRect,m_pBkImage->GetWidth()-m_nTitleHeight,m_pBkImage->GetHeight()-m_nTitleHeight,m_nTitleHeight,m_nTitleHeight,UnitPixel);

	destRect.X = 0;
	destRect.Y = rcWindow.Height() - m_nTitleHeight;
	destRect.Width = m_nTitleHeight;
	destRect.Height = m_nTitleHeight;
	graphics.DrawImage(m_pBkImage,destRect,0,m_pBkImage->GetHeight()-m_nTitleHeight,m_nTitleHeight,m_nTitleHeight,UnitPixel);

	//左边框
	destRect.X = 0;
	destRect.Y = m_nTitleHeight;
	destRect.Width = m_nFrameWidth;
	destRect.Height = rcWindow.Height() - 2*m_nTitleHeight;
	graphics.DrawImage(m_pBkImage,destRect,0,m_nTitleHeight,m_nFrameWidth,m_nFrameWidth,UnitPixel);


	//右边框
	destRect.X = rcWindow.Width() - m_nFrameWidth;
	destRect.Y = m_nTitleHeight;
	destRect.Width = m_nFrameWidth;
	destRect.Height = rcWindow.Height() - 2*m_nTitleHeight;
	graphics.DrawImage(m_pBkImage,destRect,m_pBkImage->GetWidth()-m_nFrameWidth,m_nTitleHeight,m_nFrameWidth,m_nFrameWidth,UnitPixel);

	//绘制标题栏
	destRect.X = 0;
	destRect.Y = 0;
	destRect.Width = rcWindow.Width();
	destRect.Height = m_nTitleHeight;
	graphics.DrawImage(m_pBkImage,destRect,50,0,5,m_nTitleHeight,UnitPixel);
	graphics.DrawImage(m_pBkImage,0,0,0,0,50,m_nTitleHeight,UnitPixel);
	graphics.DrawImage(m_pBkImage,rcWindow.Width() - 50,0,m_pBkImage->GetWidth()-50,0,50,m_nTitleHeight,UnitPixel);


	int xPos = 15;
	int yPos = 15;

	HICON hIcon = (HICON)::SendMessage(m_hWnd, WM_GETICON, FALSE, 0);
	if (hIcon)
	{
		DrawIconEx(MemDC,xPos, yPos-2,hIcon,GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0, 0, DI_NORMAL);

		xPos += GetSystemMetrics(SM_CXSMICON);
		xPos += 5;
	}

	CString strText;
	int nLen = ::GetWindowTextLength(m_hWnd);
	::GetWindowText(m_hWnd, strText.GetBufferSetLength(nLen), nLen+1);
	strText.ReleaseBuffer();

	if (!strText.IsEmpty())
	{
		//绘制标题
		LOGFONT lfFont;
		memset(&lfFont, 0, sizeof(lfFont));
		lfFont.lfHeight = -12;
		lfFont.lfWeight |= FW_BOLD;
		lstrcpy(lfFont.lfFaceName, _T("宋体"));
		Gdiplus::Font font(dc.GetSafeHdc(), &lfFont);

		StringFormat stringFormat;
		stringFormat.SetFormatFlags( StringFormatFlagsNoWrap);
		stringFormat.SetAlignment(StringAlignmentNear);
		stringFormat.SetLineAlignment(StringAlignmentNear);
		CStringW strTitle(strText);
		SolidBrush brush((ARGB)Color::White);
		PointF point;

		point.X=(Gdiplus::REAL)xPos;
		point.Y=(Gdiplus::REAL)yPos;
		graphics.DrawString(strTitle, strTitle.GetLength(), &font, point,&stringFormat, &brush);

	}

	CRect rcPaint;
	dc.GetClipBox(&rcPaint);
	std::map<int,CDUIButton>::iterator iter;
	for (iter = m_TitleBtn.begin(); iter != m_TitleBtn.end(); iter++)
	{
		CDUIButton& dcControl = iter->second;
		CRect rcControl;
		dcControl.GetRect(&rcControl);

		// 判断当前按钮是否需要重绘
		if(!rcPaint.IsRectEmpty() && !CRect().IntersectRect(&rcControl, rcPaint))
		{
			continue;
		}

		dcControl.DrawButton(graphics);
	}



	dc.BitBlt(0,0,rcWindow.Width(),rcWindow.Height(),&MemDC,0,0,SRCCOPY);

	dc.SelectClipRgn(NULL);

	dc.Detach();

	ReleaseDC(m_hWnd,hdc);


}

// CSkinWndHelper message handlers

LRESULT CSkinWndHelper::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
	//LRESULT lResult = CallWindowProc(m_oldWndProc,m_hWnd, WM_NCPAINT,wParam,lParam);
    DoNcPaint();
	return 0;
}

LRESULT CSkinWndHelper::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
{
	//LRESULT lResult = CallWindowProc(m_oldWndProc,m_hWnd, WM_NCCALCSIZE,wParam,lParam);

	BOOL bCalcValidRects = (BOOL)wParam;
	NCCALCSIZE_PARAMS* lpncsp  = (NCCALCSIZE_PARAMS*)lParam;

	if (bCalcValidRects)   
	{   

		CRect& rc = (CRect&)lpncsp->rgrc[0];//get the client rectangle   
		rc.top += m_nTitleHeight;   
		rc.left += m_nFrameWidth;   
		rc.bottom -= m_nFrameWidth;   
		rc.right -= m_nFrameWidth;   
		return 0;
	}

	
	return CallWindowProc(m_oldWndProc,m_hWnd, WM_NCCALCSIZE,wParam,lParam);

}

LRESULT CSkinWndHelper::OnNcHitTest(WPARAM wParam, LPARAM lParam)
{
	CRect rtButton;
	CRect rcWindow;
	GetWindowRect(m_hWnd,&rcWindow);
	CPoint pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	pt.x -=rcWindow.left;
	pt.y -= rcWindow.top;

	int iButton = TButtonHitTest(pt, rtButton);
	if(iButton != -1)
	{
		switch(iButton)
		{
		case ID_CLOSE_BTN:
			{
				return HTCLOSE;
			}
			break;
		case ID_MAX_BTN:
			{

				return HTMAXBUTTON;
			}
			break;
		case ID_MIN_BTN:
			{
				return HTMINBUTTON;
			}
			break;
		}
	}
	else if (m_rcIcon.PtInRect(pt))
	{
		return HTSYSMENU;
	}

	rcWindow.OffsetRect( -rcWindow.left, -rcWindow.top);

	if (pt.x>=rcWindow.right - 70&&pt.x<=rcWindow.right - m_nFrameWidth&&pt.y<=m_nTitleHeight&&pt.y>=m_nFrameWidth)
	{
		return HTCAPTION;
	}

	return CallWindowProc(m_oldWndProc,m_hWnd,WM_NCHITTEST,wParam,lParam);
}

LRESULT CSkinWndHelper::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
{
	MINMAXINFO* lpMMI = (MINMAXINFO*)lParam;
	lpMMI->ptMinTrackSize.y = m_nTitleHeight + m_nFrameWidth;
	return  CallWindowProc(m_oldWndProc,m_hWnd, WM_GETMINMAXINFO,wParam,lParam);
}

LRESULT CSkinWndHelper::OnNcActivate(WPARAM wParam, LPARAM lParam)
{
	//LRESULT  lResult= CallWindowProc(m_oldWndProc,m_hWnd, WM_NCACTIVATE,wParam,lParam);
	DoNcPaint();
	return TRUE;
}

LRESULT CSkinWndHelper::OnActivate(WPARAM wParam, LPARAM lParam)
{
    LRESULT  lResult= CallWindowProc(m_oldWndProc,m_hWnd, WM_ACTIVATE,wParam,lParam);
	DoNcPaint();
	return lResult;
}

LRESULT CSkinWndHelper::OnNcLButtonDblClk(WPARAM wParam, LPARAM lParam)
{

   UINT nHitTest = wParam;
   CPoint point(LOWORD(lParam),HIWORD(lParam));
	CRect rcWindow;
	GetWindowRect(m_hWnd,&rcWindow);
	rcWindow.bottom = rcWindow.top + m_nTitleHeight;

	CRect rtButton;
	int iButton = TButtonHitTest(point, rtButton);
	if(iButton != -1)
	{
		m_TitleBtn[iButton].LButtonDown();
		DoNcPaint();
		return 1;
	}

	if (rcWindow.PtInRect(point))
	{
		if (IsZoomed(m_hWnd))
		{
			ShowWindow(m_hWnd,SW_RESTORE);
		}
		else
		{
			ShowWindow(m_hWnd,SW_MAXIMIZE);
		}

		DoNcPaint();
		return 1;
	}

	DoNcPaint();
	return 1;
}

LRESULT CSkinWndHelper::OnNcLButtonDown(WPARAM wParam, LPARAM lParam)
{

	UINT nHitTest = wParam;
	CPoint point(LOWORD(lParam),HIWORD(lParam));
	CPoint ptOrg = point;

	CRect rtButton;
	CRect rcWindow;
	GetWindowRect(m_hWnd,&rcWindow);
	point.x -=rcWindow.left;
	point.y -= rcWindow.top;

	int iButton = TButtonHitTest(point, rtButton);
	if(iButton != -1)
	{
		m_TitleBtn[iButton].LButtonDown();
		DoNcPaint();
		return 1;
	}


	if(m_rcIcon.PtInRect(point)) 
	{
		HMENU hSysMenu = GetSystemMenu(m_hWnd,FALSE);
		if (hSysMenu)
		{
			TrackPopupMenu(hSysMenu,TPM_LEFTALIGN, ptOrg.x, ptOrg.y,0,m_hWnd, NULL);
		}
		return 1;
	}
	else if(nHitTest >= HTLEFT && nHitTest <= HTBOTTOMRIGHT || nHitTest == HTCAPTION)
	{		
		return CallWindowProc(m_oldWndProc,m_hWnd, WM_NCLBUTTONDOWN,wParam,lParam);
	}

	return CallWindowProc(m_oldWndProc,m_hWnd, WM_NCLBUTTONDOWN,wParam,lParam);
}

LRESULT CSkinWndHelper::OnNcLButtonUp(WPARAM wParam, LPARAM lParam)
{

	UINT nHitTest = wParam;
	CPoint point(LOWORD(lParam),HIWORD(lParam));

	CRect rtButton;
	CRect rcWindow;
	GetWindowRect(m_hWnd,&rcWindow);
	point.x -=rcWindow.left;
	point.y -= rcWindow.top;

	int iButton = TButtonHitTest(point, rtButton);
	if(iButton != -1)
	{
		switch(iButton)
		{
		case ID_CLOSE_BTN:
			{
				SendMessage(m_hWnd,WM_SYSCOMMAND,SC_CLOSE,0);
			}
			break;
		case ID_MAX_BTN:
			{
				if (IsZoomed(m_hWnd))
				{
					SendMessage(m_hWnd,WM_SYSCOMMAND,SC_RESTORE,0);
				}
				else
				{
					SendMessage(m_hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);
				}
			}
			break;
		case ID_MIN_BTN:
			{
				SendMessage(m_hWnd,WM_SYSCOMMAND,SC_MINIMIZE,0);
			}
			break;
		default:
			{
				m_TitleBtn[iButton].LButtonUp();
				DoNcPaint();
			}
			break;
		}
	}
	else
	{
		return CallWindowProc(m_oldWndProc,m_hWnd, WM_NCLBUTTONUP,wParam,lParam);
	}

	return 1;
}

LRESULT CSkinWndHelper::OnNcMouseMove(WPARAM wParam, LPARAM lParam)
{
	UINT nHitTest = wParam;
	CPoint point(LOWORD(lParam),HIWORD(lParam));
    LRESULT lResult = 0;
	if (!m_bNCTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_NONCLIENT;
		tme.dwHoverTime = 1;
		m_bNCTracking = _TrackMouseEvent(&tme);
	}

	if(nHitTest>=HTLEFT && nHitTest <= HTBOTTOMRIGHT || 
		nHitTest == HTCAPTION)
	{
		lResult = CallWindowProc(m_oldWndProc,m_hWnd, WM_NCMOUSEMOVE,wParam,lParam);

	}

	CRect rtButton;
	CRect rcWindow;
	GetWindowRect(m_hWnd,&rcWindow);
	point.x -=rcWindow.left;
	point.y -= rcWindow.top;
	int iButton = TButtonHitTest(point, rtButton);
	if(iButton != m_iXButtonHovering)
	{
		if(m_iXButtonHovering != -1)
		{
			m_TitleBtn[m_iXButtonHovering].MouseLeave();
			m_iXButtonHovering = -1;
		}
		if(iButton != -1)
		{
			m_iXButtonHovering = iButton;
			m_TitleBtn[m_iXButtonHovering].MouseHover();
		}

		DoNcPaint();
	}

    return lResult;
}

LRESULT CSkinWndHelper::OnNcMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_bNCHovering = TRUE;
    return 1;
}

LRESULT CSkinWndHelper::OnNcMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bNCTracking = FALSE;
	m_bNCHovering = FALSE;

	if(m_iXButtonHovering != -1)
	{
		m_TitleBtn[m_iXButtonHovering].MouseLeave();
		m_iXButtonHovering = -1;
	}

	return 1;

}

LRESULT CSkinWndHelper::OnSize(WPARAM wParam, LPARAM lParam)
{

	LRESULT lResult = CallWindowProc(m_oldWndProc,m_hWnd, WM_SIZE,wParam,lParam);

	UINT nType = wParam;
	int cx = LOWORD(lParam);
	int cy = HIWORD(lParam);


	if (nType != SIZE_MINIMIZED && nType != SIZE_MAXHIDE )
	{
		if (m_Rgn.GetSafeHandle())
		{
			m_Rgn.DeleteObject();
		}

		CRect rc;
		GetWindowRect(m_hWnd,&rc); //获得窗口矩形
		rc -= rc.TopLeft();
		m_Rgn.CreateRoundRectRgn(rc.left, rc.top,   rc.right+1, rc.bottom+1, 5, 5); //根据窗口矩形创建一个圆角矩形
		SetWindowRgn(m_hWnd,m_Rgn, TRUE); //根据圆角矩形指定的区域改变窗口的形状
	}

	CRect rcWnd;
	GetWindowRect(m_hWnd,&rcWnd);
	rcWnd.OffsetRect( -rcWnd.left, -rcWnd.top);

	if (m_bHaveMaxBox||m_bHaveMinBox)
	{
		CRect rMin(rcWnd.right - 74, 8, rcWnd.right-54, 30);
		m_TitleBtn[ID_MIN_BTN].SetRect(rMin);
		CRect rMax(rcWnd.right - 52, 8, rcWnd.right-32, 30);
		m_TitleBtn[ID_MAX_BTN].SetRect(rMax);
	}

	CRect rClose(rcWnd.right - 30, 8, rcWnd.right - 10, 30);
	m_TitleBtn[ID_CLOSE_BTN].SetRect(rClose);

	if (nType == SIZE_MAXIMIZED||
		nType == SIZE_RESTORED)
	{
		DoNcPaint();
	}

	return lResult;

}

LRESULT CSkinWndHelper::OnSysCommand(WPARAM wParam, LPARAM lParam)
{

	if (wParam != SC_CLOSE)
	{
		DoNcPaint();
	}

	return CallWindowProc(m_oldWndProc,m_hWnd, WM_SYSCOMMAND,wParam,lParam);
}

LRESULT CSkinWndHelper::WindowProc(HWND hWnd,UINT message, WPARAM wParam, LPARAM lParam)
{

	CSkinWndHelper* pThis = (CSkinWndHelper*)GetProp(hWnd, g_szPropSkinWnd);
	if (pThis==NULL)
	{
		return 0;
	}

	switch(message)
	{
	case WM_NCPAINT:
		{
			return pThis->OnNcPaint(wParam,lParam);
		}
		break;
	case WM_NCCALCSIZE:
		{
			return pThis->OnNcCalcSize(wParam,lParam);
		}
		break;
	case WM_NCHITTEST:
		{
			return pThis->OnNcHitTest(wParam,lParam);
		}
	case WM_GETMINMAXINFO:
		{
			return pThis->OnGetMinMaxInfo(wParam,lParam);
		}
		break;
	case WM_NCACTIVATE:
		{
			return pThis->OnNcActivate(wParam,lParam);
		}
		break;
	case WM_ACTIVATE:
		{
			return pThis->OnActivate(wParam,lParam);
		}
		break;
	case WM_NCLBUTTONDBLCLK:
		{
			return pThis->OnNcLButtonDblClk(wParam,lParam);

		}
		break;
	case WM_NCLBUTTONDOWN:
		{
			return pThis->OnNcLButtonDown(wParam,lParam);
		}
		break;
	case WM_NCLBUTTONUP:
		{
			return pThis->OnNcLButtonUp(wParam,lParam);
		}
		break;
	case WM_NCMOUSEMOVE:
		{
			return pThis->OnNcMouseMove(wParam,lParam);
		}
		break;
	case WM_NCMOUSEHOVER:
		{
			return pThis->OnNcMouseHover(wParam,lParam);
		}
		break;
	case WM_NCMOUSELEAVE:
		{
			return pThis->OnNcMouseLeave(wParam,lParam);
		}
		break;
	case WM_SIZE:
		{
			return pThis->OnSize(wParam,lParam);
		}
		break;
	case WM_SYSCOMMAND:
		{
			return pThis->OnSysCommand(wParam,lParam);
		}
		break;
	default:
		break;

	}

	if (message == 0x125)
	{
		pThis->DoNcPaint();
	}

	if (message ==0x00AE||//WM_NCUAHDRAWCAPTION
		message==0x00AF)//WM_NCUAHDRAWFRAME)
	{
		pThis->DoNcPaint();
		return 0;
	}

	return CallWindowProc(pThis->m_oldWndProc,hWnd,message,wParam,lParam);
}

BOOL  CSkinWndHelper::Attach(HWND hWnd)
{
	m_hWnd = hWnd;

	// Set the window property 
	if( !SetProp(hWnd, g_szPropSkinWnd, (HANDLE)this))
		return FALSE;

	m_oldWndProc = (WNDPROC)::GetWindowLongPtr(hWnd, GWLP_WNDPROC);
	::SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, (INT_PTR)CSkinWndHelper::WindowProc);


	CRect rcWnd;
	GetWindowRect(m_hWnd,&rcWnd);
	rcWnd.OffsetRect( -rcWnd.left, -rcWnd.top);

	CRect rcControl;
	rcControl.left = rcWnd.right- 35;
	rcControl.top = 5;
	rcControl.right = rcControl.left + 20;
	rcControl.bottom = rcControl.top + 20;

	DWORD dwStyle = (DWORD)GetWindowLong(m_hWnd, GWL_STYLE);;//获取样式
	if (dwStyle&WS_MAXIMIZEBOX)
	{
		m_bHaveMaxBox = TRUE;
	}
	if (dwStyle&WS_MINIMIZEBOX)
	{
		m_bHaveMinBox = TRUE;
	}
	if (dwStyle&WS_SYSMENU)
	{
		m_bHaveCloseBtn = TRUE;
	}

	CDUIButton *pButton = AddTitleButton(rcControl,m_WindowBtnImage[2],3,ID_CLOSE_BTN);
	if (!m_bHaveCloseBtn)
	{
		pButton->EnableButton(FALSE);
	}

	if (m_bHaveMaxBox||m_bHaveMinBox)
	{
		pButton = AddTitleButton(rcControl,m_WindowBtnImage[1],3,ID_MAX_BTN);
		if (!m_bHaveMaxBox)
		{
			pButton->EnableButton(FALSE);
		}

		pButton = AddTitleButton(rcControl,m_WindowBtnImage[0],3,ID_MIN_BTN);
		if (!m_bHaveMinBox)
		{
			pButton->EnableButton(FALSE);
		}

	}

	//触发WM_NCCALLSIZE调用
	SetWindowPos(m_hWnd,NULL,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	return TRUE;


}

void CSkinWndHelper::Detach()
{
	// Remove the subclass procedure
	SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)(LONG_PTR)m_oldWndProc);
	RemoveProp(m_hWnd, g_szPropSkinWnd);
}


CDUIButton* CSkinWndHelper::AddTitleButton(LPRECT lpRect, Image *pImage, UINT nCount /*= 3*/ , UINT nID/* = 0*/,LPCTSTR lpszCaption/*=NULL*/)
{
	CDUIButton dcControl;
	dcControl.CreateButton(lpszCaption, lpRect,m_hWnd,pImage,nCount, nID);
	m_TitleBtn[nID] = dcControl;

	return &m_TitleBtn[nID];
}

int CSkinWndHelper::TButtonHitTest(CPoint point, CRect& rtButton)
{
	std::map<int,CDUIButton>::iterator iter;
	for (iter = m_TitleBtn.begin(); iter != m_TitleBtn.end(); iter++)
	{
		CDUIButton& dcControl = iter->second;
		if(dcControl.PtInButton(point))
		{
			dcControl.GetRect(&rtButton);
			return dcControl.GetControlId();
		}
	}
	return -1;
}
