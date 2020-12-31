
#include "StdAfx.h"
#include "Resource.h"
#include "SkinComboBox.h"
#include "SkinHelper.h"
#include "DrawHelpers.h"

CSkinImage CSkinComboBox::m_ImageDefButton;

BEGIN_MESSAGE_MAP(CSkinComboBoxList, CListBox)
	ON_WM_NCPAINT()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSkinComboBoxEdit, CSkinEdit)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSkinComboBox, CComboBox)
    ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCbnCloseup)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

// 构造函数
CSkinComboBoxList::CSkinComboBoxList()
{
}

// 析构函数
CSkinComboBoxList::~CSkinComboBoxList()
{
}

// 绘画子项
void CSkinComboBoxList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// 变量定义
	CRect rcItem=lpDrawItemStruct->rcItem;
	CDC* pDCControl = CDC::FromHandle(lpDrawItemStruct->hDC);

	// 创建缓冲
	CBufferDC BufferDC(pDCControl->GetSafeHdc(), rcItem);

	// 设置环境
	BufferDC.SelectObject(&CSkinHelper::GetDefaultFont());

	// 获取字符
	CString strString;
	GetText(lpDrawItemStruct->itemID, strString);

	// 计算位置
	CRect rcString;
	rcString.SetRect(4, 0, rcItem.Width() - 8, rcItem.Height());

	// 颜色定义
	COLORREF crTextColor = ((lpDrawItemStruct->itemState & ODS_SELECTED) != 0) ? RGB(255, 255, 255) : RGB(0, 0, 0);
	COLORREF crBackColor = ((lpDrawItemStruct->itemState & ODS_SELECTED) != 0) ? RGB(10, 36, 106) : RGB(255, 255, 255);

	// 绘画背景
	BufferDC.FillSolidRect(0, 0, rcItem.Width(), rcItem.Height(), crBackColor);

	// 绘画字符
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SetTextColor(crTextColor);
	BufferDC.DrawText(strString, &rcString, DT_VCENTER | DT_SINGLELINE);

	return;
}

// 界面绘画
void CSkinComboBoxList::OnNcPaint()
{
	__super::OnNcPaint();

	// 获取位置
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	// 绘画边框
	CWindowDC WindowDC(this);
	COLORREF crBoradFrame = RGB(92, 100, 105);
	WindowDC.Draw3dRect(0, 0, rcWindow.Width(), rcWindow.Height(), crBoradFrame, crBoradFrame);

	return;
}

//////////////////////////////////////////////////////////////////////////

LRESULT CSkinComboBoxEdit::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	CSkinComboBox* pControl = (CSkinComboBox*)GetParent();

	if (pControl->m_bHighlighted)
	{
		TRACKMOUSEEVENT tme = {sizeof(TRACKMOUSEEVENT), TME_LEAVE, pControl->m_hWnd, HOVER_DEFAULT};
		_TrackMouseEvent(&tme);
	}

	return 0L;
}

void CSkinComboBoxEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rc;
	GetClientRect(&rc);

	CSkinComboBox* pControl = (CSkinComboBox*)GetParent();

	BOOL bHot = rc.PtInRect(point) /*&& !m_bFocused*/;
	if (bHot != pControl->m_bHighlighted)
	{
		pControl->m_bHighlighted = bHot;
		pControl->RedrawFocusedFrame();

		if (bHot)
		{
			TRACKMOUSEEVENT tme = {sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_hWnd, HOVER_DEFAULT};
			_TrackMouseEvent(&tme);
		}
	}


	__super::OnMouseMove(nFlags, point);
}

void CSkinComboBoxEdit::OnKillFocus(CWnd* pNewWnd)
{
	__super::OnKillFocus(pNewWnd);

	CSkinComboBox* pControl = (CSkinComboBox*)GetParent();
	if (pNewWnd != GetParent())
	{
		pControl->m_bFocused = FALSE;
		pControl->m_bHighlighted = FALSE;
		pControl->RedrawFocusedFrame();
	}
}

void CSkinComboBoxEdit::OnSetFocus(CWnd* pOldWnd)
{
	__super::OnSetFocus(pOldWnd);

	CSkinComboBox* pControl = (CSkinComboBox*)GetParent();

	pControl->m_bFocused = TRUE;
	pControl->m_bHighlighted = TRUE;
	pControl->RedrawFocusedFrame();
}

