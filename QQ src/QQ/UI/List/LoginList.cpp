#include "StdAfx.h"
#include "LoginList.h"

CLoginList::CLoginList(void)
{
	m_nHoverItem = -1;
	m_pHeadImage = NULL;
	m_pCloseImage = NULL;
	m_rcClose.SetRectEmpty();
	m_buttonState = bsNormal;
}

CLoginList::~CLoginList(void)
{
}

void CLoginList::SetHeadBitmap(UINT nResourceID)
{
	if(ImageFromIDResource(nResourceID, "PNG", m_pHeadImage))
	{
		m_sizeHeadImage.SetSize(m_pHeadImage->GetWidth() / 2, m_pHeadImage->GetHeight());
	}
}
void CLoginList::SetHeadBitmap(CString strImage)
{
	USES_CONVERSION; 
	m_pHeadImage = Image::FromFile(A2W(strImage), TRUE);

	if(	m_pHeadImage)
	{
		m_sizeHeadImage.SetSize(m_pHeadImage->GetWidth() / 2, m_pHeadImage->GetHeight());
	}
}

void CLoginList::SetDeleteBitmap(UINT nResourceID)
{
	if(ImageFromIDResource(nResourceID, "PNG", m_pCloseImage))
	{
		m_sizeCloseImage.SetSize(m_pCloseImage->GetWidth() / 4, m_pCloseImage->GetHeight());
	}
}

void CLoginList::SetDeleteBitmap(CString strImage)
{
	USES_CONVERSION; 
	m_pCloseImage = Image::FromFile(A2W(strImage), FALSE);

	if(	m_pCloseImage)
	{
		m_sizeCloseImage.SetSize(m_pHeadImage->GetWidth() / 4, m_pHeadImage->GetHeight());
	}
}

bool CLoginList::GetItemNumber(UINT nItem, CString &strNumber)
{
	ASSERT(nItem < m_vecItem.size());
	if (nItem >= m_vecItem.size())  return false;

	EditListItem &editListItem = m_vecItem.at(nItem);
	strNumber = editListItem.strNumber;

	return true;
}

bool CLoginList::GetItemName(UINT nItem, CString &strName)
{
	ASSERT(nItem < m_vecItem.size());
	if (nItem >= m_vecItem.size())  return false;

	EditListItem &editListItem = m_vecItem.at(nItem);
	strName = editListItem.strName;

	return true;
}

bool CLoginList::GetItemImage(UINT nItem, UINT &nResourceID, CString &strImageFile)
{
	ASSERT(nItem < m_vecItem.size());
	if (nItem >= m_vecItem.size())  return false;

	EditListItem &editListItem = m_vecItem.at(nItem);

	nResourceID = editListItem.nResourceID;
	strImageFile = editListItem.strImagrFile;

	return true;
}

bool CLoginList::DeleteItem(UINT nItem)
{
	ASSERT(nItem < m_vecItem.size());
	if (nItem >= m_vecItem.size())  return false;

	m_vecItem.erase(m_vecItem.begin() + m_nHoverItem);
	if(m_nHoverItem >= m_vecItem.size())
	{
		m_nHoverItem -= 1;
	}
	SetItemPoint();
	
	return true;
}

void CLoginList::DrawWindow(CDC &dc, CRect rcClient)
{
	int nItemCount =  m_vecItem.size();
	CFont *pOldFont = dc.SelectObject(&m_font);
	COLORREF clrOld = dc.SetTextColor(RGB(0, 20, 35));
	CRect rcItem, rcText;
	CSize sizeImage;

	for(int i = 0; i < nItemCount; i++)
	{
		EditListItem &editListItem = m_vecItem.at(i);
		rcItem = editListItem.rcItem;
		sizeImage = editListItem.sizeImage;

		// 名字帐号
 		if(i == m_nHoverItem)
 		{
 			dc.FillSolidRect(&rcItem, RGB(0, 147, 209));
 
 			dc.SetTextColor(RGB(0, 20, 35));
 			rcText.SetRect(rcItem.left + 47, rcItem.top + 6, rcItem.left + 160, rcItem.top + 24);
 			dc.DrawText(editListItem.strName, &rcText, DT_TOP | DT_LEFT | DT_SINGLELINE | DT_WORD_ELLIPSIS);
 
 			dc.SetTextColor(RGB(255, 255, 255));
 			rcText.OffsetRect(0, 21);
 			dc.DrawText(editListItem.strNumber, &rcText, DT_TOP | DT_LEFT | DT_SINGLELINE | DT_WORD_ELLIPSIS);
 		}
 		else
		{
			dc.SetTextColor(RGB(0, 20, 35));
			rcText.SetRect(rcItem.left + 47, rcItem.top, rcItem.left + 160, rcItem.bottom);
			dc.DrawText(editListItem.strNumber, &rcText, DT_VCENTER | DT_LEFT | DT_SINGLELINE | DT_WORD_ELLIPSIS);
		}
	}
	dc.SelectObject(pOldFont);
	dc.SetTextColor(clrOld);
}


