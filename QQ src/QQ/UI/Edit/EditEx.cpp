#include "StdAfx.h"
#include "EditEx.h"

CEditEx::CEditEx(HWND hWnd, UINT uControlID, CRect rc, CString strTitle/* = ""*/, BOOL bPassWord/* = FALSE*/, BOOL bIsVisible/* = TRUE*/, 
						   BOOL bIsDisable/* = FALSE*/ ,BOOL bIsPressDown/* = FALSE*/)
						   : CControlBase(hWnd, uControlID, rc, strTitle, bIsVisible, bIsDisable)
{
	m_bDown = false;
	m_bDownTemp = false;
	m_buttonState = bsNormal;
	m_EditState = bsNormal;
	m_pImage = NULL;
	m_pSmallImage = NULL;
	m_pEdit = NULL;
	m_bPassWord = bPassWord;

	SetRect(rc);

	VERIFY(m_fontTemp.CreateFont(
		16,							// 字体的高度  
		0,							// 字体的宽度  
		0,							// 字体显示的角度
		0,							// 字体的角度
		FW_DONTCARE,				// 字体的磅数
		FALSE,						// 斜体字体
		FALSE,						// 带下划线的字体
		0,							// 带删除线的字体
		GB2312_CHARSET,				// 所需的字符集
		OUT_DEFAULT_PRECIS,			// 输出的精度
		CLIP_DEFAULT_PRECIS,		// 裁减的精度
		DEFAULT_QUALITY,			// 逻辑字体与输出设备的实际
		DEFAULT_PITCH | FF_SWISS,	// 字体间距和字体集
		"宋体"));					// 字体名称
}

CEditEx::~CEditEx(void)
{
	if (m_fontTemp.m_hObject)
	{
		m_fontTemp.DeleteObject();
	}
}

bool CEditEx::SetBitmap(UINT nResourceID)
{
	if(ImageFromIDResource(nResourceID, "PNG", m_pImage))
	{
		m_sizeImage.SetSize(m_pImage->GetWidth() / 2, m_pImage->GetHeight());
		return true;
	}
	return false;
}

bool CEditEx::SetBitmap(CString strImage)
{
	USES_CONVERSION; 
	m_pImage = Image::FromFile(A2W(strImage), TRUE);

	if(m_pImage->GetLastStatus() == Ok)
	{
		m_sizeImage.SetSize(m_pImage->GetWidth() / 2, m_pImage->GetHeight());
		return true;
	}
	return false;
}

bool CEditEx::SetSmallBitmap(UINT nResourceID)
{
	if(ImageFromIDResource(nResourceID, "PNG", m_pSmallImage))
	{
		m_sizeSmallImage.SetSize(m_pSmallImage->GetWidth() / 4, m_pSmallImage->GetHeight());
		return true;
	}
	return false;
}

bool CEditEx::SetSmallBitmap(CString strImage)
{
	USES_CONVERSION; 
	m_pSmallImage = Image::FromFile(A2W(strImage), TRUE);

	if(m_pImage->GetLastStatus() == Ok)
	{
		m_sizeSmallImage.SetSize(m_pSmallImage->GetWidth() / 4, m_pSmallImage->GetHeight());
		return true;
	}
	return false;
}

void  CEditEx::SetRect(CRect rc) 
{
	m_rc = rc;
	m_rcText = m_rc;
	m_rcText.top += 4;
	m_rcText.left += 6;
	m_rcText.bottom -= 4;
	m_rcText.right -= (3 + m_sizeSmallImage.cx);
}

BOOL CEditEx::IsDraw(CPoint point)
{
 	if(m_buttonState == bsDown)
 	{
 		return false;
 	}
	CRect  rc;
	rc.left = m_rc.right - m_sizeSmallImage.cx - 2;
	rc.top = m_rc.top + (m_rc.Height() - m_sizeSmallImage.cy) / 2;
	rc.right = rc.left + m_sizeSmallImage.cx;
	rc.bottom = rc.top + m_sizeSmallImage.cy;

	if(rc.PtInRect(point))
	{
		if(m_buttonState == bsNormal)
			return true;
	}
	else
	{
		if(m_buttonState != bsNormal)
			return true;
	}

	return false;
}

BOOL CEditEx::OnFocus(bool bFocus)
{
	enumButtonState buttonState = m_buttonState;
	enumButtonState editState = m_EditState;

	m_bDown = false;
	m_buttonState = bsNormal;
	m_EditState = bsNormal;
	HideEdit();

	bool bIsDraw = buttonState != m_buttonState || editState != m_EditState;
	if(bIsDraw)
	{
		::InvalidateRect(m_hWnd, &m_rc, true);
	}

	return bIsDraw;
}

BOOL CEditEx::OnMouseMove(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_buttonState;
	enumButtonState editState = m_EditState;
	if(!m_bIsDisable)
	{
		if(m_rc.PtInRect(point))
		{
			
			m_EditState = bsHover;
			if(m_buttonState != bsDown)
			{
				CRect  rc;
				rc.left = m_rc.right - m_sizeSmallImage.cx - 2;
				rc.top = m_rc.top + (m_rc.Height() - m_sizeSmallImage.cy) / 2;
				rc.right = rc.left + m_sizeSmallImage.cx;
				rc.bottom = rc.top + m_sizeSmallImage.cy;

				if(rc.PtInRect(point))
				{
					m_buttonState = bsHover;
				}
				else
				{
					//ShowEdit();
					m_buttonState = bsNormal;
				}
			}
		}
		else
		{
			if(m_buttonState != bsDown)
			{
				m_buttonState = bsNormal;
				m_EditState = bsNormal;
			}
		}
	}
	
	return buttonState != m_buttonState || editState != m_EditState;
}