//////////////////////////////////////////////////////////////////////////////////

// 构造函数
CSkinComboBox::CSkinComboBox()
{
	// 设置变量
	m_uButtonWidth = 16;
	m_crEnableBack = RGB(255, 255, 255);
	m_crEnableBorder = RGB(76, 162, 225);
	m_crDisableBack = RGB(125, 125, 125);
	m_crDisableBorder = RGB(150, 150, 150);

	// 控制变量
	m_bHighlighted = FALSE;
	m_bFocused = FALSE;
	m_bDrawBorder = true;

	if (!m_ImageDefButton.IsValid())
	{
		HMODULE hModule = GetModuleHandle(SKIN_CONTROLS_DLL_NAME);
		m_ImageDefButton.LoadFromResource(hModule, MAKEINTRESOURCE(IDB_COMBOBOX));
	}
}

// 析构函数
CSkinComboBox::~CSkinComboBox()
{
}

// 控件绑定
void CSkinComboBox::PreSubclassWindow()
{
	// 获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	// 配置控件
	Initialization();
	RectifyControl(rcClient.Width(), rcClient.Height());

	return;
}

// 测量子项
void CSkinComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// 设置变量
	lpMeasureItemStruct->itemWidth = 0;
	lpMeasureItemStruct->itemHeight = GetItemHeight(LB_ERR);

	return;
}

// 边框设置
void CSkinComboBox::SetDrawBorder(bool bDrawBorder)
{
	//设置变量
	m_bDrawBorder = bDrawBorder;

	// 更新界面
	if (m_hWnd != NULL) Invalidate(FALSE);

	return;
}

// 设置资源
bool CSkinComboBox::SetButtonImage(LPCTSTR pszFileName, BitmapFormat bf)
{
	// 效验参数
	ASSERT(pszFileName != NULL);
	if (pszFileName == NULL) return false;

	// 加载图
	m_ImageButton.DestroyImage();
	m_ImageButton.LoadFromFile(pszFileName, bf);
	ASSERT(m_ImageButton.IsValid());
	if (!m_ImageButton.IsValid()) return false;

	// 获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	// 设置控件
	m_uButtonWidth = m_ImageButton.GetWidth() / _nImageCount;
	SetItemHeight(LB_ERR, m_ImageButton.GetHeight());

	// 配置控件
	RectifyControl(rcClient.Width(), rcClient.Height());

	// 更新界面
	if (m_hWnd != NULL) RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);

	return true;
}

// 设置资源
bool CSkinComboBox::SetButtonImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf)
{
	// 效验参数
	ASSERT(pBuffer && dwBufferSize);
	if (pBuffer==NULL || dwBufferSize == 0) return false;

	// 加载图
	m_ImageButton.DestroyImage();
	m_ImageButton.LoadFromMemory(pBuffer, dwBufferSize, bf);
	ASSERT(m_ImageButton.IsValid());
	if (!m_ImageButton.IsValid()) return false;

	// 获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	// 设置控件
	m_uButtonWidth = m_ImageButton.GetWidth() / _nImageCount;
	SetItemHeight(LB_ERR, m_ImageButton.GetHeight());

	// 配置控件
	RectifyControl(rcClient.Width(), rcClient.Height());

	// 更新界面
	if (m_hWnd != NULL) RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);

	return true;
}

// 设置资源
bool CSkinComboBox::SetButtonImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf)
{
	m_ImageButton.DestroyImage();
	m_ImageButton.LoadFromResource(hInst, lpszResource, bf);
	ASSERT(m_ImageButton.IsValid());
	if (!m_ImageButton.IsValid()) return false;

	// 获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	// 设置控件
	m_uButtonWidth = m_ImageButton.GetWidth() / _nImageCount;
	SetItemHeight(LB_ERR, m_ImageButton.GetHeight());

	// 配置控件
	RectifyControl(rcClient.Width(), rcClient.Height());

	// 更新界面
	if (m_hWnd != NULL) RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);

	return true;
}

// 配置控件
void CSkinComboBox::Initialization()
{
	// 设置状态
	m_bHighlighted = FALSE;
	m_bFocused = FALSE;

	// 变量定义
	COMBOBOXINFO ComboBoxInfo;
	ComboBoxInfo.cbSize = sizeof(ComboBoxInfo);

	// 绑定控件
	if (GetComboBoxInfo(&ComboBoxInfo) == TRUE)
	{
		if (ComboBoxInfo.hwndItem != NULL) m_SkinComboBoxEdit.SubclassWindow(ComboBoxInfo.hwndItem);
		if (ComboBoxInfo.hwndList != NULL)
		{
			m_SkinComboBoxList.SubclassWindow(ComboBoxInfo.hwndList);
		}
	}

	return;
}

