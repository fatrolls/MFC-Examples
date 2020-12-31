// MyListCtrl1.cpp : implementation file
//

#include "stdafx.h"
#include "QuickList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuickList

//Constructor
CQuickList::CListItemData::CListItemData()
{
	Reset();
}

//Get which item/row
int CQuickList::CListItemData::GetItem() const
{
	return m_item;
}

//Get which subitem/column
int CQuickList::CListItemData::GetSubItem() const
{
	return m_subitem;
}

//Is item selected?
bool CQuickList::CListItemData::IsSelected() const
{
	return m_isSelected;
}

//Is item hot?
bool CQuickList::CListItemData::IsHot() const
{
	return m_isHot;
}

//Reset settings.
void CQuickList::CListItemData::Reset()
{
	m_text.Empty();
	m_item = m_subitem = 0;
	m_isSelected = false;
	m_isHot = false;
	m_noSelection = false;

#ifndef QUICKLIST_NOEDIT
	m_allowEdit = false;
#endif
	
#ifndef QUICKLIST_NOTEXTSTYLE 
	m_textStyle.m_textPosition = DT_VCENTER | DT_SINGLELINE | DT_LEFT | DT_END_ELLIPSIS;
	m_textStyle.m_bold = false;
	m_textStyle.m_italic = false;
#endif

#ifndef QUICKLIST_NOIMAGE
	m_image.m_imageID = -1;
	m_image.m_imageList = NULL;
	m_image.m_noSelection = true;
	m_image.m_center = false;
	m_image.m_blend = ILD_BLEND50;
#endif

#ifndef QUICKLIST_NOBUTTON
	m_button.m_draw = false;
	m_button.m_style = DFCS_BUTTONCHECK;
	m_button.m_noSelection=true;
	m_button.m_center=false;
#endif

#ifndef QUICKLIST_NOCOLORS
	m_colors.m_backColor =
	m_colors.m_selectedBackColor =
	m_colors.m_selectedTextColor =
	m_colors.m_selectedBackColorNoFocus = 
	m_colors.m_hotTextColor = 
	m_colors.m_textColor = DEFAULTCOLOR;

	#ifndef QUICKLIST_NONAVIGATION
		m_colors.m_navigatedTextColor =
		m_colors.m_navigatedBackColor = DEFAULTCOLOR;
	#endif
#endif

#ifndef QUICKLIST_NOPROGRESSBAR
	m_progressBar.m_maxvalue = -1;
	m_progressBar.m_value = 0;
	m_progressBar.m_fillTextColor = 
	m_progressBar.m_fillColor = DEFAULTCOLOR;
	m_progressBar.m_edge = EDGE_SUNKEN;
#endif
}

//Constructor
CQuickList::CQuickList()
{
#ifndef QUICKLIST_NOKEYFIND
	#ifndef QUICKLIST_NONAVIGATION
		m_keyFindColumn = KEYFIND_CURRENTCOLUMN;
	#else
		m_keyFindColumn = 0;
	#endif
#endif

#ifndef QUICKLIST_NONAVIGATION
	m_enableNavigation=true;
	m_navigationColumn=0;
#endif

#ifndef QUICKLIST_NOEDIT
	m_edit = NULL;

	m_editOnEnter =
	m_editOnF2 = 
	m_editOnDblclk = true;

	m_editOnWriting = false;

	m_editEndOnLostFocus = true;

	m_editLastEndKey = 0;
#endif
	m_lastget = new CListItemData;

#ifndef QUICKLIST_NOXPTHEME
	m_theme = NULL;
#endif
}

//Destructor
CQuickList::~CQuickList()
{
	delete m_lastget;
}


BEGIN_MESSAGE_MAP(CQuickList, CListCtrl)
	//{{AFX_MSG_MAP(CQuickList)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP

	ON_NOTIFY_REFLECT(LVN_HOTTRACK, OnLvnHotTrack) 
	ON_NOTIFY_REFLECT_EX(NM_CLICK, OnClickEx)
	ON_NOTIFY_REFLECT_EX(NM_DBLCLK, OnDblClickEx)

	#ifndef QUICKLIST_NOKEYFIND
		ON_NOTIFY_REFLECT_EX(LVN_ODFINDITEM, OnOdfinditem)
	#endif

#ifndef QUICKLIST_NOTOOLTIP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
#endif

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuickList message handlers

//Edit when user start to write
void CQuickList::SetEditOnWriting(const bool edit)
{
#ifndef QUICKLIST_NOEDIT
	m_editOnWriting = edit;
#else
	UNREFERENCED_PARAMETER(edit);
#endif
}

//Edit when enter is pressed
void CQuickList::SetEditOnEnter(const bool edit)
{
#ifndef QUICKLIST_NOEDIT
	m_editOnEnter = edit;
#else
	UNREFERENCED_PARAMETER(edit);
#endif
}

//Edit when F2 is pressed
void CQuickList::SetEditOnF2(const bool edit)
{
#ifndef QUICKLIST_NOEDIT
	m_editOnF2 = edit;
#else
	UNREFERENCED_PARAMETER(edit);
#endif

}

//Edit when double click
void CQuickList::SetEditOnDblclk(const bool edit)
{
#ifndef QUICKLIST_NOEDIT
	m_editOnDblclk = edit;
#else
	UNREFERENCED_PARAMETER(edit);
#endif
}

//End edit when edit box losing focus
void CQuickList::SetEndEditOnLostFocus(bool autoend)
{
#ifndef QUICKLIST_NOEDIT
	m_editEndOnLostFocus = autoend;

	if(m_edit != NULL)
		m_edit->SetEndOnLostFocus(m_editEndOnLostFocus);
#else
	UNREFERENCED_PARAMETER(autoend);
#endif
}

#ifndef QUICKLIST_NOXPTHEME
//Set which theme manager to use
void CQuickList::SetThemeManager(CTheme* theme)
{
	m_theme = theme;
}
#endif

//Edit when edit box is losing focus?
bool CQuickList::GetEndEditOnLostFocus() const
{
#ifndef QUICKLIST_NOEDIT
	return m_editEndOnLostFocus;
#else
	return false;
#endif
}

//Return which key was pressed when edit box was closed
//0, VK_RETURN or VK_ESACPE
UINT CQuickList::GetLastEndEditKey() const
{
#ifndef QUICKLIST_NOEDIT
	return m_editLastEndKey;
#else
	return 0;
#endif
}

//Get current edit box
CEdit* CQuickList::GetEditBox() const
{
#ifndef QUICKLIST_NOEDIT
	return m_edit;
#else
	return NULL;
#endif
}

//Custom draw
void CQuickList::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{	
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	
  //  *pResult = 0;	return;

    // If this is the beginning of the control's paint cycle, request
    // notifications for each item.
	
    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
        *pResult = CDRF_NOTIFYITEMDRAW;
	}
    else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
        // This is the pre-paint stage for an item.  We need to make another
        // request to be notified during the post-paint stage.
        *pResult = CDRF_NOTIFYSUBITEMDRAW;;
	}
	
    else if ( (CDDS_ITEMPREPAINT| CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
		CDC* pDC = CDC::FromHandle(pLVCD->nmcd.hdc);

		DrawItem(static_cast<int> (pLVCD->nmcd.dwItemSpec),
				 pLVCD->iSubItem, pDC);

		*pResult = CDRF_SKIPDEFAULT;	// We've painted everything.
	}
}




/*
	About GetTextColor and GetBackColor:
		Here you see why you shouldn't try to optimze your code :-)
  */

#ifndef COLOR_HOTLIGHT
	#define COLOR_HOTLIGHT 26
#endif

