#include "StdAfx.h"
#include "ButtonEx.h"

CButtonEx::CButtonEx(HWND hWnd, UINT uControlID, CRect rc, CString strTitle/* = ""*/, BOOL bIsVisible/* = TRUE*/, 
						   BOOL bIsDisable/* = FALSE*/ ,BOOL bIsPressDown/* = FALSE*/)
						   : CControlBase(hWnd, uControlID, rc, strTitle, bIsVisible, bIsDisable)
{
	m_buttonState = bsNormal;
	m_pImage = NULL;
	m_pSmallImage = NULL;
}

CButtonEx::~CButtonEx(void)
{

}

bool CButtonEx::SetBitmap(UINT nResourceID)
{
	if(ImageFromIDResource(nResourceID, "PNG", m_pImage))
	{
		m_sizeImage.SetSize(m_pImage->GetWidth() / 4, m_pImage->GetHeight());
		return true;
	}
	return false;
}

bool CButtonEx::SetBitmap(CString strImage)
{
	USES_CONVERSION; 
	m_pImage = Image::FromFile(A2W(strImage), TRUE);

	if(	m_pImage->GetLastStatus() == Ok)
	{
		m_sizeImage.SetSize(m_pImage->GetWidth() / 4, m_pImage->GetHeight());
		return true;
	}
	return false;
}

bool CButtonEx::SetSmallBitmap(UINT nResourceID)
{
	if(ImageFromIDResource(nResourceID, "PNG", m_pSmallImage))
	{
		m_sizeSmallImage.SetSize(m_pSmallImage->GetWidth(), m_pSmallImage->GetHeight());
		return true;
	}
	return false;
}

bool CButtonEx::SetSmallBitmap(CString strImage)
{
	USES_CONVERSION; 
	m_pSmallImage = Image::FromFile(A2W(strImage), TRUE);

	if(	m_pSmallImage->GetLastStatus() == Ok)
	{
		m_sizeSmallImage.SetSize(m_pSmallImage->GetWidth(), m_pSmallImage->GetHeight());
		return true;
	}
	return false;
}

BOOL CButtonEx::OnMouseMove(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_buttonState;
	if (!m_bIsDisable && m_buttonState != bsDown)
	{
		if(m_rc.PtInRect(point))
		{
			m_buttonState = bsHover;
		}
		else
		{
			m_buttonState = bsNormal;
		}
	}
	return buttonState != m_buttonState;
}

BOOL CButtonEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_buttonState;
	if (!m_bIsDisable)
	{
		if(m_rc.PtInRect(point))
		{
			m_buttonState = bsDown;
			SendMessage(m_uID, 0, BUTTOM_DOWN);
		}
	}
	return buttonState != m_buttonState;
}

BOOL CButtonEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_buttonState;
	if (!m_bIsDisable)
	{
		if(m_rc.PtInRect(point))
		{
			m_buttonState = bsHover;
			SendMessage(m_uID, 0, BUTTOM_UP);
		}
		else
		{
			m_buttonState = bsNormal;
		}
	}
	return buttonState != m_buttonState;
}

void CButtonEx::Draw(CDC &dc, CRect rcUpdate)
{
	Graphics graphics(dc);
	CRect rc = m_rc;
	if (m_buttonState == bsDown)
	{
		rc.left += 2;
		rc.top += 2;
	}

	DrawImageFrame(graphics, m_pImage, m_rc, m_buttonState * m_sizeImage.cx, 0, m_sizeImage.cx, m_sizeImage.cy, 4);

	if(m_pSmallImage)
	{
		graphics.DrawImage(m_pSmallImage, RectF(rc.left + 8, rc.top + (rc.Height() - m_sizeSmallImage.cy) / 2,  m_sizeSmallImage.cx, m_sizeSmallImage.cy),
			0, 0, m_sizeSmallImage.cx, m_sizeSmallImage.cy, UnitPixel);

		rc.left += m_sizeSmallImage.cx + 8;
	}


 	dc.SetBkMode(TRANSPARENT);
	COLORREF clrOld = dc.SetTextColor(RGB(0, 28, 48));
 	CFont *pOldFont = dc.SelectObject(&m_font);
 	dc.DrawText(m_strTitle, &rc, DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
 	dc.SelectObject(pOldFont);
	dc.SetTextColor(clrOld);

}