// 调整控件
void CSkinComboBox::RectifyControl(int nWidth, int nHeight)
{
	// 移动控件
	if (m_SkinComboBoxEdit.m_hWnd != NULL && (GetStyle() & 0x000F) != CBS_SIMPLE)
	{
		// 获取位置
		CRect rcClient;
		GetClientRect(&rcClient);

		// 移动控件
		CFont* pFont = m_SkinComboBoxEdit.GetFont();
		LOGFONT lf; 
		pFont->GetLogFont(&lf); 
		CSize SizeEdit;
		long lHeight = (lf.lfHeight < 0 ? -lf.lfHeight : lf.lfHeight) + 2;
		SizeEdit.SetSize(rcClient.Width() - m_uButtonWidth - 10, lHeight);
		m_SkinComboBoxEdit.SetWindowPos(NULL, 6, (rcClient.Height() - lHeight) / 2, SizeEdit.cx, SizeEdit.cy, SWP_NOZORDER);
	}

	return;
}

void CSkinComboBox::SetHighlighted(BOOL bHot)
{
	if (bHot != m_bHighlighted)
	{
		m_bHighlighted = bHot;
		RedrawFocusedFrame();

		if (bHot)
		{
			TRACKMOUSEEVENT tme = {sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_hWnd, HOVER_DEFAULT};
			_TrackMouseEvent(&tme);
		}
	}
}

void CSkinComboBox::RedrawFocusedFrame()
{
	if (((GetStyle() & 0x000F) != CBS_SIMPLE))
	{
		// 获取位置
		CRect rcClient;
		GetClientRect(&rcClient);

		CRect rcButton(rcClient.right - m_uButtonWidth - 1, rcClient.top, rcClient.right - 1, rcClient.bottom);
		InvalidateRect(&rcButton, FALSE);
	}
}

