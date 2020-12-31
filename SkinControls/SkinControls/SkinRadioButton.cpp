
#include "stdafx.h"
#include "Resource.h"
#include "SkinRadioButton.h"
#include "SkinHelper.h"

enum
{
	_nImageUnCheckNormal = 0,
	_nImageUnCheckHover,
	_nImageUnCheckDisabled,
	_nImageCheckNormal,
	_nImageCheckHover,
	_nImageCheckDisabled,

	_nImageCount
};

IMPLEMENT_DYNAMIC(CSkinRadioButton, CSkinRadioBox)

BEGIN_MESSAGE_MAP(CSkinRadioButton, CSkinRadioBox)
	ON_WM_CREATE()
END_MESSAGE_MAP()

CSkinRadioButton::CSkinRadioButton()
{
}

CSkinRadioButton::~CSkinRadioButton()
{
}

// 对象附加到现有窗口
void CSkinRadioButton::PreSubclassWindow()
{
	CButton::PreSubclassWindow();
	UINT uButtonStyle = GetButtonStyle();
	uButtonStyle &= ~(0xF);
	uButtonStyle |= BS_AUTORADIOBUTTON;
	SetButtonStyle(uButtonStyle);
	ModifyStyle(0, BS_OWNERDRAW);

	if(m_ImageButton.IsValid())
	{
		if (m_bAutoClipTrans) CalcButtonRgn();
		SizeToImage();
	}

	SendMessage(WM_SETFONT, (WPARAM)(HFONT)(CSkinHelper::GetDefaultFont()), TRUE);

	return;
}

// 界面绘制
void CSkinRadioButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rcItem(lpDIS->rcItem);
	bool bDisable = ((lpDIS->itemState&ODS_DISABLED) != 0);

	if (m_ImageButton.IsValid())
	{
		int nItemWidth =  m_ImageButton.GetWidth() / _nImageCount;
		int nItemHeight = m_ImageButton.GetHeight();
		int nImage = _nImageUnCheckNormal;
		if (m_bChecked)
		{
			nImage = _nImageCheckNormal;
			if (m_bMouseOver) nImage = _nImageCheckHover;
			else if (bDisable) nImage = _nImageCheckDisabled;
		}
		else
		{
			if (m_bMouseOver) nImage = _nImageUnCheckHover;
			else if (bDisable) nImage = _nImageUnCheckDisabled;
		}

		m_ImageButton.DrawImage(pDC, 0, 0, nItemWidth, nItemHeight, nImage * nItemWidth, 0, nItemWidth, nItemHeight, m_clrMask);
	}

	CString strText;
	GetWindowText(strText);
	if (!strText.IsEmpty())
	{
		CFont* pOldFont = pDC->SelectObject(&CSkinHelper::GetCaptionFont());
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_clrTextColor);
		pDC->DrawText(strText, &rcItem, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		pDC->SelectObject(pOldFont);
	}
}

// 加载位图
bool CSkinRadioButton::SetButtonImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf, bool bAutoClipTrans)
{
	m_bAutoClipTrans = bAutoClipTrans;

	// 加载位图
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

// 加载位图
bool CSkinRadioButton::SetButtonImage(LPCTSTR pszFileName, BitmapFormat bf, bool bAutoClipTrans)
{
	// 效验参数
	ASSERT(pszFileName);
	if (pszFileName == NULL) return false;

	m_bAutoClipTrans = bAutoClipTrans;

	// 加载位图
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
bool CSkinRadioButton::SetButtonImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf, bool bAutoClipTrans)
{
	//效验参数
	ASSERT(pBuffer && dwBufferSize);
	if (pBuffer == NULL || dwBufferSize == 0) return false;

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

// 建立消息
int CSkinRadioButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct)==-1) return -1;
	lpCreateStruct->style &= ~(0xF);
	lpCreateStruct->style |= BS_AUTORADIOBUTTON;
	ModifyStyle(0, BS_OWNERDRAW);

	if(m_ImageButton.IsValid())
	{
		if (m_bAutoClipTrans) CalcButtonRgn();
		SizeToImage();
	}

	SendMessage(WM_SETFONT, (WPARAM)(HFONT)(CSkinHelper::GetDefaultFont()), TRUE);

	return 0;
}

void CSkinRadioButton::SizeToImage()
{
	ASSERT(::IsWindow(m_hWnd) && m_ImageButton.IsValid());
	if (m_hWnd == NULL) return;
	if (!m_ImageButton.IsValid()) return;
	int cx = m_ImageButton.GetWidth() / _nImageCount;
	int cy = m_ImageButton.GetHeight();
	SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE);
}

bool CSkinRadioButton::CalcButtonRgn()
{
	if (m_hWnd == NULL) return false;
	ASSERT(m_ImageButton.IsValid());
	if (!m_ImageButton.IsValid()) return false;

	// 创建区域
	int cx = m_ImageButton.GetWidth() / _nImageCount;
	int cy = m_ImageButton.GetHeight();
	CRgn RgnControl;
	m_ImageButton.CreateBitmapRegion(RgnControl, 0, 0, cx, cy, m_clrMask);

	// 设置区域
	SetWindowRgn(RgnControl, TRUE);

	return true;
}