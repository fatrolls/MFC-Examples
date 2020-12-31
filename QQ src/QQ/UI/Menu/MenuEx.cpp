#include "StdAfx.h"
#include "MenuEx.h"

CMenuEx::CMenuEx(void)
{
	m_nHoverItem = -1;
}

CMenuEx::~CMenuEx(void)
{
}

void CMenuEx::DrawWindow(CDC &dc, CRect rcClient)
{
	int nItemCount =  m_vecItem.size();
	CFont *pOldFont = dc.SelectObject(&m_font);
	COLORREF clrOld = dc.SetTextColor(RGB(0, 20, 35));
	CRect rcItem, rcText;
	CSize sizeImage;

	for(int i = 0; i < nItemCount; i++)
	{
		MeunExItem &meunExItem = m_vecItem.at(i);
 		rcItem = meunExItem.rcItem;
 		sizeImage = meunExItem.sizeImage;
 
		if(meunExItem.bSeparator)
		{
			dc.FillSolidRect(&rcItem, RGB(183, 195, 204));
		}
		else
		{
 			// 菜单文字
  			if(i == m_nHoverItem)
  			{
				dc.SetTextColor(RGB(255, 255, 255));
  				dc.FillSolidRect(&rcItem, RGB(0, 147, 209));
				rcText.SetRect(rcItem.left + 35, rcItem.top, rcItem.left + 112, rcItem.bottom);
				dc.DrawText(meunExItem.strText, &rcText, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_WORD_ELLIPSIS);
				dc.SetTextColor(RGB(0, 20, 35));
  			}
  			else
 			{
 				rcText.SetRect(rcItem.left + 35, rcItem.top, rcItem.left + 112, rcItem.bottom);
 				dc.DrawText(meunExItem.strText, &rcText, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_WORD_ELLIPSIS);
 			}
		}
	}
	dc.SelectObject(pOldFont);
	dc.SetTextColor(clrOld);
}

void CMenuEx::DrawWindowEx(CDC &dc, CRect rcClient)
{
	int nItemCount =  m_vecItem.size();
	CRect rcItem;
	CSize sizeImage;
	Graphics graphics(dc);

	for(int i = 0; i < nItemCount; i++)
	{
		MeunExItem &meunExItem = m_vecItem.at(i);
		rcItem = meunExItem.rcItem;
		sizeImage = meunExItem.sizeImage;

		if(!meunExItem.bSeparator)
		{
			// 图标			
			if(meunExItem.pImage)
			{	
				int nLeft = rcItem.left + (25 - sizeImage.cx) / 2;
				int nTop =  rcItem.top + (rcItem.Height() - sizeImage.cy) / 2;;

				graphics.DrawImage(meunExItem.pImage, RectF(nLeft, nTop, sizeImage.cx, sizeImage.cy),
					0, 0, sizeImage.cx, sizeImage.cy, UnitPixel);
			}
		}
	}
}

void CMenuEx::InitUI()
{
	AddMenu("我在线上", IDB_PNG_IMONLINE, 1);
	AddMenu("Q我吧", IDB_PNG_QME, 2);
	AddSeparator();
	AddMenu("离开", IDB_PNG_AWAY, 3);
	AddMenu("忙碌", IDB_PNG_BUSY, 4);
	AddMenu("请勿打扰", IDB_PNG_MUTE, 5);
	AddSeparator();
	AddMenu("隐身", IDB_PNG_INVISIBLE, 6);
}

int  CMenuEx::AddMenu(CString strText, int nResourceID, UINT uMenuID)
{
	MeunExItem meunExItem;
	meunExItem.bSeparator = FALSE;
	meunExItem.strText = strText;
	meunExItem.uMenuID = uMenuID;
	meunExItem.pImage = NULL;
	if(ImageFromIDResource(nResourceID, "PNG", meunExItem.pImage))
	{
		meunExItem.sizeImage.SetSize(meunExItem.pImage->GetWidth(), meunExItem.pImage->GetHeight());
	}
	m_vecItem.push_back(meunExItem);

	SetItemPoint();

	return m_vecItem.size();
}

int CMenuEx::AddSeparator()
{
	MeunExItem meunExItem;
	meunExItem.bSeparator = TRUE;
	meunExItem.strText = "";
	meunExItem.uMenuID = 0;
	meunExItem.pImage = NULL;
	meunExItem.sizeImage.SetSize(0, 0);
	m_vecItem.push_back(meunExItem);

	SetItemPoint();

	return m_vecItem.size();
}

void CMenuEx::SetItemPoint()
{
	int nItemCount =  m_vecItem.size();
	int nHeight = 0;

	int nStratTop = 6;
	for (int i = 0; i < nItemCount; i++)
	{
		MeunExItem &meunExItem = m_vecItem.at(i);
		
		if(meunExItem.bSeparator)
		{
			meunExItem.rcItem.SetRect(32, nStratTop + 2, 110, nStratTop + 3);
			nStratTop += 4;
		}
		else
		{
			meunExItem.rcItem.SetRect(6, nStratTop, 110, nStratTop + 22);
			nStratTop += 22;
		}
	}
	nHeight = nStratTop + 6;
	
	SetWindowPos(NULL, 0, 0, 116, nHeight, SWP_NOMOVE);
}

bool CMenuEx::OnMouseMove(CPoint point)
{
	bool bDraw = false;

	if(m_nHoverItem != -1)
	{
		MeunExItem &meunExItem = m_vecItem.at(m_nHoverItem);
		if(meunExItem.rcItem.PtInRect(point))
		{
			return false;
		}
		else
		{
			bDraw = true;
			m_nHoverItem = -1;
		}
	}
	
	int nItemCount =  m_vecItem.size();
	for (int i = 0; i < nItemCount; i++)
	{
		MeunExItem &meunExItem = m_vecItem.at(i);
		if(!meunExItem.bSeparator)
		{
			if(meunExItem.rcItem.PtInRect(point))
			{
				bDraw = true;
				m_nHoverItem = i;
				return true;
			}
		}
	}
	
	return bDraw;
}

bool CMenuEx::OnLButtonDown(CPoint point)
{
	return false;
}

bool CMenuEx::OnLButtonUp(CPoint point)
{ 
	bool bDraw = false;
 	if(m_nHoverItem != -1)
	{
		MeunExItem &meunExItem = m_vecItem.at(m_nHoverItem);
		if(meunExItem.rcItem.PtInRect(point))
		{
			SendMessage(m_uMessageID, 0, meunExItem.uMenuID);
		}
		else
		{
			m_nHoverItem = -1;
			bDraw = true;
		}
	}		

	return bDraw;
}