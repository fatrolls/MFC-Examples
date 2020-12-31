#include "StdAfx.h"
#include "LinkButton.h"

CLinkButton::CLinkButton(HWND hWnd, UINT uControlID, CRect rc, CString strTitle, CString strLink,
									COLORREF clrTextNormal ,COLORREF clrTextHover, COLORREF clrTextDown ,COLORREF clrTextDisable,
									BOOL bIsVisible, BOOL bIsDisable)
									: CControlBase(hWnd, uControlID, rc, strTitle, bIsVisible, bIsDisable)
{
	m_buttonState = bsNormal;
	m_clrTextNormal = clrTextNormal;
	m_clrTextHover = clrTextHover;
	m_clrTextDown = clrTextDown;
	m_clrTextDisable = clrTextDisable;
	m_strLink = strLink;
	m_bDown = FALSE;

	SetTitleText(strTitle);
}

CLinkButton::~CLinkButton(void)
{

}

void CLinkButton::SetTitleText(CString strTitle)
{
	m_strTitle = strTitle;
	CDC dc;
	dc.Attach(::GetDC(this->m_hWnd));

	CFont *pOldFont = dc.SelectObject(&m_font);
 	CSize sizeText = dc.GetTextExtent(strTitle);
 	
	m_rcText = m_rc;
	m_rcText.right = m_rcText.left + sizeText.cx;
	m_rcText.bottom = m_rcText.top + sizeText.cy;

	m_rc.right = m_rc.left + __min(m_rc.Width(), sizeText.cx);
	m_rc.bottom = m_rc.top + 1 + __min(m_rc.Height(), sizeText.cy);

	dc.SelectObject(pOldFont);

	dc.Detach();
}

BOOL CLinkButton::OnMouseMove(UINT nFlags, CPoint point)
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

BOOL CLinkButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_buttonState;
	if (!m_bIsDisable)
	{
		if(m_rc.PtInRect(point))
		{
			m_buttonState = bsDown;
		}
	}
	return buttonState != m_buttonState;
}

BOOL CLinkButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_buttonState;
	if (!m_bIsDisable)
	{
		if(m_rc.PtInRect(point))
		{
			if(m_buttonState == bsDown)
			{
				ShellExecute(NULL, "open", m_strLink, NULL,NULL,SW_SHOWMAXIMIZED); 
			}
			m_buttonState = bsHover;			
		}
		else
		{
			m_buttonState = bsNormal;
		}
	}
	return buttonState != m_buttonState;
}

void CLinkButton::Draw(CDC &dc, CRect rcUpdate)
{
	COLORREF clrText = m_clrTextNormal;
	if (m_buttonState == bsDisable)
	{
		clrText = m_clrTextDisable;
	}
	else if (m_buttonState == bsDown)
	{
		clrText = m_clrTextDown;
	}
	else if(m_buttonState == bsHover)
	{
		clrText = m_clrTextHover;
	}

 	dc.SetBkMode(TRANSPARENT);
	CFont *pOldFont = dc.SelectObject(&m_font);

	COLORREF clrOld = dc.SetTextColor(clrText);
	dc.DrawText(m_strTitle, &m_rc, DT_TOP| DT_LEFT | DT_SINGLELINE | DT_WORD_ELLIPSIS);

	// ÏÂ»®Ïß
	if((m_buttonState == bsHover || m_buttonState == bsDown ) && m_rcText.bottom <= m_rc.bottom)
	{
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, clrText);
		CPen *pOldPen = dc.SelectObject(&pen); 	
		dc.MoveTo(m_rcText.left, m_rcText.bottom);
		dc.LineTo(m_rcText.right, m_rcText.bottom);
		dc.SelectObject(pOldPen);
		pen.DeleteObject();
	}

 	dc.SelectObject(pOldFont);
	dc.SetTextColor(clrOld);
}