// 重画消息
void CSkinComboBox::OnPaint()
{
	CPaintDC dc(this);

	// 获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	CBufferDC dcMem(dc, rcClient);

	if ((GetStyle() & 0x000F) == CBS_SIMPLE)
	{
		CComboBox::DefWindowProc(WM_PAINT, (WPARAM)dcMem.m_hDC, 0);
	}
	else
	{
		BOOL bPressed = GetDroppedState() != FALSE;
		BOOL bSelected = /*m_bFocused ||*/ m_bHighlighted;
		BOOL bEnabled = IsWindowEnabled();

		// 绘画背景
		if (((GetStyle() & 0x000F) == CBS_DROPDOWN) || (GetCurSel() == LB_ERR))
		{
			if (bEnabled)
			{
				dcMem.FillSolidRect(1, 1, rcClient.Width() - m_uButtonWidth - 2, rcClient.Height() - 2, m_crEnableBack);
			}
			else
			{
				dcMem.FillSolidRect(1, 1, rcClient.Width() - m_uButtonWidth - 2, rcClient.Height() - 2, m_crDisableBack);
			}
		}

		// 绘画背景
		if ((GetStyle() & 0x000F) == CBS_DROPDOWNLIST)
		{
			// 设置颜色
			if (GetFocus()->GetSafeHwnd() == m_hWnd)
			{
				dcMem.FillSolidRect(0, 0, rcClient.Width() - m_uButtonWidth, rcClient.Height(), m_crEnableBack);
			}
			else
			{
				dcMem.FillSolidRect(0, 0, rcClient.Width(), rcClient.Height(), m_crEnableBack);
			}
		}

		// 绘画字符
		if ((GetStyle() & 0x000F) == CBS_DROPDOWNLIST)
		{
			// 获取字符
			CString strString;
			GetWindowText(strString);

			// 获取字符
			CRect rcText;
			GetClientRect(&rcText);

			// 设置环境
			dcMem.SetBkMode(TRANSPARENT);
			dcMem.SelectObject(GetFont());

			// 绘画字符
			rcText.left += 4;
			dcMem.DrawText(strString, rcText, DT_VCENTER | DT_SINGLELINE);
		}

		// 绘画边框
		if (m_bDrawBorder)
		{
			if (bEnabled)
			{
				dcMem.Draw3dRect(0, 0, rcClient.Width(), rcClient.Height(), m_crEnableBorder, m_crEnableBorder);
			}
			else
			{

				dcMem.Draw3dRect(0, 0, rcClient.Width(), rcClient.Height(), m_crDisableBorder, m_crDisableBorder);
			}
		}
		else
		{
			dcMem.Draw3dRect(0, 0, rcClient.Width(), rcClient.Height(), m_crEnableBack, m_crEnableBack);
		}

		// 按钮背景
		if (bEnabled)
		{
			dcMem.FillSolidRect(rcClient.Width() - m_uButtonWidth - 1, rcClient.top + 1, m_uButtonWidth,rcClient.Height() - 2, m_crEnableBack);
		}
		else
		{
			dcMem.FillSolidRect(rcClient.Width() - m_uButtonWidth - 1, rcClient.top + 1, m_uButtonWidth,rcClient.Height() - 2, m_crDisableBack);
		}

		// 计算位置
		INT nImageIndex = 0;
		if (!bEnabled) nImageIndex = _nImageDisabled;
		else if (bPressed) nImageIndex = _nImagePushed;
		else if (bSelected) nImageIndex = _nImageFocusOrHover;

		// 绘画按钮
		if (m_ImageButton.IsValid())
		{
			CSize SizeButton;
			SizeButton.SetSize(m_ImageButton.GetWidth() / _nImageCount, m_ImageButton.GetHeight());
			INT nYPos = rcClient.top + (rcClient.Height() - SizeButton.cy ) / 2;
			m_ImageButton.DrawImage(&dcMem, rcClient.Width() - m_uButtonWidth - 1, nYPos, m_uButtonWidth, SizeButton.cy,
				nImageIndex * SizeButton.cx, 0, SizeButton.cx, SizeButton.cy);
		}
		else
		{
			CSize SizeButton;
			SizeButton.SetSize(m_ImageDefButton.GetWidth() / _nImageCount, m_ImageDefButton.GetHeight());
			INT nYPos = rcClient.top + (rcClient.Height() - SizeButton.cy ) / 2;
			m_ImageDefButton.DrawImage(&dcMem, rcClient.Width() - m_uButtonWidth - 1, nYPos, m_uButtonWidth, SizeButton.cy,
				nImageIndex * SizeButton.cx, 0, SizeButton.cx, SizeButton.cy);
		}
	}

	return;
}

// 绘画背景
BOOL CSkinComboBox::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

// 创建消息
int CSkinComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	// 获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	// 配置控件
	Initialization();
	RectifyControl(rcClient.Width(), rcClient.Height());

	return 0;
}

// 鼠标消息
void CSkinComboBox::OnMouseMove(UINT nFlags, CPoint Point)
{
	CRect rc;
	GetClientRect(&rc);

	BOOL bHot = rc.PtInRect(Point) /*&& !m_bFocused*/;
	SetHighlighted(bHot);

	__super::OnMouseMove(nFlags, Point);
}

LRESULT CSkinComboBox::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	Default();

	if (m_SkinComboBoxEdit.m_hWnd)
	{
		CPoint pt;
		GetCursorPos(&pt);

		CRect rcEdit;
		m_SkinComboBoxEdit.GetWindowRect(rcEdit);

		if (rcEdit.PtInRect(pt))
		{
			TRACKMOUSEEVENT tme = {sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_SkinComboBoxEdit.m_hWnd, HOVER_DEFAULT};
			_TrackMouseEvent(&tme);

			SetHighlighted(TRUE);
			return 0L;
		}
	}

	SetHighlighted(FALSE);

	return 0L;
}

void CSkinComboBox::OnKillFocus(CWnd* pNewWnd)
{
	__super::OnKillFocus(pNewWnd);

	if (pNewWnd != &m_SkinComboBoxEdit)
	{
		m_bFocused = FALSE;
		m_bHighlighted = FALSE;
		RedrawFocusedFrame();
	}
}

void CSkinComboBox::OnSetFocus(CWnd* pOldWnd)
{
	__super::OnSetFocus(pOldWnd);

	m_bFocused = TRUE;
	m_bHighlighted = TRUE;
	RedrawFocusedFrame();
}

void CSkinComboBox::OnCbnCloseup()
{
	RedrawFocusedFrame();

	return;
}