//Get which text color to use
COLORREF CQuickList::GetTextColor(const CQuickList::CListItemData& id, const bool forceNoSelection, const bool forceSelection)
{
	bool navigated = false;
#ifndef QUICKLIST_NONAVIGATION
	if(id.GetSubItem() == m_navigationColumn && m_enableNavigation)
		navigated = true;
#endif

	if(	(!forceNoSelection && id.IsSelected()) //IsSelected(id.m_item, id.m_subitem)) 
		|| forceSelection)
	{
		#ifndef QUICKLIST_NOCOLORS
			#ifndef QUICKLIST_NONAVIGATION
				if(navigated && GetFocus() == this) 
				{
					if(id.m_colors.m_navigatedTextColor!= DEFAULTCOLOR)
						return id.m_colors.m_navigatedTextColor;
					else
						return ::GetSysColor(COLOR_HIGHLIGHTTEXT);
				}
			#endif

			if(id.m_colors.m_selectedTextColor != DEFAULTCOLOR)
				return id.m_colors.m_selectedTextColor;
			else
			{
				if(GetFocus() == this)
					return ::GetSysColor(COLOR_HIGHLIGHTTEXT);
				else
					return ::GetSysColor(COLOR_WINDOWTEXT);
			}
		#else

				if(GetFocus() == this)
					return ::GetSysColor(COLOR_HIGHLIGHTTEXT);
				else
					return ::GetSysColor(COLOR_WINDOWTEXT);
		
		#endif
	}

	//Is item hot?
	if( GetHotItem() == id.GetItem() )
	{
		#ifndef QUICKLIST_NOCOLORS
			if(id.m_colors.m_hotTextColor != DEFAULTCOLOR)
				return id.m_colors.m_hotTextColor;
			else
		#endif
			return ::GetSysColor(COLOR_HOTLIGHT);
	}
	else
	{
		#ifndef QUICKLIST_NOCOLORS
			if(id.m_colors.m_textColor != DEFAULTCOLOR)
				return id.m_colors.m_textColor;
			else
		#endif
				return ::GetSysColor(COLOR_WINDOWTEXT);
	}


}

//Get which background color to use
COLORREF CQuickList::GetBackColor(const CQuickList::CListItemData& id, const bool forceNoSelection)
{	
	bool navigated = false;
#ifndef QUICKLIST_NONAVIGATION
	if(id.GetSubItem() == m_navigationColumn && m_enableNavigation)
		navigated = true;
#endif

	bool hasFocus = (GetFocus() == this);

	//Is selected
	if(!forceNoSelection && id.IsSelected()) //IsSelected(id.m_item, id.m_subitem))
	{
		//Return selected color
		#ifndef QUICKLIST_NOCOLORS
			#ifndef QUICKLIST_NONAVIGATION
				if(navigated && GetFocus() == this)  
				{
					if(id.m_colors.m_navigatedBackColor!= DEFAULTCOLOR)
						return id.m_colors.m_navigatedBackColor;
					else
						return ::GetSysColor(COLOR_HOTLIGHT);
				}
			#endif

			if(	(hasFocus && id.m_colors.m_selectedBackColor != DEFAULTCOLOR) ||
				(!hasFocus && id.m_colors.m_selectedBackColorNoFocus != DEFAULTCOLOR) )
			{
				if(hasFocus)
					return id.m_colors.m_selectedBackColor;
				else
					return id.m_colors.m_selectedBackColorNoFocus;
			}
			else
			{
				if(!IsColumnNavigationOn() && id.IsHot())
					return ::GetSysColor(COLOR_HOTLIGHT);

				if(hasFocus)
					return ::GetSysColor(COLOR_HIGHLIGHT);
				else
					return ::GetSysColor(COLOR_BTNFACE);
			}
		#else
			//Simple window colors
			if(navigated && GetFocus() == this)
				return ::GetSysColor(COLOR_HOTLIGHT);
			else if(!IsColumnNavigationOn() && id.IsHot())
				return ::GetSysColor(COLOR_HOTLIGHT);
			else
			{
				if(GetFocus() == this)
					return ::GetSysColor(COLOR_HIGHLIGHT);
				else
					return ::GetSysColor(COLOR_BTNFACE);
			}
		#endif
				
	}

	#ifndef QUICKLIST_NOCOLORS
		if(id.m_colors.m_backColor != DEFAULTCOLOR)
			return id.m_colors.m_backColor;
		else
	#endif
			return ::GetSysColor(COLOR_WINDOW);
}