void CLoginList::DrawWindowEx(CDC &dc, CRect rcClient)
{
	int nItemCount =  m_vecItem.size();
	CRect rcItem;
	CSize sizeImage;
	Graphics graphics(dc);

	for(int i = 0; i < nItemCount; i++)
	{
		EditListItem &editListItem = m_vecItem.at(i);
		rcItem = editListItem.rcItem;
		sizeImage = editListItem.sizeImage;

		// 名字帐号
		if(i == m_nHoverItem)
		{
			graphics.DrawImage(m_pCloseImage, RectF(m_rcClose.left, m_rcClose.top, m_rcClose.Width(), m_rcClose.Height()),
				m_buttonState * m_sizeCloseImage.cx, 0, m_sizeCloseImage.cx, m_sizeCloseImage.cy, UnitPixel); 
		}

		// 头像
		if(editListItem.pImage)
		{	
			CRect rcHead(rcItem.left + 1, rcItem.top + 2, rcItem.left + 1 + rcItem.Height() - 4, rcItem.top + 2 + rcItem.Height() - 4);
			graphics.DrawImage(editListItem.pImage, RectF(rcHead.left, rcHead.top, rcHead.Width(), rcHead.Height()),
				0, 0, editListItem.sizeImage.cx, editListItem.sizeImage.cy, UnitPixel);

			DrawImageFrame(graphics, m_pHeadImage, rcHead, i == m_nHoverItem ? m_sizeHeadImage.cx : 0, 0, m_sizeHeadImage.cx, m_sizeHeadImage.cy, 5);
		}
	}
}


void CLoginList::InitUI()
{
 	AddItem("ICE", "278162354", IDB_PNG_HEAD_106);
 	AddItem("是ICE", "278162354", IDB_PNG_HEAD_105);
 	AddItem("就是ICE", "278162354", IDB_PNG_HEAD_104);
 	AddItem("还是ICE", "278162354", IDB_PNG_HEAD_103);
 	AddItem("ICE没错", "278162354", IDB_PNG_HEAD_102);
	AddItem("冰", "278162354", IDB_PNG_HEAD_101);
	AddItem("Ice", "278162354@qq.com", IDB_PNG_HEAD_100);
	
}

int CLoginList::AddItem(CString strName, CString strNumber, int nResourceID, CString strImageFile)
{
	EditListItem editListItem;
	editListItem.strName = strName;
	editListItem.strNumber = strNumber;
	editListItem.strImagrFile = strImageFile;
	editListItem.nResourceID = nResourceID;
	editListItem.pImage = NULL;
	editListItem.sizeImage.SetSize(0 ,0);
 	if(!strImageFile.IsEmpty())
 	{
 		USES_CONVERSION; 
 		editListItem.pImage = Image::FromFile(A2W(strImageFile), TRUE);
 
 		if(	editListItem.pImage)
 		{
 			editListItem.sizeImage.SetSize(editListItem.pImage->GetWidth(), editListItem.pImage->GetHeight());
 		}
 	}
	if(editListItem.pImage == NULL || editListItem.pImage->GetLastStatus() != Ok)
	{
		if(ImageFromIDResource(editListItem.nResourceID, "PNG", editListItem.pImage))
		{
			editListItem.sizeImage.SetSize(editListItem.pImage->GetWidth(), editListItem.pImage->GetHeight());
		}
	}
	m_vecItem.push_back(editListItem);

	if(m_nHoverItem == -1)
	{
		m_nHoverItem = 0;
	}

	SetItemPoint();

	return m_vecItem.size();
}

