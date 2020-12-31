#include "StdAfx.h"
#include "CheckButton.h"

CCheckButton::CCheckButton(HWND hWnd, UINT uControlID, CRect rc, CString strTitle/* = ""*/, BOOL bIsVisible/* = TRUE*/, 
						   BOOL bIsDisable/* = FALSE*/ ,BOOL bIsPressDown/* = FALSE*/)
						   : CControlBase(hWnd, uControlID, rc, strTitle, bIsVisible, bIsDisable)
{
	m_buttonState = bsNormal;
	m_pImage = NULL;
	m_bDown = false;
	m_bDownTemp = false;
}

CCheckButton::~CCheckButton(void)
{

}

bool CCheckButton::SetBitmap(UINT nResourceID)
{
	if(ImageFromIDResource(nResourceID, "PNG", m_pImage))
	{
		m_sizeImage.SetSize(m_pImage->GetWidth() / 6, m_pImage->GetHeight());
		return true;
	}
	return false;
}

bool CCheckButton::SetBitmap(CString strImage)
{
	USES_CONVERSION; 
	m_pImage = Image::FromFile(A2W(strImage), TRUE);

	if(m_pImage->GetLastStatus() == Ok)
	{
		m_sizeImage.SetSize(m_pImage->GetWidth() / 6, m_pImage->GetHeight());
		return true;
	}
	return false;
}

bool CCheckButton::GetCheck()
{
	return m_bDown;
}

bool CCheckButton::SetCheck(bool bCheck)
{
	if (m_bIsDisable)
	{
		return m_bDown;
	}

	bool bDown = m_bDown;
	m_bDown = bCheck;
	if(m_bDown)
	{
		m_buttonState = bsDown;
	}
	else
	{
		 m_buttonState = bsNormal;
	}
	if(m_bDown != bDown)
	{
		::InvalidateRect(m_hWnd, &m_rc, true);
	}
	return m_bDown;
}

BOOL CCheckButton::OnMouseMove(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_buttonState;
	if (!m_bIsDisable && !m_bDownTemp)
	{
		if(m_rc.PtInRect(point))
		{
			if(m_bDown)
			{
				m_buttonState = bsHoverDown;
			}
			else
			{
				m_buttonState = bsHover;
			}
		}
		else
		{
			if(m_bDown)
			{
				m_buttonState = bsDown;
			}
			else
			{
				m_buttonState = bsNormal;
			}
		}
	}
	return buttonState != m_buttonState;
}

BOOL CCheckButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_buttonState;
	if (!m_bIsDisable)
	{
		if(m_rc.PtInRect(point))
		{
			m_bDownTemp = true;
			if(m_bDown)
			{
				m_buttonState = bsHoverDown;
			}
			else
			{
				m_buttonState = bsHover;
			}

		}
	}
	return buttonState != m_buttonState;
}

BOOL CCheckButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	enumButtonState buttonState = m_buttonState;
	if (!m_bIsDisable)
	{
		if(m_rc.PtInRect(point))
		{
			if(m_bDownTemp)
			{
				m_bDown = !m_bDown;
				SendMessage(m_uID, 0, BUTTOM_UP);
			}
			if(m_bDown)
			{
				m_buttonState = bsHoverDown;
			}
			else
			{
				m_buttonState = bsHover;
			}			
		}
		else
		{
			if(m_bDown)
			{
				m_buttonState = bsDown;
			}
			else
			{
				m_buttonState = bsNormal;
			}			
		}
	}
	m_bDownTemp = false;
	return buttonState != m_buttonState;
}

void CCheckButton::Draw(CDC &dc, CRect rcUpdate)
{
	Graphics graphics(dc);	

	graphics.DrawImage(m_pImage, RectF(m_rc.left, m_rc.top,   m_sizeImage.cx, m_sizeImage.cy),
		m_buttonState * m_sizeImage.cx, 0, m_sizeImage.cx, m_sizeImage.cy, UnitPixel);

	if(!m_strTitle.IsEmpty())
	{
		CRect rc = m_rc;
		rc.left += m_sizeImage.cx + 3;
		dc.SetBkMode(TRANSPARENT);
		COLORREF clrOld = dc.SetTextColor(RGB(0, 28, 48));
		CFont *pOldFont = dc.SelectObject(&m_font);
		dc.DrawText(m_strTitle, &rc, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_WORD_ELLIPSIS);
		dc.SelectObject(pOldFont);
		dc.SetTextColor(clrOld);
	}

}