//Is item selected?
bool CQuickList::IsSelected(const int item, const int subitem)
{
	if (GetItemState(item, LVIS_SELECTED))
	{
		if ( subitem == 0 ||	//First column or...	 
			 FullRowSelect()	//full row select?
		   )			
		{
			// has focus?
			if (m_hWnd != ::GetFocus())
			{
				if (GetStyle() & LVS_SHOWSELALWAYS)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			return true;
		}
	}

	return false;
}

//On painting
void CQuickList::OnPaint() 
{
	Default();

#ifndef QUICKLIST_NOEMPTYMESSAGE	
	//Draw empty list message
	if (GetItemCount() <= 0 && !m_emptyMessage.IsEmpty())
	{
		CDC* pDC = GetDC();
		int nSavedDC = pDC->SaveDC();

		CRect rc;
		GetWindowRect(&rc);
		ScreenToClient(&rc);
		CHeaderCtrl* pHC = GetHeaderCtrl();
		if (pHC != NULL)
		{
			CRect rcH;
			pHC->GetItemRect(0, &rcH);
			rc.top += rcH.bottom;
		}
		rc.top += 10;

		COLORREF crText =  CListCtrl::GetTextColor();

		pDC->SetTextColor(crText);
		int oldMode = pDC->SetBkMode(TRANSPARENT);
		
		pDC->SelectStockObject(ANSI_VAR_FONT);
		pDC->DrawText(m_emptyMessage, -1, rc, DT_CENTER | DT_WORDBREAK | DT_NOPREFIX | DT_NOCLIP);
		pDC->SetBkMode(oldMode);
		pDC->RestoreDC(nSavedDC);
		ReleaseDC(pDC);
	}
#endif


}

#ifndef QUICKLIST_NOEMPTYMESSAGE	
//Set empty message
void CQuickList::SetEmptyMessage(const CString &message)
{
	m_emptyMessage = message;
}
//Set empty message
void CQuickList::SetEmptyMessage(UINT ID)
{
	CString temp;
	temp.LoadString(ID);

	SetEmptyMessage(temp);
}
#endif

//Get rect of subitem.
/*BOOL CQuickList::GetSubItemRect(int nItem,
								int nSubItem,
								int nArea,
								CRect& rect) 
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetHeaderCtrl()->GetItemCount());
	if ((nSubItem < 0) || nSubItem >= GetHeaderCtrl()->GetItemCount())
		return FALSE;

	BOOL bRC = CListCtrl::GetSubItemRect(nItem, nSubItem, nArea, rect);

	// if nSubItem == 0, the rect returned by CListCtrl::GetSubItemRect
	// is the entire row, so use left edge of second subitem

	if (nSubItem == 0)
	{
		if (GetHeaderCtrl()->GetItemCount() > 1)
		{
			CRect rect1;
			bRC = GetSubItemRect(nItem, 1, LVIR_BOUNDS, rect1);
			rect.right = rect1.left;			
		}
	}

	return bRC;
}*/
//Get rect of subitem.
BOOL CQuickList::GetSubItemRect(int nItem,
								int nSubItem,
								int nArea,
								CRect& rect) 
{
	ASSERT(nItem >= 0);
	ASSERT(nItem < GetItemCount());
	if ((nItem < 0) || nItem >= GetItemCount())
		return FALSE;
	ASSERT(nSubItem >= 0);
	ASSERT(nSubItem < GetHeaderCtrl()->GetItemCount());
	if ((nSubItem < 0) || nSubItem >= GetHeaderCtrl()->GetItemCount())
		return FALSE;

	BOOL bRC = CListCtrl::GetSubItemRect(nItem, nSubItem, nArea, rect);

	// if nSubItem == 0, the rect returned by CListCtrl::GetSubItemRect
	// is the entire row. To solve this we use the left and right position
	// of the column header, which should be the same.
	if (nSubItem == 0)
	{
		//If the horisontal scroll is used, we need to handle the offset.
		int offset = rect.left;

		CRect firstColumnRect;
		GetHeaderCtrl()->GetItemRect(0, &firstColumnRect);
		rect.left = firstColumnRect.left + offset;
		rect.right = firstColumnRect.right + offset;
	}

	return bRC;
}

//Get progress bar rect
//Return false if none
bool CQuickList::GetProgressRect(const int item, const int subitem, CRect& rect, bool interior)
{
	CQuickList::CListItemData& data = GetItemData(item, subitem);
	return GetProgressRect(data, rect, interior);
}

//Get progress bar rect
//Return false if none
bool CQuickList::GetProgressRect(CQuickList::CListItemData& id, CRect& rect, bool interior)
{
#ifdef QUICKLIST_NOPROGRESSBAR
	UNREFERENCED_PARAMETER(id);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(interior);

	return false;
#else
	if(id.m_progressBar.m_maxvalue <= 0)
		return false;

	//Pretty much as text box, so use this
	GetTextRect(id, rect);

	rect.top += 1;
	rect.bottom -= 1;
	rect.left += 1;		// leave margin in case row is highlighted
	rect.right -= 2;

	//Shrink if interior and border is drawn
	if(interior && (id.m_progressBar.m_edge != 0))
		rect.DeflateRect(2, 2);

	return true;
#endif
}

//Get text rect
//Return false if none
bool CQuickList::GetTextRect(const int item, const int subitem, CRect& rect)
{
	CQuickList::CListItemData& data = GetItemData(item, subitem);

	return GetTextRect(data, rect);
}

//Get text rect
//Return false if none
bool CQuickList::GetTextRect(CQuickList::CListItemData& id, CRect& rect)
{
	GetSubItemRect(id.GetItem(), id.GetSubItem(), LVIR_BOUNDS, rect);

	CRect temp;

	//Move if image
	if( GetImageRect(id, temp, false) )
		rect.left = temp.right;
	else if( GetCheckboxRect(id, temp, false) )
		rect.left = temp.right;
	
	return true;
}

//Get check box rect
//Return false if none
bool CQuickList::GetCheckboxRect(const int item, const int subitem, CRect& rect, bool checkOnly)
{
	CQuickList::CListItemData& data = GetItemData(item, subitem);

	return GetCheckboxRect(data, rect, checkOnly);
}

//Get check box rect
//Return false if none
bool CQuickList::GetCheckboxRect(CQuickList::CListItemData& id, CRect& rect, bool checkOnly)
{
#ifdef QUICKLIST_NOBUTTON
	UNREFERENCED_PARAMETER(id);
	UNREFERENCED_PARAMETER(rect);

	return false;
#else
	if(!id.m_button.m_draw)
		return false;

	CRect full;
	GetSubItemRect(id.GetItem(), id.GetSubItem(), LVIR_BOUNDS, full);

	rect = full;

	int checkWidth = full.Height();

	if(id.m_button.m_center)
	{
		rect.left = full.CenterPoint().x - (checkWidth)/2;
		rect.right = full.CenterPoint().x + (checkWidth+1)/2;
	}
	else
		rect.right = rect.left + checkWidth;	// width = height

	if(!checkOnly)
		rect.left = full.left;

	return true;
#endif
}


//Get image rect
//Return false if none
bool CQuickList::GetImageRect(const int item, const int subitem, CRect& rect, bool imageOnly)
{
	CQuickList::CListItemData& data = GetItemData(item, subitem);

	return GetImageRect(data, rect, imageOnly);
}

//Get image rect
//Return false if none
bool CQuickList::GetImageRect(CQuickList::CListItemData& id, CRect& rect, bool imageOnly)
{
#ifdef QUICKLIST_NOIMAGE

	UNREFERENCED_PARAMETER(id);
	UNREFERENCED_PARAMETER(rect);
	UNREFERENCED_PARAMETER(imageOnly);

	return false;
#else
	if(id.m_image.m_imageID == -1)
		return false;

	GetSubItemRect(id.GetItem(), id.GetSubItem(), LVIR_BOUNDS, rect);

	//If there is an image box we has to move the rect
	int leftMarging = 1;
	{
		CRect chk;
		if(GetCheckboxRect(id, chk, false))
		{
			leftMarging = 0;
			rect.left = chk.right;
		}
	}

	//Draw image?
	if (id.m_image.m_imageList)
	{
		int nImage = id.m_image.m_imageID;

		if (nImage < 0)
			return false;

		SIZE sizeImage;
		sizeImage.cx = sizeImage.cy = 0;
		IMAGEINFO info;

		if (rect.Width() > 0 && id.m_image.m_imageList->GetImageInfo(nImage, &info))
		{
			//if imageOnly we only return the rect of the image.
			//otherwise we also include area under and below image.
			sizeImage.cx = info.rcImage.right - info.rcImage.left;
			sizeImage.cy = info.rcImage.bottom - info.rcImage.top;

			//Real size
			SIZE size;
			size.cx = rect.Width() < sizeImage.cx ? rect.Width() : sizeImage.cx;
			size.cy = 1+rect.Height() < sizeImage.cy ? rect.Height() : sizeImage.cy;

			POINT point;
			point.y = rect.CenterPoint().y - (sizeImage.cy/2);
			//Center image?
			if(id.m_image.m_center)
				point.x = rect.CenterPoint().x - (sizeImage.cx/2);
			else
				point.x = rect.left;

			point.x += leftMarging;

			//Out of area?
			if(point.y<rect.top)
				point.y = rect.top;

			//
			if( !imageOnly )
			{
				rect.right = point.x+sizeImage.cx;				
			}
			else
				//Make rect of point and size, and return this
				rect = CRect(point, size);

			return true;
		}
	}

	return false;
#endif
}

//Draw an item in pDC
void CQuickList::DrawItem(int item, int subitem, CDC* pDC)
{	
	
		CListItemData id = GetItemData(	item, subitem );
		//Draw button?
#ifndef QUICKLIST_NOBUTTON
		if(id.m_button.m_draw)
			DrawButton(id, pDC);
#endif

		//Draw image?
#ifndef QUICKLIST_NOIMAGE
		if(id.m_image.m_imageID != -1)
			DrawImage(id, pDC);
#endif

		//Draw progressbar?
#ifndef QUICKLIST_NOPROGRESSBAR
		if(id.m_progressBar.m_maxvalue > 0)
			DrawProgressBar(id, pDC);
#endif

		DrawText(id, pDC);

}

#ifndef QUICKLIST_NOIMAGE
//Draw image
void CQuickList::DrawImage(	CQuickList::CListItemData& id,
							CDC* pDC)
{
	CRect imgRect;

	if(GetImageRect(id, imgRect, false))
	{
		CImageList* pImageList = id.m_image.m_imageList;

		COLORREF blendColor = GetBackColor(id);

		// save image list background color
		COLORREF rgb = pImageList->GetBkColor();

		// set image list background color
		pImageList->SetBkColor( GetBackColor(id, id.m_image.m_noSelection || id.m_noSelection));

		//Fill background
		FillSolidRect(	pDC,
						imgRect,
						GetBackColor(id, id.m_image.m_noSelection || id.m_noSelection)
						);

		GetImageRect(id, imgRect, true);

		if(	id.m_noSelection || 
			!id.IsSelected() ||
			id.m_image.m_blend == 0 ||
			blendColor == TRANSPARENTCOLOR)
		{
			pImageList->DrawIndirect(	pDC, 
										id.m_image.m_imageID, 
										imgRect.TopLeft(), 
										imgRect.Size(), 
										CPoint(0, 0));
		}
		else
		{
			pImageList->DrawIndirect(	pDC, 
										id.m_image.m_imageID, 
										imgRect.TopLeft(), 
										imgRect.Size(), 
										CPoint(0, 0),
										ILD_NORMAL|id.m_image.m_blend,
										SRCCOPY,
										CLR_DEFAULT,
										blendColor);
		}
		pImageList->SetBkColor(rgb);
	}

	return;

}
#endif

//Draw text
void CQuickList::DrawText(		CQuickList::CListItemData& id,
								CDC* pDC)
{
	ASSERT(pDC);
	
	CRect rect, fulltextrect;

#ifndef QUICKLIST_NOPROGRESSBAR
	if(id.m_progressBar.m_maxvalue > 0)
		GetProgressRect(id, rect, true);
	else
#endif
	{
		GetTextRect(id, rect);


	}

	fulltextrect = rect;

	if(id.m_text.IsEmpty())
	{
		//Just clean if no progress bar
		#ifndef QUICKLIST_NOPROGRESSBAR
			if(id.m_progressBar.m_maxvalue <= 0)
		#endif
			FillSolidRect(	pDC,
					fulltextrect,
					GetBackColor(id, !FullRowSelect() || id.m_noSelection));
	}
	else
	{		
		UINT textFormat=0;

#ifdef QUICKLIST_NOTEXTSTYLE 
		textFormat = DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | GetTextJustify(id.GetSubItem());
#else
		CFont *pOldFont = NULL;
		CFont boldfont;

		textFormat = id.m_textStyle.m_textPosition;

		// check if bold specified for subitem
		if (id.m_textStyle.m_bold || id.m_textStyle.m_italic)
		{
			CFont *font = pDC->GetCurrentFont();
			if (font)
			{
				LOGFONT lf;
				font->GetLogFont(&lf);

				if(id.m_textStyle.m_bold)
					lf.lfWeight = FW_BOLD;
				if(id.m_textStyle.m_italic)
					lf.lfItalic = TRUE;

				boldfont.CreateFontIndirect(&lf);
				pOldFont = pDC->SelectObject(&boldfont);
			}
		}
#endif


		CString text = id.m_text;
		//If we don't do this, character after & will be underlined.
		text.Replace(_T("&"), _T("&&"));

#ifndef QUICKLIST_NOPROGRESSBAR
		if(id.m_progressBar.m_maxvalue <= 0)
#endif
		{
			rect.left += 2;
			
			pDC->SetTextColor( GetTextColor(id, id.m_noSelection) );

			COLORREF backColor = GetBackColor(id, id.m_noSelection);

			{
/*				//Calculate rect area
				CRect textRect=rect;
				pDC->DrawText(text, &textRect, textFormat|DT_CALCRECT);

				//Draw background, but exclude the text area
	            pDC->SaveDC();
				pDC->ExcludeClipRect(textRect);
*/
				FillSolidRect(	pDC,
								fulltextrect,
								GetBackColor(id, !FullRowSelect() || id.m_noSelection)
						 );
				
//				pDC->RestoreDC(-1);
			}
			
			if( backColor == TRANSPARENTCOLOR)
				pDC->SetBkMode(TRANSPARENT);
			else
			{
				pDC->SetBkMode(OPAQUE);
				pDC->SetBkColor( backColor );
			}			
			
			pDC->DrawText(text, &rect, textFormat);
		}
#ifndef QUICKLIST_NOPROGRESSBAR
		else
		{
			//Draw text in progress bar. We have to split the text in two parts
			pDC->SetBkMode(TRANSPARENT);
			
			CRect inRect = rect;
			inRect.right = inRect.left + GetBarSize(id, inRect);		

			COLORREF fillText = id.m_progressBar.m_fillTextColor;
			if(fillText == DEFAULTCOLOR)
				fillText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);

			
			//Draw first text...
            pDC->SaveDC();
            pDC->IntersectClipRect(inRect);
            pDC->SetTextColor( fillText ); //GetTextColor(id, false, true) );
            pDC->DrawText(text, &rect, textFormat);
            pDC->RestoreDC(-1);
			
            pDC->SaveDC();
            pDC->ExcludeClipRect(inRect);
            pDC->SetTextColor( GetTextColor(id, true) );
            pDC->DrawText(text, &rect, textFormat);
            pDC->RestoreDC(-1);
		}
#endif

#ifndef QUICKLIST_NOTEXTSTYLE 
		if (pOldFont)
			pDC->SelectObject(pOldFont);
#endif

	}


	if(	IsColumnNavigationOn() &&
		GetNavigationColumn() == id.GetSubItem() &&
		GetFocus() == this &&
		GetItemInFocus() == id.GetItem()
		)
	{
		//fulltextrect.DeflateRect(1,0,0,1);
		pDC->DrawFocusRect(&fulltextrect);
	}	
}


