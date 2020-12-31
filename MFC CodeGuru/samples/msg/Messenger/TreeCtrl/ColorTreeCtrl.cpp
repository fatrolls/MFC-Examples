//=========================================================
//	TITLE:		Global 
//				for WinNT, MSVC 5.0, MFC 4.1
//				Copyright (C) Matrix Baltic Software
//				Vilnius, Lithuania
//	MODULE:		
//	PURPOSE:	
//
//	AUTHOR:		Audrius Vasiliauskas
// 
//	NOTES:		
//
//=========================================================

// ColorTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ColorTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorTreeItem

CColorTreeCtrl::CColorTreeItem::CColorTreeItem()
{
	pLogFont = NULL;
}

CColorTreeCtrl::CColorTreeItem::CColorTreeItem(const CColorTreeItem &x)
{
	pLogFont = NULL;
	*this = x;
}

CColorTreeCtrl::CColorTreeItem::~CColorTreeItem()
{
	RemoveFont();
}

void CColorTreeCtrl::CColorTreeItem::RemoveFont()
{
	if(pLogFont != NULL)
	{
		delete pLogFont;
	}
	pLogFont = NULL;
}

void CColorTreeCtrl::CColorTreeItem::SetFont(LOGFONT &logFont)
{
	RemoveFont();

	pLogFont = new LOGFONT;
	CopyMemory(pLogFont,&logFont,sizeof(*pLogFont));
}


