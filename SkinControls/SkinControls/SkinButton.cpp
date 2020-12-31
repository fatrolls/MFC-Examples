
#include "stdafx.h"
#include "Resource.h"
#include "SkinButton.h"
#include "SkinHelper.h"
#include "DrawHelpers.h"

CSkinImage CSkinButton::m_ImageDefButton; // 默认按钮

#define BUTTON_CORNER_CX			2			// 圆角大小
#define BUTTON_CORNER_CY			2			// 圆角大小

enum
{
	_nImageNormal = 0,
	_nImageFocusOrHover,
	_nImagePushed,
	_nImageDisabled,

	_nImageCount = 4,
};

IMPLEMENT_DYNAMIC(CSkinButton, CButton)

BEGIN_MESSAGE_MAP(CSkinButton, CButton)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

// 构造函数
CSkinButton::CSkinButton() : m_bMouseOver(false), m_bAutoClipTrans(false), m_clrMask(MASK_COLOR)
{
	if (!m_ImageDefButton.IsValid())
	{
		HMODULE hModule = GetModuleHandle(SKIN_CONTROLS_DLL_NAME);
		m_ImageDefButton.LoadFromResource(hModule, MAKEINTRESOURCE(IDB_BUTTON), BF_BMP);
	}
}

// 析构函数
CSkinButton::~CSkinButton()
{
}

// 对象附加到现有窗口
void CSkinButton::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	ModifyStyle(0, BS_OWNERDRAW);

	if(m_ImageButton.IsValid())
	{
		if (m_bAutoClipTrans) CalcButtonRgn();
		SizeToImage();
	}
	else
	{
		CRect rcClient;
		GetWindowRect(&rcClient);
		SetWindowPos(NULL, 0, 0, rcClient.Width(), m_ImageDefButton.GetHeight(), SWP_NOMOVE | SWP_NOACTIVATE);
		SetWindowRgn(NULL, FALSE);
		HRGN hRgn = CreateRoundRectRgn(0, 0, rcClient.Width() + 1, m_ImageDefButton.GetHeight() + 1, BUTTON_CORNER_CX, BUTTON_CORNER_CY);
		SetWindowRgn(hRgn, TRUE);
		::DeleteObject(hRgn);
	}

	SendMessage(WM_SETFONT, (WPARAM)(HFONT)(CSkinHelper::GetDefaultFont()), TRUE);

	return;
}

// 界面绘画函数
void CSkinButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CRect ClientRect;
	GetClientRect(&ClientRect);
	bool bDisable = ((lpDrawItemStruct->itemState&ODS_DISABLED) != 0);
	bool bButtonDown = ((lpDrawItemStruct->itemState&ODS_SELECTED) != 0);

	// 设置 DC
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	// 计算位图位置
	int nImage = _nImageNormal;
	if (bButtonDown) nImage = _nImagePushed;
	else if (m_bMouseOver) nImage = _nImageFocusOrHover;
	else if (bDisable) nImage = _nImageDisabled;

	// 加载背景图
	if (m_ImageButton.IsValid())
	{
		INT nBtnWidth = m_ImageButton.GetWidth() / _nImageCount;
		m_ImageButton.DrawImage(pDC, 0, 0, nBtnWidth, m_ImageButton.GetHeight(), nImage * nBtnWidth, 0,
			nBtnWidth, m_ImageButton.GetHeight(), m_clrMask);
	}
	else
	{
		// 绘画默认界面
		INT nHeight = m_ImageDefButton.GetHeight();
		// 按钮左边
		m_ImageDefButton.DrawImage(pDC, 0, 0, 2, nHeight, nImage * 2, 0, 2, nHeight, m_clrMask);

		// 按钮中间
		CDC BufferDC;
		CBitmap BufferBmp;
		BufferDC.CreateCompatibleDC(pDC);
		BufferBmp.CreateCompatibleBitmap(pDC,ClientRect.Width()-4, ClientRect.Height());
		CBitmap* pOldBitmap = BufferDC.SelectObject(&BufferBmp);
		for (long xpos = 0; xpos < ClientRect.right - 4; xpos += 1)
		{
			m_ImageDefButton.DrawImage(&BufferDC, xpos, 0, 1, nHeight, nImage + 8, 0, 1, nHeight);
		}
		// 绘画中间
		pDC->BitBlt(2, 0, ClientRect.Width() - 4, ClientRect.Height(), &BufferDC, 0, 0, SRCCOPY);
		BufferDC.DeleteDC();
		BufferBmp.DeleteObject();
		pDC->SelectObject(pOldBitmap);

		// 按钮右边
		m_ImageDefButton.DrawImage(pDC, ClientRect.right - 2, 0, 2, nHeight, nImage * 2 + 12, 0, 2, nHeight, m_clrMask);

		//CSkinImage BufferImage;
		//BufferImage.Create(ClientRect.Width(), ClientRect.Height());
		//CCompatibleDC BufferDC(pDC, (HBITMAP)BufferImage);

		//// 按钮左边
		//m_ImageDefButton.DrawImage(&BufferDC, 0, 0, 2, nHeight, nImage * 2, 0, 2, nHeight);

		//// 按钮中间
		//for (long xpos = 2; xpos < ClientRect.right - 2; xpos += 1)
		//{
		//	m_ImageDefButton.DrawImage(&BufferDC, xpos, 0, 1, nHeight, nImage + 8, 0, 1, nHeight);
		//}

		//// 按钮右边
		//m_ImageDefButton.DrawImage(&BufferDC, ClientRect.right - 2, 0, 2, nHeight, nImage * 2 + 12, 0, 2, nHeight);
		//
		//// 透明绘画
		//CSkinImage::TransparentBlt(pDC->GetSafeHdc(), ClientRect, BufferDC.GetSafeHdc(), ClientRect, m_clrMask);

		//BufferImage.DestroyImage();
	}

	// 获取文字
	CString strText;
	GetWindowText(strText);

	if (!strText.IsEmpty())
	{
		// 绘画字体
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		CFont* pOldFont = pDC->SelectObject(&CSkinHelper::GetDefaultFont());
		ClientRect.top += (bButtonDown == true) ? 3 : 1;
		pDC->DrawText(strText, strText.GetLength(), ClientRect, DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
		pDC->SelectObject(pOldFont);
	}

	return;
}