#ifndef QUICKLIST_NOBUTTON
//Draw button (check box/radio button)
void CQuickList::DrawButton(	CQuickList::CListItemData& id,
								CDC* pDC)
{
	ASSERT(pDC);

	CRect chkboxrect;
	
	GetCheckboxRect(id, chkboxrect, false);

	//Clear background
	FillSolidRect(	pDC,
					chkboxrect,
					GetBackColor(id, id.m_button.m_noSelection || id.m_noSelection)
				 );

	GetCheckboxRect(id, chkboxrect, true);

#ifndef QUICKLIST_NOXPTHEME
	//Draw with themes?
	if(m_theme != NULL && m_theme->m_bXPTheme)
	{
		//Convert style
		int type = BP_CHECKBOX;
		int style = CBS_UNCHECKEDNORMAL;

		if(id.m_button.m_style & DFCS_BUTTONRADIO)
		{
			type = BP_RADIOBUTTON;

			if(id.m_button.m_style & DFCS_CHECKED)
				style = RBS_CHECKEDNORMAL;
			else
				style = RBS_UNCHECKEDNORMAL;
		}
		else if(id.m_button.m_style & DFCS_BUTTONPUSH)
		{
			type = BP_PUSHBUTTON;

			if(id.m_button.m_style & DFCS_CHECKED)
				style = PBS_PRESSED;
			else
				style = PBS_NORMAL;
		}
		else //Assume check box 
		{
			type = BP_CHECKBOX;

			if(id.m_button.m_style & DFCS_CHECKED)
				style = CBS_CHECKEDNORMAL;
			else
				style = CBS_UNCHECKEDNORMAL;
		}

		m_theme->DrawThemeBackground(	*pDC,
										&chkboxrect,
										type,
										style 
									);
	}
	else //Draw with old methods
#endif
	pDC->DrawFrameControl(&chkboxrect, DFC_BUTTON, id.m_button.m_style );

}
#endif


#ifndef QUICKLIST_NOPROGRESSBAR
//Draw progress bar
void CQuickList::DrawProgressBar(CQuickList::CListItemData& id,
								CDC* pDC)
{
	ASSERT(pDC);

	CRect rect;

	GetProgressRect(id, rect, false);
	

	//First, fill area outside progress bar with background color
	{		
		CRect outrect;
		GetTextRect(id, outrect);

		pDC->SaveDC();
		pDC->ExcludeClipRect(&rect);
		FillSolidRect(pDC, outrect, GetBackColor(id, !FullRowSelect() || id.m_noSelection));

		pDC->RestoreDC(-1);
	}

	if(id.m_progressBar.m_edge != 0)
	{
		// draw border	
		pDC->DrawEdge(&rect, id.m_progressBar.m_edge, BF_RECT);
	}

	GetProgressRect(id, rect, true);

	// fill interior with background color
	FillSolidRect(pDC, rect, GetBackColor(id, true)); //id.m_progressBar.m_fillColor==DEFAULTCOLOR));

	if (id.m_progressBar.m_value > 0)
	{
		// draw progress bar and text
		rect.right = rect.left + GetBarSize(id, rect);
				
		COLORREF fill = id.m_progressBar.m_fillColor;
		if(fill == DEFAULTCOLOR)
			fill = ::GetSysColor(COLOR_HIGHLIGHT);

		FillSolidRect(pDC, rect, fill);
	}
}

