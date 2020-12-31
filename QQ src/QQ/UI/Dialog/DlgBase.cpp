

#include "StdAfx.h"
#include <winuser.h>
#include <Windows.h>
#include <Windowsx.h>
#include <Shlwapi.h>
#include <cmath>
#include "..\..\Resource.h"
#include "DlgBase.h"
#include "..\Button\ImageButton.h"
#include "..\Other\Area.h"

// 控件
#define					BT_MIN								10000
#define					BT_CLOSE							10001

IMPLEMENT_DYNAMIC(CDlgBase, CDialog)

CDlgBase::CDlgBase(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
: CDialog(nIDTemplate, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_MinSize.cx = 380;
	m_MinSize.cy = 280;

	m_nFrameTopBottomSpace = 3;
	m_nFrameLeftRightSpace = 3;

	m_nOverRegio = 0;
	m_sizeBKImage.cx = 100;
	m_sizeBKImage.cy = 100;

	m_bTracking = false;
	m_bIsSetCapture = false;
	m_clrBK = RGB(186, 226, 239);

	m_bIsLButtonDown = FALSE;
	m_rcLButtonDown.SetRect(-1, -1, -1, -1);
	m_bIsLButtonDblClk = FALSE;
	m_pOldMemBK = NULL;
	m_pControl = NULL;
	m_pFocusControl = NULL;
	m_pEditControl = NULL;
	m_pEdit = NULL;
	m_pWndPopup = NULL;

	char fileName[MAX_PATH];
	if (!GetModuleFileName(NULL, fileName, sizeof(fileName)))
		return ;

	char *p = strrchr(fileName, '\\');
	if (p)
	{
		*(p + 1) = '\0';
	}

	m_strPath = fileName;
}

CDlgBase::~CDlgBase()
{
	if (m_hIcon)
	{
		DestroyIcon(m_hIcon);
		m_hIcon = NULL;
	}

	if(m_BKImage.m_hObject != NULL)
	{
		m_BKImage.DeleteObject();
		m_MemBKDC.SelectObject(m_pOldMemBK);
		m_MemBK.DeleteObject();
	}

	if(m_TitleFont.m_hObject != NULL)
	{
		m_TitleFont.DeleteObject();
	}
	m_Rgn.DeleteObject();

	for (size_t i = 0; i < m_vecControl.size(); i++)
	{
		CControlBase * pControlBase = m_vecControl.at(i);
		if (pControlBase)
		{
			delete pControlBase;
		}		
	}

	for (size_t i = 0; i < m_vecBaseControl.size(); i++)
	{
		CControlBase * pControlBase = m_vecBaseControl.at(i);
		if (pControlBase)
		{
			delete pControlBase;
		}		
	}

	for (size_t i = 0; i < m_vecArea.size(); i++)
	{
		CControlBase * pControlBase = m_vecArea.at(i);
		if (pControlBase)
		{
			delete pControlBase;
		}		
	}

	for (size_t i = 0; i < m_vecBaseArea.size(); i++)
	{
		CControlBase * pControlBase = m_vecBaseArea.at(i);
		if (pControlBase)
		{
			delete pControlBase;
		}		
	}
}

BEGIN_MESSAGE_MAP(CDlgBase, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCPAINT()
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_NCDESTROY()
	ON_WM_CLOSE()
	ON_WM_NCACTIVATE()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_WM_SYSCOMMAND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DROPFILES()
	ON_MESSAGE(BT_MIN,OnMessageButtomMin)
	ON_MESSAGE(BT_CLOSE,OnMessageButtomClose)
	ON_MESSAGE(WM_POPUP_CLOSE,OnMessagePopupClose)
END_MESSAGE_MAP()

// 设置最小窗口大小
void CDlgBase::SetMinSize(int iWidth, int iHeight)
{
	m_MinSize.cx = iWidth;
	m_MinSize.cy = iHeight;
}

CSize CDlgBase::GetMinSize()
{
	return	m_MinSize;
}

void CDlgBase::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	CDialog::OnGetMinMaxInfo(lpMMI);
	lpMMI->ptMinTrackSize.x = m_MinSize.cx;
	lpMMI->ptMinTrackSize.y = m_MinSize.cy;

	CRect	rc(0, 0, 1024, 768);
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
	lpMMI->ptMaxPosition.x = rc.left;
	lpMMI->ptMaxPosition.y = rc.top;
	lpMMI->ptMaxSize.x = rc.Width();
	lpMMI->ptMaxSize.y = rc.Height();
}

// CDlgBase message handlers

BOOL CDlgBase::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	SetWindowText("QQ");

	CFont	tmpFont;
	tmpFont.Attach(GetStockObject(DEFAULT_GUI_FONT));

	LOGFONT font;
	memset(&font, 0, sizeof(font));
	tmpFont.GetLogFont(&font);

	CWindowDC dc(this);
	strcpy(font.lfFaceName,"宋体");
	font.lfHeight = -10 * GetDeviceCaps(dc.m_hDC, LOGPIXELSY) / 72;
	font.lfWeight = 600;

	m_TitleFont.CreateFontIndirect(&font);

	::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, m_MinSize.cx, m_MinSize.cy, SWP_SHOWWINDOW | SWP_NOMOVE);

	CRect	rc;
	GetClientRect(rc);

	InitBaseUI(rc);
	InitUI(rc);

	CenterWindow();

	return TRUE;
}

