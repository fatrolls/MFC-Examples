#include "StdAfx.h"
#include "PhotoFrame.h"

CPhotoFrame::CPhotoFrame(HWND hWnd, UINT uControlID, CRect rc, CString strTitle/* = ""*/, BOOL bIsVisible/* = TRUE*/, 
					 BOOL bIsDisable/* = FALSE*/ ,BOOL  bRresponse /* = FALSE*/)
					 : CControlBase(hWnd, uControlID, rc, strTitle, bIsVisible, bIsDisable, bRresponse)
{
	m_state = pfNormal;
	m_pImage = NULL;
	m_pFrameImage = NULL;
}

CPhotoFrame::~CPhotoFrame(void)
{

}

bool CPhotoFrame::SetImageBitmap(UINT nResourceID)
{
	if(ImageFromIDResource(nResourceID, "PNG", m_pImage))
	{
		m_sizeImage.SetSize(m_pImage->GetWidth(), m_pImage->GetHeight());
		return true;
	}
	return false;
}

bool CPhotoFrame::SetImageBitmap(CString strImage)
{
	USES_CONVERSION; 
	m_pImage = Image::FromFile(A2W(strImage), TRUE);

	if(	m_pImage->GetLastStatus() == Ok)
	{
		m_sizeImage.SetSize(m_pImage->GetWidth(), m_pImage->GetHeight());
		return true;
	}
	return false;
}

bool CPhotoFrame::SetFrameBitmap(UINT nResourceID)
{
	if(ImageFromIDResource(nResourceID, "PNG", m_pFrameImage))
	{
		m_sizeFrameImage.SetSize(m_pFrameImage->GetWidth(), m_pFrameImage->GetHeight());
		return true;
	}
	return false;
}

bool CPhotoFrame::SetFrameBitmap(CString strImage)
{
	USES_CONVERSION; 
	m_pFrameImage = Image::FromFile(A2W(strImage), TRUE);

	if(	m_pFrameImage->GetLastStatus() == Ok)
	{
		m_sizeFrameImage.SetSize(m_pFrameImage->GetWidth(), m_pFrameImage->GetHeight());
		return true;
	}
	return false;
}

void CPhotoFrame::Draw(CDC &dc, CRect rcUpdate)
{
	CRect rc = m_rc;
	if (m_state == pfDown)
	{
		rc.left += 2;
		rc.top += 2;
		m_state = pfDown;
	}
	
	Graphics graphics(dc);
	graphics.DrawImage(m_pImage, RectF(m_rc.left + 1, m_rc.top + 1, m_rc.Width() - 2, m_rc.Height() - 2),
		0, 0, m_sizeImage.cx, m_sizeImage.cy, UnitPixel);

	if(m_pFrameImage && m_pImage)
	{
		DrawImageFrame(graphics, m_pFrameImage, m_rc, 0, 0, m_sizeFrameImage.cx, m_sizeFrameImage.cy, 4);
	}
}