//Calculate how wide the bar should be in pixels
int CQuickList::GetBarSize(const CQuickList::CListItemData& id, const CRect& rect) const
{
	int w = (rect.Width() * id.m_progressBar.m_value) / id.m_progressBar.m_maxvalue;

	//More than full?
	if(id.m_progressBar.m_value >= id.m_progressBar.m_maxvalue)
		w = rect.Width();

	return w;
}

#endif

//Fill a solid rect, unless transparent color
void CQuickList::FillSolidRect(CDC *pDC, const RECT& rect, const COLORREF color)
{
	if(color != TRANSPARENTCOLOR)
		pDC->FillSolidRect(&rect, color);
}


//Called when the list needs information about items to draw them
//The reason this function is implemented is that it help the list a little
//bit to calculate item width more correctly
void CQuickList::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	
	//Create a pointer to the item
	LV_ITEM* pItem= &(pDispInfo)->item;

	//Which item number?
	int itemid = pItem->iItem;

	//Do the list need text information?
	if( (pItem->mask & LVIF_IMAGE) || (pItem->mask & LVIF_TEXT) ) 
	{
		CQuickList::CListItemData &id = GetItemData(itemid, pItem->iSubItem);

		if( (pItem->mask & LVIF_TEXT) )
		{
			//Copy the text to the LV_ITEM structure
			//Maximum number of characters is in pItem->cchTextMax
			lstrcpyn(pItem->pszText, id.m_text, pItem->cchTextMax);
		}

		//Do the list need image information?	
		if( pItem->mask & LVIF_IMAGE) 
		{
			#ifndef QUICKLIST_NOIMAGE
				//Set which image to use
				pItem->iImage=id.m_image.m_imageID;
			#endif
			
			//Show check box?
			#ifndef QUICKLIST_NOBUTTON
			if(id.m_button.m_draw)
			{
				//To enable check box, we have to enable state mask...
				pItem->mask |= LVIF_STATE;
				pItem->stateMask = LVIS_STATEIMAGEMASK;

				if( (id.m_button.m_style & DFCS_CHECKED) != 0)
				{
					//Turn check box on..
					pItem->state = INDEXTOSTATEIMAGEMASK(2);
				}
				else
				{
					//Turn check box off
					pItem->state = INDEXTOSTATEIMAGEMASK(1);
				}
			}
			#endif
		}
	}

	
	*pResult = 0;
}

//Get information about an item
CQuickList::CListItemData& CQuickList::GetItemData(const int item, const int subitem)
{

	ASSERT(item >= 0);
	ASSERT(item < GetItemCount());
	ASSERT(subitem >= 0);

	//Static, so we doesn't new to create a new every time
	CListItemData& id = *m_lastget;
	id.Reset();

	id.m_item = item;
	id.m_subitem = subitem;
	id.m_isSelected = IsSelected(item, subitem); //GetItemState(item, LVIS_SELECTED)!=0;
	id.m_isHot = (GetHotItem() == id.m_item);

#ifndef QUICKLIST_NOIMAGE
	id.m_image.m_imageList = GetImageList(LVSIL_SMALL);

	if(!FullRowSelect())
		id.m_image.m_noSelection = true;
#endif

#ifndef QUICKLIST_NOTEXTSTYLE 
	//Same align as in column
	id.m_textStyle.m_textPosition = DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | GetTextJustify(subitem);
#endif


	::SendMessage(	GetParent()->GetSafeHwnd(), 
					WM_QUICKLIST_GETLISTITEMDATA, 
					(WPARAM) GetSafeHwnd(), 
					(LPARAM) &id);

	return id;
}

//Return wich alignment an column has (DT_LEFT, DT_CENTER or DT_RIGHT).
UINT CQuickList::GetTextJustify(const int headerpos)
{
	HDITEM hditem;
	hditem.mask = HDI_FORMAT;
	GetHeaderCtrl()->GetItem(headerpos, &hditem);
	
	int nFmt = hditem.fmt & HDF_JUSTIFYMASK;
		
	if (nFmt == HDF_CENTER)
		return  DT_CENTER;
	else if (nFmt == HDF_LEFT)
		return  DT_LEFT;
	else
		return  DT_RIGHT;
}

//Is full row selection enabled?
bool CQuickList::FullRowSelect()
{
	return (GetExtendedStyle() & LVS_EX_FULLROWSELECT) != 0;
}

#ifndef QUICKLIST_NOKEYFIND
//Called when user writes in the list to find an item
BOOL CQuickList::OnOdfinditem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_keyFindColumn == KEYFIND_DISABLED)
	{		
		//When we return FALSE this message will be handled 
		//by the parent. Just the way we want it!
		return FALSE;
	}

	int column = m_keyFindColumn;

#ifndef QUICKLIST_NONAVIGATION
	//Use current column?
	if(column == KEYFIND_CURRENTCOLUMN)
		column = GetNavigationColumn();
#endif

	ASSERT(column >= 0);

	NMLVFINDITEM* pFindInfo = (NMLVFINDITEM*)pNMHDR;

	// Set the default return value to -1
	// That means we didn't find any match.
	*pResult = -1;

	//This is the string we search for
	CString searchstr = pFindInfo->lvfi.psz;

//	TRACE(_T("Find: %s\n"), searchstr);
	
	int startPos = pFindInfo->iStart;
	//Is startPos outside the list (happens if last item is selected)
	if(startPos >= GetItemCount())
		startPos = 0;

	int currentPos=startPos;
	
	//Let's search...
	do
	{		
		//Do this word begins with all characters in searchstr?
		if( _tcsnicmp(	GetItemData(currentPos, column).m_text, 
						searchstr, 
						searchstr.GetLength()
						) == 0)
		{
			//Select this item and stop search.
			*pResult = currentPos;
			break;
		}

		//Go to next item
		currentPos++;

		//Need to restart at top?
		if(currentPos >= GetItemCount())
			currentPos = 0;

	//Stop if back to start
	}while(currentPos != startPos);		

	return TRUE;

}
#endif

//Test where a point is on an item
bool CQuickList::HitTest(const POINT& point, CListHitInfo &info)
{
	return HitTest(point, info.m_item, info.m_subitem, &info.m_onButton, &info.m_onImage);
}

//Test where a point is on an item
bool CQuickList::HitTest(const POINT& point, int& item, int& subitem, bool* onCheck, bool* onImage)
{
	LVHITTESTINFO test;
	test.pt = point;
	test.flags=0;
	test.iItem = test.iSubItem = -1;

	if(ListView_SubItemHitTest(m_hWnd, &test) == -1)
		return false;

	item = test.iItem;
	subitem = test.iSubItem;

	//Make check box hit test?
	if(onCheck != NULL)
	{
		CRect checkrect;
	
		//Has check box?
		if(GetCheckboxRect(test.iItem, test.iSubItem, checkrect, true))
		{
			if( checkrect.PtInRect(point) )
				*onCheck = true;
			else
				*onCheck = false;
		}
		else
			*onCheck = false;

	}

	//Make image hit test?
	if(onImage != NULL)
	{
		CRect imgrect;
	
		//Has image box?
		if(GetImageRect(test.iItem, test.iSubItem, imgrect, true))
		{
			if( imgrect.PtInRect(point) )
				*onImage = true;
			else
				*onImage = false;
		}
		else
			*onImage = false;

	}


	return true;
}

//Redraw images
void CQuickList::RedrawImages(const int top, const int bottom, const int column, BOOL erase)
{
	RedrawSubitems(top, bottom, column, 2, erase);
}

//Redraw check boxes
void CQuickList::RedrawCheckBoxs(const int top, const int bottom, const int column, BOOL erase)
{
	RedrawSubitems(top, bottom, column, 1, erase);
}

//Redraw items in a column
void CQuickList::RedrawSubitems(const int top, const int bottom, const int column, BOOL erase)
{
	RedrawSubitems(top, bottom, column, 0, erase);
}

//Redraw text/progressbar in a column
void CQuickList::RedrawText(const int top, const int bottom, const int column, BOOL erase)
{
	RedrawSubitems(top, bottom, column, 3, erase);
}