void CDlgBase::InitBaseUI(CRect rcClient)
{
	CRect rcTemp;
	CControlBase * pControlBase = NULL;


	int nStartButton = rcClient.right - 39;
	rcTemp.SetRect(nStartButton, 0, nStartButton + 39, 20);
	pControlBase = new CImageButton(GetSafeHwnd(), BT_CLOSE, rcTemp);
	((CImageButton *)pControlBase)->SetBitmap(IDB_BT_CLOSE);
	m_vecBaseControl.push_back(pControlBase);

	nStartButton -= 28;
	rcTemp.SetRect(nStartButton, 0, nStartButton + 28, 20);
	pControlBase = new CImageButton(GetSafeHwnd(), BT_MIN, rcTemp);
	((CImageButton *)pControlBase)->SetBitmap(IDB_BT_MIN);
	m_vecBaseControl.push_back(pControlBase);
}

CControlBase *CDlgBase::GetControl(UINT uControlID)
{
	for (size_t i = 0; i < m_vecControl.size(); i++)
	{
		CControlBase * pControlBase = m_vecControl.at(i);
		if (pControlBase)
		{
			if (pControlBase->GetControlID() == uControlID)
			{
				return pControlBase;
			}
		}
	}
	for (size_t i = 0; i < m_vecBaseControl.size(); i++)
	{
		CControlBase * pControlBase = m_vecBaseControl.at(i);
		if (pControlBase)
		{
			if (pControlBase->GetControlID() == uControlID)
			{
				return pControlBase;
			}
		}
	}

	return NULL;
}

int CDlgBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// 设置窗口风格
	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE)
		| WS_MAXIMIZEBOX | WS_MINIMIZEBOX
		| WS_SYSMENU | WS_SIZEBOX | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	dwStyle &= ~(WS_CAPTION|WS_THICKFRAME);

	::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

	return CDialog::OnCreate(lpCreateStruct);
}

void CDlgBase::OnDropFiles(HDROP hDropInfo)
{
	char szFileName[MAX_PATH + 1] = {0};
	UINT nFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	for(UINT i = 0; i < nFiles; i++)
	{		
		DragQueryFile(hDropInfo, i, szFileName, MAX_PATH);
		if(PathIsDirectory(szFileName))
		{
			continue;
		}	
		CString strFileName = szFileName;
		strFileName = strFileName.Right(3);
		if (0 == strFileName.CompareNoCase("bmp") || 0 == strFileName.CompareNoCase("jpg") || 0 == strFileName.CompareNoCase("png"))
		{
			LoadImage(szFileName);	
			Invalidate();
			break;
		}
	}

	// CDialog::OnDropFiles(hDropInfo);
}


void CDlgBase::LoadImage(UINT nIDResource)
{
	CBitmap bitBackground;
 	bitBackground.LoadBitmap(nIDResource);
 	GetSize(bitBackground, m_sizeBKImage);
	DrawBackground(bitBackground);	
}

