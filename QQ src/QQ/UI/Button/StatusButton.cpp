#include "StdAfx.h"
#include "StatusButton.h"

CStatusButton::CStatusButton(HWND hWnd, UINT uControlID, CRect rc, CString strTitle/* = ""*/, BOOL bIsVisible/* = TRUE*/, 
						   BOOL bIsDisable/* = FALSE*/ ,BOOL bIsPressDown/* = FALSE*/)
: CControlBase(hWnd, uControlID, rc, strTitle, bIsVisible, bIsDisable)
{
	m_buttonState = bsNormal;
	m_pImage = NULL;
	m_pStatusImage = NULL;
}

CStatusButton::~CStatusButton(void)
{

}

bool CStatusButton::SetBitmap(UINT nResourceID)
{
	if(ImageFromIDResource(nResourceID, "PNG", m_pImage))
	{
		m_sizeImage.SetSize(m_pImage->GetWidth(), m_pImage->GetHeight());
		return true;
	}
	return false;
}

bool CStatusButton::SetBitmap(CString strImage)
{
	USES_CONVERSION; 
	m_pImage = Image::FromFile(A2W(strImage), TRUE);

	if(m_pImage->GetLastStatus() == Ok)
	{
		m_sizeImage.SetSize(m_pImage->GetWidth(), m_pImage->GetHeight());
		return true;
	}
	return false;
}

bool CStatusButton::SetStatusBitmap(UINT nResourceID)
{
	if(ImageFromIDResource(nResourceID, "PNG", m_pStatusImage))
	{
		m_sizeStatusImage.SetSize(m_pStatusImage->GetWidth(), m_pStatusImage->GetHeight());
		return true;
	}
	return false;
}

bool CStatusButton::SetStatusBitmap(CString strImage)
{
	USES_CONVERSION; 
	m_pStatusImage = Image::FromFile(A2W(strImage), TRUE);

	if(m_pStatusImage->GetLastStatus() == Ok)
	{
		m_sizeStatusImage.SetSize(m_pStatusImage->GetWidth(), m_pStatusImage->GetHeight());
		return true;
	}
	return false;
}

BOOL CStatusButton::OnMouseMove(UINT nFlags, CPoint point)
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

BOOL CStatusButton::OnLButtonDown(UINT nFlags, CPoint point)
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

BOOL CStatusButton::OnLButtonUp(UINT nFlags, CPoint point)
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

void CStatusButton::Draw(CDC &dc, CRect rcUpdate)
{
	BOOL bIsPressDown = false;
 	Graphics graphics(dc);
	CRect rc = m_rc;
 	if (m_buttonState == bsDown)
	{
		rc.left += 1;
		rc.top += 1;
		m_buttonState = bsDown;
	}


	if(m_buttonState == bsHover)
	{
		DrawRectangle(dc, m_rc, TRUE, 50, 90);
	}
	else if (m_buttonState == bsDown)
	{
		DrawRectangle(dc, m_rc, FALSE, 90, 50);
	}
	graphics.DrawImage(m_pImage, RectF(m_rc.right - m_sizeImage.cx - (m_sizeImage.cx) / 2, m_rc.top + (m_rc.Height() - m_sizeImage.cy + 1) / 2, m_sizeImage.cx, m_sizeImage.cy),
		0, 0, m_sizeImage.cx, m_sizeImage.cy, UnitPixel);

	graphics.DrawImage(m_pStatusImage, RectF(rc.left + (m_sizeStatusImage.cx + 1) / 2, rc.top + (m_rc.Height() - m_sizeStatusImage.cy + 1) / 2, m_sizeStatusImage.cx, m_sizeStatusImage.cy),
		0, 0, m_sizeStatusImage.cx, m_sizeStatusImage.cy, UnitPixel);

}