CColorTreeCtrl::CColorTreeItem &CColorTreeCtrl::CColorTreeItem::operator = (const CColorTreeItem &x)
{
	if(this != &x)
	{
		Color = x.Color;
		ColorText = x.ColorText;
		Text = x.Text;

		if(x.pLogFont != NULL)
		{
			SetFont(*(x.pLogFont));
		}
		else
		{
			RemoveFont();
		}
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CColorTreeItemArray 

CColorTreeCtrl::CColorTreeItemArray::CColorTreeItemArray()
{
	Action = 0;
}


CColorTreeCtrl::CColorTreeItemArray &CColorTreeCtrl::CColorTreeItemArray::operator = (const CColorTreeItemArray &x)
{
	if(this != &x)
	{
		Action = x.Action;
		this->Copy(x);
	}

	return *this;
}

void CColorTreeCtrl::CColorTreeItemArray::DrawItem(CDC &cdc,CRect &crect,UINT nState,DWORD &dwWidth,BOOL isFocus)
{
	int i;
	CColorTreeItem cArray;
	CRect rc = crect;
	CRect area;
	UINT sFlag = TVIS_DROPHILITED | TVIS_SELECTED;

	CFont font;
	CFont *pOldFont;
	LOGFONT logFont;

	int bkMode;
	COLORREF rgbHighlight, rgbHighlightText;
	COLORREF rgbBkColor, rgbTextColor;

	rc.left += 2;
	area = rc;
	dwWidth = 0;
	rgbTextColor = cdc.SetTextColor(0);
	rgbBkColor = cdc.SetBkColor(0);

	for(i = 0;i < GetSize();i ++)
	{
		cArray = GetAt(i);
		if(cArray.Text.IsEmpty())
			continue;

		if(nState & sFlag)
		{
			rgbHighlightText = GetSysColor(COLOR_HIGHLIGHTTEXT);
			rgbHighlight = GetSysColor(COLOR_HIGHLIGHT);
		}
		else
		{
			if(cArray.ColorText != -1)
				rgbHighlightText = cArray.ColorText;
			else
				rgbHighlightText = 0;

			if(cArray.Color != -1)
				rgbHighlight = cArray.Color;
			else
				rgbHighlight = GetSysColor(COLOR_WINDOW);
		}

		cdc.SetTextColor(rgbHighlightText);
		cdc.SetBkColor(rgbHighlight);

		if(cArray.pLogFont != NULL)
		{
			CopyMemory(&logFont,cArray.pLogFont,sizeof(logFont));

			logFont.lfHeight = -(crect.Height() - 4);

			font.CreateFontIndirect(&logFont);
			pOldFont = cdc.SelectObject(&font);
		}

		cdc.DrawText(cArray.Text, &area,DT_VCENTER | DT_SINGLELINE | DT_CALCRECT);

		area.top = crect.top;
		area.bottom = crect.bottom;
		if(i == 0)
			area.left -= 2;
		if(i == GetUpperBound())
			area.right += 2;
		cdc.FillSolidRect(&area,rgbHighlight);

		bkMode = cdc.SetBkMode(TRANSPARENT);
		cdc.DrawText(cArray.Text, &rc,DT_VCENTER | DT_SINGLELINE);
		cdc.SetBkMode(bkMode);

		if(cArray.pLogFont != NULL)
		{
			cdc.SelectObject(pOldFont);
			font.DeleteObject();
		}

		dwWidth += area.Width(); 
		rc.left = area.right;
		area = rc;
	}

	cdc.SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
	cdc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

	if(isFocus && (nState & TVIS_SELECTED))
	{
		area = crect;
		area.right = area.left + dwWidth;
		cdc.DrawFocusRect(&area);
	}

	cdc.SetTextColor(rgbTextColor);
	cdc.SetBkColor(rgbBkColor);
}

CString CColorTreeCtrl::CColorTreeItemArray::GetText()
{
	int i;
	CString str;

	for(i = 0;i < GetSize();i ++)
	{
		str += GetAt(i).Text;
	}

	return str;
}


/////////////////////////////////////////////////////////////////////////////
// CColorTreeCtrl

CColorTreeCtrl::CColorTreeCtrl()
{
}

CColorTreeCtrl::~CColorTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CColorTreeCtrl, CCustomTreeCtrl)
	//{{AFX_MSG_MAP(CColorTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorTreeCtrl message handlers


// Overidables
BOOL CColorTreeCtrl::DrawItem(CTreeCursor &htreeitem,CDC &cdc,
								CRect &crect,UINT nState,DWORD &dwWidth)
{
	CColorTreeItemArray cArray;
	CRect	rc;

	if(m_TreeItem.Lookup(htreeitem,cArray))
	{
		cArray.DrawItem(cdc,crect,nState,dwWidth,GetFocus() == this);
		return TRUE;
	}
	else
	{
		CCustomTreeCtrl::DrawItem(htreeitem,cdc,crect,nState,dwWidth);
	}

	return FALSE;
}

void CColorTreeCtrl::RemoveText(CTreeCursor &cursor)
{
	m_TreeItem.RemoveKey(cursor);
}

int CColorTreeCtrl::AddText(CTreeCursor &cursor,LPCSTR str,COLORREF colorText,COLORREF color)
{
	int ret;
	CColorTreeItemArray cArray;
	CColorTreeItem cItem;

	cItem.Text = str;
	cItem.Color = color;
	cItem.ColorText = colorText;

	m_TreeItem.Lookup(cursor,cArray);
	ret = cArray.Add(cItem);
	m_TreeItem.SetAt(cursor,cArray);

	return ret;
}

BOOL CColorTreeCtrl::GetText(CTreeCursor &cursor,int index,CString &text)
{
	CColorTreeItemArray cArray;

	if(m_TreeItem.Lookup(cursor,cArray))
	{
		if(index >= 0 && index < cArray.GetSize())
		{
			text = cArray[index].Text;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CColorTreeCtrl::SetText(CTreeCursor &cursor,int index,LPCSTR text)
{
	CColorTreeItemArray cArray;

	if(m_TreeItem.Lookup(cursor,cArray))
	{
		if(index >= 0 && index < cArray.GetSize())
		{
			cArray[index].Text = text;
			m_TreeItem.SetAt(cursor,cArray);
			InvalidateRect(cursor);
			return TRUE;
		}
	}
	return FALSE;
}



BOOL CColorTreeCtrl::SetFont(CTreeCursor &cursor,int index,LOGFONT &logFont)
{
	CColorTreeItemArray cArray;

	if(m_TreeItem.Lookup(cursor,cArray))
	{
		if(index >= 0 && index < cArray.GetSize())
		{
			cArray[index].SetFont(logFont);
			m_TreeItem.SetAt(cursor,cArray);
			InvalidateRect(cursor);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CColorTreeCtrl::GetColor(CTreeCursor &cursor,int index,COLORREF &colorText,COLORREF &color)
{
	CColorTreeItemArray cArray;

	if(m_TreeItem.Lookup(cursor,cArray))
	{
		if(index >= 0 && index < cArray.GetSize())
		{
			colorText = cArray[index].ColorText;
			color = cArray[index].Color;
			m_TreeItem.SetAt(cursor,cArray);
			InvalidateRect(cursor);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CColorTreeCtrl::SetColor(CTreeCursor &cursor,int index,COLORREF colorText,COLORREF color)
{
	CColorTreeItemArray cArray;

	if(m_TreeItem.Lookup(cursor,cArray))
	{
		if(index >= 0 && index < cArray.GetSize())
		{
			cArray[index].ColorText = colorText;
			cArray[index].Color = color;
			m_TreeItem.SetAt(cursor,cArray);
			InvalidateRect(cursor);
			return TRUE;
		}
	}
	return FALSE;
}




BOOL CColorTreeCtrl::GetAction(CTreeCursor &cursor,long &action)
{
	CColorTreeItemArray cArray;

	if(m_TreeItem.Lookup(cursor,cArray))
	{
		action = cArray.Action;
		return TRUE;
	}

	return FALSE;
}

BOOL CColorTreeCtrl::SetAction(CTreeCursor &cursor,long action)
{
	CColorTreeItemArray cArray;

	if(m_TreeItem.Lookup(cursor,cArray))
	{
		cArray.Action = action;
		m_TreeItem.SetAt(cursor,cArray);
		return TRUE;
	}

	return FALSE;
}

void CColorTreeCtrl::InvalidateRect(CTreeCursor &cursor)
{
	CRect rc;

	cursor.GetRect(&rc,TRUE);
	CCustomTreeCtrl::InvalidateRect(&rc,FALSE);
}

CString CColorTreeCtrl::GetToolTips(CTreeCursor &cursor,UINT nFlags)
{
	CColorTreeItemArray cArray;

	if(m_TreeItem.Lookup(cursor,cArray))
	{
		return cArray.GetText();
	}
	return CCustomTreeCtrl::GetToolTips(cursor,nFlags);
}