void CDlgBase::LoadImage(CString strFileName)
{
	CBitmap bitBackground;
	::LoadImage(strFileName, bitBackground, m_sizeBKImage);	
	DrawBackground(bitBackground);	
}

// 画背景图片
void CDlgBase::DrawBackground(CBitmap &bitBackground)
{
	if(m_MinSize.cx > m_sizeBKImage.cx || m_MinSize.cy > m_sizeBKImage.cy)
	{
		m_nOverRegio = __min(100, m_sizeBKImage.cx);
		m_nOverRegio = __min(m_nOverRegio, m_sizeBKImage.cy);
	}
	else
	{
		m_nOverRegio = 0;
	}
	if(bitBackground.m_hObject)
	{
		int nWidth = m_sizeBKImage.cx;
		int nHeight = m_sizeBKImage.cy;

		if(m_MemBKDC.m_hDC)
		{
			m_MemBKDC.DeleteDC();
		}

		CDC *pDC = GetDC();
		::GetAverageColor(pDC, bitBackground, m_sizeBKImage, m_clrBK);

		m_MemBKDC.CreateCompatibleDC(pDC);

		if(m_MemBK.m_hObject)
		{
			m_MemBK.DeleteObject();
		}
		m_MemBK.CreateCompatibleBitmap(pDC, m_sizeBKImage.cx, m_sizeBKImage.cy);
		m_pOldMemBK =  m_MemBKDC.SelectObject(&m_MemBK);

		CDC TempDC;
		TempDC.CreateCompatibleDC(pDC);

		CBitmap* pOldBitmap = TempDC.SelectObject(&bitBackground);

		// 画出平均图片
		m_MemBKDC.FillSolidRect(0, 0, nWidth, nHeight, m_clrBK); 

		// 左上
		m_MemBKDC.BitBlt(0, 0, nWidth - m_nOverRegio , nHeight - m_nOverRegio, &TempDC, 0, 0, SRCCOPY ); 

		if(m_nOverRegio > 0)
		{
			// 中间
			CRect rc(0, 0, nWidth, nHeight);
			DrawRightBottomTransition(m_MemBKDC, TempDC, rc, m_nOverRegio, m_clrBK);

			// 右上
			rc.SetRect(nWidth - m_nOverRegio, 0, nWidth, nHeight - m_nOverRegio);
			DrawHorizontalTransition(m_MemBKDC, TempDC, rc, rc, 0, 100);

			// 左下
			rc.SetRect(0, nHeight - m_nOverRegio, nWidth - m_nOverRegio, nHeight);
			DrawVerticalTransition(m_MemBKDC, TempDC, rc, rc, 0, 100);
		}

		TempDC.SelectObject(pOldBitmap);
		TempDC.DeleteDC();


		ReleaseDC(pDC);
	}
}

BOOL CDlgBase::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

HCURSOR CDlgBase::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDlgBase::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

 		//SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
 
 		//// 使图标在工作矩形中居中
  	//	int cxIcon = GetSystemMetrics(SM_CXICON);
  	//	int cyIcon = GetSystemMetrics(SM_CYICON);
  	//	CRect rect;
  	//	GetClientRect(&rect);
  	//	int x = (rect.Width() - cxIcon + 1) / 2;
  	//	int y = (rect.Height() - cyIcon + 1) / 2;
 
 		//// 绘制图标
 		//dc.DrawIcon(x, y, m_hIcon);
		dc.SetPixel(10, 10, RGB(255, 255, 255));
	}
	else
	{
 		CRect	rcClient;
 		GetClientRect(&rcClient);

		CPaintDC	dc(this);
		CDC MemDC;
		MemDC.CreateCompatibleDC(&dc);
		CBitmap memBmp;
		memBmp.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
		CBitmap *pOldmap =  MemDC.SelectObject(&memBmp);

		DrawImageStyle(MemDC, rcClient);

		dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &MemDC, 0, 0, SRCCOPY);

		MemDC.SelectObject(pOldmap);
		MemDC.DeleteDC();
	}
}


