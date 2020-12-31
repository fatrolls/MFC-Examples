#include "stdafx.h"
#include "resource.h"
#include "atlimage.h"
#include "CDrawDlg.h"

IMPLEMENT_DYNAMIC(CDrawDlg, CDialog)

CDrawDlg::CDrawDlg(UINT nIDTemplate, CWnd* pParent/* = NULL */)
: CDialog(nIDTemplate, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDrawDlg::~CDrawDlg()
{
}

void CDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCHITTEST()
	ON_WM_NCACTIVATE()
	ON_WM_NCRBUTTONDOWN()
	ON_WM_STYLECHANGED()
END_MESSAGE_MAP()


LRESULT CDrawDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	//WM_NCUAHDRAWCAPTION，WM_NCUAHDRAWFRAME
	if(message == 0x00AE || message == 0x00AF)
	{
		return 0;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CDrawDlg::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	GetWindowStyle();
	SetButtonRegion();
	OnNcPaint();
	CDialog::OnStyleChanged(nStyleType, lpStyleStruct);
}

BOOL CDrawDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 加载位图
	CImage ImageNormal, ImageHover, ImageDown;
	HBITMAP bmpNormal, bmpHover, bmpDown;

	// 加载关闭位图
	ImageNormal.Load(_T(".\\image\\Close_Normal.bmp"));
	ImageHover.Load(_T(".\\image\\Close_Hover.bmp"));
	ImageDown.Load(_T(".\\image\\Close_Down.bmp"));

	bmpNormal = ImageNormal.Detach();
	bmpHover  = ImageHover.Detach();
	bmpDown   = ImageDown.Detach();

	m_bmCloseNormal.Attach(bmpNormal);
	m_bmCloseHover.Attach(bmpHover);
	m_bmCloseDown.Attach(bmpDown);

	// 加载最大化位图
	ImageNormal.Load(_T(".\\image\\Max_Normal.bmp"));
	ImageHover.Load(_T(".\\image\\Max_Hover.bmp"));
	ImageDown.Load(_T(".\\image\\Max_Down.bmp"));

	bmpNormal = ImageNormal.Detach();
	bmpHover  = ImageHover.Detach();
	bmpDown   = ImageDown.Detach();

	m_bmMaxNormal.Attach(bmpNormal);
	m_bmMaxHover.Attach(bmpHover);
	m_bmMaxDown.Attach(bmpDown);

	// 加载还原位图
	ImageNormal.Load(_T(".\\image\\Restore_Normal.bmp"));
	ImageHover.Load(_T(".\\image\\Restore_Hover.bmp"));
	ImageDown.Load(_T(".\\image\\Restore_Down.bmp"));

	bmpNormal = ImageNormal.Detach();
	bmpHover  = ImageHover.Detach();
	bmpDown   = ImageDown.Detach();

	m_bmRestoreNormal.Attach(bmpNormal);
	m_bmRestoreHover.Attach(bmpHover);
	m_bmRestoreDown.Attach(bmpDown);

	// 加载最小化位图
	ImageNormal.Load(_T(".\\image\\Min_Normal.bmp"));
	ImageHover.Load(_T(".\\image\\Min_Hover.bmp"));
	ImageDown.Load(_T(".\\image\\Min_Down.bmp"));

	bmpNormal = ImageNormal.Detach();
	bmpHover  = ImageHover.Detach();
	bmpDown   = ImageDown.Detach();

	m_bmMinNormal.Attach(bmpNormal);
	m_bmMinHover.Attach(bmpHover);
	m_bmMinDown.Attach(bmpDown);

	return TRUE;
}

