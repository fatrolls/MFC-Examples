
#include "StdAfx.h"
#include "DUIControl.h"
#include "DUIManager.h"

CDUIControl::CDUIControl()
{
	m_bVisible = true;
	m_bEnabled = true;
	m_rcItem.SetRect(0, 0, 0, 0);
	m_clrBk = RGB(255, 255, 255);
	m_clrTextColor = RGB(0, 0, 0);
	m_uTextFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	m_uLayoutFormat = DT_LEFT | DT_TOP;
	m_pDUIManager = NULL;
	m_pFont = NULL;
}

CDUIControl::~CDUIControl()
{
}

// 控件名字 必须唯一
UINT CDUIControl::GetID() const
{
	return m_uID;
}

void CDUIControl::SetID(UINT uID)
{
	m_uID = uID;
}

void CDUIControl::SetName(LPCTSTR lpszName)
{
	if (m_pDUIManager && _tcscmp(lpszName, m_strName) != 0)
	{
		m_pDUIManager->ModifyNameHash(this, m_strName, lpszName);
	}
	m_strName = lpszName;
}

const CString& CDUIControl::GetName() const
{
	return m_strName;
}

// 类名 根据这个来分类控件 比如"Button" "CheckBox"等
LPCTSTR CDUIControl::GetClass() const
{
	return	TEXT("DUIControl");
}

void CDUIControl::SetManager(CDUIManager* pDUIManager)
{
	m_pDUIManager = pDUIManager;
}

// 文本相关
CString CDUIControl::GetText() const
{
	return m_strText;
}

void CDUIControl::SetText(LPCTSTR pszText, bool bReDraw)
{
	m_strText = pszText;
	if (bReDraw) UpdateControl();
}

void CDUIControl::SetTextColor(COLORREF crText, bool bReDraw)
{
	m_clrTextColor = crText;
	if (bReDraw) UpdateControl();
}

void CDUIControl::SetFont(CFont* Font)
{
	m_pFont = Font;
}

// DrawText的最后一个参数的格式
void CDUIControl::SetTextFormat(UINT uFormat, bool bReDraw)
{
	m_uTextFormat = uFormat;
	if (bReDraw) UpdateControl();
}

// 位置相关
CRect CDUIControl::GetPos() const
{
	CRect rcReal = m_rcItem;
	if (m_pDUIManager!= NULL)
	{
		if (m_uLayoutFormat & DT_RIGHT)
		{
			rcReal.left = m_pDUIManager->GetWndSize().cx - m_rcItem.Width() - m_rcItem.left;
			rcReal.right = m_pDUIManager->GetWndSize().cx - m_rcItem.left;
		}
		else if (m_uLayoutFormat & DT_CENTER)
		{
			rcReal.left = m_pDUIManager->GetWndSize().cx / 2 + m_rcItem.left;
			rcReal.right = rcReal.left + m_rcItem.Width();
		}

		if (m_uLayoutFormat & DT_BOTTOM)
		{
			rcReal.top = m_pDUIManager->GetWndSize().cy - m_rcItem.Height() - m_rcItem.top;
			rcReal.bottom = m_pDUIManager->GetWndSize().cy - m_rcItem.top;
		}
		else if (m_uLayoutFormat & DT_VCENTER)
		{
			rcReal.top = m_pDUIManager->GetWndSize().cy / 2 + m_rcItem.top;
			rcReal.bottom = rcReal.top + m_rcItem.Height();
		}
	}
	return rcReal;
}

void CDUIControl::SetPos(const CRect& rc, bool bReDraw)
{
	m_rcItem = rc;
	if (bReDraw) UpdateControl();
}

void CDUIControl::SetPos(int x, int y, int cx, int cy, bool bReDraw)
{
	m_rcItem.left = x;
	m_rcItem.top = y;
	m_rcItem.right = m_rcItem.left + cx;
	m_rcItem.bottom = m_rcItem.top + cy;
	if (bReDraw) UpdateControl();
}

int CDUIControl::GetWidth() const
{
	return m_rcItem.Width();
}

int CDUIControl::GetHeight() const
{
	return m_rcItem.Height();
}

int CDUIControl::GetX() const
{
	return GetPos().left;
}