void CDlgBase::DrawImageStyle(CDC &dc, const CRect &rcClient)
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	MemDC.SetBkMode(TRANSPARENT);

	dc.FillSolidRect(0, 0, rcClient.Width(), rcClient.Height(), m_clrBK);

	int nShowBkImageWidth = rcClient.Width();
	int nShowBkImageHeight = rcClient.Height();

	
	if (rcClient.Width() > m_sizeBKImage.cx)
	{
		// 右
		nShowBkImageWidth = m_sizeBKImage.cx;
	}

	if (rcClient.Height() > m_sizeBKImage.cy)
	{
		// 下
		nShowBkImageHeight = m_sizeBKImage.cy;
	}

	// 左上
	dc.BitBlt(0, 0, nShowBkImageWidth , nShowBkImageHeight, &m_MemBKDC, 0, 0, SRCCOPY ); 

	// 画控件
	DrawControl(dc, rcClient);

	CRect rcClientTemp = rcClient;
	// 画边框
	if (!IsZoomed() && !IsIconic())
	{
		CDC TempDC;
		TempDC.CreateCompatibleDC(&dc);

		CBitmap memBmp;
		memBmp.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
		CBitmap* pOldBitmap = TempDC.SelectObject(&memBmp);

		TempDC.FillSolidRect(&rcClient, RGB(0, 0, 0));

		rcClientTemp.left++;
		rcClientTemp.top++;
		rcClientTemp.right--;
		rcClientTemp.bottom--;
		TempDC.FillSolidRect(&rcClientTemp, RGB(255, 255, 255));



		BLENDFUNCTION blend;
		memset( &blend, 0, sizeof( blend) );
		blend.BlendOp= AC_SRC_OVER;
		blend.SourceConstantAlpha = 128; // 透明度	
		// 左
		dc.AlphaBlend(0, 0, 2, rcClient.Height(), &TempDC, 0, 0, 2, rcClient.Height(), blend);
		// 上中
		dc.AlphaBlend(2, 0, rcClient.Width() - 2, 2, &TempDC, 2, 0, rcClient.Width() - 2, 2, blend);
		// 右
		dc.AlphaBlend(rcClient.Width() - 2, 0, 2, rcClient.Height(), &TempDC, rcClient.Width() - 2, 0, 2, rcClient.Height(), blend);
		// 下
		dc.AlphaBlend(2, rcClient.Height() - 2, rcClient.Width() - 2, 2, &TempDC, 2, rcClient.Height() - 2, rcClient.Width() - 2, 2, blend);

		for (int i = 0; i < 3; i++)
		{
			// 左上
			dc.AlphaBlend(i, 3 - i, 1, 1, &TempDC, 0, 0, 1, 1, blend);
			dc.AlphaBlend(i + 1, 3 - i, 1, 1, &TempDC, 1, 1, 1, 1, blend);

			// 右上
			dc.AlphaBlend(rcClient.right - 4 + i, i, 1, 1, &TempDC, 0, 0, 1, 1, blend);
			dc.AlphaBlend(rcClient.right - 4 + i, i + 1, 1, 1, &TempDC, 1, 1, 1, 1, blend);

			// 左下
			dc.AlphaBlend(i, rcClient.bottom - 4 + i, 1, 1, &TempDC, 0, 0, 1, 1, blend);
			dc.AlphaBlend(i + 1, rcClient.bottom - 4 + i, 1, 1, &TempDC, 1, 1, 1, 1, blend);

			// 右下
			dc.AlphaBlend(rcClient.right - 4 + i, rcClient.bottom - i - 1, 1, 1, &TempDC, 0, 0, 1, 1, blend);
			dc.AlphaBlend(rcClient.right - 4 + i, rcClient.bottom - i - 2, 1, 1, &TempDC, 1, 1, 1, 1, blend);

		}

		TempDC.SelectObject(pOldBitmap);
		TempDC.DeleteDC();

		MemDC.SelectObject(pOldBitmap);
		memBmp.DeleteObject();
	}

	MemDC.DeleteDC();
}