void CDrawDlg::OnPaint()
{
	if(IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

BOOL CDrawDlg::OnNcActivate(BOOL bActive)
{
	return TRUE;
}

void CDrawDlg::OnNcPaint()
{
	// 不存在标题栏
	if(WS_CAPTION != m_CaptionStyle) 
	{
		return;
	}

	CRect rtWin;
	CDC MemDC;
	GetWindowRect(&rtWin);
	CDC *pDC = GetWindowDC();
	MemDC.CreateCompatibleDC(pDC);

	// 绘制标题栏
	pDC->FillSolidRect(0, 0, rtWin.Width(), m_cyCaption, RGB(126, 208, 255));
	// 绘制左边框
	pDC->FillSolidRect(0, 0, m_ptDlgFrame.x, rtWin.Height(), RGB(126, 208, 255));
	// 绘制右边框
	pDC->FillSolidRect(rtWin.Width() - m_ptDlgFrame.x, 0, rtWin.Width(), rtWin.Height(), RGB(126, 208, 255));
	// 绘制下边框
	pDC->FillSolidRect(0, rtWin.Height() - m_ptDlgFrame.y, rtWin.Width(), m_ptDlgFrame.y, RGB(126, 208, 255));

	// 绘制图标
	DrawIconEx(
		pDC->m_hDC,
		m_ptDlgFrame.x, (m_cyCaption - GetSystemMetrics(SM_CYSMICON)) / 2,
		m_hIcon,
		GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0, 0, DI_NORMAL
	);

	// 绘制字体
	CString strText;
	GetWindowText(strText);
	if(!strText.IsEmpty())
	{
		CSize FontSize = pDC->GetTextExtent(strText);
		CRect rtFont;
		rtFont.left   = m_ptDlgFrame.x + GetSystemMetrics(SM_CXSMICON);
		rtFont.right  = rtFont.left + FontSize.cx;
		rtFont.top    = (m_cyCaption - FontSize.cy) / 2;
		rtFont.bottom = rtFont.top + FontSize.cy;
		pDC->DrawText(strText, &rtFont, DT_SINGLELINE | DT_LEFT);
	}

	// 绘制关闭按钮
	if(WS_SYSMENU == m_SysMenuStyle)
	{
		MemDC.SelectObject(&m_bmCloseNormal);
		pDC->BitBlt(m_rtCloseBox.left, m_rtCloseBox.top, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	}
	
	// 绘制最大化按钮
	if(WS_MAXIMIZEBOX == m_MaxStyle)
	{
		MemDC.SelectObject(&m_bmMaxNormal);
		if(IsZoomed())
		{
			MemDC.SelectObject(&m_bmRestoreNormal);
		}
		pDC->BitBlt(m_rtMaxBox.left, m_rtMaxBox.top, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	}
	
	// 绘制最小化按钮
	if(WS_MINIMIZEBOX == m_MinStyle)
	{
		MemDC.SelectObject(&m_bmMinNormal);
		pDC->BitBlt(m_rtMinBox.left, m_rtMinBox.top, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	}

	MemDC.DeleteDC();
	ReleaseDC(pDC);
}

HCURSOR CDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDrawDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	Invalidate();
}

void CDrawDlg::PreSubclassWindow()
{
	// 获取系统的边框的高度和宽度
	m_ptDlgFrame.x = GetSystemMetrics(SM_CXDLGFRAME);
	m_ptDlgFrame.y = GetSystemMetrics(SM_CYDLGFRAME);

	GetWindowStyle();
	CDialog::PreSubclassWindow();
}

void CDrawDlg::SetButtonRegion()
{
	CRect rtDlg;
	GetWindowRect(&rtDlg);

	m_rtCloseBox.right  = rtDlg.Width() - m_ptDlgFrame.x;
	m_rtCloseBox.left   = m_rtCloseBox.right - BMP_WIDTH;
	m_rtCloseBox.top    = m_ptDlgFrame.y;
	m_rtCloseBox.bottom = m_rtCloseBox.top + BMP_HEIGHT;

	m_rtMaxBox.right  = m_rtCloseBox.left - 1;
	m_rtMaxBox.left   = m_rtMaxBox.right - BMP_WIDTH;
	m_rtMaxBox.top    = m_rtCloseBox.top;
	m_rtMaxBox.bottom = m_rtCloseBox.bottom;

	m_rtMinBox.right  = m_rtMaxBox.left - 1;
	m_rtMinBox.left   = m_rtMinBox.right - BMP_WIDTH;
	m_rtMinBox.top    = m_rtCloseBox.top;
	m_rtMinBox.bottom = m_rtCloseBox.bottom;

	// 不存在系统菜单，当然也不会存在最大化、最小化和关闭按钮
	if(WS_SYSMENU != m_SysMenuStyle)
	{
		memset(&m_rtCloseBox, 0, sizeof(CRect));
		memset(&m_rtMaxBox, 0, sizeof(CRect));
		memset(&m_rtMinBox, 0, sizeof(CRect));
	}
	else
	{
		if(WS_MAXIMIZEBOX != m_MaxStyle)
		{
			m_rtMinBox = m_rtMaxBox;
			memset(&m_rtMaxBox, 0, sizeof(CRect));
		}
		if(WS_MINIMIZEBOX != m_MinStyle)
		{
			memset(&m_rtMinBox, 0, sizeof(CRect));
		}
	}
}

void CDrawDlg::GetWindowStyle()
{
	m_MaxStyle = GetWindowLong(m_hWnd, GWL_STYLE) & WS_MAXIMIZEBOX;
	m_MinStyle = GetWindowLong(m_hWnd, GWL_STYLE) & WS_MINIMIZEBOX;
	m_CaptionStyle = GetWindowLong(m_hWnd, GWL_STYLE) & WS_CAPTION;
	m_SysMenuStyle = GetWindowLong(m_hWnd, GWL_STYLE) & WS_SYSMENU;
}

BOOL CDrawDlg::PtInRect(CRect &rtWin, CRect &rtClientBtn, CPoint &pt)
{
	CRect rtScreenBtn;
	//计算相对于屏幕的按钮坐标
	rtScreenBtn.left   = rtWin.left + rtClientBtn.left;
	rtScreenBtn.right  = rtWin.left + rtClientBtn.right;
	rtScreenBtn.top    = rtWin.top  + rtClientBtn.top;
	rtScreenBtn.bottom = rtWin.top  + rtClientBtn.bottom;

	return rtScreenBtn.PtInRect(pt);
}

void CDrawDlg::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	if(lpncsp->lppos != NULL)
	{
		m_cyCaption = lpncsp->rgrc[2].top - lpncsp->lppos->y;
		SetButtonRegion();
	}
	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CDrawDlg::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
	if(HTCLOSE == nHitTest || HTMAXBUTTON == nHitTest || HTMINBUTTON == nHitTest)
	{
		return;
	}
	CDialog::OnNcRButtonDown(nHitTest, point);
}

void CDrawDlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// 不存在系统菜单或是没有双击标题栏
	if(WS_SYSMENU != m_SysMenuStyle || nHitTest != HTCAPTION)
	{
		return;
	}

	if(WS_MAXIMIZEBOX == m_MaxStyle)
	{
		if(IsZoomed())
		{
			ShowWindow(SW_RESTORE);
		}
		else
		{
			ShowWindow(SW_MAXIMIZE);
		}
	}
}

void CDrawDlg::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	CRect rtWin;
	GetWindowRect(&rtWin);
	if(HTMAXBUTTON == nHitTest)
	{
		if(ID_DOWN_MAX == m_nIDBtn)
		{
			if(IsZoomed())
			{
				ShowWindow(SW_RESTORE);
			}
			else
			{
				ShowWindow(SW_MAXIMIZE);
			}
		}
		return;
	}
	if(HTMINBUTTON == nHitTest)
	{
		if(ID_DOWN_MIN == m_nIDBtn)
		{
			ShowWindow(SW_MINIMIZE);
		}
		return;
	}

	if(HTCLOSE == nHitTest)
	{
		if(ID_DOWN_CLOSE == m_nIDBtn)
		{
			SendMessage(WM_CLOSE);
		}
	}
}

HRESULT CDrawDlg::OnNcHitTest(CPoint point)
{
	CRect rtWin;
	GetWindowRect(&rtWin);

	if(PtInRect(rtWin, m_rtCloseBox, point))
	{
		return HTCLOSE;
	}
	if(PtInRect(rtWin, m_rtMaxBox, point))
	{
		return HTMAXBUTTON;
	}
	if(PtInRect(rtWin, m_rtMinBox, point))
	{
		return HTMINBUTTON;
	}
	return CDialog::OnNcHitTest(point);
}

void CDrawDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	m_nIDBtn = ID_DOWN_INVALID;

	CRect *prtDraw = NULL;

	CDC MemDC;
	CDC *pDC = GetWindowDC();
	MemDC.CreateCompatibleDC(pDC);

	do 
	{
		if(HTMAXBUTTON == nHitTest)
		{
			m_nIDBtn = ID_DOWN_MAX;
			prtDraw = &m_rtMaxBox;
			if(IsZoomed())
			{
				MemDC.SelectObject(&m_bmRestoreDown);
			}
			else
			{	
				MemDC.SelectObject(&m_bmMaxDown);
			}
			break;
		}
		if(HTMINBUTTON == nHitTest)
		{
			m_nIDBtn = ID_DOWN_MIN;
			prtDraw = &m_rtMinBox;
			MemDC.SelectObject(&m_bmMinDown);
			break;
		}
		if(HTCLOSE == nHitTest)
		{
			m_nIDBtn = ID_DOWN_CLOSE;
			prtDraw = &m_rtCloseBox;
			MemDC.SelectObject(&m_bmCloseDown);
			break;
		}

		// 如果不是最大化窗口，允许拖动窗口
		if(!IsZoomed())
		{
			CDialog::OnNcLButtonDown(nHitTest, point);
		}

	} while (0);

	if(NULL != prtDraw)
	{
		pDC->BitBlt(prtDraw->left, prtDraw->top, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	}
	MemDC.DeleteDC();
	ReleaseDC(pDC);
}

void CDrawDlg::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	if(WS_SYSMENU != m_SysMenuStyle)
	{
		return;
	}

	CDC MemDC;
	CDC *pDC = GetWindowDC();
	MemDC.CreateCompatibleDC(pDC);

	if(HTCLOSE == nHitTest)
	{
		MemDC.SelectObject(&m_bmCloseHover);
	}
	else
	{
		MemDC.SelectObject(&m_bmCloseNormal);
	}
	if(WS_SYSMENU == m_SysMenuStyle)
	{
		pDC->BitBlt(m_rtCloseBox.left, m_rtCloseBox.top, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	}

	if(HTMAXBUTTON == nHitTest)
	{
		MemDC.SelectObject(&m_bmMaxHover);
		if(IsZoomed())
		{
			MemDC.SelectObject(&m_bmRestoreHover);
		}
	}
	else
	{
		MemDC.SelectObject(&m_bmMaxNormal);
		if(IsZoomed())
		{
			MemDC.SelectObject(&m_bmRestoreNormal);
		}
	}
	if(WS_MAXIMIZEBOX == m_MaxStyle)
	{
		pDC->BitBlt(m_rtMaxBox.left, m_rtMaxBox.top, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	}
	
	if(HTMINBUTTON == nHitTest)
	{
		MemDC.SelectObject(&m_bmMinHover);
	}
	else
	{
		MemDC.SelectObject(&m_bmMinNormal);
	}
	if(WS_MINIMIZEBOX == m_MinStyle)
	{
		pDC->BitBlt(m_rtMinBox.left, m_rtMinBox.top, BMP_WIDTH, BMP_HEIGHT, &MemDC, 0, 0, SRCCOPY);
	}

	MemDC.DeleteDC();
	ReleaseDC(pDC);
}