//Redraw some of a subitem
void CQuickList::RedrawSubitems(int top, int bottom, int column, int part, BOOL erase)
{
	if(GetItemCount() <= 0)
		return;

	if(!MakeInside(top, bottom))
		//No need to redraw items.
		return;

	CRect t, b;
	
	if(part == 0) //Redraw subitem completely
	{
		GetSubItemRect(top, column, LVIR_BOUNDS, t);
		GetSubItemRect(bottom, column, LVIR_BOUNDS, b);
	}else if(part == 1)//Redraw check boxs
	{
		GetCheckboxRect(top, column, t, true);
		GetCheckboxRect(bottom, column, b, true);
	}else if(part == 2)//Redraw images
	{
		GetImageRect(top, column, t, true);
		GetImageRect(bottom, column, b, true);
	}
	else //Redraw text/progressbar
	{
		GetTextRect(top, column, t);
		GetTextRect(bottom, column, b);
	}


	//Mix them
	t.UnionRect(&t, &b);

	InvalidateRect( &t, erase );

}

//Make items inside visible area
bool CQuickList::MakeInside(int& top, int &bottom)
{
	int min = GetTopIndex(), max = min+GetCountPerPage();

	if(max >= GetItemCount())
		max = GetItemCount()-1;

	//Is both outside visible area?
	if(top < min && bottom < min)
		return false;
	if(top > max && bottom > max)
		return false;

	if(top < min)
		top = min;

	if(bottom > max)
		bottom = max;

	return true;
}

//Set which column to search in when message LVN_ODFINDITEM is recieved
void CQuickList::SetKeyfindColumn(const int col)
{
	#ifndef QUICKLIST_NOKEYFIND
		m_keyFindColumn = col;
	#else
		UNREFERENCED_PARAMETER(col);
	#endif
}

//Start editing an sub item
CEdit* CQuickList::EditSubItem (int Item, int Column, LPCTSTR addToEnd)
{
#ifdef QUICKLIST_NOEDIT
	TRACE(_T("Editing is not supported!. Don't define QUICKLIST_NOEDIT to be happy.\n"));

	UNREFERENCED_PARAMETER(Item);
	UNREFERENCED_PARAMETER(Column);

	return NULL;
#else

    // Make sure that the item is visible
    if (!EnsureVisible (Item, TRUE)) 
    {
		return NULL;
    }

    // Make sure that nCol is valid
	{
		CHeaderCtrl* pHeader = (CHeaderCtrl*) GetDlgItem(0);
		int nColumnCount = pHeader->GetItemCount();
		if (Column >= nColumnCount || GetColumnWidth (Column) < 5)
			return NULL;
	}
 
	CQuickList::CListItemData& id = GetItemData(Item, Column);

	//Not editing allowed?
	if(!id.m_allowEdit)
		return NULL;

	CString text = id.m_text;

	{
		LV_DISPINFO dispinfo;
		dispinfo.hdr.hwndFrom = m_hWnd;
		dispinfo.hdr.idFrom = GetDlgCtrlID();
		dispinfo.hdr.code = LVN_BEGINLABELEDIT;

		dispinfo.item.mask = LVIF_TEXT;
		dispinfo.item.iItem = Item;
		dispinfo.item.iSubItem = Column;

		//Copy the text we get from a simple WM_USER_GETLISTITEMDATA message
		//and add some extra space to allow changing the item
		dispinfo.item.cchTextMax = text.GetLength()*4;

		if(dispinfo.item.cchTextMax < 2048)
			dispinfo.item.cchTextMax = 2048;

		dispinfo.item.pszText = new TCHAR[dispinfo.item.cchTextMax];
		_tcscpy(dispinfo.item.pszText, text);

		//Send to parent
		BOOL ret =	::SendMessage (	GetParent()->GetSafeHwnd(),
									WM_NOTIFY, 
									(WPARAM) GetDlgCtrlID(), 
									(LPARAM) &dispinfo);

		//Copy editing text
		text = dispinfo.item.pszText;
		delete [] dispinfo.item.pszText;

		//Editing is not allowed, skip this
		if(ret == TRUE)
			return NULL;
				
	}

	if(addToEnd != NULL)
		text += addToEnd;


    CRect Rect;
    //GetItemRect (Item, &Rect, LVIR_BOUNDS);
	GetTextRect(id, Rect);

    // Now scroll if we need to expose the column
    CRect ClientRect;
    GetClientRect (&ClientRect);

//    Rect.right = Rect.left + GetColumnWidth (Column);
    if (Rect.right > ClientRect.right)
		Rect.right = ClientRect.right;

	//Make a little bit larger, looks better on some fonts
	Rect.top-=1;
	Rect.bottom+=2;

    // Get Column alignment
	DWORD style = 0;
	
	{
		UINT justify=GetTextJustify(Column);
		if(justify==DT_CENTER) style = ES_CENTER;
		else if(justify==DT_LEFT) style = ES_LEFT;
		else style = DT_RIGHT;
	}	

#define IDC_EDITCELL 1001

	//ASSERT(m_edit == NULL);
	if(m_edit != NULL)
	{
		TRACE(_T("Warning: Edit box was visible when an item was started to edit.\n"));
		StopEdit();
	}

    style |= WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER;
    m_edit = new CQuickEdit (this, Item, Column, text, m_editEndOnLostFocus);
    m_edit->Create (style, Rect, this, IDC_EDITCELL);

	//if(addToEnd != NULL)
		m_edit->SetSel(text.GetLength(), text.GetLength());

    return m_edit;
#endif
}

//Called from edit box when editing is stopped
//Calling parent to save the text
#ifndef QUICKLIST_NOEDIT
void CQuickList::OnEndEdit(const int item, const int subitem, const CString text, bool bEscape, UINT endkey)
{
	m_edit = NULL;
	m_editLastEndKey = endkey;

	SetFocus();

    LV_DISPINFO dispinfo;
    dispinfo.hdr.hwndFrom = m_hWnd;
    dispinfo.hdr.idFrom = GetDlgCtrlID();
    dispinfo.hdr.code = LVN_ENDLABELEDIT;

    dispinfo.item.mask = LVIF_TEXT;
    dispinfo.item.iItem = item;
    dispinfo.item.iSubItem = subitem;
    dispinfo.item.pszText = bEscape ? NULL : LPTSTR ((LPCTSTR) text);
    dispinfo.item.cchTextMax = text.GetLength();

    GetParent()->SendMessage (WM_NOTIFY, GetDlgCtrlID(), (LPARAM) &dispinfo);
	
	RedrawText(item, item, subitem);
}
#endif

//When mouse wheel is used
BOOL CQuickList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	StopEdit();	
	return CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
}

//When vertical scroll
void CQuickList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	StopEdit();	
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

//When horisontial scorll
void CQuickList::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	StopEdit();

	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

//Stop editing.
void CQuickList::StopEdit(bool cancel)
{
#ifndef QUICKLIST_NOEDIT
	if(m_edit != NULL)
	{
		TRACE(_T("Stop editing\n"));
		//m_edit->DestroyWindow();
		m_edit->StopEdit(cancel);
	}
#endif
}

//When key is pressed
void CQuickList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

#ifndef QUICKLIST_NONAVIGATION
	if(m_enableNavigation)
	{
		int prevCol = m_navigationColumn;
		bool ret = false;

		switch (nChar)
		{		
			case VK_LEFT :
			{
				TryNavigate(m_navigationColumn-1);			
				ret = true;
				break;
			}
			case VK_RIGHT :
			{
				TryNavigate(m_navigationColumn+1);
				ret = true;
				break;
			}
			
			#ifndef QUICKLIST_NOEDIT
				case VK_RETURN:
				{
					if(m_editOnEnter)
					{
						EditSubItem(GetItemInFocus(), m_navigationColumn);
						return;
					}
					break;
				}

				case VK_F2:
				{
					if(m_editOnF2)
					{
						EditSubItem(GetItemInFocus(), m_navigationColumn);
						return;
					}
					break;
				}
			#endif
		}

		//Navigation column changed?
		if(prevCol != m_navigationColumn)
		{
			//int a = GetSelectedCount();
			//Redraw sub items (focus rect is changed)
			int focus = GetItemInFocus();
			RedrawSubitems( focus,
							focus,
							prevCol);
			
			RedrawSubitems( focus,
							focus,
							m_navigationColumn);		
		}

		if(ret)
			return;

	}
	#endif

	
	CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CQuickList::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