void CDlgBase::DrawControl(CDC &dc, const CRect &rcClient)
{
	for (int i = 0; i < m_vecArea.size(); i++)
	{
		CControlBase * pControlBase = m_vecArea.at(i);
		if (pControlBase)
		{
			pControlBase->Draw(dc, rcClient);
		}
	}

	for (int i = 0; i < m_vecBaseArea.size(); i++)
	{
		CControlBase * pControlBase = m_vecBaseArea.at(i);
		if (pControlBase)
		{
			pControlBase->Draw(dc, rcClient);
		}
	}

	for (int i = 0; i < m_vecControl.size(); i++)
	{
		CControlBase * pControlBase = m_vecControl.at(i);
		if (pControlBase)
		{
			if (pControlBase->GetVisible() && !(pControlBase->GetRect() & rcClient).IsRectEmpty())
			{
				pControlBase->Draw(dc, rcClient);
			}			
		}
	}

	for (int i = 0; i < m_vecBaseControl.size(); i++)
	{
		CControlBase * pControlBase = m_vecBaseControl.at(i);
		if (pControlBase)
		{
			if (pControlBase->GetVisible() && !(pControlBase->GetRect() & rcClient).IsRectEmpty())
			{
				pControlBase->Draw(dc, rcClient);
			}			
		}
	}	
}

void CDlgBase::OnNcPaint()
{
}

LRESULT CDlgBase::OnNcHitTest(CPoint point)
{
	return	HTCLIENT;
}

void CDlgBase::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (!IsIconic())
	{
		BOOL bIsMaximize = IsZoomed();
		int border_offset[] = {3, 2, 1};
		if (bIsMaximize)
		{				
			SetupRegion(border_offset, 0);
			m_nFrameLeftRightSpace = m_nFrameTopBottomSpace = 0;
		}
		else
		{
			SetupRegion(border_offset, 3);
			m_nFrameLeftRightSpace = m_nFrameTopBottomSpace = 3;
		}	
	}

	CRect rc;
	GetClientRect(&rc);
	OnBaseSize(rc);
	OnSize(rc);
	InvalidateRect(NULL);
}

void CDlgBase::OnBaseSize(CRect rcClient)
{
	for (int i = 0; i < m_vecBaseArea.size(); i++)
	{
		CControlBase * pControlBase = m_vecBaseArea.at(i);
		CRect rcTemp;
		if (pControlBase)
		{
			UINT uControlID = pControlBase->GetControlID();
			
			if (BT_CLOSE == uControlID)
			{
				rcTemp.SetRect(0, rcClient.bottom - 36, rcClient.right, rcClient.bottom);
			}	
			else
			{
				continue;
			}
			pControlBase->SetRect(rcTemp);
		}
	}
	for (int i = 0; i < m_vecBaseControl.size(); i++)
	{
		CControlBase * pControlBase = m_vecBaseControl.at(i);
		CRect rcTemp;
		if (pControlBase)
		{
			UINT uControlID = pControlBase->GetControlID();
 			if (0 == uControlID)
 			{
 			}
 			else
 			{
 				continue;
 			}
 			pControlBase->SetRect(rcTemp);
		}
	}
}

