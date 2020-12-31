
#include "stdafx.h"
#include "Resource.h"
#include "SkinCheckBox.h"
#include "SkinHelper.h"

CSkinImage CSkinCheckBox::m_ImageDefButton;

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

IMPLEMENT_DYNAMIC(CSkinCheckBox, CSkinButton)

BEGIN_MESSAGE_MAP(CSkinCheckBox, CSkinButton)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(BM_GETCHECK, OnGetCheck)
	ON_MESSAGE(BM_SETCHECK, OnSetCheck)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

CSkinCheckBox::CSkinCheckBox()
{
	m_bChecked = FALSE;
	m_clrTextColor = RGB(0,0,0);
	m_clrBack = CLR_NONE;

	if (!m_ImageDefButton.IsValid())
	{
		HMODULE hModule = GetModuleHandle(SKIN_CONTROLS_DLL_NAME);
		m_ImageDefButton.LoadFromResource(hModule, MAKEINTRESOURCE(IDB_CHECKBOX));
	}
}

CSkinCheckBox::~CSkinCheckBox()
{
}

// 控件子类化
void CSkinCheckBox::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);

	SendMessage(WM_SETFONT, (WPARAM)(HFONT)(CSkinHelper::GetDefaultFont()), TRUE);
}

// 界面绘制
void CSkinCheckBox::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rcItem(lpDIS->rcItem);
	bool bDisable = ((lpDIS->itemState&ODS_DISABLED) != 0);

	if (m_clrBack != CLR_NONE) pDC->FillSolidRect(&rcItem, m_clrBack);
	if (m_ImageBackground.IsValid()) m_ImageBackground.DrawImage(pDC, rcItem.left, rcItem.top, rcItem.Width(), rcItem.Height());

	CSkinImage* pImage = NULL;
	if (m_ImageButton.IsValid()) pImage = &m_ImageButton;
	else pImage = &m_ImageDefButton;
	INT nItemWidth =  pImage->GetWidth() / _nImageCount;
	INT nItemHeight = pImage->GetHeight();
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
	pImage->DrawImage(pDC, rcItem.left, (rcItem.Height() - nItemHeight) / 2, nItemWidth, nItemHeight,
		nImage * nItemWidth, 0, nItemWidth, nItemHeight, m_clrMask);

	CString strText;
	GetWindowText(strText);
	if (!strText.IsEmpty())
	{
		CFont* pOldFont = pDC->SelectObject(&CSkinHelper::GetDefaultFont());
		pDC->SetTextColor(m_clrTextColor);
		pDC->SetBkMode(TRANSPARENT);
		rcItem.left = nItemWidth + 4;
		pDC->DrawText(strText, &rcItem, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_END_ELLIPSIS);
		pDC->SelectObject(pOldFont);
	}
}

// 设置文字颜色
void CSkinCheckBox::SetCheckBoxTextColor(COLORREF clrTextColor)
{
	m_clrTextColor = clrTextColor;
}

// 加载位图
bool CSkinCheckBox::SetButtonImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf)
{
	// 加载位图
	m_ImageButton.DestroyImage();
	m_ImageButton.LoadFromResource(hInst, lpszResource, bf);
	ASSERT(m_ImageButton.IsValid());

	return (!m_ImageButton.IsValid()) ? false : true;
}

// 加载位图
bool CSkinCheckBox::SetButtonImage(LPCTSTR lpszFileName, BitmapFormat bf)
{
	// 效验参数
	ASSERT(lpszFileName);
	if (lpszFileName == NULL) return false;

	// 加载位图
	m_ImageButton.DestroyImage();
	m_ImageButton.LoadFromFile(lpszFileName, bf);
	ASSERT(m_ImageButton.IsValid());

	return (!m_ImageButton.IsValid()) ? false : true;
}

// 加载位图
bool CSkinCheckBox::SetButtonImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf)
{
	// 效验参数
	ASSERT(pBuffer && dwBufferSize);
	if (pBuffer == NULL || dwBufferSize == 0) return false;

	// 加载图
	m_ImageButton.DestroyImage();
	m_ImageButton.LoadFromMemory(pBuffer, dwBufferSize, bf);
	ASSERT(m_ImageButton.IsValid());

	return (!m_ImageButton.IsValid()) ? false : true;
}

// 设置背景图片
void CSkinCheckBox::SetBackImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf)
{
	// 加载位图
	m_ImageBackground.DestroyImage();
	m_ImageBackground.LoadFromResource(hInst, lpszResource, bf);
	ASSERT(m_ImageBackground.IsValid());
}

// 从文件加载图片设置背景图片
void CSkinCheckBox::SetBackImage(LPCTSTR pszFileName, BitmapFormat bf)
{
	// 效验参数
	ASSERT(pszFileName);
	if (pszFileName == NULL) return;

	// 加载位图
	m_ImageBackground.DestroyImage();
	m_ImageBackground.LoadFromFile(pszFileName, bf);
	ASSERT(m_ImageBackground.IsValid());
}

// 从内存加载图片设置背景图片
void CSkinCheckBox::SetBackImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf)
{
	//效验参数
	ASSERT(pBuffer && dwBufferSize);
	if (pBuffer == NULL || dwBufferSize == 0) return;

	// 加载图
	m_ImageBackground.DestroyImage();
	m_ImageBackground.LoadFromMemory(pBuffer, dwBufferSize, bf);
	ASSERT(m_ImageBackground.IsValid());
}

// 建立消息
int CSkinCheckBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct)==-1) return -1;
	ModifyStyle(0, BS_OWNERDRAW);

	SendMessage(WM_SETFONT, (WPARAM)(HFONT)(CSkinHelper::GetDefaultFont()), TRUE);

	return 0;
}

// 大小消息
void CSkinCheckBox::OnSize(UINT nType, int cx, int cy)
{
	CButton::OnSize(nType, cx, cy);
}

// 左键按下
void CSkinCheckBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);

	__super::OnLButtonDown(nFlags, point);
}

// 左键松开
void CSkinCheckBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	if (rcClient.PtInRect(point))
	{
		m_bChecked = !m_bChecked;
	}

	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);

	__super::OnLButtonUp(nFlags, point);
}

void CSkinCheckBox::OnKillFocus(CWnd* pNewWnd) 
{
	__super::OnKillFocus(pNewWnd);

	m_bMouseOver = false;

	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
}

LRESULT CSkinCheckBox::OnGetCheck(WPARAM, LPARAM)
{
	return m_bChecked ? BST_CHECKED	: BST_UNCHECKED;
}

LRESULT CSkinCheckBox::OnSetCheck(WPARAM fCheck, LPARAM)
{
	ASSERT(fCheck != BST_INDETERMINATE);

	if ((!m_bChecked) != (fCheck == BST_UNCHECKED)) 
	{
		m_bChecked = fCheck != BST_UNCHECKED;

		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}

	return 0;
}

HBRUSH CSkinCheckBox::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)::GetStockObject(NULL_BRUSH);
}