
#include "Stdafx.h"
#include "SkinEdit.h"

BEGIN_MESSAGE_MAP(CSkinEdit, CEdit)
	ON_WM_NCPAINT()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

// 构造函数
CSkinEdit::CSkinEdit()
{
	// 背景颜色
	m_crEnableBK = RGB(255,255,255);
	m_crDisableBK = RGB(125,125,125);

	// 字体颜色
	m_crEnableText = RGB(10,10,10);
	m_crDisableText = RGB(50,50,50);

	// 边框颜色
	m_crEnableBorder = RGB(76,162,225);
	m_crDisableBorder = GetSysColor(COLOR_WINDOW);

	// 创建画刷
	m_brEnable.DeleteObject();
	m_brDisable.DeleteObject();
	m_brEnable.CreateSolidBrush(m_crEnableBK);
	m_brDisable.CreateSolidBrush(m_crDisableBK);
}

// 析构函数
CSkinEdit::~CSkinEdit()
{
}

// 设置颜色
void CSkinEdit::SetEnableColor(COLORREF crEnableText, COLORREF crEnableBK, COLORREF crEnableBorder)
{
	// 设置颜色
	m_crEnableBK = crEnableBK;
	m_crEnableText = crEnableText;
	m_crEnableBorder = crEnableBorder;

	// 创建画刷
	m_brEnable.DeleteObject();
	m_brEnable.CreateSolidBrush(m_crEnableBK);

	// 更新界面
	if (m_hWnd != NULL)
	{
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}

	return;
}

// 设置颜色
void CSkinEdit::SetDisableColor(COLORREF crDisableText, COLORREF crDisableBK, COLORREF crDisableBorder)
{
	// 设置颜色
	m_crDisableBK = crDisableBK;
	m_crDisableText = crDisableText;
	m_crDisableBorder = crDisableBorder;

	// 创建画刷
	m_brDisable.DeleteObject();
	m_brDisable.CreateSolidBrush(m_crDisableBK);

	// 更新界面
	if (m_hWnd != NULL)
	{
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}

	return;
}

// 重画消息
void CSkinEdit::OnNcPaint()
{
	// 状态变量
	bool bDisable = (IsWindowEnabled() == FALSE);
	COLORREF crColorBK = (bDisable == false) ? m_crEnableBK : m_crDisableBK;
	COLORREF crColorBorder = (bDisable == false) ? m_crEnableBorder : m_crDisableBorder;

	// 绘画边框
	CClientDC ClientDC(this);

	// 获取位置
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	ScreenToClient(&rcWindow);

	// 绘画边框
	if (GetExStyle()&WS_EX_CLIENTEDGE)
	{
		ClientDC.Draw3dRect(&rcWindow, crColorBorder, crColorBorder);
		ClientDC.Draw3dRect(rcWindow.left+1, rcWindow.top+1, rcWindow.Width()-2, rcWindow.Height()-2, crColorBK, crColorBK);
	}
	else
	{
		ClientDC.Draw3dRect(&rcWindow, crColorBK, crColorBK);
		ClientDC.Draw3dRect(rcWindow.left+1, rcWindow.top+1, rcWindow.Width()-2, rcWindow.Height()-2, crColorBK, crColorBK);
	}

	return;
}

// 绘画控件
HBRUSH CSkinEdit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// 设置环境
	if (IsWindowEnabled() == FALSE)
	{
		// 禁用状态
		pDC->SetBkColor(m_crDisableBK);
		pDC->SetTextColor(m_crDisableText);
		return m_brDisable;
	}
	else
	{
		// 启用状态
		pDC->SetBkColor(m_crEnableBK);
		pDC->SetTextColor(m_crEnableText);
		return m_brEnable;
	}

	return NULL;
}
