#include "StdAfx.h"
#include "ImageButton.h"

CImageButton::CImageButton(HWND hWnd, UINT uControlID, CRect rc, CString strTitle/* = ""*/, BOOL bIsVisible/* = TRUE*/, 
						   BOOL bIsDisable/* = FALSE*/ ,BOOL bIsPressDown/* = FALSE*/)
: CControlBase(hWnd, uControlID, rc, strTitle, bIsVisible, bIsDisable)
{
	m_buttonState = bsNormal;
	m_pImage = NULL;
}

CImageButton::~CImageButton(void)
{

}

bool CImageButton::SetBitmap(UINT nResourceID)
{
	if(ImageFromIDResource(nResourceID, "PNG", m_pImage))
	{
		m_sizeImage.SetSize(m_pImage->GetWidth() / 4, m_pImage->GetHeight());
		return true;
	}
	return false;
}

bool CImageButton::SetBitmap(CString strImage)
{
	USES_CONVERSION; 
	m_pImage = Image::FromFile(A2W(strImage), TRUE);

	if(m_pImage->GetLastStatus() == Ok)
	{
		m_sizeImage.SetSize(m_pImage->GetWidth() / 4, m_pImage->GetHeight());
		return true;
	}
	return false;
}

BOOL CImageButton::OnMouseMove(UINT nFlags, CPoint point)
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

BOOL CImageButton::OnLButtonDown(UINT nFlags, CPoint point)
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

BOOL CImageButton::OnLButtonUp(UINT nFlags, CPoint point)
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

void CImageButton::Draw(CDC &dc, CRect rcUpdate)
{
 	Graphics graphics(dc);
	CRect rc = m_rc;
	if (m_buttonState == bsDown)
	{
		rc.left += 2;
		rc.top += 2;
	}

 	graphics.DrawImage(m_pImage, RectF(m_rc.left, m_rc.top,  m_rc.Width(), m_rc.Height()),
		m_buttonState * m_sizeImage.cx, 0, m_sizeImage.cx, m_sizeImage.cy, UnitPixel);

}