// 设置窗口区域
void CDlgBase::SetupRegion(int border_offset[], int nSize)
{
	CDC* pDC = GetDC();

	CRect	rc;
	GetWindowRect(rc);
	rc.OffsetRect(-rc.left, -rc.top);

	CRgn	rgn;
	rgn.CreateRectRgn(0, 0, rc.Width(), rc.Height());
	CRgn	rgn_xor;
	CRect	rcXor;
	
	for (int y = 0; y < nSize; ++y)
	{
		rcXor.SetRect(0, y, border_offset[y], y + 1);
		rgn_xor.CreateRectRgn(0, y, border_offset[y], y + 1);
		rgn.CombineRgn(&rgn, &rgn_xor, RGN_XOR);
		rgn_xor.DeleteObject();
	}

	for (int y = 0; y < nSize; ++y)
	{
		rcXor.SetRect(rc.right - border_offset[y], y, rc.right, y + 1);
		rgn_xor.CreateRectRgn(rc.right - border_offset[y], y, rc.right, y + 1);
		rgn.CombineRgn(&rgn, &rgn_xor, RGN_XOR);
		rgn_xor.DeleteObject();
	}

	for (int y = 0; y < nSize; ++y)
	{
		rcXor.SetRect(0, rc.bottom - y - 1, border_offset[y],  rc.bottom - y);
		rgn_xor.CreateRectRgn(0, rc.bottom - y - 1, border_offset[y],  rc.bottom - y);
		rgn.CombineRgn(&rgn, &rgn_xor, RGN_XOR);
		rgn_xor.DeleteObject();
	}

	for (int y = 0; y < nSize; ++y)
	{
		rcXor.SetRect(rc.right - border_offset[y], rc.bottom - y - 1, rc.right, rc.bottom -  y);
		rgn_xor.CreateRectRgn(rc.right - border_offset[y], rc.bottom - y - 1, rc.right,rc.bottom -  y);
		rgn.CombineRgn(&rgn, &rgn_xor, RGN_XOR);
		rgn_xor.DeleteObject();
	}
// 	HWND hWnd = GetSafeHwnd();
// 	SetWindowLong(hWnd,GWL_EXSTYLE,GetWindowLong(hWnd,GWL_EXSTYLE) | WS_EX_LAYERED);
// 	SetLayeredWindowAttributes(RGB(255, 0, 255), 0, LWA_COLORKEY );	

	SetWindowRgn((HRGN)rgn, TRUE);
	m_Rgn.DeleteObject();
	m_Rgn.Attach(rgn.Detach());
	ReleaseDC(pDC);
}

void CDlgBase::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);

	CRect	rcWindow;

	if (bCalcValidRects && lpncsp->lppos)
	{
		rcWindow.SetRect(lpncsp->lppos->x, lpncsp->lppos->y,
			lpncsp->lppos->x + lpncsp->lppos->cx,
			lpncsp->lppos->y + lpncsp->lppos->cy);
	}
	else
	{
		GetWindowRect(rcWindow);
	}

	lpncsp->rgrc[0] = rcWindow;
 
}

void CDlgBase::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	if (lpwndpos->cx < m_MinSize.cx)
	{
		lpwndpos->cx = m_MinSize.cx;
	}
	if (lpwndpos->cy < m_MinSize.cy)
	{
		lpwndpos->cy = m_MinSize.cy;
	}
}

void CDlgBase::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	//	CDialog::OnWindowPosChanged(lpwndpos);

	::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED
		| SWP_NOSENDCHANGING | SWP_NOACTIVATE);

	SendMessage(WM_MOVE, 0, MAKELPARAM(lpwndpos->x, lpwndpos->y));
	SendMessage(WM_SIZE, 0, MAKELPARAM(lpwndpos->cx, lpwndpos->cy));
}

void CDlgBase::PostNcDestroy()
{

}

void CDlgBase::OnClose()
{
	OnCancel();
}

void CDlgBase::OnMinimize()
{
	ShowWindow(SW_MINIMIZE);
}
BOOL CDlgBase::OnMaximize()
{

 	if (IsZoomed())
 	{
 		ShowWindow(SW_RESTORE);
		return FALSE;
 	}
 	else
 	{
 		//TRACE("\n\n");
 		ShowWindow(SW_SHOWMAXIMIZED);
		return TRUE;
 	}
}

LRESULT CDlgBase::OnMessageButtomMin(WPARAM wParam, LPARAM lParam)
{
	if(BUTTOM_UP == lParam)
	{
		OnMinimize();
	}

	return 0;
}

LRESULT CDlgBase::OnMessageButtomClose(WPARAM wParam, LPARAM lParam)
{
	if(BUTTOM_UP == lParam)
	{
		OnClose();
	}

	return 0;
}

LRESULT CDlgBase::OnMessagePopupClose(WPARAM wParam, LPARAM lParam)
{
	if(m_pFocusControl && m_pControl != m_pFocusControl)
	{
		m_pFocusControl->OnFocus(false);
		InvalidateRect(m_pFocusControl->GetRect());
		m_pFocusControl = NULL;
	}
	return 0;
}