BOOL CEditEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_buttonState;	
	enumButtonState editState = m_EditState;
	if(!m_bIsDisable)
	{
		if(m_rc.PtInRect(point))
		{
			CRect  rc;
			rc.left = m_rc.right - m_sizeSmallImage.cx - 2;
			rc.top = m_rc.top + (m_rc.Height() - m_sizeSmallImage.cy) / 2;
			rc.right = rc.left + m_sizeSmallImage.cx;
			rc.bottom = rc.top + m_sizeSmallImage.cy;

			if(rc.PtInRect(point))
			{
				m_bDown = !m_bDown;
				m_bDownTemp = true;
				if(m_bDown)
				{
					m_buttonState = bsDown;
				}
				else
				{				
					m_buttonState = bsHover;
				}				
				SendMessage(m_uID, BUTTOM, BUTTOM_DOWN);
				HideEdit();
			}
			else
			{
				if(m_bDown)
				{
					m_bDown = false;
					m_buttonState = bsHover;
				}
				ShowEdit();
				
				SendMessage(m_uID, EDIT, BUTTOM_DOWN);
			}		
		}
		else
		{
			m_buttonState = bsNormal;
			m_EditState = bsNormal;
		}
	}
	
	return buttonState != m_buttonState || editState != m_EditState;
}

BOOL CEditEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_buttonState;
	enumButtonState editState = m_EditState;
	if(!m_bIsDisable)
	{
		if(m_rc.PtInRect(point))
		{
			m_EditState = bsHover;

			CRect  rc;
			rc.left = m_rc.right - m_sizeSmallImage.cx - 2;
			rc.top = m_rc.top + (m_rc.Height() - m_sizeSmallImage.cy) / 2;
			rc.right = rc.left + m_sizeSmallImage.cx;
			rc.bottom = rc.top + m_sizeSmallImage.cy;

			if(rc.PtInRect(point))
			{				
				if(m_bDown)
				{
					m_buttonState = bsDown;
				}
				else
				{
					m_buttonState = bsHover;
				}	
				SendMessage(m_uID, BUTTOM, BUTTOM_UP);
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
				SendMessage(m_uID, EDIT, BUTTOM_UP);
			}			
		}
		else
		{
			if(!m_bDown)
			{
				m_buttonState = bsNormal;
				m_EditState = bsNormal;
			}
		}
	}
	
	m_bDownTemp = false;
	return buttonState != m_buttonState || editState != m_EditState;
}

void CEditEx::Draw(CDC &dc, CRect rcUpdate)
{
	Graphics graphics(dc);

	DrawImageFrame(graphics, m_pImage, m_rc, m_EditState * m_sizeImage.cx, 0, m_sizeImage.cx, m_sizeImage.cy, 4);

	if(m_pSmallImage)
	{
		CRect  rc;
		rc.left = m_rc.right - m_sizeSmallImage.cx - 2;
		rc.top = m_rc.top + (m_rc.Height() - m_sizeSmallImage.cy) / 2;
		rc.right = rc.left + m_sizeSmallImage.cx;
		rc.bottom = rc.top + m_sizeSmallImage.cy;
		
		graphics.DrawImage(m_pSmallImage, RectF(rc.left , rc.top, rc.Width(), rc.Height()),
			m_buttonState * m_sizeSmallImage.cx, 0, m_sizeSmallImage.cx, m_sizeSmallImage.cy, UnitPixel);
	}

	if(!m_strTitle.IsEmpty())
	{
		dc.SetBkMode(TRANSPARENT);
		COLORREF clrOld = dc.SetTextColor(RGB(0, 28, 48));
		CFont *pOldFont = dc.SelectObject(&m_fontTemp);
		dc.DrawText(m_strTitle, &m_rcText, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_WORD_ELLIPSIS);
		dc.SelectObject(pOldFont);
		dc.SetTextColor(clrOld);
	}

}

BOOL CEditEx::GetLButtonDown()
{
	return m_buttonState == bsDown;;
}

BOOL CEditEx::GetLButtonUp()
{
	return FALSE;
}

void CEditEx::ShowEdit()
{
 	if(NULL == m_pEdit)
 	{
		CRect rc;
		rc = m_rcText;
		rc.left--;
		rc.top += 2;
  		m_pEdit = new CEdit;
  		m_pEdit->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, rc, CWnd::FromHandle(m_hWnd),   1111 ); 
  		m_pEdit->SetFont(&m_fontTemp);
		m_pEdit->SetWindowText(m_strTitle);	
		if(m_bPassWord)
		{
			m_pEdit->SetPasswordChar('*');
		}
		m_pEdit->SetSel(0, -1);
		m_pEdit->SetFocus();
 	}
}

void CEditEx::HideEdit()
{
	if(m_pEdit)
	{
		m_pEdit->GetWindowText(m_strTitle);
		if(m_bPassWord)
		{
			int nlen = m_strTitle.GetLength();
			m_strTitle = "";
			for(int i = 0; i < nlen; i++)
			{
				m_strTitle += '*';
			}
		}
		delete m_pEdit;
		m_pEdit = NULL;
	}
	
}