int CDUIControl::GetY() const
{
	return GetPos().top;
}

void CDUIControl::SetLayoutAlign(UINT uLayoutFormat)
{
	m_uLayoutFormat = uLayoutFormat;
}

COLORREF CDUIControl::GetBkColor() const
{
	return m_clrBk;
}

void CDUIControl::SetBkColor(COLORREF crBk, bool bReDraw)
{
	m_clrBk = crBk;
	if (bReDraw) UpdateControl();
}

// 鼠标提示
CString CDUIControl::GetToolTip() const
{
	return m_strToolTip;
}

void CDUIControl::SetToolTip(LPCTSTR pszText)
{
	m_strToolTip = pszText;
}

// 一些重要的属性
bool CDUIControl::IsVisible() const
{
	return m_bVisible;
}

void CDUIControl::SetVisible(bool bVisible, bool bReDraw)
{
	m_bVisible = bVisible;
	if (bReDraw) UpdateControl();
}

bool CDUIControl::IsEnabled() const
{
	return m_bEnabled;
}

void CDUIControl::SetEnabled(bool bEnable, bool bReDraw)
{
	m_bEnabled = bEnable;
	if (bReDraw) UpdateControl();
}

void CDUIControl::SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("pos")) == 0)
	{
		CRect rcPos;
		LPTSTR lpstr = NULL;
		rcPos.left = _tcstol(lpszValue, &lpstr, 10); ASSERT(lpstr);
		rcPos.top = _tcstol(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		rcPos.right = rcPos.left + _tcstol(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		rcPos.bottom = rcPos.top + _tcstol(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		SetPos(rcPos);
	}
	else if (_tcscmp(lpszName, TEXT("textcolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		SetTextColor(RGB(r, g, b));
	}
	else if (_tcscmp(lpszName, TEXT("bkcolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		SetBkColor(RGB(r, g, b));
	}
	else if (_tcscmp(lpszName, TEXT("layoutalign")) == 0)
	{
		if ( _tcsstr(lpszValue, TEXT("center")) != NULL)
		{
			m_uLayoutFormat &= ~(DT_LEFT | DT_RIGHT);
			m_uLayoutFormat |= DT_CENTER;
		}
		if (_tcsstr(lpszValue, TEXT("left")) != NULL)
		{
			m_uLayoutFormat &= ~(DT_CENTER | DT_RIGHT);
			m_uLayoutFormat |= DT_LEFT;
		}
		if (_tcsstr(lpszValue, TEXT("right")) != NULL)
		{
			m_uLayoutFormat &= ~(DT_LEFT | DT_CENTER);
			m_uLayoutFormat |= DT_RIGHT;
		}
		if (_tcsstr(lpszValue, TEXT("top")) != NULL)
		{
			m_uLayoutFormat &= ~(DT_BOTTOM | DT_VCENTER);
			m_uLayoutFormat |= DT_TOP;
		}
		if (_tcsstr(lpszValue, TEXT("vcenter")) != NULL)
		{
			m_uLayoutFormat &= ~(DT_TOP | DT_BOTTOM);			
			m_uLayoutFormat |= DT_VCENTER;
		}
		if (_tcsstr(lpszValue, _T("bottom")) != NULL)
		{
			m_uLayoutFormat &= ~(DT_TOP | DT_VCENTER);
			m_uLayoutFormat |= DT_BOTTOM;
		}
	}
	else if (_tcscmp(lpszName, TEXT("align")) == 0)
	{
		if ( _tcsstr(lpszValue, TEXT("center")) != NULL)
		{
			m_uTextFormat &= ~(DT_LEFT | DT_RIGHT);
			m_uTextFormat |= DT_CENTER;
		}
		if (_tcsstr(lpszValue, TEXT("left")) != NULL)
		{
			m_uTextFormat &= ~(DT_CENTER | DT_RIGHT);
			m_uTextFormat |= DT_LEFT;
		}
		if (_tcsstr(lpszValue, TEXT("right")) != NULL)
		{
			m_uTextFormat &= ~(DT_LEFT | DT_CENTER);
			m_uTextFormat |= DT_RIGHT;
		}
		if (_tcsstr(lpszValue, TEXT("top")) != NULL)
		{
			m_uTextFormat &= ~(DT_BOTTOM | DT_VCENTER);
			m_uTextFormat |= DT_TOP;
		}
		if (_tcsstr(lpszValue, TEXT("vcenter")) != NULL)
		{
			m_uTextFormat &= ~(DT_TOP | DT_BOTTOM);			
			m_uTextFormat |= DT_VCENTER;
		}
		if (_tcsstr(lpszValue, _T("bottom")) != NULL)
		{
			m_uTextFormat &= ~(DT_TOP | DT_VCENTER);
			m_uTextFormat |= DT_BOTTOM;
		}
	}
	else if (_tcscmp(lpszName, TEXT("endellipsis")) == 0)
	{
		if (_tcscmp(lpszValue, TEXT("true")) == 0) m_uTextFormat |= DT_END_ELLIPSIS;
		else m_uTextFormat &= ~DT_END_ELLIPSIS;
	}    
	else if (_tcscmp(lpszName, TEXT("id")) == 0) SetID(_tcstoul(lpszValue, NULL, 10));
	else if( _tcscmp(lpszName, TEXT("name")) == 0) SetName(lpszValue);
	else if (_tcscmp(lpszName, TEXT("text")) == 0) SetText(lpszValue);
	else if (_tcscmp(lpszName, TEXT("tooltip")) == 0) SetToolTip(lpszValue);
	else if (_tcscmp(lpszName, TEXT("enabled")) == 0) SetEnabled(_tcscmp(lpszValue, TEXT("true")) == 0);
	else if (_tcscmp(lpszName, TEXT("visible")) == 0) SetVisible(_tcscmp(lpszValue, TEXT("true")) == 0);
}

// 绘画
void CDUIControl::DoPaint(CDC* pDC)
{
	// 绘制循序：背景颜色->背景图->状态图->文本
	PaintBkColor(pDC);
	PaintBkImage(pDC);
	PaintStatusImage(pDC);
	PaintText(pDC);
}

void CDUIControl::PaintBkColor(CDC* pDC)
{

}

void CDUIControl::PaintBkImage(CDC* pDC)
{

}

void CDUIControl::PaintStatusImage(CDC * pDC)
{

}

void CDUIControl::PaintText(CDC* pDC)
{

}

// 操作相关
bool CDUIControl::OnMouseMove(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	if (rcReal.PtInRect(point) == TRUE) return true;
	return false;
}

bool CDUIControl::OnMouseLeave()
{
	return false;
}

bool CDUIControl::OnLButtonDown(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	if (rcReal.PtInRect(point) == TRUE) return true;
	return false;
}

bool CDUIControl::OnLButtonUp(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	if (rcReal.PtInRect(point) == TRUE) return true;
	return false;
}

bool CDUIControl::OnRButtonDown(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	if (rcReal.PtInRect(point) == TRUE) return true;
	return false;
}

bool CDUIControl::OnRButtonUp(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	if (rcReal.PtInRect(point) == TRUE) return true;
	return false;
}

bool CDUIControl::OnMouseCursor(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	if (rcReal.PtInRect(point) == TRUE) return true;
	return false;
}

void CDUIControl::OnClick()
{

}

void CDUIControl::UpdateControl()
{
	if (m_pDUIManager == NULL) return;
	CWnd* pOwnerWnd = m_pDUIManager->GetOwnerWnd();
	if (pOwnerWnd == NULL || pOwnerWnd->GetSafeHwnd() == NULL) return;
	pOwnerWnd->InvalidateRect(GetPos());
}

void CDUIControl::UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("textcolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		SetTextColor(RGB(r, g, b));
	}
	else if (_tcscmp(lpszName, TEXT("bkcolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		SetBkColor(RGB(r, g, b));
	}
}

// 创建控件
bool CDUIControl::CreateControl(UINT uID, LPCTSTR lpszName, CDUIManager* pDUIManager, const CRect& rc, LPCTSTR pszText, bool bVisible)
{
	m_uID = uID;
	m_strName = lpszName;
	m_rcItem = rc;
	m_strText = pszText;
	m_bVisible = bVisible;
	m_pDUIManager = pDUIManager;

	return true;
}