BOOL CDlgBase::OnNcActivate(BOOL bActive)
{
	m_bNCActive = (bool)bActive;

	if(m_bNCActive)
	{
		CloseDlgPopup();
	}
	else
	{
		m_bTracking = false;
		m_bIsSetCapture = false;
		m_rcLButtonDown.SetRect(-1, -1, -1, -1);
		m_pt.SetPoint(-1, -1);
		m_bIsLButtonDblClk = FALSE;
		
		if(m_bIsLButtonDown)
		{
			m_bIsLButtonDown = FALSE;
			if(m_pControl)
			{
				m_pControl->OnLButtonUp(0, m_pt);
				m_pControl = NULL;				
			}
		}	
		else
		{
			if(m_pControl)
			{
				m_pControl->OnMouseMove(0, m_pt);
				m_pControl = NULL;				
			}
		}
	}
	InvalidateRect(NULL);

	return TRUE;	
}


void CDlgBase::PreSubclassWindow()
{
	DragAcceptFiles(TRUE);
	
	CDialog::PreSubclassWindow();
}


void CDlgBase::OnMouseMove(UINT nFlags, CPoint point) 
{	
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = ::_TrackMouseEvent(&tme);
	}

	if (m_pControl)
	{
		CRect rc = m_pControl->GetRect();
		if(rc.PtInRect(point) && m_bTracking)
		{
			m_pt = point;
			if(m_pControl->OnMouseMove(nFlags, m_pt))
			{
				InvalidateRect(&m_pControl->GetRect());
			}
			return;
		}	
	}

	if (!m_bIsLButtonDown)
	{
		m_pt = point;

		CControlBase * pOldControl = m_pControl;
		BOOL bIsSelect = FALSE;

		if(m_bTracking)
		{
			for (int i = 0; i < m_vecBaseControl.size(); i++)
			{
				CControlBase * pControlBase = m_vecBaseControl.at(i);
				if (pControlBase)
				{
					if(pControlBase->GetVisible() && pControlBase->GetRresponse())
					{
						pControlBase->OnMouseMove(nFlags, m_pt);
						CRect rc = pControlBase->GetRect();
						if(rc.PtInRect(point))
						{
							m_pControl = pControlBase;
							bIsSelect = TRUE;
						}
					}
				}		
			}
			if(!bIsSelect)
			{
				for (int i = 0; i < m_vecControl.size(); i++)
				{
					CControlBase * pControlBase = m_vecControl.at(i);
					if (pControlBase)
					{
						if( pControlBase->GetVisible() && pControlBase->GetRresponse())
						{
							pControlBase->OnMouseMove(nFlags, m_pt);
							CRect rc = pControlBase->GetRect();
							if(rc.PtInRect(point))
							{
								m_pControl = pControlBase;
								bIsSelect = TRUE;
							}
						}
					}		
				}
			}
		}

		if (pOldControl)
		{
			InvalidateRect(&pOldControl->GetRect());
		}

		if (bIsSelect)
		{
			if (m_pControl)
			{
				InvalidateRect(&m_pControl->GetRect());
			}
		}
		else
		{
			m_pControl = NULL;
		}
	}
	
	//CDialog::OnMouseMove(nFlags, point);
}

LRESULT CDlgBase::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bTracking = FALSE;
	if (!m_bIsLButtonDown)
	{
		if (m_pControl)
		{
			CRect rc = m_pControl->GetRect();
			if (IsZoomed())
			{
				CPoint point;
				GetCursorPos(&point);
				ScreenToClient(&point);

				if(rc.PtInRect(point))
				{
					m_pt = point;
				}
				else
				{
					m_pt.SetPoint(-1, -1);
				}
			}
			else
			{
				m_pt.SetPoint(-1, -1);
			}
			m_pControl->OnMouseMove(0, m_pt);
			InvalidateRect(&rc);
		}
		m_pControl = NULL;
	}
	
	return 0;
}