// 加载位图
bool CSkinButton::SetButtonImage(LPCTSTR pszFileName, BitmapFormat bf, bool bAutoClipTrans)
{
	// 效验参数
	ASSERT(pszFileName);
	if (pszFileName == NULL) return false;

	m_bAutoClipTrans = bAutoClipTrans;

	// 加载图
	m_ImageButton.DestroyImage();
	m_ImageButton.LoadFromFile(pszFileName, bf);
	ASSERT(m_ImageButton.IsValid());

	// 调整位置
	if (GetSafeHwnd()) 
	{
		if (m_bAutoClipTrans) CalcButtonRgn();
		else SetWindowRgn(NULL, TRUE);
		SizeToImage();
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}

	return true;
}

// 加载位图
bool CSkinButton::SetButtonImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf, bool bAutoClipTrans)
{
	// 效验参数
	ASSERT(pBuffer && dwBufferSize);
	if (pBuffer==NULL || dwBufferSize == 0) return false;

	m_bAutoClipTrans = bAutoClipTrans;

	// 加载图
	m_ImageButton.DestroyImage();
	m_ImageButton.LoadFromMemory(pBuffer, dwBufferSize, bf);
	ASSERT(m_ImageButton.IsValid());

	// 调整位置
	if (GetSafeHwnd()) 
	{
		if (m_bAutoClipTrans) CalcButtonRgn();
		else SetWindowRgn(NULL, TRUE);
		SizeToImage();
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}

	return true;
}

// 加载位图
bool CSkinButton::SetButtonImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf, bool bAutoClipTrans)
{
	m_bAutoClipTrans = bAutoClipTrans;

	m_ImageButton.DestroyImage();
	m_ImageButton.LoadFromResource(hInst, lpszResource, bf);
	ASSERT(m_ImageButton.IsValid());

	// 调整位置
	if (GetSafeHwnd()) 
	{
		if (m_bAutoClipTrans) CalcButtonRgn();
		else SetWindowRgn(NULL, TRUE);
		SizeToImage();
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}

	return true;
}

// 建立消息
int CSkinButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	ModifyStyle(0, BS_OWNERDRAW);

	if(m_ImageButton.IsValid())
	{
		if (m_bAutoClipTrans) CalcButtonRgn();
		SizeToImage();
	}

	SendMessage(WM_SETFONT, (WPARAM)(HFONT)(CSkinHelper::GetDefaultFont()), TRUE);

	return 0;
}

// 鼠标移动消息
void CSkinButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bMouseOver == false)
	{
		// 注册消息
		m_bMouseOver = true;
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
		TRACKMOUSEEVENT TrackMouseEvent;
		TrackMouseEvent.cbSize = sizeof(TrackMouseEvent);
		TrackMouseEvent.dwFlags = TME_LEAVE;
		TrackMouseEvent.hwndTrack = GetSafeHwnd();
		TrackMouseEvent.dwHoverTime = HOVER_DEFAULT;
		_TrackMouseEvent(&TrackMouseEvent);
	}
	__super::OnMouseMove(nFlags, point);
}

// 鼠标离开消息
LRESULT CSkinButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bMouseOver = false;
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	return 0;
}

// 背景函数
BOOL CSkinButton::OnEraseBkgnd(CDC * pDC)
{
	return TRUE;
}

// 大小消息
void CSkinButton::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	if (!m_ImageButton.IsValid())
	{
		SetWindowPos(NULL, 0, 0, cx, m_ImageDefButton.GetHeight(), SWP_NOMOVE | SWP_NOACTIVATE);
		SetWindowRgn(NULL, FALSE);
		HRGN hRgn = CreateRoundRectRgn(0, 0, cx + 1, m_ImageDefButton.GetHeight() + 1, BUTTON_CORNER_CX, BUTTON_CORNER_CY);
		SetWindowRgn(hRgn, TRUE);
		::DeleteObject(hRgn);
	}
}

void CSkinButton::SizeToImage()
{
	ASSERT(::IsWindow(m_hWnd) && m_ImageButton.IsValid());
	if (m_hWnd == NULL) return;
	if (!m_ImageButton.IsValid()) return;
	int cx = m_ImageButton.GetWidth() / _nImageCount;
	int cy = m_ImageButton.GetHeight();
	SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE);
}

bool CSkinButton::CalcButtonRgn()
{
	ASSERT(m_ImageButton.IsValid());
	if (!m_ImageButton.IsValid()) return false;

	if (m_hWnd == NULL) return false;

	// 创建区域
	int cx = m_ImageButton.GetWidth() / _nImageCount;
	int cy = m_ImageButton.GetHeight();
	CRgn RgnControl;
	m_ImageButton.CreateBitmapRegion(RgnControl, 0, 0, cx, cy, m_clrMask);

	// 设置区域
	SetWindowRgn(RgnControl, TRUE);

	return true;
}