#ifndef QUICKLIST_NOEDIT
	if(	m_editOnWriting && 
		nChar != VK_RETURN && 
		nChar != VK_SPACE && 
		nChar != VK_BACK &&
		nRepCnt >= 0 &&
		nChar >= 32 //Ignore ctrl+a, b and similar
		)
	{
		//TRACE(_T("Edit by writing\n"));
		CString text( (TCHAR) nChar, nRepCnt==0?1:nRepCnt );

		EditSubItem(GetItemInFocus(), m_navigationColumn, text);
		return;
	}
#endif

	CListCtrl::OnChar(nChar, nRepCnt, nFlags);
}


//Try to navigate to a new column
void CQuickList::TryNavigate(const int newcol)
{
#ifndef QUICKLIST_NONAVIGATION
	if(!m_enableNavigation)
		return;

	if(newcol < 0 || newcol >= GetHeaderCtrl()->GetItemCount())
		return;

	CQuickList::CNavigationTest test;
	test.m_previousColumn = m_navigationColumn;
	test.m_newColumn = newcol;
	test.m_allowChange = true;

	//Ask parent if it's ok to change column
	::SendMessage(	GetParent()->GetSafeHwnd(),
					WM_QUICKLIST_NAVIGATIONTEST,
					(WPARAM) GetSafeHwnd(),
					(LPARAM) &test);

	if(test.m_allowChange)
		SetNavigationColumn(test.m_newColumn);
#else
	UNREFERENCED_PARAMETER(newcol);
#endif
}

//Set navigation column
void CQuickList::SetNavigationColumn(const int column)
{
#ifndef QUICKLIST_NONAVIGATION
	MakeColumnVisible(column);

	int oldCol = m_navigationColumn;

	int topVisible = 0, bottomVisible = GetItemCount()-1;
	MakeInside(topVisible, bottomVisible);

	//Redraw the visible items that are selected
	for(int item=topVisible; item <= bottomVisible; item++)
	{
		if(IsSelected(item, 0))
		{
			m_navigationColumn = -1;
			RedrawSubitems(item, item, oldCol);
			m_navigationColumn = column;
			RedrawSubitems(item, item, m_navigationColumn);
		}
	}

	m_navigationColumn = column;
#else
	UNREFERENCED_PARAMETER(column);
#endif
}

//Enable/disable column navigation
void CQuickList::EnableColumnNavigation(const bool enable)
{
#ifndef QUICKLIST_NONAVIGATION
	m_enableNavigation = enable;
#else
	UNREFERENCED_PARAMETER(enable);
#endif
}

//Get which column that is activated. -1 if none
int CQuickList::GetNavigationColumn() const
{
#ifndef QUICKLIST_NONAVIGATION
	return m_navigationColumn;
#else
	return -1;
#endif
}

//Is column navigation on?
bool CQuickList::IsColumnNavigationOn() const
{
#ifndef QUICKLIST_NONAVIGATION
	return m_enableNavigation;
#else
	return false;
#endif
}

//Pretranslate message
BOOL CQuickList::PreTranslateMessage(MSG* pMsg) 
{
#ifndef QUICKLIST_NONAVIGATION
	if (pMsg->message == WM_KEYDOWN)
    {
		if (pMsg->wParam == VK_RETURN)
		{
			::TranslateMessage (pMsg);
			::DispatchMessage (pMsg);
			return TRUE;		    	
		}
    }
#endif
	
	return CListCtrl::PreTranslateMessage(pMsg);
}

//Make a column visible
void CQuickList::MakeColumnVisible(int nCol)
{
	if(nCol < 0)
		return;
	// Get the order array to total the column offset.
	CHeaderCtrl* pHeader = GetHeaderCtrl();

	int nColCount = pHeader->GetItemCount();
	ASSERT( nCol < nColCount);
	int *pOrderarray = new int[nColCount];
	Header_GetOrderArray(pHeader->m_hWnd, nColCount, pOrderarray);
	// Get the column offset
	int offset = 0;
	for(int i = 0; pOrderarray[i] != nCol; i++)
		offset += GetColumnWidth(pOrderarray[i]);

	int colwidth = GetColumnWidth(nCol);
	delete[] pOrderarray;

	CRect rect;
	GetItemRect(0, &rect, LVIR_BOUNDS);
	// Now scroll if we need to show the column
	CRect rcClient;
	GetClientRect(&rcClient);
	if(offset + rect.left < 0 || offset + colwidth + rect.left > rcClient.right)
	{
		CSize size(offset + rect.left,0);
		Scroll(size);
		Invalidate(FALSE);
		UpdateWindow();
	}
}


//Create dragimage : Icon + the itemtext
//THIS DOESN'T WORK AT ALL!!! Help me! :-)
/*
CImageList* CQuickList::CreateDragImageEx(const int nItem, const int nSubItem)
{
    CImageList *pList = new CImageList;          

	CQuickList::CListItemData& id = GetItemData(nItem, nSubItem);

	CRect rc;
	GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rc);

	rc.OffsetRect(-rc.left, -rc.top);            

	pList->Create(rc.Width(), rc.Height(),ILC_COLOR|ILC_MASK, 0, 1);//| ILC_MASK, 1, 1);
	CDC *pDC = GetDC();                          
	if(pDC) 
	{
		CDC dc;	      
		dc.CreateCompatibleDC(pDC);      
		CBitmap bmpMap;
		bmpMap.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());

		CBitmap *pOldBmp = dc.SelectObject(&bmpMap);
//		CFont *pOldFont = dc.SelectObject(pFont);
		dc.FillSolidRect(rc, RGB(0,0, 128)); //GetSysColor(COLOR_WINDOW));
		dc.FillSolidRect(rc.left, rc.top, rc.Width()/2, rc.Height(), RGB(255,0,0));
		dc.TextOut(5, 5, _T("sad"));
		dc.FillSolidRect(rc.left, rc.top, rc.Width()/2, rc.Height(), RGB(255,0,0));
		dc.SetPixel(0, 0, RGB(128, 0, 200));
		dc.SetPixel(1, 0, RGB(128, 0, 200));
		dc.SetPixel(2, 0, RGB(128, 0, 200));
		dc.SetPixel(0, 2, RGB(128, 0, 200));
		dc.SetPixel(0, 1, RGB(128, 0, 200));

		dc.SelectObject(pOldBmp);

		//causes an error if the 1st column is hidden so must check the imagelist
		if(pList->m_hImageList != NULL)
			pList->Add(&bmpMap, RGB(0,255,255));
		else 
		{ 
			delete pList;
			pList=NULL;
		}

		ReleaseDC(pDC);   
	}   

	return pList;
}*/