LRESULT CDlgBase::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
 	if (m_pControl)
 	{
 		CPoint point;
 		GetCursorPos(&point);
 		ScreenToClient(&point);
 		CRect rc = m_pControl->GetRect();
 		if (rc.PtInRect(point))
 		{
 			m_pt = point;
 			InvalidateRect(&rc);			
 		}
 	}
	return 0;
}

void CDlgBase::OnLButtonDown(UINT nFlags, CPoint point)
{
	BOOL bIsSelect = false;

	if(m_pFocusControl != m_pControl && m_pFocusControl != NULL)
	{
		m_pFocusControl->OnFocus(false);
		m_pFocusControl = NULL;
	}
	if (m_pControl)
	{
		CRect rc = m_pControl->GetRect();
		if (rc.PtInRect(point))
		{
			bIsSelect = TRUE;
			m_bIsLButtonDown = TRUE;

			m_pFocusControl = m_pControl;
			m_rcLButtonDown = rc;
			if(m_pControl->OnLButtonDown(nFlags, point))
			{
				
				InvalidateRect(&rc);	
			}		
		}
	}

	
	
	if (bIsSelect && !m_bIsSetCapture)
	{
		SetCapture();
		m_bIsSetCapture = TRUE;
		
		return;
	}

	m_rcLButtonDown.SetRect(-1, -1, -1, -1);
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x, point.y));

	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgBase::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bIsSetCapture)
	{
		ReleaseCapture();
		m_bIsSetCapture = false;
	}

	m_bIsLButtonDown = FALSE;

	if (m_pControl)
	{
		CRect rc = m_pControl->GetRect();
		
		if(m_pControl->OnLButtonUp(nFlags, point))
		{
			InvalidateRect(&rc);
		}
		
		if (m_rcLButtonDown.PtInRect(point))
		{
			m_pt = point;
		}
		else
		{
			if (rc.PtInRect(point))
			{
				m_pt = point;
			}
			else
			{
				m_pt.SetPoint(-1, -1);
				m_pControl = NULL;
			}
		}			
	}
	
	m_bIsLButtonDblClk = FALSE;
	m_rcLButtonDown.SetRect(-1, -1, -1, -1);

	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgBase::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	for (int i = 0; i < m_vecBaseControl.size(); i++)
	{
		CControlBase * pControlBase = m_vecBaseControl.at(i);
		if (pControlBase)
		{
			CRect rc = pControlBase->GetRect();
			if(rc.PtInRect(point))
			{
				m_rcLButtonDown = rc;			
				m_bIsLButtonDblClk = TRUE;
				return;;
			}
		}		
	}

	for (int i = 0; i < m_vecControl.size(); i++)
	{
		CControlBase * pControlBase = m_vecControl.at(i);
		if (pControlBase)
		{
			CRect rc = pControlBase->GetRect();
			if(rc.PtInRect(point))
			{
				m_rcLButtonDown = rc;			
				m_bIsLButtonDblClk = TRUE;
				return;;
			}
		}		
	}

	//OnMaximize();

	CDialog::OnLButtonDblClk(nFlags, point);
}

// 打开弹出对话框
void CDlgBase::OpenDlgPopup(CWndPopup *pWndPopup, CRect rc, UINT uMessageID)
{
	ASSERT(pWndPopup);
	CloseDlgPopup();
	ClientToScreen(&rc);
	m_pWndPopup = pWndPopup;
	m_pWndPopup->Create(this, rc, uMessageID);
}

// 关闭弹出对话框
void CDlgBase::CloseDlgPopup()
{
	if(m_pWndPopup)
	{
 		if(m_pFocusControl && m_pControl != m_pFocusControl)
 		{
 			m_pFocusControl->OnFocus(false);
 			m_pFocusControl = NULL;
 		}
		if(IsWindow(m_pWndPopup->GetSafeHwnd()))
		{
			m_pWndPopup->CloseWindow();			
		}
	}
	m_pWndPopup = NULL;
}

BOOL CDlgBase::PreTranslateMessage(MSG* pMsg)
{
	if ( pMsg->message == WM_KEYDOWN )
	{
		if( pMsg->wParam == VK_ESCAPE ) 
		{
			return TRUE;
		}
		if( pMsg->wParam == VK_RETURN  )
		{
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