void CLoginList::SetItemPoint()
{
	int nItemCount =  m_vecItem.size();
	int nHeight = 4;
	nHeight += 24 * nItemCount;
	if(0 == nItemCount) nHeight += 40;
	if(nItemCount >= 1) nHeight += 20;
	if(nItemCount >= 2) nHeight += 9;
	if(nItemCount >= 2) nHeight += 9;

	int nStratTop = 2;
	for (int i = 0; i < nItemCount; i++)
	{
		EditListItem &editListItem = m_vecItem.at(i);
		editListItem.rcItem.left = 2;
		editListItem.rcItem.right = 189;
		if(i - 1 == m_nHoverItem && m_nHoverItem != -1 || i + 1 == m_nHoverItem)
		{
			editListItem.rcItem.top = nStratTop;
			editListItem.rcItem.bottom = nStratTop + 33;
			nStratTop += 33;
		}
		else if( i == m_nHoverItem)
		{
			editListItem.rcItem.top = nStratTop;
			editListItem.rcItem.bottom = nStratTop + 44;
			nStratTop += 44;

			int nLeft = editListItem.rcItem.right - m_sizeCloseImage.cx - 7;
			int nTop = editListItem.rcItem.top + (44 - m_sizeCloseImage.cy) / 2 + 1;

			m_rcClose.SetRect(nLeft, nTop, nLeft + m_sizeCloseImage.cx, nTop + m_sizeCloseImage.cy);
		}
		else
		{
			editListItem.rcItem.top = nStratTop;
			editListItem.rcItem.bottom = nStratTop + 24;
			nStratTop += 24;
		}
	}
	
	SetWindowPos(NULL, 0, 0, 191, nHeight, SWP_NOMOVE);
}

bool CLoginList::OnMouseMove(CPoint point)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	bool bDraw = false;
	if(rcClient.PtInRect(point))
	{	
		int nHoverItem = m_nHoverItem;
		
		if(m_nHoverItem != -1)
		{
			EditListItem &editListItem = m_vecItem.at(m_nHoverItem);
			if(editListItem.rcItem.PtInRect(point))
			{
				if(m_rcClose.PtInRect(point))
				{
					bDraw = m_buttonState != bsHover;
					m_buttonState = bsHover;
				}
				else
				{
					bDraw = m_buttonState == bsHover;
					m_buttonState = bsNormal;
				}
			}
			else
			{
				nHoverItem = -1;			
				bDraw = true;
			}
		}

		if(m_nHoverItem != nHoverItem)
		{
			int nItemCount =  m_vecItem.size();
			for (int i = 0; i < nItemCount; i++)
			{
				EditListItem &editListItem = m_vecItem.at(i);
				if(editListItem.rcItem.PtInRect(point))
				{
					m_nHoverItem = i;
					bDraw = true;
					break;
				}
			}
			if(m_nHoverItem != -1)
			{
				SetItemPoint();
			}
			if(m_rcClose.PtInRect(point))
			{
				m_buttonState = bsHover;
			}
			else
			{
				m_buttonState = bsNormal;
			}
			bDraw = true;
		}
	}
	else
	{
		m_buttonState = bsNormal;
		bDraw = true;
	}
	
	return bDraw;
}

bool CLoginList::OnLButtonDown(CPoint point)
{
	if(m_buttonState == bsHover)
	{
		m_buttonState = bsDown;
		return true;
	}
	
	return false;
}

bool  CLoginList::OnLButtonUp(CPoint point)
{ 
	bool bDraw = false;
	if(m_buttonState == bsDown)
	{
		if(m_rcClose.PtInRect(point))
		{
			if(m_nHoverItem != -1)
			{
				SendMessage(m_uMessageID, DELETE_ITEM, m_nHoverItem);
				bDraw = true;
			}
		}	
		else
		{
			bDraw = m_buttonState != bsNormal;
			m_buttonState = bsNormal;
		}
	}
	else if(m_nHoverItem != -1)
	{
		EditListItem &editListItem = m_vecItem.at(m_nHoverItem);
		if(editListItem.rcItem.PtInRect(point))
		{
			SendMessage(m_uMessageID, SELECT_ITEM, m_nHoverItem);
		}
	}
	
	return bDraw;
}