#ifndef QUICKLIST_NOTOOLTIP
//On tool tip test
int CQuickList::OnToolHitTest(CPoint point, TOOLINFO * pTI) const
{

#ifndef QUICKLIST_NOEDIT
	//The list could get focus in XP. We don't like that
	//if we are editing 
	if(m_edit != NULL)
		return -1;
#endif


	LVHITTESTINFO lvhitTestInfo;
	
	lvhitTestInfo.pt = point;
	
	int nItem = ListView_SubItemHitTest(this->m_hWnd, &lvhitTestInfo);

	//If no item, ignore this
	if(nItem < 0)
		return -1;

	int nSubItem = lvhitTestInfo.iSubItem;
	//TRACE(_T("in OnToolHitTest: %d,%d\n"), nItem, nSubItem);

	ASSERT(nItem >= 0 && nSubItem >= 0);

	UINT nFlags = lvhitTestInfo.flags;

	// nFlags is 0 if the SubItemHitTest fails
	// Therefore, 0 & <anything> will equal false
	if (nFlags & (LVHT_ONITEMLABEL|LVHT_ONITEMICON|LVHT_ONITEMSTATEICON) )
	{
		// If it did fall on a list item,
		// and it was also hit one of the
		// item specific subitems we wish to show tool tips for
		
		// get the client (area occupied by this control
		RECT rcClient;
		GetClientRect(&rcClient);
		
		// fill in the TOOLINFO structure
		pTI->hwnd = m_hWnd;
		pTI->uId = (UINT) (nItem * 1000 + nSubItem + 1);
		pTI->lpszText = LPSTR_TEXTCALLBACK;
		pTI->rect = rcClient;
		
		return pTI->uId;	// By returning a unique value per listItem,
							// we ensure that when the mouse moves over another
							// list item, the tooltip will change
	}
	else
	{
		//Otherwise, we aren't interested, so let the message propagate
		return -1;
	}
}

//On tooltip text
BOOL CQuickList::OnToolTipText(UINT /*id*/, NMHDR *pNMHDR, LRESULT *pResult)
{
	UINT nID = pNMHDR->idFrom;
		
	// check if this is the automatic tooltip of the control
	if (nID == 0) 
		return TRUE;	// do not allow display of automatic tooltip,
						// or our tooltip will disappear

	// handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	
	*pResult = 0;
	
	// get the mouse position
	const MSG* pMessage;
	pMessage = GetCurrentMessage();
	ASSERT(pMessage);
	CPoint pt;
	pt = pMessage->pt;		// get the point from the message
	ScreenToClient(&pt);	// convert the point's coords to be relative to this control
	
	// see if the point falls onto a list item
	int nItem=-1, nSubItem=-1;
	if(HitTest(pt, nItem, nSubItem) )
	{
		// If it did fall on a list item,
		// and it was also hit one of the
		// item specific subitems we wish to show tooltips for
		
		CString strToolTip;
		strToolTip = GetItemData(nItem, nSubItem).m_tooltip;

		if (!strToolTip.IsEmpty())
		{
			// If there was a CString associated with the list item,
			// copy it's text (up to 80 characters worth, limitation 
			// of the TOOLTIPTEXT structure) into the TOOLTIPTEXT 
			// structure's szText member
			
			
#ifndef _UNICODE
			if (pNMHDR->code == TTN_NEEDTEXTA)
				lstrcpyn(pTTTA->szText, strToolTip, 80);
			else if(pNMHDR->code == TTN_NEEDTEXTW)
				//I'm not if this is correct. It could sometimes make the program crash, I think...
				mbstowcs(pTTTW->szText, strToolTip, 80);
#else
			if (pNMHDR->code == TTN_NEEDTEXTA)
				_wcstombsz(pTTTA->szText, strToolTip, 80);
			else
				lstrcpyn(pTTTW->szText, strToolTip, 80);
#endif
			
			return TRUE;
		//	return FALSE;	 // we found a tool tip,
		}

	}
	
	return FALSE;	// we didn't handle the message, let the 
					// framework continue propagating the message
					
}
#endif

//On click 
BOOL CQuickList::OnClickEx(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	//Try to change navigation column when user clicks on an item
	CListHitInfo clickinfo;
	clickinfo.m_item = clickinfo.m_subitem = -1;
	clickinfo.m_onButton = clickinfo.m_onImage = false;

	if(HitTest(pNMListView->ptAction, clickinfo))
	{
		//First, try to navigate to the column
		TryNavigate(clickinfo.m_subitem);

		::SendMessage(	GetParent()->GetSafeHwnd(), 
				WM_QUICKLIST_CLICK, 
				(WPARAM) GetSafeHwnd(), 
				(LPARAM) &clickinfo);
	}	

	*pResult = 0;

	return FALSE;
}

//On double click
BOOL CQuickList::OnDblClickEx(NMHDR* pNMHDR, LRESULT* ) //pResult)
{
#ifndef QUICKLIST_NOEDIT
	//Edit on double click?
	if(m_editOnDblclk)
	{
		NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

		CQuickList::CListHitInfo hit;

		if(HitTest(pNMListView->ptAction, hit))
		{
			if(!hit.m_onButton && !hit.m_onImage)
				EditSubItem(	hit.m_item,
								hit.m_subitem);
		}
	}
#else
	UNREFERENCED_PARAMETER(pNMHDR);
	
#endif

	return FALSE;
}

//Return the only item with the LVNI_FOCUSED state
int CQuickList::GetItemInFocus()
{
	return GetNextItem(-1, LVNI_FOCUSED);
}


void CQuickList::OnMouseMove(UINT nFlags, CPoint point) 
{
	/*	If you run CQuickList on a WindowXP system
		and using a manifest file and editing an item
		and moving the mouse pointer over the list,
		some list item will be redrawn over the edit
		box. The solution to this is to handle the
		WM_MOUSEMOVE message and make sure the
		base class isn't called.
	*/

	//Don't call base class!!!
	//CListCtrl::OnMouseMove(nFlags, point);
}

void CQuickList::OnLvnHotTrack(NMHDR * /*pNMHDR*/, LRESULT *pResult)
{
	/*	If you run CQuickList on a WindowXP system
		and using a manifest file, the hot item
		will be changed. This is not good.
		To solve this, we handle the LVN_HOTTRACK message 
		and return -1.

		Sense OnMouseMove is also handled this function
		will never be called, but it's still good to have.
	*/
	*pResult = -1;
}

void CQuickList::PreSubclassWindow() 
{
#ifdef _DEBUG
	//Doesn't have LVS_OWNERDATA?
	if(!(GetStyle() & LVS_OWNERDATA))
	{
		::MessageBox(NULL, _T("ERROR : You must set the LVS_OWNERDATA style for your CQuickList in the resources"), _T("Error"), MB_OK);
	}

	//Have owner draw fixed?
	if(GetStyle() & LVS_OWNERDRAWFIXED)
	{
		::MessageBox(NULL, _T("ERROR : You should NOT set the LVS_OWNERDRAWFIXED style for your CQuickList in the resources"), _T("Error"), MB_OK);
	}

	//Not in report view?
	DWORD style = GetStyle()&LVS_TYPEMASK;

	if(style != LVS_REPORT)
	{
		::MessageBox(NULL, _T("You should only use CQuickList in report view. Please change!"), _T("Why not report view?"), MB_OK);
	}
#endif
	
	CListCtrl::PreSubclassWindow();
}


//To handle the "right click on column header" message
BOOL CQuickList::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// Credits!
	// http://www.codeguru.com/Cpp/controls/listview/columns/article.php/c985

	HD_NOTIFY	*pHDN = (HD_NOTIFY*)lParam;

	LPNMHDR pNH = (LPNMHDR) lParam; 
	// wParam is zero for Header ctrl
	if( wParam == 0 && pNH->code == NM_RCLICK )
	{
		// Right button was clicked on header
		CPoint pt(GetMessagePos());
		CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
		pHeader->ScreenToClient(&pt);

		CHeaderRightClick cr;
		cr.m_column = -1;
		cr.m_mousePos = pt;
		
		// Determine the column index
		CRect rcCol;
		for( int i=0; Header_GetItemRect(pHeader->m_hWnd, i, &rcCol); i++ )
		{
			if( rcCol.PtInRect( pt ) )
			{
				cr.m_column = i;
				break;
			}
		}

		//Make screen cordinates
		ClientToScreen(&cr.m_mousePos);

		//Notify parent
		::SendMessage (	GetParent()->GetSafeHwnd(),
						WM_QUICKLIST_HEADERRIGHTCLICK,
						(WPARAM) GetSafeHwnd(), 
						(LPARAM) &cr);
	}

	
	return CListCtrl::OnNotify(wParam, lParam, pResult);
}

